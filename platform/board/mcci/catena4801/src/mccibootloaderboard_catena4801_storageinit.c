/*

Module:	mccibootloaderboard_catena4801_storageinit.c

Function:
	McciBootloaderBoard_Catena4801_storageInit()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena4801.h"

#include "mcci_bootloader_board_catena_abz.h"
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

static void
storagePowerOn(void)
	{
	// enable GPIOH
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_IOPENR,
		MCCI_STM32L0_REG_RCC_IOPENR_IOPHEN
		);

	// turn on power to the storage chip (4801) by making PH1 an output and
	// driving it to a one.
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOH + MCCI_STM32L0_GPIO_MODER,
		MCCI_STM32L0_GPIO_MODE_P(1),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(1), MCCI_STM32L0_GPIO_MODE_OUT)
		);

	McciArm_putRegOr(
		MCCI_STM32L0_REG_GPIOH + MCCI_STM32L0_GPIO_BSRR,
		MCCI_STM32L0_GPIO_BSRR_BS_P(1)
		);

	// delay 50 ms
	McciBootloaderPlatform_delayMs(50);
	}


void
McciBootloaderBoard_Catena4801_storageInit(
	void
	)
	{
	storagePowerOn();
	McciBootloaderPlatform_spiInit();
	McciBootloaderFlash_Mx25v8035f_storageInit();
	}


/**** end of mccibootloaderboard_catena4801_storageinit.c ****/
