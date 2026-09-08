##############################################################################
#
#	The catena5220 library
#
##############################################################################

# get the pre-conditions
include platform/board/mcci/catena_1sj/mk/libmcci_bootloader_catena_1sj.mk
include platform/driver/flash_mx25v8035f/mk/libmcci_bootloader_flash_mx25v8035f.mk

# set things up
LIBRARIES += libmcci_bootloader_catena5220

_ := platform/board/mcci/catena5220

CFLAGS_OPT_libmcci_bootloader_catena5220 += -Os

INCLUDES_libmcci_bootloader_catena5220 :=				\
	$(INCLUDES_libmcci_bootloader_catena_1sj)			\
	platform/driver/flash_mx25v8035f/i				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena5220

SOURCES_libmcci_bootloader_catena5220 :=				\
	$_/src/mccibootloaderboard_catena5220_platforminterface.c	\
	$_/src/mccibootloaderboard_catena5220_storageinit.c		\
# end SOURCES_libmcci_bootloader_catena5220
