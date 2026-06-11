/*

Module:	mcci_bootloader_device_spi_bus_stm32l0.h

Function:
	MccBootloaderDeviceSpiBusStm32l0_t

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_spi_bus_stm32l0_h_
#define _mcci_bootloader_device_spi_bus_stm32l0_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_spi_bus_stm32l0_types_h_
# include "mcci_bootloader_device_spi_bus_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_spi_device_stm32l0_types_h_
# include "mcci_bootloader_device_spi_device_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_spi_bus_h_
# include "mcci_bootloader_device_spi_bus.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct McciBootloaderDeviceSpiBusStm32l0_Contents_s
	{
	McciBootloaderDeviceSpiBus_CONTENTS;

	uint32_t	baseAddress;
	uint32_t	timingr;
	};

union McciBootloaderDeviceSpiBusStm32l0_u
	{
	McciBootloaderDeviceSpiBus_UNION;
	McciBootloaderDeviceSpiBusStm32l0_Contents_t	Stm32l0;
	};

McciBootloaderDeviceSpiBus_t *
McciBootloader_Stm32L0Interface_initSpiBus(
	void *pRamForBus,
	size_t sizeForBus,
	uint32_t baseAddress,
	uint32_t timingr115k,
	uint32_t timingr400k,
	uint32_t timingr1m
	);

bool McciBootloaderDeviceSpiBusStm32l0_attach(
	McciBootloaderDeviceSpiBusStm32l0_t *pBus,
	McciBootloaderDeviceSpiDeviceStm32l0_t *pDevice
	);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_spi_bus_stm32l0_h_ */
