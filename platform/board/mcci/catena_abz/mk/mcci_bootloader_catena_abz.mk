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

