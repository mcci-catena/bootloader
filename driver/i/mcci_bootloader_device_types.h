/*

Module:	mcci_bootloader_device_types.h

Function:
	Device interface types for all portable drivers

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_types_h_
#define _mcci_bootloader_device_types_h_	/* prevent multiple includes */

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (McciBootloaderDevice_BeginFn_t)();
typedef bool (McciBootloaderDevice_EndFn_t)();

typedef struct McciBootloaderDeviceMethods_s McciBootloaderDeviceMethods_t;

typedef union McciBootloaderDevice_u McciBootloaderDevice_t;

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_types_h_ */
