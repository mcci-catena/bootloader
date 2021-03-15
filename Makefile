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

PROGRAMS += McciBootloader

SOURCES_McciBootloader =			\
	src/mccibootloader_main.c		\
### end SOURCES_McciBootloader

INCLUDES_McciBootloader =				\
	i						\
	pkgsrc/mcci_arduino_development_kit_adk/src	\
### end INCLUDES_McciBootloader

CFLAGS_OPT_McciBootloader ?= -Os

LDFLAGS_McciBootloader = 			\
### end LDFLAGS_McciBootloader

LDSCRIPT_McciBootloader = $(abspath mk/mccibootloader.ld)

#
# building mcci_tweetnacl
LIBRARIES += libmcci_tweetnacl

_ := pkgsrc/mcci_tweetnacl/src

CFLAGS_OPT_libmcci_tweetnacl += -Os

SOURCES_libmcci_tweetnacl =						\
	$_/lib/mcci_tweetnacl.c						\
	$_/lib/mcci_tweetnacl_sign.c					\
	$_/lib/mcci_tweetsalt_crypto_auth_hmacsha512256.c 		\
	$_/lib/mcci_tweetsalt_crypto_auth_hmacsha512256_verify.c 	\
	$_/hal/mcci_tweetnacl_box_keypair.c				\
	$_/hal/mcci_tweetnacl_hal_randombytes.c				\
	$_/hal/mcci_tweetnacl_sign_keypair.c				\
# end SOURCES_libmcci_tweetnacl

INCLUDES_libmcci_tweetnacl =			\
	$_					\
# end INCLUDES_libmcci_tweetnacl

# post processing
include mk/tail.mk

#### end of file ####
