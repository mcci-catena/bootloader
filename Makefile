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

include platform/board/mcci/catena_abz/mk/mcci_bootloader_catena_abz.mk
include mk/libmcci_bootloader.mk
include platform/board/mcci/catena4801/mk/mcci_bootloader_4801.mk
include platform/board/mcci/catena46xx/mk/mcci_bootloader_46xx.mk
include platform/board/st/stm32h7b3i_dk/mk/mcci_bootloader_stm32h7b3i_dk.mk

include platform/arch/cm0plus/mk/libmcci_bootloader_cm0plus.mk
include platform/soc/stm32l0/mk/libmcci_bootloader_stm32l0.mk
include platform/driver/flash_mx25v8035f/mk/libmcci_bootloader_flash_mx25v8035f.mk

include platform/board/mcci/catena_abz/mk/libmcci_bootloader_catena_abz.mk
include pkgsrc/mk/mcci_tweetnacl.mk
include platform/arch/cm7/mk/libmcci_bootloader_cm7.mk
include platform/soc/stm32h7/mk/libmcci_bootloader_stm32h7.mk
include platform/board/st/stm32h7b3i_dk/mk/libmcci_bootloader_stm32h7b3i_dk.mk

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
