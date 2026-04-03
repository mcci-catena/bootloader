
##############################################################################
#
#	The stm32h7b3i_dk library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_stm32h7b3i_dk.mk),)
_GUARD_libmcci_bootloader_stm32h7b3i_dk.mk := 1	# prevent multiple includes.

# requirements
include platform/soc/stm32h7/mk/libmcci_bootloader_stm32h7.mk

# contents
LIBRARIES += libmcci_bootloader_stm32h7b3i_dk

_ := platform/board/st/stm32h7b3i_dk

CFLAGS_OPT_libmcci_bootloader_stm32h7b3i_dk += -Os

INCLUDES_libmcci_bootloader_stm32h7b3i_dk :=				\
	$(INCLUDES_libmcci_bootloader_stm32h7)				\
	$_/i								\
# end INCLUDES_libmcci_bootloader_stm32h7b3i_dk

SOURCES_libmcci_bootloader_stm32h7b3i_dk :=				\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_annunciator.c		\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_request.c		\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_platforminterface.c	\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_prepareforlaunch.c	\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_storage.c		\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_systeminit.c		\
	$_/src/mccibootloaderboard_stm32h7b3i_dk_vectors.c		\
# end SOURCES_libmcci_bootloader_stm32h7b3i_dk

endif # _GUARD_libmcci_bootloader_stm32h7b3i_dk.mk
