/*

Module:	mcci_bootloader_device_i2c.h

Function:
	Common types for I2C work.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#ifndef _mcci_bootloader_device_i2c_h_
#define _mcci_bootloader_device_i2c_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_types_h_
# include "mcci_bootloader_device_i2c_types.h"
#endif

#ifndef _mcci_bootloader_device_h_
# include "mcci_bootloader_device.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

///
/// Result codes returned by any I2C-related driver. These are intended to be used both
/// by the bus driver and by the individual device drivers, and are intended to be
/// portable.
///
enum McciBootloaderDeviceI2cResult_e
	{
	McciBootloaderDeviceI2cResult_OK = 0,		///< No errors detected.
	McciBootloaderDeviceI2cResult_ArbitrationLost,	///< Lost arbitration, couldn't perform operation.
	McciBootloaderDeviceI2cResult_Timeout,		///< Operation timed out.
	McciBootloaderDeviceI2cResult_BusError,		///< A bus error occurred.
	McciBootloaderDeviceI2cResult_Nack,		///< A NACK was received.
	McciBootloaderDeviceI2cResult_InternalError,	///< An internal error occurrd; generallyh indicates a bug.
	McciBootloaderDeviceI2cResult_InvalidParameter,	///< A parameter to an API call was not valid.
	};

// typedef uint32_t McciBootloaderDeviceI2cResult_t;	-- in mcci_bootloader_device_i2c_types.h

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_i2c_h_ */
