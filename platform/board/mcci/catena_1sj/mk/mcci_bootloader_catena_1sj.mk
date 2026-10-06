##############################################################################
#
#	The board settings -- gives the path to the link scripts etc
#
##############################################################################

ifeq ($(_GUARD_mcci_bootloader_catena_1sj.mk),)
_GUARD_mcci_bootloader_catena_1sj.mk := 1	# prevent multiple includes.

BOOTLOADER_LDSCRIPT_1SJ := $(abspath platform/board/mcci/catena_1sj/mk/mccibootloader_1sj.ld)

BOOTLOADER_LIBS_1SJ :=	\
	${T_OBJDIR}/libmcci_bootloader_cm0plus.a	\
	${T_OBJDIR}/libmcci_bootloader_stm32l0.a	\
	${T_OBJDIR}/libmcci_bootloader_catena_1sj.a	\
	${T_OBJDIR}/libmcci_bootloader_flash_mx25v8035f.a \
# end BOOTLOADER_LIBS_1SJ

endif # _GUARD_mcci_bootloader_catena_1sj.mk
