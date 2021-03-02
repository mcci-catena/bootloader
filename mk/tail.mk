##############################################################################
#
# Module:  tail.mk
#
# Function:
#	GNU make tail for builds in the bootloader project
#
# Copyright notice:
#	This file copyright (C) 2020 by
#
#		MCCI Corporation
#		3520 Krums Corners Road
#		Ithaca, NY  14850
#
#	An unpublished work.  All rights reserved.
#
#	This file is proprietary information, and may not be disclosed
#	or copied without the prior permission of MCCI Corporation.
#
#	See accompanying LICENSE file for license information.
#
# Author:
#	Terry Moore, MCCI Corporation	July 2020
#
##############################################################################

### collect everything we're building ###
TARGETS := $(LIBRARIES) $(PROGRAMS)

#
# set up rules
#   define OUTPUT_OPTION=-E to preprocess, etc.
#
COMPILE.c = $(CC) $(MCCI_DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
MCCI_DEPFLAGS = -MT $@ -MMD -MP -MF ${@:.o=.td}
MCCI_POSTCOMPILE = mv -f $(@:.o=.td) $(@:.o=.d)

#
# Specific rules for generating .o from .c, and dependencies.
#
%.o : %.c

##############################################################################
#
# Macro:  MCCI_DOCOMPILE
#
# Function:
#	Generate the code for building a single .c source file
#
# Usage:
#	$(call MCCI_DOCOMPILE, sourcefile, encompassingtarget)
#
# Input:
#	T_OBJDIR	where to build the .o and .d files
#	OUTPUT_OPTION	options needed for building dependencies.
#	COMPILE.c	rule for C compilations
#
# Variables:
#	_TOBJ_$1	used to remember the object file
#	_TDEP_$1	used for remembering the dependency file
#
##############################################################################

define MCCI_DOCOMPILE
_TOBJ_$1 := $$(patsubst %.c,$$(T_OBJDIR)/%.o,$$(notdir $1))
_TDEP_$1 := $$(patsubst %.c,$$(T_OBJDIR)/%.d,$$(notdir $1))
_TCPPFLAGS_$1 := $$(CPPFLAGS_$2) $$(CPPFLAGS_$1) \
	$${foreach includedir, $${INCLUDES_$2} $${INCLUDES_$1}, -I $$(includedir)}
_TCFLAGS_$1 := $$(CFLAGS_$2) $$(CFLAGS_$1) $$(_TCPPFLAGS_$1)

$$(_TOBJ_$1): $1 $(_TDEP_$1)
	@echo $1
	$${MAKEHUSH}$$(COMPILE.c) $$(OUTPUT_OPTION) $$(CFLAGS) $$(_TCFLAGS_$1) $1
	$${MAKEHUSH}mv -f $$(@:.o=.td) $$(@:.o=.d)

$(_TDEP_$1) : ;
.PRECIOUS: $(_TDEP_$1)
endef

##############################################################################
#
# Macro:  MCCI_SETOBJECTS
#
# Function:
# 	For each of the targets, define OBJECTS_{target} and DEPENDS_{target}
#
# Usage:
#	1 = specific target (library or program)
#	$(eval $(MCCI_SETOBJECTS))
#
# Input:
#	SOURCES_$1	list of sources
#	T_OBJDIR	object direcory
#
# Output:
#	DEPENDS_$1	list of dependency files
#	OBJECTS_$1	list of object files
#	OBJECTS		updated to append the objects for this target
#	DEPENDS		updated to append the dependency files for this target
#
# Notes:
#	We strip directory info off the SOURCES files and force the objects
#	to live in $T_OBJDIR directory. This means you can't have
#	dir1/sources.c and dir2sources.cpp in the same Makefile. On the other
#	hand, this means you can do out-of-tree builds
#
##############################################################################

define MCCI_SETOBJECTS
OBJECTS_$1 := $$(patsubst %.c,$$(T_OBJDIR)/%.o,$$(notdir $$(SOURCES_$1)))
DEPENDS_$1 := $$(patsubst %.c,$$(T_OBJDIR)/%.d,$$(notdir $$(SOURCES_$1)))
OBJECTS += $$(OBJECTS_$1)
DEPENDS += $$(DEPENDS_$1)
endef

##############################################################################
#
# execute MCCI_SETOBJECTS for each target, then build OBJECTDIRS and create
# object directories.
#
##############################################################################

$(foreach 1,$(TARGETS),$(eval $(MCCI_SETOBJECTS)))

# extract the list of objectdir names.
OBJECTDIRS := $(patsubst %/,%,$(sort $(dir $(OBJECTS))))

# create object directories
ifneq ($(OBJECTDIRS),)
 _TEST := $(shell if mkdir -p $(OBJECTDIRS) ; then echo yes; else echo no; fi)
 ifneq ($(_TEST),yes)
  $(error Can't make directores)
 endif
endif

##############################################################################
#
# Install section
#
#	Other builds should add things to the following vars:
#
#	MCCI_INSTALLDIR_BIN	Where to put programs and scripts
#	MCCI_INSTALLDIR_LIB	Where to put libraries
#	MCCI_INSTALLDIR_SCRIPTS	Where to put scripts
#	MCCI_INSTALLDIR_INCLUDES Where to put include files
#
#	Install is controlled by:

##############################################################################

.PHONY:	install preintstall _install postinstall _install_announce \
	_install_programs _install_libraries _install_includes \
	_install_scripts _install_rules _install_files

# arrange the order of thigns
preinstall:	_install_announce
_install:				\
		preinstall		\
		_install_programs	\
		_install_libraries	\
		_install_includes	\
		_install_scripts	\
		_install_rules		\
		_install_files		\
# end of _install
postinstall:	_install
install:	postinstall

_install_announce:
	@echo install ${T_OBJDIR} to ${T_MCCI_INSTALLDIR}

##############################################################################
#
# Macro: MCCI_DOLIBRARY
#
# Function:
#	Generate the rules for building a library.
#
# Usage:
#	$(call MCCI_DOLIBRARY,libraryname)
#
# Input:
#	$1		name of library (without .a)
#	SOURCES_$1	list of sources for the library
#	INCLUDES_$1	Include paths for all files in the library
#	OBJECTS_$1	list of objects for the library
#	T_OBJDIR	where to put objects
#
# Output:
#	MCCI_CLEANFILES	updated with additional files to remove
#	all;		is updated with the library to be built.
#
# Notes:
#	The archive suffix (.a) is supplied here. The libraryname should not
#	include it.
#
# 	It is best if library names begin with "lib", but that's not enforced
#	here.
#
##############################################################################

define MCCI_DOLIBRARY
MCCI_CLEANFILES += $$(T_OBJDIR)/$1.a

$$(T_OBJDIR)/$1.a: $$(OBJECTS_$1)
	@echo $1.a
	$${MAKEHUSH}$$(AR) cr $$@ $$(OBJECTS_$1)

all $1.a:	$$(T_OBJDIR)/$1.a
.PHONY:		$1.a		

_MCCI_INSTALLDIR_LIB_EXPAND_$1 := $${subst *,$1,$${MCCI_INSTALLDIR_LIB}}
_install_libraries: 	_install_libraries_$1

.PHONY:	_install_libraries_$1
_install_libraries_$1:	$${T_OBJDIR}/$1.a
	$${MAKEHUSH}$${MCCI_INSTALLDIR_CMD} $${_MCCI_INSTALLDIR_LIB_EXPAND_$1}.
	$${MAKEHUSH}$${MCCI_INSTALL_CMD} -m 444 $${T_OBJDIR}/$1.a $${_MCCI_INSTALLDIR_LIB_EXPAND_$1}.

### rules for includes
ifneq ($$(INSTALL_INCLUDES_$1),)
_MCCI_INSTALLDIR_INCLUDES_EXPAND_$1 := $${subst *,$1,$${MCCI_INSTALLDIR_INCLUDES}}

_install_includes:	_install_includes_$1
.PHONY:			_install_includes_$1
_install_includes_$1:	$$(INSTALL_INCLUDES_$1)
	$${MAKEHUSH}$${MCCI_INSTALLDIR_CMD}  $${_MCCI_INSTALLDIR_INCLUDES_EXPAND_$1}.
	$${MAKEHUSH}$${MCCI_INSTALL_CMD} -m 444 $$(INSTALL_INCLUDES_$1) $${_MCCI_INSTALLDIR_INCLUDES_EXPAND_$1}.
endif

### rules for udev rules
ifneq ($$(INSTALL_UDEVRULES_$1),)
$$(info generating rules for INSTALL_UDEVRULES_$1)
_install_rules: _install_rules_$1
.PHONY:		_install_rules_$1
_install_rules_$1:	$$(INSTALL_UDEVRULES_$1)
	$${MAKEHUSH}$${MCCI_INSTALLDIR_CMD}  $${MCCI_INSTALLDIR_UDEVRULES}.
	$${MAKEHUSH}$${MCCI_INSTALL_CMD} -m 444 $$(INSTALL_UDEVRULES_$1) $${MCCI_INSTALLDIR_UDEVRULES}.
endif

### rules for objects
$(foreach S,$(SOURCES_$1),$(eval $(call MCCI_DOCOMPILE,$(S),$1)))
endef

##############################################################################
#
#	Generate the rules for each of the LIBRARIES
#
##############################################################################

$(foreach L,$(LIBRARIES),$(eval $(call MCCI_DOLIBRARY,$(L))))

##############################################################################
#
# Name: MCCI_DOPROGRAM
#
# Function:
#	Macro for generating rules for building a program.
#
# Usage:
#	$(call MCCI_DOPROGRAM, programname)
#
# Input:
#	$1		name of the executable file (without .exe suffix)
#	SOURCES_$1 	the sources for that program
#	INCLUDES_$1	include paths for all files in the pgrogram
#	CC		the compiler name
#	CFLAGS		the compilation flags
#	LDFLAGS		the link flags (CC-form)
#	LDADD_$1	the additional pre-existing libraries to be used for
#			this program, but not added to dependencies
#	LIBS_$1		the libraries to be used for this program, and added
#			to dependencies.
#	LDFLAGS_$1	the specific link flags for this program
#	LDADDDEP_$1	any additional dependencies to be added.
#	LDSCRIPT_$1	the linker script
#
# Output:
#	all: is updated with $(T_OBJDIR)/$1
#	MCCI_CLEANFILES is similarly updated.
#
##############################################################################

define MCCI_DOPROGRAM
MCCI_CLEANFILES += $$(T_OBJDIR)/$1

ifneq ($$(LDSCRIPT_$1),)
$$(error Not provided: LDSCRIPT_$1)
endif

$$(T_OBJDIR)/$1: $$(OBJECTS_$1) $$(LIBS_$1) $${LDADDDEP_$1} ${LDSCRIPT_$1}
	@echo $1
	$${MAKEHUSH}$$(CC) $$(CFLAGS) $$(LDFLAGS) $$(LDFLAGS_$1) -o $$@ $$(OBJECTS_$1) -Wl,--start-group $$(LIBS) $$(LIBS_$1) $$(LDADD) $$(LDADD_$1) -Wl,--end-group -T $$(LDSCRIPT_$1)

all:	$$(T_OBJDIR)/$1

### rules for installing
_install_programs:	_install_programs_$1
.PHONY:			_install_programs_$1
_install_programs_$1:	$$(T_OBJDIR)/$1
	$${MAKEHUSH}$${MCCI_INSTALLDIR_CMD}  $${MCCI_INSTALLDIR_BIN}.
	$${MAKEHUSH}$${MCCI_INSTALL_CMD} -m 555 $$(T_OBJDIR)/$1 $${MCCI_INSTALLDIR_BIN}.

### rules for compiling
$(foreach S,$(SOURCES_$1),$(eval $(call MCCI_DOCOMPILE,$(S),$1)))
endef

##############################################################################
#
#	Generate the rules for building the programs
#
##############################################################################

$(foreach P,$(PROGRAMS),$(eval $(call MCCI_DOPROGRAM,$(P))))

##############################################################################
#
#	COLLECTIONS
#
##############################################################################

define MCCI_MAKEMODULE
$2: $2-$1

#
# it's much easier for debugging if we don't allow optimization;
# so we override the makefile.
#
$2-$1:
	make -C $1 -j4 BUILDTYPE=debug CFLAGS_OPT= \
		MCCI_INSTALLDIR_LOCAL="$${MCCI_INSTALLDIR_LOCAL}" \
		MCCI_INSTALL_BINUSER="$${MCCI_INSTALL_BINUSER}" \
		MCCI_INSTALL_BINGROUP="$${MCCI_INSTALL_BINGROUP}" \
		MCCI_INSTALL_BINMODE="$${MCCI_INSTALL_BINGROUP}" \
		$2
	make -C $1 -j4 BUILDTYPE=release \
		MCCI_INSTALLDIR_LOCAL="$${MCCI_INSTALLDIR_LOCAL}" \
		MCCI_INSTALL_BINUSER="$${MCCI_INSTALL_BINUSER}" \
		MCCI_INSTALL_BINGROUP="$${MCCI_INSTALL_BINGROUP}" \
		MCCI_INSTALL_BINMODE="$${MCCI_INSTALL_BINGROUP}" \
		$2
endef

##############################################################################
#
# Name: MCCI_DOSOURCERELEASE
#
# Function:
#	Macro for generating rules for building a collection.
#
# Usage:
#	$(call MCCI_DOSOURCERELEASE, module)
#
# Input:
#	$1		name of the module
#	TAG_$1		tag to use when releasing.
#
# Output:
#	release: is updated to create build/$1-TAG.tar.gz
#	clean: is updated to remove releases
#	MCCI_CLEANFILES is similarly updated.
#
##############################################################################

# $1 toplevel name
define MCCI_DOSOURCERELEASE

source-release:	source-release-$1

ifneq ($$(TAG_$1),)
MCCI_CLEANFILES += build/$1-$$(TAG_$1).tar.gz build/$1-$$(TAG_$1).tar build/$1-$$(TAG_$1).tgz
endif

.PHONY: source-release-$1
source-release-$1:
	@if [ X"$$(TAG_$1)" = X ]; then echo Set TAG_$1 to the release tag ; exit 1; fi
	@if [ ! -x "$$(GIT_ARCHIVE_ALL_SH)" ]; then \
	    echo "GIT_ARCHIVE_ALL_SH: $${GIT_ARCHIVE_ALL_SH}"; \
		echo "GIT_ARCHIVE_ALL_SH_DIR: $${GIT_ARCHIVE_ALL_SH_DIR}"; \
		echo "Set GIT_ARCHIVE_ALL_SH_DIR to the path to git-archive-all.sh"; \
		echo "This may be cloned from https://github.com/mcci-usb/git-archive-all.sh" ; \
		exit 1; \
	fi
	@if [ ! -d build ]; then mkdir build ; fi
	rm -f "build/$1-$$(TAG_$1).tar" "build/$1-$$(TAG_$1).tar.gz"
	$$(GIT_ARCHIVE_ALL_SH) --format tar.gz --prefix "$1-$$(TAG_$1)/" "build/$1-$$(TAG_$1)-source.tgz"
endef

##############################################################################
#
# Name: MCCI_DOCOLLECTION
#
# Function:
#	Macro for generating rules for building a collection.
#
# Usage:
#	$(call MCCI_DOCOLLECTION, collectionname)
#
# Input:
#	$1		name of the collection
#	MODULES_$1	the paths to the modlues to be built.
#	TAG_$1		tag to use when releasing.
#
# Output:
#	all: is updated with all-$1
#	clean: is updated with clean-$1
#	install: is updated with install-$1
#	MCCI_CLEANFILES is similarly updated.
#
##############################################################################

define MCCI_DOCOLLECTION
$(foreach M,$(MODULES_$1),$(eval $(call MCCI_MAKEMODULE,$(M),all)))

$(foreach M,$(MODULES_$1),$(eval $(call MCCI_MAKEMODULE,$(M),clean)))

$(foreach M,$(MODULES_$1),$(eval $(call MCCI_MAKEMODULE,$(M),install)))

$(call MCCI_DOSOURCERELEASE,$1)
endef

##############################################################################
#
#	Generate the rules for building the collections
#
##############################################################################

$(foreach C,$(COLLECTIONS),$(eval $(call MCCI_DOCOLLECTION,$(C))))

##############################################################################
#
# 	The top-level targets
#
##############################################################################

#
# all: rebuild everything.
#
.DEFAULT_GOAL := all
.PHONY: all
all:

#
# clean: remove all the generated files
#
.PHONY: clean
clean:

# if we have things to clean, add.
ifneq ($(strip $(MCCI_CLEANFILES) $(OBJECTS) $(DEPENDS)),)
clean:
	@rm -f $(MCCI_CLEANFILES) $(OBJECTS) $(DEPENDS)
endif

#
# install: links to install targets for each program
#
install: $(addprefix install-,$(PROGRAMS) $(LIBRARIES))
.PHONY: install $(addprefix install-,$(PROGRAMS) $(LIBRARIES))

#
# source-release: source release
#
.PHONY: source-release
source-release:

# pick up the dependencies.
-include $(DEPENDS)

#### end of file ####
