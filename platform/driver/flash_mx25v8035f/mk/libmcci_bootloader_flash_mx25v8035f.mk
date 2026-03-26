##############################################################################
#
#	The MX25V8035F flash library
#
##############################################################################

LIBRARIES += libmcci_bootloader_flash_mx25v8035f

_ := platform/driver/flash_mx25v8035f

CFLAGS_OPT_libmcci_bootloader_flash_mx25v8035f += -Os

INCLUDES_libmcci_bootloader_flash_mx25v8035f :=				\
	$(INCLUDES_libmcci_bootloader)					\
	$_/i								\
# end INCLUDES_libmcci_bootloader_flash_mx25v8035f

SOURCES_libmcci_bootloader_flash_mx25v8035f :=				\
	$_/src/mccibootloaderflash_mx25v8035f.c				\
# end SOURCES_libmcci_bootloader_flash_mx25v8035f

