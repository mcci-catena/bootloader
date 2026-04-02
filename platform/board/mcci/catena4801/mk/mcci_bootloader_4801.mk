##############################################################################
#
#	The 4801 bootloader
#
##############################################################################

include platform/board/mcci/catena_abz/mk/mcci_bootloader_catena_abz.mk

BOOTLOADERS += McciBootloader_4801

LIBS_McciBootloader_4801 :=				\
	${BOOTLOADER_LIBS_ABZ}				\
	${T_OBJDIR}/libmcci_bootloader_catena4801.a	\
### end LIBS_McciBootloader_4801

LDSCRIPT_McciBootloader_4801	:=	$(BOOTLOADER_LDSCRIPT_ABZ)

include platform/board/mcci/catena4801/mk/libmcci_bootloader_catena4801.mk
