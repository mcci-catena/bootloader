##############################################################################
#
#	The board settings -- gives the path to the link scripts etc
#
##############################################################################

BOOTLOADER_LDSCRIPT_ABZ := $(abspath platform/board/mcci/catena_abz/mk/mccibootloader.ld)

BOOTLOADER_LIBS_ABZ :=	\
	${T_OBJDIR}/libmcci_bootloader_cm0plus.a	\
	${T_OBJDIR}/libmcci_bootloader_stm32l0.a	\
	${T_OBJDIR}/libmcci_bootloader_catena_abz.a	\
	${T_OBJDIR}/libmcci_bootloader_flash_mx25v8035f.a \
# end BOOTLOADER_LIBS_ABZ

##############################################################################
#
#	The catena-abz library
#
##############################################################################

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

