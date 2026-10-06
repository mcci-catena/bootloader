/*

Module:	mccibootloaderboard_catena5220_storageinit.c

Function:
	McciBootloaderBoard_Catena5220_storageInit()

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Pranau Ravikumar, MCCI Corporation	September 2026

*/

#include "mcci_bootloader_board_catena5220.h"

#include "mcci_bootloader_flash_mx25v8035f.h"
#include "mcci_stm32l0xx.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static void
storagePowerOn(void);

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/



/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

/*

Name:	storagePowerOn()

Function:
	Turn on the VOUT1 load switch that powers the flash and FRAM.

Description:
	On the Catena 5220, VOUT1 (which powers the SPI flash and the FRAM)
	is gated by a TPS22960 load switch, enabled by PA7 (D10). There is no
	PMIC on this board -- the enable line is a plain GPIO, driven directly
	by the bootloader.

	The TPS22960's internal soft-start limits the output rise time to
	well under 1 ms; we wait 50 ms for margin (matching the analogous
	delay used for the 4801's regulator) before touching the bus.

Returns:
	No explicit result.

*/

static void
storagePowerOn(void)
	{
	// enable GPIOA
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_IOPENR,
		MCCI_STM32L0_REG_RCC_IOPENR_IOPAEN
		);

	// make PA7 an output.
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_MODER,
		MCCI_STM32L0_GPIO_MODE_P(7),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(7), MCCI_STM32L0_GPIO_MODE_OUT)
		);

	// drive PA7 (D10 / ON1) high to enable VOUT1.
	McciArm_putRegOr(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_BSRR,
		MCCI_STM32L0_GPIO_BSRR_BS_P(7)
		);

	// delay 50 ms for VOUT1 to come up.
	McciBootloaderPlatform_delayMs(50);
	}

void
McciBootloaderBoard_Catena5220_storageInit(
	void
	)
	{
	storagePowerOn();
	McciBootloaderPlatform_spiInit();
	McciBootloaderFlash_Mx25v8035f_storageInit();
	}


/**** end of mccibootloaderboard_catena5220_storageinit.c ****/
