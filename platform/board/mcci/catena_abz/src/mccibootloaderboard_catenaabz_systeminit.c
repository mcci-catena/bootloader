/*

Module:	mccibootloaderboard_catenaabz_systeminit.c

Function:
	McciBootloaderBoard_CatenaABZ_SystemInit() and system init logic for
	MCCI Catenas based on Murata type-ABZ modules.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena_abz.h"

#include "mcci_bootloader_cm0plus_appimage.h"
#include "mcci_bootloader.h"
#include "mcci_bootloader_stm32l0.h"
#include "mcci_stm32l0xx.h"
#include "mcci_arm_cm0plus.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static void
McciBootloaderBoard_CatenaAbz_delayMs(uint32_t ms);

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

Name:	McciBootloaderBoard_CatenaAbz_systemInit()

Function:
	Initialize MCCI Catena based on Murata ABZ module for bootloader.

Definition:
	McciBootloaderPlatform_SystemInitFn_t
		McciBootloaderBoard_CatenaAbz_systemInit;

	void McciBootloaderBoard_CatenaAbz_systemInit(
		void
		);

Description:
	We set up the CPU for 32 MHz operation (using stm32l0 initialization).

	We then then enable GPIOs for the LED (pin PB2).

Returns:
	No explicit result.

Notes:
	

*/

void
McciBootloaderBoard_CatenaAbz_systemInit(
	void
	)
	{
	McciBootloader_Stm32L0_systemInit();

	// enable GPIO port B
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_IOPENR,
		MCCI_STM32L0_REG_RCC_IOPENR_IOPBEN
		);

	// set up GPIO port B2 as an output
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_MODER,
		MCCI_STM32L0_GPIO_MODE_P(2),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(
			MCCI_STM32L0_GPIO_MODE_P(2),
			MCCI_STM32L0_GPIO_MODE_OUT
			)
		);

	// clear B2
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_BRR,
		UINT32_C(1) << 2
		);

	// set B2 and clear it, so we can see things on a scope
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_BSRR,
		UINT32_C(1) << 2
		);
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_BRR,
		UINT32_C(1) << 2
		);
	}

static void
McciBootloaderBoard_CatenaAbz_delayMs(uint32_t ms)
	{
	for (++ms; ms > 0; --ms)
		{
		while ((McciArm_getReg(MCCI_CM0PLUS_SYSTICK_CSR) & MCCI_CM0PLUS_SYSTICK_CSR_COUNTFLAG) == 0)
			;
		}
	}

void
McciBootloaderBoard_CatenaAbz_fail(
	McciBootloaderError_t errorCode
	)
	{
	uint32_t rOdr = McciArm_getReg(MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_ODR);

	while (true)
		{
		// blink the led
		rOdr ^= UINT32_C(1) << 2;
		McciArm_putReg(MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_ODR, rOdr);
		McciBootloaderBoard_CatenaAbz_delayMs(100);
		}
	}

/**** end of mccibootloaderboard_catenaabz_systeminit.c ****/
