##############################################################################
#
#	mcci_tweetnacl
#
##############################################################################

ifeq ($(_GUARD_mcci_tweetnacl.mk),)
_GUARD_mcci_tweetnacl.mk := 1	# prevent multiple includes.

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

endif # _GUARD_mcci_tweetnacl.mk
