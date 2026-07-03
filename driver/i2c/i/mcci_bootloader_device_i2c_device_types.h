/*

Module:	mcci_bootloader_device_i2c_device_types.h

Function:
	Types for i2c device connected via i2c bus

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_i2c_device_types_h_
#define _mcci_bootloader_device_i2c_device_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_types_h_
# include "mcci_bootloader_device_i2c_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

typedef struct McciBootloaderDeviceI2cDeviceMethods_s McciBootloaderDeviceI2cDeviceMethods_t;
typedef union McciBootloaderDeviceI2cDevice_u McciBootloaderDeviceI2cDevice_t;
typedef struct McciBootloaderDeviceI2cDevice_Contents_s McciBootloaderDeviceI2cDevice_Contents_t;

///
/// @brief read bytes from an I2C device.
///
/// @param [in] pI2cDevice indicates the device instance.
/// @param [out] pBuffer points to the buffer to be filled with data.
/// @param [in] nBuffer  number of bytes to be read into pBuffer.
/// @param [out] pnResult  points to cell which will be set to actual byte count.
///
/// @returns
///	Status code. McciBootloaderDeviceI2cResult_OK for success, other values
///	for failure.
///
typedef McciBootloaderDeviceI2cResult_t (McciBootloaderDeviceI2cDevice_ReadFn_t)(
		McciBootloaderDeviceI2cDevice_t *pI2cDevice,
		uint8_t *pBuffer,
		size_t nBuffer,
		size_t *pnResult
		);

///
/// @brief write bytes to an I2C device.
///
/// @param [in] pI2cDevice indicates the device instance.
/// @param [in] pBuffer points to the buffer to be filled with data.
/// @param [in] nBuffer  number of bytes to be read into pBuffer.
/// @param [out] pnResult  points to cell which will be set to actual byte count.
///
/// @returns
///	Status code. McciBootloaderDeviceI2cResult_OK for success, other values
///	for failure.
///
typedef McciBootloaderDeviceI2cResult_t (McciBootloaderDeviceI2cDevice_WriteFn_t)(
		McciBootloaderDeviceI2cDevice_t *pI2cDevice,
		const uint8_t *pBuffer,
		size_t nBuffer,
		size_t *pnResult
		);

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_i2c_device_types_h_ */
