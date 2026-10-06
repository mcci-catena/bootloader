##############################################################################
#
#	The catena5230 library
#
##############################################################################

# get the pre-conditions
include platform/board/mcci/catena_1sj/mk/libmcci_bootloader_catena_1sj.mk
include platform/driver/flash_mx25v8035f/mk/libmcci_bootloader_flash_mx25v8035f.mk
include driver/npm1300/mk/libmcci_bootloader_driver_npm1300.mk

# set things up
LIBRARIES += libmcci_bootloader_catena5230

_ := platform/board/mcci/catena5230

CFLAGS_OPT_libmcci_bootloader_catena5230 += -Os

INCLUDES_libmcci_bootloader_catena5230 :=				\
	$(INCLUDES_libmcci_bootloader_catena_1sj)			\
	platform/driver/flash_mx25v8035f/i				\
	$_/i								\
	$(INCLUDES_libmcci_bootloader_driver_npm1300)			\
# end INCLUDES_libmcci_bootloader_catena5230

SOURCES_libmcci_bootloader_catena5230 :=				\
	$_/src/mccibootloaderboard_catena5230_platforminterface.c	\
	$_/src/mccibootloaderboard_catena5230_prepareforlaunch.c	\
	$_/src/mccibootloaderboard_catena5230_systeminit.c		\
	$_/src/mccibootloaderboard_catena5230_storageinit.c		\
# end SOURCES_libmcci_bootloader_catena5230
