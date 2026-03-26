##############################################################################
#
#	The stm32h7 library
#
##############################################################################

LIBRARIES += libmcci_bootloader_stm32h7

_ := platform/soc/stm32h7

CFLAGS_OPT_libmcci_bootloader_stm32h7 += -Os

INCLUDES_libmcci_bootloader_stm32h7 :=					\
	$(INCLUDES_libmcci_bootloader_cm7)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_stm32h7

SOURCES_libmcci_bootloader_stm32h7 :=					\
	$_/src/mccibootloader_stm32h7_prepareforlaunch.c		\
	$_/src/mccibootloader_stm32h7_systemflash.c			\
	$_/src/mccibootloader_stm32h7_systeminit.c			\
	$_/src/mccibootloaderplatform_stm32h7_checkimagevalid.c		\
	$_/src/mccibootloaderplatform_stm32h7_getappinfo.c		\
	$_/src/mccibootloaderplatform_stm32h7_getsignatureblock.c	\
	$_/src/mccibootloaderplatform_stm32h7_startapp.c		\
# end SOURCES_libmcci_bootloader_stm32h7

