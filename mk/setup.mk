##############################################################################
#
# Module:  setup.mk
#
# Function:
#	GNU make setup for builds in the bootloader project
#
# Copyright notice:
#	This file copyright (C) 2017, 2020 by
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
#	Terry Moore, MCCI Corporation	July 2020
#
##############################################################################

# record where we are
_SETUP_MK := $(lastword $(MAKEFILE_LIST))

# remove built-in special suffix handling, and enable .c, .o, .a
.SUFFIXES:
.SUFFIXES: .c .o .a

# Since this is in the mk subdir, we extract dir, go up one level and make abs
# We also append a /, which makes error messaging better if it happens to be
# empty
MCCIBOOTLOADER_ROOT := $(abspath $(dir $(_SETUP_MK))/..)/

# It's handy to have the MCCI_ROOT, too.
MCCI_ROOT := $(abspath $(MCCIBOOTLOADER_ROOT)..)/

# we want to be able to parse the error messages, so force them to be
# in ANSI.
export	LC_ALL = C

# define CROSS_COMPILE to the cross-compiler prefix to get a cross-compilation
CC	:=	$(CROSS_COMPILE)gcc

# strip the final '-' off CROSS_COMPILE, if any
CC_MULTIARCH := $(notdir $(CROSS_COMPILE:%-=%))

# if CC_MULTIARCH is empty, it's not a cross-compile, so ask CC what
# arch to to use
ifeq ($(CC_MULTIARCH),)
 CC_MULTIARCH :=	$(shell $(CC) --print-multiarch)
 ifeq ($(CC_MULTIARCH),)
  $(error No CROSS_COMPILE= and CC[$(CC)] doesn't point to a known compiler.)
 endif
endif

#
# define the targets dirs. T_BUILDTREE is where we intend to build,
# generally speaking
#
ifndef T_BUILDTREE
T_BUILDTREE = build
endif

#
# make sure BUILDTYPE is set.... then set T_BUILDTYPE to the canonical
# version.  T_BUILDTYPE is "release" or "debug"; we also accept "checked"
# and "free" to accord with MCCI usage.
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
# Set T_OBJDIR to the usual location for building things
#
T_OBJDIR = $(T_BUILDTREE)/$(CC_MULTIARCH)/$(T_BUILDTYPE)

##############################################################################
#
#	Handle definition of MAKEHUSH= based on MAKEVERBOSE
#
##############################################################################

ifeq (${MAKEVERBOSE},)
 MAKEVERBOSE = 0
endif

ifeq (${MAKEVERBOSE},0)
 MAKEHUSH ?= @
else
 MAKEHUSH ?=
endif

##############################################################################
#
#	Make setup
#
##############################################################################

#
# Alert make to the usual targets.
#
.PHONY: all install clean

##############################################################################
#
#	Compiler setup
#
##############################################################################

ifeq (${T_BUILDTYPE},release)
CFLAGS_OPT_DEFAULT ?=	-Os
endif

CFLAGS_BUILDTYPE_release ?= -DNDEBUG
CFLAGS_BUILDTYPE_debug ?= -g -DDEBUG

CFLAGS_CPU ?= 	-mcpu=cortex-m0plus -mthumb

CFLAGS	=	-Wall -g -Werror ${CFLAGS_OPT}
CFLAGS  +=	-Werror=missing-prototypes
CFLAGS	+=	$(CFLAGS_CPU)
CFLAGS	+=	-ffunction-sections -fdata-sections -std=gnu11
CFLAGS	+=	-nostdlib
CFLAGS  +=	${CFLAGS_BUILDTYPE_${T_BUILDTYPE}}
CFLAGS 	+=	${CFLAGS_PROGRAM} ${CFLAGS_USER}

INCLUDES_GLOBAL += ${MCCIBOOTLOADER_ROOT}i

CPPFLAGS +=	${CPPFLAGS_PROGRAM} ${CPPFLAGS_USER}
CPPFLAGS +=	${foreach includedir, ${INCLUDES_GLOBAL} ${INCLUDES_PROGRAM}, -I $(includedir)}

LDFLAGS	?=					\
	--gc-sections 				\
	--check-sections 			\
	--unresolved-symbols=report-all 	\
	--warn-common 				\
	--warn-section-align			\
	--print-memory-usage			\
	${LDFLAGS_USER}				\
### end LDFLAGS ###

LDADD	?=					\
	-lgcc					\
### end LDADD ###

AR	:=	$(CROSS_COMPILE)ar

##############################################################################
#
#	Things to add to your program's build instructions
#
##############################################################################

# libraries to be included
MCCIBOOTLOADER_LDSCRIPT	:=	$(abspath ${MCCIBOOTLOADER_ROOT}mk/mccibootloader.ld)

##############################################################################
#
#	Where to find useful things.
#
##############################################################################

#
# for source releases, we need a copy of git-archive-all.
#
GIT_ARCHIVE_ALL_SH ?= $(shell D=$(GIT_ARCHIVE_ALL_SH_DIR); which "$$D$${D:+/}git-archive-all.sh")

#
# get the bootloader info. Turn off cross-compile because we need the version for the host
#

# path to bootloader tree
MCCIBOOTLOADER_IMAGE_ROOT := $(abspath ${MCCIBOOTLOADER_ROOT}/tools/mccibootloader_image)

# path to directory holding image, and image suffix
MCCIBOOTLOADER_IMAGE_PATH := $(shell make -C "${MCCIBOOTLOADER_IMAGE_ROOT}" CROSS_COMPILE= --no-print-directory print-target-path)
MCCIBOOTLOADER_IMAGE_SUFFIX := $(shell make -C "${MCCIBOOTLOADER_IMAGE_ROOT}" CROSS_COMPILE= --no-print-directory print-target-suffix)

# make sure the image path is well formed (either blank, or ending with a slash)
ifneq ($(strip $(MCCIBOOTLOADER_IMAGE_PATH)),)
 override MCCIBOOTLOADER_IMAGE_PATH := $(MCCIBOOTLOADER_IMAGE_PATH:/=)/
endif

# path of bootloader_image itself
MCCIBOOTLOADER_IMAGE ?=	${MCCIBOOTLOADER_IMAGE_PATH}mccibootloader_image${MCCIBOOTLOADER_IMAGE_SUFFIX}

#
# set path to test-signing key file
#
MCCI_BOOTLOADER_KEYFILE_TEST :=  ${MCCIBOOTLOADER_IMAGE_ROOT}/test/mcci-test.pem

#
# set path to key file to use; if input is blank, then point to the test-signing key
#
ifeq ($(strip $(MCCI_BOOTLOADER_KEYFILE)),)
 MCCI_BOOTLOADER_KEYFILE = $(MCCI_BOOTLOADER_KEYFILE_TEST)
endif

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
