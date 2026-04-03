##############################################################################
#
#	The cm0plus library
#
##############################################################################

ifeq ($(_GUARD_libmcci_bootloader_cm0plus.mk),)
_GUARD_libmcci_bootloader_cm0plus.mk := 1	# prevent multiple includes.

# only one arch-type file can be included.
ifneq ($(_GUARD_CFLAGS_CPU),)
 $(error only one CPU architecture file can be included in a single make. Previous include: $(_GUARD_CFLAGS_CPU))
endif
_GUARD_CFLAGS_CPU := libmcci_bootloader_cm0plus.mk

# set CPU_FLAGS (but allow command-line overrides)
CFLAGS_CPU ?= 	-mcpu=cortex-m0plus -mthumb

# requirements
include mk/libmcci_bootloader.mk

# contents
LIBRARIES += libmcci_bootloader_cm0plus

_ := platform/arch/cm0plus

CFLAGS_OPT_libmcci_bootloader_cm0plus += -Os

INCLUDES_libmcci_bootloader_cm0plus :=					\
	$(INCLUDES_libmcci_bootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_cm0plus

SOURCES_libmcci_bootloader_cm0plus :=					\
	$_/src/mccibootloaderplatform_checkimagevalid.c			\
	$_/src/mccibootloaderplatform_getappinfo.c			\
	$_/src/mccibootloaderplatform_getsignatureblock.c		\
	$_/src/mccibootloaderplatform_startapp.c			\
# end SOURCES_libmcci_bootloader_cm0plus

endif # _GUARD_libmcci_bootloader_cm0plus.mk
