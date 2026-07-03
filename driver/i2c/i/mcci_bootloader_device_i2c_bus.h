/*

Module:	mcci_bootloader_device_i2c_bus.h

Function:
	Device object for an I2C bus ddriver

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_i2c_bus_h_
#define _mcci_bootloader_device_i2c_bus_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_bus_types_h_
# include "mcci_bootloader_device_i2c_bus_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_common_h_
# include "mcci_bootloader_device_i2c_common.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct McciBootloaderDeviceI2cBusMethods_s
	{
	McciBootloaderDeviceI2cBus_ReadFn_t	*pRead;
	McciBootloaderDeviceI2cBus_WriteFn_t	*pWrite;
	};

struct McciBootloaderDeviceI2cBus_Contents_s
	{
	McciBootloaderDeviceI2c_CONTENTS;

	const McciBootloaderDeviceI2cBusMethods_t *pMethods;
	};

#define McciBootloaderDeviceI2cBus_CONTENTS			\
	McciBootloaderDeviceI2cBus_Contents_t	Bus

union McciBootloaderDeviceI2cBus_u
	{
	McciBootloaderDeviceI2c_UNION;
	McciBootloaderDeviceI2cBus_Contents_t	I2cBus;
	};

#define McciBootloaderDeviceI2cBus_UNION			\
	McciBootloaderDeviceI2c_UNION;				\
	McciBootloaderDeviceI2cBus_Contents_t	I2cBus;		\
	McciBootloaderDeviceI2cBus_t		I2cBusCast

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_bus_h_ */
