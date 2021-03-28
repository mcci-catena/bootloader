##############################################################################
#
# Module:  setup.mk
#
# Function:
#	GNU make setup for bootloader tool builds
#
# Copyright notice:
#	This file copyright (C) 2021 by
#
#		MCCI Corporation
#		3520 Krums Corners Road
#		Ithaca, NY  14850
#
#	An unpublished work.  All rights reserved.
#
#	See accompanying LICENSE file for license information.
#
# Author:
#	Terry Moore, MCCI Corporation	March 2021
##
##############################################################################

# record where we are
_SETUP_MK := $(lastword $(MAKEFILE_LIST))
MCCI_TAIL := $(abspath $(dir $(_SETUP_MK))/tool_tail.mk)

# remove built-in special suffix handling, and enable .c, .o, .a
.SUFFIXES:
.SUFFIXES: .c .o .a .cpp

# Since this is in the mk subdir, we extract dir, go up one level and make abs
# We also append a /, which makes error messaging better if it happens to be
# empty
MCCIBOOTLOADER_ROOT := $(abspath $(dir $(_SETUP_MK))/../..)/

# we want to be able to parse the error messages, so force them to be
# in ANSI.
export	LC_ALL = C

##############################################################################
#
#	Detect the host (not target tool exe) environment
#
##############################################################################

# post-condition: MCCI_MAKEHOST is set to our judgement of the build env:
# Windows, Darwin or Linux.
ifeq ($(OS),Windows_NT)
  MCCI_MAKEHOST := Windows
else
  MCCI_UNAME_S := $(shell uname -s)
  ifeq ($(MCCI_UNAME_S),Darwin)
    MCCI_MAKEHOST := Darwin
  else
    MCCI_MAKEHOST := Linux
  endif
endif

# post-condition: MCCI_CC is set to clang or gcc
ifeq ($(MCCI_MAKEHOST),Windows)
  MCCI_CC := clang
else
  MCCI_CC := gcc
endif

# post-condition: CC, CCLINK and CXXLINK are set up
#
# CCLINK is set to the comand to be used for linking programs without C++ support.
# CXXLINK is set to the comand to be use for linking programs with C++ support.
#
ifeq ($(MCCI_CC),gcc)
  CC := $(CROSS_COMPILE)gcc
  CCLINK := $(CROSS_COMPILE)gcc
  CXXLINK := $(CROSS_COMPILE)g++
else ifeq ($(MCCI_CC),clang)
  CC := $(CROSS_COMPILE)clang
  CCLINK := $(CROSS_COMPILE)clang
  CXXLINK := $(CROSS_COMPILE)clang
else
  $(error Unknown compiler MCCI_CC($(MCCI_CC)))
endif

# post-condition: CC_MULTIARCH is set to the target ID
# start by guessing that we can use CROSS_COMPILE

# strip the final '-' off CROSS_COMPILE, if any
CC_MULTIARCH := $(notdir $(CROSS_COMPILE:%-=%))

# if CC_MULTIARCH is empty, it's not a cross-compile, so ask compiler what
# arch to to use
ifeq ($(CC_MULTIARCH),)
  ifeq ($(MCCI_CC),gcc)
    CC_MULTIARCH := $(shell $(CC) --print-multiarch)
  else ifeq ($(MCCI_CC),clang)
    CC_MULTIARCH := $(shell $(CC) --print-target-triple)
  else
    $(error Unknown compiler MCCI_CC($(MCCI_CC)))
  endif
endif

#
# figure out the target executable suffix
# postcondition: T_EXE_SUFFIX is .exe or empty.
#
ifneq ($(filter %-windows-msvc,$(CC_MULTIARCH)),)
  T_EXE_SUFFIX=.exe
else
  T_EXE_SUFFIX=
endif

#
# figure out the situation for --start-group and --end-group
#
ifneq ($(filter %-windows-msvc,$(CC_MULTIARCH)),)
  T_LDFLAG_STARTGROUP=
  T_LDFLAG_ENDGROUP=
else
  T_LDFLAG_STARTGROUP=--start-group
  T_LDFLAG_ENDGROUP=--end-group
endif

#
# Define the targets dirs. T_BUILDTREE is where we intend to build,
# generally speaking. Note that we build in the current directory
# at the time make is invoked.
#
# Postcondition: T_BUILDTREE is a (possibly relative) path to the
# top-level directory where build artifacts will be constructed.
#
ifndef T_BUILDTREE
T_BUILDTREE = build
endif

#
# make sure BUILDTYPE is set.... then set T_BUILDTYPE to the canonical
# version.  T_BUILDTYPE is "release" or "debug"; we also accept "checked"
# and "free" to accord with MCCI usage.
#
# Postcondition: T_BUILDTYPE is either "release" or "debug".
#
ifeq (${BUILDTYPE},)
 T_BUILDTYPE=release
else ifeq (${BUILDTYPE},release)
 T_BUILDTYPE=release
else ifeq (${BUILDTYPE},free)
 T_BUILDTYPE=release
else ifeq (${BUILDTYPE},debug)
 T_BUILDTYPE=debug
else ifeq (${BUILDTYPE},checked)
 T_BUILDTYPE=debug
else
 ${error BUILDTYPE not valid: ${BUILDTYPE}}
endif

#
# Set T_OBJDIR to the location for building things
#
# Precondition: CC_MULTIARCH must be non-empty
# Postcondition: T_OBJDIR is a reasonable directory path
#
ifeq ($(T_BUILDTREE),)
  $(error T_BUILDTREE is empty)
else ifeq ($(CC_MULTIARCH),)
  $(error CC_MULTIARCH is empty)
