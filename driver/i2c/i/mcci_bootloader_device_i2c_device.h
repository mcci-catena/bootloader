/*

Module:	mcci_bootloader_device_i2c_device.h

Function:
	McciBootloaderDeviceI2cDevice_t, etc.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_i2c_device_h_
#define _mcci_bootloader_device_i2c_device_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_device_types_h_
# include "mcci_bootloader_device_i2c_device_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_bus_types_h_
# include "mcci_bootloader_device_i2c_bus_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_h_
# include "mcci_bootloader_device_i2c.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

///
/// Method table for I2C Device instances
///
struct McciBootloaderDeviceI2cDeviceMethods_s
	{
	McciBootloaderDeviceI2cDevice_ReadFn_t	*pRead;
	McciBootloaderDeviceI2cDevice_WriteFn_t	*pWrite;
	};

///
/// Instance data for I2C devices. This is derived from the basic
/// bootloader device abstract class, but is still abstract.
///
struct McciBootloaderDeviceI2cDevice_Contents_s
	{
	McciBootloaderDevice_CONTENTS;

	/// the method table
	const McciBootloaderDeviceI2cDeviceMethods_t *pMethods;
	/// bus that controls this device.
	McciBootloaderDeviceI2cBus_t		*pBus;
	/// the 7-bit address of the target device, right justified
	uint8_t					bAddress;
	};

/// Content macro for subclasses derived from McciBootloaderDeviceI2cDevice_t
#define McciBootloaderDeviceI2cDevice_CONTENTS		\
	McciBootloaderDeviceI2cDevice_Contents_t	I2cDevice

///
/// Layout union for abstract McciBootloaderDeviceI2cDevice_t class objects.
///
union McciBootloaderDeviceI2cDevice_u
	{
	McciBootloaderDevice_UNION;
	McciBootloaderDeviceI2cDevice_Contents_t	I2cDevice;
	};

/// Macro for defining subclass unions derived frmo McciBootloaderDeviceI2cDevice_t
#define McciBootloaderDeviceI2cDevice_UNION				\
	McciBootloaderDevice_UNION;					\
	McciBootloaderDeviceI2cDevice_Contents_t	I2cDevice;	\
	McciBootloaderDeviceI2cDevice_t			I2cDeviceCast

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_i2c_device_h_ */
