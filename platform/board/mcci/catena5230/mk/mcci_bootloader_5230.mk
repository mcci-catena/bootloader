##############################################################################
#
#	The 5230 bootloader
#
##############################################################################

include platform/board/mcci/catena_1sj/mk/mcci_bootloader_catena_1sj.mk

BOOTLOADERS += McciBootloader_5230

LIBS_McciBootloader_5230 :=				\
	${BOOTLOADER_LIBS_1SJ}				\
	${T_OBJDIR}/libmcci_bootloader_catena5230.a	\
	${T_OBJDIR}/libmcci_bootloader_driver.a		\
	${T_OBJDIR}/libmcci_bootloader_driver_npm1300.a	\
### end LIBS_McciBootloader_5230

LDSCRIPT_McciBootloader_5230	:=	$(BOOTLOADER_LDSCRIPT_1SJ)

include platform/board/mcci/catena5230/mk/libmcci_bootloader_catena5230.mk
