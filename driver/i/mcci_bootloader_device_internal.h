/*

Module:	mcci_bootloader_device_internal.h

Function:
	Internal definitions for portable driver operations.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	July 2026

*/

#ifndef _mcci_bootloader_device_internal_h_
#define _mcci_bootloader_device_internal_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif


MCCI_BOOTLOADER_BEGIN_DECLS

///
/// @brief device method table.
///
/// These are not meant to be called directly, so the structure
/// is defiend in mcci_bootloader_device_internals.h,
/// rather than one of the API header files.
///
struct McciBootloaderDeviceMethods_s
	{
	/// initialize the device -- implementation provided by
	/// concrete layer
	McciBootloaderDevice_BeginFn_t *pBegin;
	/// deinitialze the device -- implementatoin provided by
	/// concrete layer
	McciBootloaderDevice_EndFn_t *pEnd;
	};

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_internal_h_ */
