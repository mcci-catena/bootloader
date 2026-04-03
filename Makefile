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

include mk/setup.mk

FAMILY_MAKEFILES := $(wildcard Makefile-*.mk)

##############################################################################
#
#	doxygen documentation
#
##############################################################################

.PHONY: doxygen clean-doxygen

doxygen:
	doxygen

clean-doxygen:
	rm -rf doc/doxygen

clean: clean-doxygen

# post processing
include mk/tail.mk

#### end of file ####
