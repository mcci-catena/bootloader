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

TARGET_FAMILY := stm32l0
include mk/setup.mk

include platform/board/mcci/catena4801/mk/mcci_bootloader_4801.mk
include platform/board/mcci/catena46xx/mk/mcci_bootloader_46xx.mk

# post processing
include mk/tail.mk

#### end of file ####
