##############################################################################
#
#	The catena-abz library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_catena_abz.mk),)
_GUARD_libmcci_bootloader_catena_abz.mk := 1	# prevent multiple includes.

# prerequisites
include platform/soc/stm32l0/mk/libmcci_bootloader_stm32l0.mk

# contents
LIBRARIES += libmcci_bootloader_catena_abz

_ := platform/board/mcci/catena_abz

CFLAGS_OPT_libmcci_bootloader_catena_abz += -Os

INCLUDES_libmcci_bootloader_catena_abz :=				\
	$(INCLUDES_libmcci_bootloader_stm32l0)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_catena_abz

SOURCES_libmcci_bootloader_catena_abz :=				\
	$_/src/mccibootloaderboard_catenaabz_annunciator.c		\
	$_/src/mccibootloaderboard_catenaabz_eeprom.c			\
	$_/src/mccibootloaderboard_catenaabz_prepareforlaunch.c		\
	$_/src/mccibootloaderboard_catenaabz_spi.c			\
	$_/src/mccibootloaderboard_catenaabz_storage.c			\
	$_/src/mccibootloaderboard_catenaabz_systeminit.c		\
	$_/src/mccibootloaderboard_catenaabz_vectors.c			\
# end SOURCES_libmcci_bootloader_catena_abz

endif # _GUARD_libmcci_bootloader_catena_abz.mk
