/*

Module:	mcci_bootloader_device_i2c_bus_stm32l0.h

Function:
	MccBootloaderDeviceI2cBusStm32l0_t

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_i2c_bus_stm32l0_h_
#define _mcci_bootloader_device_i2c_bus_stm32l0_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_bus_stm32l0_types_h_
# include "mcci_bootloader_device_i2c_bus_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_device_stm32l0_types_h_
# include "mcci_bootloader_device_i2c_device_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_bus_h_
# include "mcci_bootloader_device_i2c_bus.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct McciBootloaderDeviceI2cBusStm32l0_Contents_s
	{
	McciBootloaderDeviceI2cBus_CONTENTS;

	uint32_t	baseAddress;
	uint32_t	timingr;
	};

union McciBootloaderDeviceI2cBusStm32l0_u
	{
	McciBootloaderDeviceI2cBus_UNION;
	McciBootloaderDeviceI2cBusStm32l0_Contents_t	Stm32l0;
	};

bool McciBootloaderDeviceI2cBusStm32l0_attach(
	McciBootloaderDeviceI2cBusStm32l0_t *pBus,
	McciBootloaderDeviceI2cDeviceStm32l0_t *pDevice
	);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_bus_stm32l0_h_ */
