##############################################################################
#
#	The 4801 bootloader
#
##############################################################################

BOOTLOADERS += McciBootloader_4801

LIBS_McciBootloader_4801 :=				\
	${BOOTLOADER_LIBS_ABZ}				\
	${T_OBJDIR}/libmcci_bootloader_catena4801.a	\
### end LIBS_McciBootloader_4801

LDSCRIPT_McciBootloader_4801	:=	$(BOOTLOADER_LDSCRIPT_ABZ)
