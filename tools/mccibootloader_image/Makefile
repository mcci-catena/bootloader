##############################################################################
#
# Module:  setup.mk
#
# Function:
#	GNU make for mccibootloader_image
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
#
##############################################################################

include ../mk/tool_setup.mk

##############################################################################
#
#	Building mccibootloader_image
#
##############################################################################

PROGRAMS += mccibootloader_image

SOURCES_mccibootloader_image =					\
	src/main.cpp						\
	src/keyfile_ed25519.cpp					\
	src/salt_test.cpp					\
# end of SOURCES_mccibootloader_image

INCLUDES_mccibootloader_image =					\
	i							\
	../../pkgsrc/mcci_tweetnacl/src				\
# end of INCLUDES_mccibootloader_image

LIBS_mccibootloader_image =					\
	${T_OBJDIR}/libmcci_tweetnacl.a				\
# end of LIBS_mccibootloader_image

##############################################################################
#
#	mcci_tweetnacl
#
##############################################################################

LIBRARIES += libmcci_tweetnacl

_ := ../../pkgsrc/mcci_tweetnacl/src

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




include ${MCCI_TAIL}
### end of file ###
