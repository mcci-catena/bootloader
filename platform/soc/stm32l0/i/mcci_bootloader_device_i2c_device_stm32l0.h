/*

Module:	mcci_bootloader_device_i2c_device_stm32l0.h

Function:
	The device object for I2C devices for the STM32L0 (and compatible) controllers

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_i2c_device_stm32l0_h_
#define _mcci_bootloader_device_i2c_device_stm32l0_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_i2c_device_stm32l0_types_h_
# include "mcci_bootloader_device_i2c_device_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_device_h_
# include "mcci_bootloader_device_i2c_device.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct McciBootloaderDeviceI2cDeviceStm32l0_Contents_s
	{
	McciBootloaderDeviceI2cDevice_CONTENTS;

	/* currently we have no contents at this layer. */
	};

union McciBootloaderDeviceI2cDeviceStm32l0_u
	{
	McciBootloaderDeviceI2cDevice_UNION;

	McciBootloaderDeviceI2cDeviceStm32l0_Contents_t	Stm32l0;
	};

#define	McciBootloaderDeviceI2cDeviceStm32l0_CONTENTS	\
	McciBootloaderDeviceI2cDeviceStm32l0_Contents_t	Stm32l0

#define	McciBootloaderDeviceI2cDeviceStm32l0_UNION			\
	McciBootloaderDeviceI2cDeviceStm32l0_Contents_t	Stm32l0;	\
	McciBootloaderDeviceI2cDeviceStm32l0_t		Stm32l0Cast

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_device_stm32l0_h_ */
