/*

Module:	mcci_bootloader_device_i2c_common.h

Function:
	Common declarations for I2C device or bus drivers.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#ifndef _mcci_bootloader_device_i2c_common_h_
#define _mcci_bootloader_device_i2c_common_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_common_types_h_
# include "mcci_bootloader_device_i2c_common_types.h"
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
	McciBootloaderDeviceI2cResult_InternalError,	///< An internal error occurred; generally indicates a bug.
	McciBootloaderDeviceI2cResult_InvalidParameter,	///< A parameter to an API call was not valid.
	};

// typedef uint32_t McciBootloaderDeviceI2cResult_t;	-- in mcci_bootloader_device_i2c_common_types.h

///
/// Instance data for all I2C objects. This is derived from the basic
/// bootloader device abstract class, but is still abstract.
///
struct McciBootloaderDeviceI2c_Contents_s
	{
	McciBootloaderDevice_CONTENTS;
	};

/// Content macro for subclasses derived from McciBootloaderDeviceI2c_t
#define McciBootloaderDeviceI2c_CONTENTS		\
	McciBootloaderDeviceI2c_Contents_t		I2cCommon

///
/// Layout union for abstract McciBootloaderDeviceI2cDevice_t class objects.
///
union McciBootloaderDeviceI2c_u
	{
	McciBootloaderDevice_UNION;
	McciBootloaderDeviceI2c_Contents_t		I2cCommon;
	};

/// Macro for defining subclass unions derived frmo McciBootloaderDeviceI2cDevice_t
#define McciBootloaderDeviceI2c_UNION					\
	McciBootloaderDevice_UNION;					\
	McciBootloaderDeviceI2c_Contents_t		I2cCommon;	\
	McciBootloaderDeviceI2c_t			I2CommonCast

///
/// Supported i2c speeds
///
enum McciBootloaderDeviceI2cSpeed_e
	{
	McciBootloaderDeviceI2cSpeed_100k = 0,		///< 100kbps, "Standard Mode"
	McciBootloaderDeviceI2cSpeed_400k,		///< 400kbps, "Fast Mode"
	McciBootloaderDeviceI2cSpeed_1M,		///< 1Mbps, "Fast Mode Plus"
	McciBootloaderDeviceI2cSpeed__MAX,		///< Count of speeds defined.
	};

// typedef uint8_t McciBootloaderDeviceI2cSpeed_t;	-- in mcci_bootloader_device_i2c_common_types.h


MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_i2c_common_h_ */
