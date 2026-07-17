##############################################################################
#
#	The driver_npm1300 library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_driver_npm1300.mk),)
_GUARD_libmcci_bootloader_driver_npm1300.mk := 1	# prevent multiple includes.

# requirements
include driver/i2c/mk/libmcci_bootloader_driver_i2c.mk

# contents
LIBRARIES += libmcci_bootloader_driver_npm1300

_ := driver/npm1300

CFLAGS_OPT_libmcci_bootloader_driver_npm1300 += -Os

INCLUDES_libmcci_bootloader_driver_npm1300 :=				\
	$(INCLUDES_libmcci_bootloader_driver_i2c)			\
	$_/i								\
# end INCLUDES_libmcci_bootloader_driver_npm1300

SOURCES_libmcci_bootloader_driver_npm1300 :=				\
	$_/src/mccibootloaderdriver_npm1300_createandattach.c		\
	$_/src/mccibootloaderdriver_npm1300_initializeregisters.c	\
# end SOURCES_libmcci_bootloader_driver_npm1300

endif # _GUARD_libmcci_bootloader_driver_npm1300.mk
