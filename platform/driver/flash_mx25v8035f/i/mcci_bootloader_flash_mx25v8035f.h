/*

Module:	mcci_bootloader_flash_mx25v8035f.h

Function:
	Driver interface for MX25V8035F flash chip

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_flash_mx25v8035f_h_
#define _mcci_bootloader_flash_mx25v8035f_h_	/* prevent multiple includes */

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_bootloader_platform_types_h_
# include "mcci_bootloader_platform_types.h"
#endif

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderFlash_Mx25v8035f_storageInit;

McciBootloaderPlatform_StorageReadFn_t
McciBootloaderFlash_Mx25v8035f_storageRead;

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_flash_mx25v8035f_h_ */
