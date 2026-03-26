##############################################################################
#
#	The stm32l0 library
#
##############################################################################

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

