##############################################################################
#
#	The driver_i2c library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_driver_i2c.mk),)
_GUARD_libmcci_bootloader_driver_i2c.mk := 1	# prevent multiple includes.

# requirements
include driver/mk/libmcci_bootloader_driver.mk

# contents
LIBRARIES += libmcci_bootloader_driver_i2c

_ := driver/i2c

CFLAGS_OPT_libmcci_bootloader_driver_i2c += -Os

INCLUDES_libmcci_bootloader_driver_i2c :=				\
	$(INCLUDES_libmcci_bootloader_driver)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_driver_i2c

SOURCES_libmcci_bootloader_driver_i2c :=				\
# end SOURCES_libmcci_bootloader_driver_i2c

endif # _GUARD_libmcci_bootloader_driver_i2c.mk
