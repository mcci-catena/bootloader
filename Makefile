##############################################################################
#
# Module:  Makefile
#
# Function:
#	GNU make building the bootloader
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
#	See accompanying LICENSE file for license information.
#
# Author:
#	Terry Moore, MCCI Corporation	July 2020
#
##############################################################################

include(mk/setup.mk)

PROGRAMS = McciBootloader

SOURCES_McciBootloader =			\
	src/mccibootloader_main.c		\
### end SOURCES_McciBootloader

INCLUDES_McciBootloader =			\
	i					\
### end INCLUDES_McciBootloader

CFLAGS_OPT_McciBootloader ?= -Os

LDFLAGS_McciBootloader = 			\
	-Wl,--gc-sections 			\
	-Wl,--cref 				\
	-Wl,--check-sections 			\
	-Wl,--unresolved-symbols=report-all 	\
	-Wl,--warn-common 			\
	-Wl,--warn-section-align		\
	-nostdlib				\
	-lgcc

LDSCRIPT_McciBootloader = $(abspath mk/mccibootloader.ld)


# post processing
include(mk/tail.mk)

#### end of file ####
