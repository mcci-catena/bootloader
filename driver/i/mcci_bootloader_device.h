/*

Module:	mcci_bootloader_device.h

Function:
	Driver interface object for all portable drivers

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_h_
#define _mcci_bootloader_device_h_	/* prevent multiple includes */

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct McciBootloaderDeviceMethods_s
	{
	/// initialize the device -- implementation provided by
	/// concrete layer
	McciBootloaderDevice_BeginFn_t *pBegin;
	/// deinitialze the device -- implementatoin provided by
	/// concrete layer
	McciBootloaderDevice_EndFn_t *pEnd;
	};

typedef struct McciBootloaderDevice_Contents_s McciBootloaderDevice_Contents_t;

struct McciBootloaderDevice_Contents_s
	{
	/// pointer to device-level method table.
	const McciBootloaderDeviceMethods_t *pMethods;
	};

union McciBootloaderDevice_t
	{
	McciBootloaderDevice_Contents_t	Device;
	};

#define McciBootloaderDevice_CONTENTS	\
	McciBootloaderDevice_Contents_t	Device

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_h_ */
