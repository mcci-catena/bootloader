##############################################################################
#
#	The 5220 bootloader
#
##############################################################################

include platform/board/mcci/catena_1sj/mk/mcci_bootloader_catena_1sj.mk

BOOTLOADERS += McciBootloader_5220

LIBS_McciBootloader_5220 :=				\
	${BOOTLOADER_LIBS_1SJ}				\
	${T_OBJDIR}/libmcci_bootloader_catena5220.a	\
### end LIBS_McciBootloader_5220

LDSCRIPT_McciBootloader_5220	:=	$(BOOTLOADER_LDSCRIPT_1SJ)

include platform/board/mcci/catena5220/mk/libmcci_bootloader_catena5220.mk
