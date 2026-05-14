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

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct McciBootloaderDeviceI2cBusMethods_s McciBootloaderDeviceI2cBusMethods_t;
typedef union McciBootloaderDeviceI2cBus_u McciBootloaderDeviceI2cBus_t;
typedef struct McciBootloaderDeviceI2cBus_Contents_s McciBootloaderDeviceI2cBus_Contents_t;

typedef bool (McciBootloaderDeviceI2cBus_ReadFn_t)(McciBootloaderDeviceI2cBus_t *, uint8_t bAddress, uint8_t *pValue, size_t nValue);
typedef bool (McciBootloaderDeviceI2cBus_WriteFn_t)(McciBootloaderDeviceI2cBus_t *, uint8_t bAddress, const uint8_t *pValue, size_t nValue);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_bus_types_h_ */