else ifeq ($(T_BUILDTYPE),)
  $(error T_BUILDTYPE is empty)
endif

T_OBJDIR = $(T_BUILDTREE)/$(CC_MULTIARCH)/$(T_BUILDTYPE)

##############################################################################
#
#	Handle definition of MAKEHUSH= based on MAKEVERBOSE
#
##############################################################################

# postcondition: MAKEVERBOSE has a value and can be meaningfully compared to zero
ifeq (${MAKEVERBOSE},)
 MAKEVERBOSE = 0
endif

# postcondition: MAKEHUSH is either @ or empty.
ifeq (${MAKEVERBOSE},0)
 MAKEHUSH ?= @
else
 MAKEHUSH ?=
endif

#
# Alert make to the usual targets.
#
# postcondition: all, install, clean are known as virtual targets to make.
.PHONY: all install clean

##############################################################################
#
#	Compiler setup
#
#	Note that for MSVC we'll have to add some additional logic, following
#	the strategy in MCCI's libport. At present, we compile for Windows
#	using clang from scoop, and these settings work.
#
##############################################################################

ifeq (${T_BUILDTYPE},release)
CFLAGS_OPT ?=	-O3
endif

CFLAGS_BUILDTYPE_release ?= -DNDEBUG
CFLAGS_BUILDTYPE_debug ?= -g -DDEBUG

CFLAGS	=	-Wall -Werror ${CFLAGS_OPT}
CFLAGS  +=	-Werror=missing-prototypes
CFLAGS  +=	${CFLAGS_BUILDTYPE_${T_BUILDTYPE}}
CFLAGS 	+=	${CFLAGS_PROGRAM} ${CFLAGS_USER}

CXXFLAGS  =	-Wall -Werror ${CFLAGS_OPT}
CXXFLAGS  +=	${CFLAGS_BUILDTYPE_${T_BUILDTYPE}}
CXXFLAGS  +=	${CXXFLAGS_PROGRAM} ${CXXFLAGS_USER}

INCLUDES_GLOBAL += ${MCCIBOOTLOADER_ROOT}i

CPPFLAGS +=	${CPPFLAGS_PROGRAM} ${CPPFLAGS_USER}
CPPFLAGS +=	${foreach includedir, ${INCLUDES_GLOBAL} ${INCLUDES_PROGRAM}, -I $(includedir)}

ifeq ($(MCCI_CC),clang)
AR  :=  $(CROSS_COMPILE)llvm-ar
else
AR	:=	$(CROSS_COMPILE)ar
endif

##############################################################################
#
#	Where to find useful things.
#
##############################################################################

GIT_ARCHIVE_ALL_SH ?= $(shell D=$(GIT_ARCHIVE_ALL_SH_DIR); which "$$D$${D:+/}git-archive-all.sh")

##############################################################################
#
#	Install control
#
##############################################################################

MCCI_INSTALLDIR_LOCAL	?=	${T_BUILDTREE}
MCCI_INSTALL_BINUSER	?=	bin
MCCI_INSTALL_BINGROUP	?=	bin
MCCI_INSTALL_BINMODE	?=	666
T_MCCI_INSTALL_BINUSER_OPT =	$(patsubst %,-o%,${MCCI_INSTALL_BINUSER})
T_MCCI_INSTALL_BINGROUP_OPT =	$(patsubst %,-g%,${MCCI_INSTALL_BINGROUP})
T_MCCI_INSTALL_BINMODE_OPT =	$(patsubst %,-m%,${MCCI_INSTALL_BINMODE})

T_MCCI_INSTALLDIR 	=	$(dir ${MCCI_INSTALLDIR_LOCAL})$(notdir ${MCCI_INSTALLDIR_LOCAL})/
MCCI_INSTALL_BINDIRS	?=	$(CC_MULTIARCH)/$(T_BUILDTYPE)
MCCI_INSTALLDIR_BIN	?=	${T_MCCI_INSTALLDIR}bin/${MCCI_INSTALL_BINDIRS}/
MCCI_INSTALLDIR_LIB	?=	${T_MCCI_INSTALLDIR}lib/*/${MCCI_INSTALL_BINDIRS}/
MCCI_INSTALLDIR_SCRIPTS	?=	${T_MCCI_INSTALLDIR}bin/
MCCI_INSTALLDIR_INCLUDES	?=	${T_MCCI_INSTALLDIR}i/*/
MCCI_INSTALLDIR_UDEVRULES	?=	${T_MCCI_INSTALLDIR}etc/udev/rules.d/

# the name of the install program
INSTALL ?=	install

# the common commands for installation
# for installing files; install rules are expected to specify the mode for the files they're installing
MCCI_INSTALL_CMD	?=	$(INSTALL) -c ${T_MCCI_INSTALL_BINUSER_OPT} ${T_MCCI_INSTALL_BINGROUP_OPT} $(USER_INSTALL_FLAGS)

# for precreating a directory; we want to specify BINMODE, to set the group of the
# directory. this often ends up requiring a `sudo` on `make install`.
MCCI_INSTALLDIR_CMD	?=	$(INSTALL) -d ${T_MCCI_INSTALL_BINUSER_OPT} ${T_MCCI_INSTALL_BINGROUP_OPT} ${T_MCCI_INSTALL_BINMODE_OPT} $(USER_INSTALL_FLAGS)

##############################################################################
#
#       Initialize the variables that the makefile will add to... PROGRAMS
#       is the list of programs to be build, LIBRARIES the list of libraries
#       to be built. See tail.mk for more details.
#
##############################################################################

PROGRAMS =
LIBRARIES =
COLLECTIONS =

#### end of setup.mk ####
