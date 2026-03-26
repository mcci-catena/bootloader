##############################################################################
#
#	The core bootloader library
#
##############################################################################

#
# common library
#
LIBRARIES += libmcci_bootloader

SOURCES_libmcci_bootloader =				\
	src/mccibootloader_checkcodevalid.c		\
	src/mccibootloader_checkstorageimage.c		\
	src/mccibootloader_main.c			\
	src/mccibootloader_programandcheckflash.c	\
	platform/src/mccibootloaderplatform_entry.c	\
	platform/src/mccibootloaderplatform_fail.c	\
### end SOURCES_libmcci_bootloader

INCLUDES_libmcci_bootloader =				\
	i						\
	platform/i					\
	pkgsrc/mcci_arduino_development_kit_adk/src	\
	pkgsrc/mcci_tweetnacl/src			\
### end INCLUDES_libmcci_bootloader

CFLAGS_OPT_libmcci_bootloader ?= -Os

