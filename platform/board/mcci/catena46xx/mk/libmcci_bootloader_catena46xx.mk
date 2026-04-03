##############################################################################
#
#	The catena46xx library
#
##############################################################################

# get the pre-conditions
include platform/board/mcci/catena_abz/mk/libmcci_bootloader_catena_abz.mk
include platform/driver/flash_mx25v8035f/mk/libmcci_bootloader_flash_mx25v8035f.mk

# set things up
LIBRARIES += libmcci_bootloader_catena46xx

_ := platform/board/mcci/catena46xx

CFLAGS_OPT_libmcci_bootloader_catena46xx += -Os

INCLUDES_libmcci_bootloader_catena46xx :=				\
	$(INCLUDES_libmcci_bootloader_catena_abz)			\
	platform/driver/flash_mx25v8035f/i				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena46xx

SOURCES_libmcci_bootloader_catena46xx :=				\
	$_/src/mccibootloaderboard_catena46xx_platforminterface.c	\
	$_/src/mccibootloaderboard_catena46xx_storageinit.c		\
# end SOURCES_libmcci_bootloader_catena46xx

