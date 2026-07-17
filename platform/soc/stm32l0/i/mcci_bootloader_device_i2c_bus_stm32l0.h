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

struct McciBootloaderDeviceI2cBusStm32l0_Masks_s
	{
	/// @brief  base address of this channel.
	uint32_t	baseAddress;		///< base address of this i2c block.

	/// values for RCC_CCIPR control for this I2C block
	struct
		{
		uint32_t	mask;		///< mask of affected bits. zero means "not applicable for this block".
		uint32_t	value;		///< value to write to RCC_CCIPR in masked field.
		}	CCIPR_select;

	uint32_t	APB1ENR_mask;		///< bit mask of block-related bit in register MCCI_STM32L0_REG_RCC_APB1ENR
	uint32_t	APB1RSTR_mask;		///< bit mask of block-related bit in register MCCI_STM32L0_REG_RCC_APB1RSTR
	};

struct McciBootloaderDeviceI2cBusStm32l0_Contents_s
	{
	McciBootloaderDeviceI2cBus_CONTENTS;

	/// pointer to I2C channel-specific bit masks
	const McciBootloaderDeviceI2cBusStm32l0_Config_t *pConfig;
	uint32_t	timingr[McciBootloaderDeviceI2cSpeed__MAX];	///< timing register value to use for each speed
	};

union McciBootloaderDeviceI2cBusStm32l0_u
	{
	McciBootloaderDeviceI2cBus_UNION;
	McciBootloaderDeviceI2cBusStm32l0_Contents_t	Stm32l0;
	};

///
/// @brief Initialize an I2C bus controller driver on an STM32L0
///
/// @param pRamForBus 	Pointer to a block of RAM to be used for the driver instance data
/// @param sizeForBus 	Size of the block of RAM. The driver checks this against the required size
///			(must be >= sizeof(McciBootloaderDeviceI2cBusStm32l0_t))
/// @param pConfig 	Configuration of the I2C block; selects the controller, etc.
/// @param timingr100k 	Value to use in timing register for 100kHz I2C operations
/// @param timingr400k 	Value to use in timing register for 400kHz I2C operations,
///			or MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED
/// @param timingr1M 	Value to use in timing register for 1MHz I2C operations,
///			or MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED
///
/// @return pointer to initialized McciBootloaderDeviceI2cBus_t object.
///
/// @details
///	For simplicity, the details of the pin mapping for the I2C I/O pins is left
///	to the caller to control. Please set up the pins prior to using the bus.
///
///	This funcion does an implicit device begin on the initialized bus.
///
McciBootloaderDeviceI2cBus_t *
McciBootloader_Stm32L0Interface_initI2cBus(
	void *pRamForBus,
	size_t sizeForBus,
	const McciBootloaderDeviceI2cBusStm32l0_Config_t *pConfig,
	uint32_t timingr100k,
	uint32_t timingr400k,
	uint32_t timingr1M
	);

/// value to use for timing parameters when a speed is not supported.
#define	MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED	UINT32_C(0xFFFFFFFF)

///
/// value for 100k ("standard mode")
///
/// @details
///
/// |----------|-----------|-------------------------------|----------|
/// | Field    | Value     | Time                          | Comments |
/// |----------|-----------|-------------------------------|----------|
/// | `PRESC`  |   3       |  t_PRESC = 4 × 31.25 = 125 ns | free choice, keeps counts in 8 bits |
/// | `SCLL`   | 39 (0x27) | 40 x 125 = 5000 ns            | >= t_LOW min, 4.7 us |
/// | `SCLH`   | 39 (0x27) | 40 x 125 = 5000 ns            | >= t_HIGH min, 4.0 us |
/// | `SDADEL` | 2         | 2 x 125 = 250 ns              | >= ~156 ns (fall time - filter - 3*t_I2CCLK); <= 3.45 us max
/// | `SCLDEL` | 9         | 10 x 125 = 1250 ns            | >= t_r + t_SU DAT = 1000+ 250 |
///
/// Actual is about 95 kHz
///
#define MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_100K	UINT32_C(0x30922727)

