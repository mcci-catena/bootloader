/*

Module:	mcci_bootloader_device_i2c_common_types.h

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

#ifndef _mcci_bootloader_device_i2c_common_types_h_
#define _mcci_bootloader_device_i2c_common_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif

/****************************************************************************\
|
|	Scalar types and type handles.
|
\****************************************************************************/


MCCI_BOOTLOADER_BEGIN_DECLS

/// I2C bus address. Could be 10 bits someday, so we use a uint16_t.
typedef	uint16_t McciBootloaderDeviceI2cAddress_t;

///
/// \brief Error codes for the portable I2C driver API.
///
/// \note enum types don't have predictable width. So we declare this as
///	a `uint32_t`, and have a separate declaration for the enum.
///
/// \see McciBootloaderDeviceI2cResult_e
///
typedef uint32_t McciBootloaderDeviceI2cResult_t;

///
/// \brief Bus speed codes for the portable I2C driver API.
///
/// \note enum types don't have predictable width. So we declare this as
///	a `uint8_t`, and have a separate declaration for the enum.
///
/// \see McciBootloaderDeviceI2cSpeed_e
///
typedef uint8_t McciBootloaderDeviceI2cSpeed_t;

/// the abstract object for all i2c bus or device object.
typedef union McciBootloaderDeviceI2c_u McciBootloaderDeviceI2c_t;

/// the abstract contents for all i2c bus or device objects
typedef struct McciBootloaderDeviceI2c_Contents_s McciBootloaderDeviceI2c_Contents_t;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_i2c_common_types_h_ */
