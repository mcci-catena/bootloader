##############################################################################
#
#	The cm7 library
#
##############################################################################

LIBRARIES += libmcci_bootloader_cm7

_ := platform/arch/cm7

CFLAGS_OPT_libmcci_bootloader_cm7 += -Os

INCLUDES_libmcci_bootloader_cm7 :=					\
	$(INCLUDES_libmcci_bootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_cm7

SOURCES_libmcci_bootloader_cm7 :=					\
	$_/src/mccibootloaderplatform_cm7_checkimagevalid.c		\
	$_/src/mccibootloaderplatform_cm7_getappinfo.c			\
	$_/src/mccibootloaderplatform_cm7_getsignatureblock.c		\
	$_/src/mccibootloaderplatform_cm7_startapp.c			\
# end SOURCES_libmcci_bootloader_cm7

