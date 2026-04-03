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

TARGET_FAMILY := stm32h7
MCCIBOOTLOADER_IMAGE_FLAGS=--app-version 1.0.0 --comment Manouria

include mk/setup.mk

include platform/board/st/stm32h7b3i_dk/mk/mcci_bootloader_stm32h7b3i_dk.mk

# post processing
include mk/tail.mk

#### end of file ####
