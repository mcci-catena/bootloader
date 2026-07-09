/*

Module:	mcci_bootloader_device_i2c_bus_types.h

Function:
	Types for I2C bus driver

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_i2c_bus_types_h_
#define _mcci_bootloader_device_i2c_bus_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_common_types_h_
# include "mcci_bootloader_device_i2c_common_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_device_types_h_
# include "mcci_bootloader_device_i2c_device_types.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct McciBootloaderDeviceI2cBusMethods_s McciBootloaderDeviceI2cBusMethods_t;
typedef union McciBootloaderDeviceI2cBus_u McciBootloaderDeviceI2cBus_t;
typedef struct McciBootloaderDeviceI2cBus_Contents_s McciBootloaderDeviceI2cBus_Contents_t;

///
/// @brief read bytes from an I2C device connected to this bus.
///
/// @param [in] pBus	points to the bus object to be used for this transfer.
/// @param [in] pDevice points to the device; used for address and speed info.
/// @param [out] pBuffer points to the buffer to be filled with data.
/// @param [in] nBuffer  number of bytes to be read into pBuffer.
/// @param [out] pnActual  points to cell which will be set to actual byte count.
///
/// @returns
///	Status code. McciBootloaderDeviceI2cResult_OK for success, other values
///	for failure.
///
/// @details
///	The bus driver is entitled to access the portable fields and to upcast
///	the device object at pDevice to get to hardware specific details. We
///	assume that the bus driver and the device driver are implemented as a
///	pair.
///
typedef McciBootloaderDeviceI2cResult_t (McciBootloaderDeviceI2cBus_ReadFn_t)(
		McciBootloaderDeviceI2cBus_t *pBus,
		McciBootloaderDeviceI2cDevice_t *pDevice,
		uint8_t *pBuffer,
		size_t nBuffer,
		size_t *pnActual
		);

///
/// @brief write bytes to an I2C device connected to this bus.
///
/// @param [in] pBus	points to the bus object to be used for this transfer.
/// @param [in] pDevice points to the device; used for address and speed info.
/// @param [in] pBuffer points to the buffer to be filled with data.
/// @param [in] nBuffer  number of bytes to be read into pBuffer.
/// @param [out] pnActual  points to cell which will be set to actual byte count.
///
/// @returns
///	Status code. McciBootloaderDeviceI2cResult_OK for success, other values
///	for failure.
///
typedef McciBootloaderDeviceI2cResult_t (McciBootloaderDeviceI2cBus_WriteFn_t)(
		McciBootloaderDeviceI2cBus_t *pBus,
		McciBootloaderDeviceI2cDevice_t *pDevice,
		const uint8_t *pBuffer,
		size_t nBuffer,
		size_t *pnActual
		);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_bus_types_h_ */
