##############################################################################
#
#	The driver library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_driver.mk),)
_GUARD_libmcci_bootloader_driver.mk := 1	# prevent multiple includes.

# requirements
include mk/libmcci_bootloader.mk

# contents
LIBRARIES += libmcci_bootloader_driver

_ := driver

CFLAGS_OPT_libmcci_bootloader_driver += -Os

INCLUDES_libmcci_bootloader_driver :=					\
	$(INCLUDES_libmcci_bootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_driver

SOURCES_libmcci_bootloader_driver :=					\
	$_/src/mccibootloaderdevice_begin.c				\
	$_/src/mccibootloaderdevice_end.c				\
# end SOURCES_libmcci_bootloader_driver

endif # _GUARD_libmcci_bootloader_driver.mk
