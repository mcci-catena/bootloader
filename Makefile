##############################################################################
#
# Module:  Makefile
#
# Function:
#	GNU make building the bootloader
#
# Copyright notice:
#	This file copyright (C) 2020, 2026 by
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

include mk/setup.mk

FAMILY_MAKEFILES := $(wildcard Makefile-*.mk)

##############################################################################
#
#	mccibootloader_image
#
##############################################################################

.PHONY: mccibootloader_image clean-mccibootloader_image

mccibootloader_image:
	@printf '%s\n' 'build tool: mccibootloader_image (release)'
	$(MAKEHUSH)$(MAKE) -C tools/mccibootloader_image --no-print-directory CROSS_COMPILE= all BUILDTYPE=release
	@printf '%s\n' 'build tool: mccibootloader_image (debug)'
	$(MAKEHUSH)$(MAKE) -C tools/mccibootloader_image --no-print-directory CROSS_COMPILE= all BUILDTYPE=debug

clean-mccibootloader_image:
	@printf '%s\n' 'clean tool: mccibootloader_image (release)'
	$(MAKEHUSH)$(MAKE) -C tools/mccibootloader_image --no-print-directory CROSS_COMPILE= clean BUILDTYPE=debug
	@printf '%s\n' 'clean tool: mccibootloader_image (debug)'
	$(MAKEHUSH)$(MAKE) -C tools/mccibootloader_image --no-print-directory CROSS_COMPILE= clean BUILDTYPE=debug

clean-pre:	clean-mccibootloader_image

all-pre:	mccibootloader_image

##############################################################################
#
#	doxygen documentation
#
##############################################################################

.PHONY: doxygen clean-doxygen

doxygen:
	@printf 'run doxygen\n'
	$(MAKEHUSH)( cat Doxyfile ; \
		     if [ "$(MAKEVERBOSE)" -eq 0 ]; then \
			printf 'QUIET = YES\n' ; \
		     fi ) | doxygen - 2>${T_BUILDTREE}/doxygen.log
	@printf '${T_BUILDTREE}/doxygen.log: %s messages\n' $$(wc -l < ${T_BUILDTREE}/doxygen.log)

clean-doxygen:
	@printf '%s\n' 'clean doxygen'
	$(MAKEHUSH)rm -rf doc/doxygen ${T_BUILDTREE}/doxygen.log

clean-post: clean-doxygen
all-post: doxygen

# post processing
include mk/tail.mk

#### end of file ####
