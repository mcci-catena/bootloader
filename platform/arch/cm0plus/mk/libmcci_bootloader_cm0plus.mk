##############################################################################
#
#	The cm0plus library
#
##############################################################################

LIBRARIES += libmcci_bootloader_cm0plus

_ := platform/arch/cm0plus

CFLAGS_OPT_libmcci_bootloader_cm0plus += -Os

INCLUDES_libmcci_bootloader_cm0plus :=					\
	$(INCLUDES_libmcci_bootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_cm0plus

SOURCES_libmcci_bootloader_cm0plus :=					\
	$_/src/mccibootloaderplatform_checkimagevalid.c			\
	$_/src/mccibootloaderplatform_getappinfo.c			\
	$_/src/mccibootloaderplatform_getsignatureblock.c		\
	$_/src/mccibootloaderplatform_startapp.c			\
# end SOURCES_libmcci_bootloader_cm0plus

