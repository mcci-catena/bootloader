##############################################################################
#
#	The 46xx bootloader
#
##############################################################################

BOOTLOADERS += McciBootloader_46xx

LIBS_McciBootloader_46xx :=				\
	${BOOTLOADER_LIBS_ABZ}				\
	${T_OBJDIR}/libmcci_bootloader_catena46xx.a	\
### end LIBS_McciBootloader_46xx

LDSCRIPT_McciBootloader_46xx	:=	$(BOOTLOADER_LDSCRIPT_ABZ)

