##############################################################################
#
#	The stm32h7b3i_dk bootloader
#
##############################################################################

BOOTLOADERS += McciBootloader_stm32h7b3i_dk

LIBS_McciBootloader_stm32h7b3i_dk :=			\
	${T_OBJDIR}/libmcci_bootloader_stm32h7.a	\
	${T_OBJDIR}/libmcci_bootloader_stm32h7b3i_dk.a	\
### end LIBS_McciBootloader_stm32h7b3i_dk

LDSCRIPT_McciBootloader_stm32h7b3i_dk := $(abspath platform/board/st/stm32h7b3i_dk/mk/mccibootloader.ld)

