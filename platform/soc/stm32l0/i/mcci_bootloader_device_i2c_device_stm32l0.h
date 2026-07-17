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

MCCI_BOOTLOADER_BEGIN_DECLS

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

///
/// @brief upcast from device to enclosing McciBootloaderDeviceI2cDeviceStm32l0_t
/// @param pDevice Pointer to device
/// @return pointer to enclosing object
///
/// @note
///	This is only safe to call when you know that the device is part of
///	a STM32L0 I2C Bus Controller driver instance.
///
static inline
McciBootloaderDeviceI2cDeviceStm32l0_t *
McciBootloaderDevice_getI2cDeviceStm32l0(
	McciBootloaderDevice_t *pDevice
	)
	{
	return (McciBootloaderDeviceI2cDeviceStm32l0_t *)pDevice;
	}

///
/// @brief upcast from i2c controller device to enclosing McciBootloaderDeviceI2cDeviceStm32l0_t
/// @param pDevice Pointer to i2c controller device
/// @return pointer to enclosing object
///
/// @note
///	This is only safe to call when you know that the device is part of
///	a STM32L0 I2C Bus Controller driver instance.
///
static inline
McciBootloaderDeviceI2cDeviceStm32l0_t *
McciBootloaderDeviceI2cDevice_getI2cDeviceStm32l0(
	McciBootloaderDeviceI2cDevice_t *pDevice
	)
	{
	return (McciBootloaderDeviceI2cDeviceStm32l0_t *)pDevice;
	}



MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_i2c_device_stm32l0_h_ */