///
/// value for 400k ("fast mode")
///
/// @details
///
/// |----------|-----------|-------------------------------|----------|
/// | Field    | Value     | Time                          | Comments |
/// |----------|-----------|-------------------------------|----------|
/// | `PRESC`  | 1         | t_PRESC = 2 × 31.25 = 62.5 ns | free choice |
/// | `SCLL`   | 20 (0x14) | 21 x 62.5 = 1312.5 ns         | >= t_LOW min, 1.3 us |
/// | `SCLH`   | 14 (0x0E) | 15 x 62.5 = 937.5 ns          | >= t_HIGH min, 0.6 us |
/// | `SDADEL` | 4         | 4 x 62.5 = 250 ns             | >= ~156 ns, <= 0.9 us |
/// | `SCLDEL` | 6         | 7 x 62.5 = 437.5 ns           | >= t_r + t_SU DAT = 400 ns |
///
/// Actual is approximately 388 kHz
///
#define MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_400K	UINT32_C(0x10640e14)

///
/// value for 1M ("fast mode plus")
///
/// @details
///
/// |----------|-----------|-------------------------------|----------|
/// | Field    | Value     | Time                          | Comments |
/// |----------|-----------|-------------------------------|----------|
/// | `PRESC`  | 0         | t_PRESC = 1 × 31.25 = 31.25 ns | free choice |
/// | `SCLL`   | 15 (0x0F) | 16 x 31.25 = 500 ns           | >= t_LOW min, 0.5 us |
/// | `SCLH`   | 9         | 10 x 31.25 = 312.5 ns         | >= t_HIGH min, 0.26 us |
/// | `SDADEL` | 0         | 0 ns                          | fast edges + analog filter cover hold time |
/// | `SCLDEL` | 5         | 6 x 31.25 = 187.5 ns          | >= t_r + t_SU DAT = 170 ns |
///
/// Actual is approximately 965 kHz
///
#define MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_1M		UINT32_C(0x0050090F)

extern const McciBootloaderDeviceI2cBusStm32l0_Config_t	gk_McciBootloaderDeviceI2cBusStm32l0_Config_I2c1;
extern const McciBootloaderDeviceI2cBusStm32l0_Config_t	gk_McciBootloaderDeviceI2cBusStm32l0_Config_I2c2;
extern const McciBootloaderDeviceI2cBusStm32l0_Config_t	gk_McciBootloaderDeviceI2cBusStm32l0_Config_I2c3;

///
/// @brief upcast from device to enclosing McciBootloaderDeviceI2cBusStm32l0_t
/// @param pDevice Pointer to device
/// @return pointer to enclosing object
///
/// @note
///	This is only safe to call when you know that the device is part of
///	a STM32L0 I2C Bus Controller driver instance.
///
static inline
McciBootloaderDeviceI2cBusStm32l0_t *
McciBootloaderDevice_getI2cBusStm32l0(
	McciBootloaderDevice_t *pDevice
	)
	{
	return (McciBootloaderDeviceI2cBusStm32l0_t *)pDevice;
	}

///
/// @brief upcast from i2c controller device to enclosing McciBootloaderDeviceI2cBusStm32l0_t
/// @param pDevice Pointer to i2c controller device
/// @return pointer to enclosing object
///
/// @note
///	This is only safe to call when you know that the device is part of
///	a STM32L0 I2C Bus Controller driver instance.
///
static inline
McciBootloaderDeviceI2cBusStm32l0_t *
McciBootloaderDeviceI2cBus_getI2cBusStm32l0(
	McciBootloaderDeviceI2cBus_t *pDevice
	)
	{
	return (McciBootloaderDeviceI2cBusStm32l0_t *)pDevice;
	}

bool McciBootloaderDeviceI2cBusStm32l0_attach(
	McciBootloaderDeviceI2cBusStm32l0_t *pBus,
	McciBootloaderDeviceI2cDeviceStm32l0_t *pDevice
	);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_bus_stm32l0_h_ */
