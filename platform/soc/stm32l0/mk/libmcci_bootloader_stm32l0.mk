##############################################################################
#
#	The stm32l0 library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_stm32l0.mk),)
_GUARD_libmcci_bootloader_stm32l0.mk := 1	# prevent multiple includes.

# pre-requisites
include platform/arch/cm0plus/mk/libmcci_bootloader_cm0plus.mk

LIBRARIES += libmcci_bootloader_stm32l0

_ := platform/soc/stm32l0

CFLAGS_OPT_libmcci_bootloader_stm32l0 += -Os

INCLUDES_libmcci_bootloader_stm32l0 :=					\
	$(INCLUDES_libmcci_bootloader_cm0plus)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_stm32l0

SOURCES_libmcci_bootloader_stm32l0 :=					\
	$_/src/mccibootloader_stm32l0_prepareforlaunch.c		\
	$_/src/mccibootloader_stm32l0_systemflash.c			\
	$_/src/mccibootloader_stm32l0_systeminit.c			\
# end SOURCES_libmcci_bootloader_stm32l0

endif # _GUARD_libmcci_bootloader_stm32l0.mk
