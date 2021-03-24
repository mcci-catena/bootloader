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

##############################################################################
#
#	The board settings -- gives the path to the link scripts etc
#
##############################################################################

BOARDPATH ?= platform/board/mcci/catena_abz

##############################################################################
#
#	The bootloader per se
#
##############################################################################

PROGRAMS += McciBootloader

SOURCES_McciBootloader =				\
	src/mccibootloader_checkcodevalid.c		\
	src/mccibootloader_main.c			\
	src/mccibootloaderplatform_entry.c		\
	src/mccibootloaderplatform_fail.c		\
### end SOURCES_McciBootloader

INCLUDES_McciBootloader =				\
	i						\
	platform/i					\
	pkgsrc/mcci_arduino_development_kit_adk/src	\
	pkgsrc/mcci_tweetnacl/src			\
### end INCLUDES_McciBootloader

CFLAGS_OPT_McciBootloader ?= -Os

LDFLAGS_McciBootloader = 				\
	--cref 						\
	-Map=$(T_OBJDIR)/McciBootloader.map		\
### end LDFLAGS_McciBootloader

LDSCRIPT_McciBootloader = $(abspath $(BOARDPATH)/mk/mccibootloader.ld)

LDADD_McciBootloader += -lc

LIBS_McciBootloader +=					\
	${T_OBJDIR}/libmcci_tweetnacl.a			\
	${T_OBJDIR}/libmcci_bootloader_cm0plus.a	\
	${T_OBJDIR}/libmcci_bootloader_stm32l0.a	\
	${T_OBJDIR}/libmcci_bootloader_catena_abz.a	\
	${T_OBJDIR}/libmcci_bootloader_catena4801.a	\
### end LIBS_McciBootloader

##############################################################################
#
#	The cm0plus library
#
##############################################################################

LIBRARIES += libmcci_bootloader_cm0plus

_ := platform/arch/cm0plus

CFLAGS_OPT_libmcci_bootloader_cm0plus += -Os

INCLUDES_libmcci_bootloader_cm0plus :=					\
	$(INCLUDES_McciBootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_cm0plus

SOURCES_libmcci_bootloader_cm0plus :=					\
	$_/src/mccibootloaderplatform_startapp.c			\
# end SOURCES_libmcci_bootloader_cm0plus

##############################################################################
#
#	The stm32l0 library
#
##############################################################################

LIBRARIES += libmcci_bootloader_stm32l0

_ := platform/soc/stm32l0

CFLAGS_OPT_libmcci_bootloader_stm32l0 += -Os

INCLUDES_libmcci_bootloader_stm32l0 :=					\
	$(INCLUDES_libmcci_bootloader_cm0plus)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_stm32l0

SOURCES_libmcci_bootloader_stm32l0 :=					\
	$_/src/mccibootloader_stm32l0_systeminit.c			\
	$_/src/mccibootloader_stm32l0_prepareforlaunch.c		\
# end SOURCES_libmcci_bootloader_stm32l0

##############################################################################
#
#	The catena-abz library
#
##############################################################################

LIBRARIES += libmcci_bootloader_catena_abz

_ := platform/board/mcci/catena_abz

CFLAGS_OPT_libmcci_bootloader_catena_abz += -Os

INCLUDES_libmcci_bootloader_catena_abz :=				\
	$(INCLUDES_libmcci_bootloader_stm32l0)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena_abz

SOURCES_libmcci_bootloader_catena_abz :=				\
	$_/src/mccibootloaderboard_catenaabz_prepareforlaunch.c		\
	$_/src/mccibootloaderboard_catenaabz_spi.c			\
	$_/src/mccibootloaderboard_catenaabz_systeminit.c		\
	$_/src/mccibootloaderboard_catenaabz_vectors.c			\
# end SOURCES_libmcci_bootloader_catena_abz

##############################################################################
#
#	The catena4801 library
#
##############################################################################

LIBRARIES += libmcci_bootloader_catena4801

_ := platform/board/mcci/catena4801

CFLAGS_OPT_libmcci_bootloader_catena4801 += -Os

INCLUDES_libmcci_bootloader_catena4801 :=				\
	$(INCLUDES_libmcci_bootloader_catena_abz)			\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena4801

SOURCES_libmcci_bootloader_catena4801 :=				\
	$_/src/mccibootloaderboard_catena4801_platforminterface.c	\
	$_/src/mccibootloaderboard_catena4801_storageinit.c		\
# end SOURCES_libmcci_bootloader_catena4801

##############################################################################
#
#	The catena46xx library
#
##############################################################################

LIBRARIES += libmcci_bootloader_catena46xx

_ := platform/board/mcci/catena46xx

CFLAGS_OPT_libmcci_bootloader_catena46xx += -Os

INCLUDES_libmcci_bootloader_catena46xx :=				\
	$(INCLUDES_libmcci_bootloader_catena_abz)			\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena46xx

SOURCES_libmcci_bootloader_catena46xx :=				\
	$_/src/mccibootloaderboard_catena46xx_platforminterface.c	\
# end SOURCES_libmcci_bootloader_catena46xx

##############################################################################
#
#	mcci_tweetnacl
#
##############################################################################

LIBRARIES += libmcci_tweetnacl

_ := pkgsrc/mcci_tweetnacl/src

CFLAGS_OPT_libmcci_tweetnacl += -O2

SOURCES_libmcci_tweetnacl :=						\
	$_/lib/mcci_tweetnacl.c						\
	$_/lib/mcci_tweetnacl_sign.c					\
	$_/lib/mcci_tweetsalt_crypto_auth_hmacsha512256.c 		\
	$_/lib/mcci_tweetsalt_crypto_auth_hmacsha512256_verify.c 	\
	$_/hal/mcci_tweetnacl_box_keypair.c				\
	$_/hal/mcci_tweetnacl_hal_randombytes.c				\
	$_/hal/mcci_tweetnacl_sign_keypair.c				\
# end SOURCES_libmcci_tweetnacl

INCLUDES_libmcci_tweetnacl :=			\
	$_					\
# end INCLUDES_libmcci_tweetnacl

# post processing
include mk/tail.mk

#### end of file ####
