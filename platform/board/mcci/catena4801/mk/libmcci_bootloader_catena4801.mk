##############################################################################
#
#	The catena4801 library
#
##############################################################################

# get the pre-conditions
include platform/board/mcci/catena_abz/mk/libmcci_bootloader_catena_abz.mk
include platform/driver/flash_mx25v8035f/mk/libmcci_bootloader_flash_mx25v8035f.mk

# set things up
LIBRARIES += libmcci_bootloader_catena4801

_ := platform/board/mcci/catena4801

CFLAGS_OPT_libmcci_bootloader_catena4801 += -Os

INCLUDES_libmcci_bootloader_catena4801 :=				\
	$(INCLUDES_libmcci_bootloader_catena_abz)			\
	platform/driver/flash_mx25v8035f/i				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena4801

SOURCES_libmcci_bootloader_catena4801 :=				\
	$_/src/mccibootloaderboard_catena4801_platforminterface.c	\
	$_/src/mccibootloaderboard_catena4801_storageinit.c		\
# end SOURCES_libmcci_bootloader_catena4801

