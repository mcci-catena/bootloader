##############################################################################
#
#	The catena_1sj library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_catena_1sj.mk),)
_GUARD_libmcci_bootloader_catena_1sj.mk := 1	# prevent multiple includes.

# prerequisites
include platform/soc/stm32l0/mk/libmcci_bootloader_stm32l0.mk

# contents
LIBRARIES += libmcci_bootloader_catena_1sj

_ := platform/board/mcci/catena_1sj

CFLAGS_OPT_libmcci_bootloader_catena_1sj += -Os

INCLUDES_libmcci_bootloader_catena_1sj :=				\
	$(INCLUDES_libmcci_bootloader_stm32l0)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena_1sj

SOURCES_libmcci_bootloader_catena_1sj :=				\
	$_/src/mccibootloaderboard_catena1sj_annunciator.c		\
	$_/src/mccibootloaderboard_catena1sj_eeprom.c			\
	$_/src/mccibootloaderboard_catena1sj_prepareforlaunch.c		\
	$_/src/mccibootloaderboard_catena1sj_spi.c			\
	$_/src/mccibootloaderboard_catena1sj_storage.c			\
	$_/src/mccibootloaderboard_catena1sj_systeminit.c		\
	$_/src/mccibootloaderboard_catena1sj_vectors.c			\
# end SOURCES_libmcci_bootloader_catena_1sj

endif # _GUARD_libmcci_bootloader_catena_1sj.mk
