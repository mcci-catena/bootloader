##############################################################################
#
#	The cm7 library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_cm7.mk),)
_GUARD_libmcci_bootloader_cm7.mk := 1	# prevent multiple includes.

# only one arch-type file can be included.
ifneq ($(_GUARD_CFLAGS_CPU),)
 $(error only one CPU architecture file can be included in a single make. Previous include: $(_GUARD_CFLAGS_CPU))
endif
_GUARD_CFLAGS_CPU := libmcci_bootloader_cm7.mk

# set CPU_FLAGS (but allow command-line overrides)
CFLAGS_CPU ?= 	-mcpu=cortex-m7 -mthumb

# requirements
include mk/libmcci_bootloader.mk

# contents
LIBRARIES += libmcci_bootloader_cm7

_ := platform/arch/cm7

CFLAGS_OPT_libmcci_bootloader_cm7 += -Os

INCLUDES_libmcci_bootloader_cm7 :=					\
	$(INCLUDES_libmcci_bootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_cm7

SOURCES_libmcci_bootloader_cm7 :=					\
	$_/src/mccibootloaderplatform_cm7_checkimagevalid.c		\
	$_/src/mccibootloaderplatform_cm7_getappinfo.c			\
	$_/src/mccibootloaderplatform_cm7_getsignatureblock.c		\
	$_/src/mccibootloaderplatform_cm7_startapp.c			\
# end SOURCES_libmcci_bootloader_cm7

endif # _GUARD_libmcci_bootloader_cm7.mk
