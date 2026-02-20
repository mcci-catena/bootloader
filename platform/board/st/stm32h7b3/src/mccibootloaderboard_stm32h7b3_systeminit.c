/*

Module:	mccibootloaderboard_stm32h7b3_systeminit.c

Function:
	McciBootloaderBoard_Stm32h7b3_systemInit() and system init logic for
	STM32H7B3 boards

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#include "mcci_bootloader_board_stm32h7b3.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_stm32h7.h"
#include "mcci_stm32h7xx.h"
#include "mcci_arm_cm7.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

#ifndef	MCCI_BOOTLOADER_LED_GPIO	/* PARAM */
# define MCCI_BOOTLOADER_LED_GPIO	MCCI_STM32H7_REG_GPIOI
#endif

#ifndef	MCCI_BOOTLOADER_LED_GPIO_PIN	/* PARAM */
# define MCCI_BOOTLOADER_LED_GPIO_PIN	3
#endif

MCCI_BOOTLOADER_NORETURN_PFX
static void
fastBlinkForever(void)
	MCCI_BOOTLOADER_NORETURN_SFX;

static void
delayTick(void);

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

Name:	McciBootloaderBoard_Stm32h7b3_systemInit()

Function:
	Initialize STM32H7B3 module for bootloader.

Definition:
	McciBootloaderPlatform_SystemInitFn_t
		McciBootloaderBoard_Stm32h7b3_systemInit;

	void McciBootloaderBoard_Stm32h7b3_systemInit(
		void
		);

Description:
	We set up the CPU for reset state.

	We then then enable GPIOs for the LED (pin PI3) and initiaize SysTick.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Stm32h7b3_systemInit(
	void
	)
	{
	McciBootloader_Stm32h7_systemInit();

	// enable GPIO port I
	McciArm_putRegOr(
		MCCI_STM32H7_REG_RCC_AHB4ENR,
		MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOIEN
		);

	// set up GPIO port I3 as low speed
	McciArm_putRegMasked(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_OSPEEDR,
		MCCI_STM32H7_GPIO_OSPEED_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(
			MCCI_STM32H7_GPIO_OSPEED_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
			MCCI_STM32H7_GPIO_OSPEED_LOW
			)
		);

	// set up GPIO port I3 as an output type push-pull
	McciArm_putRegMasked(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_OTYPER,
		MCCI_STM32H7_GPIO_OTYPE_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(
			MCCI_STM32H7_GPIO_OTYPE_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
			MCCI_STM32H7_GPIO_OTYPE_PP
			)
		);

	// set up GPIO port I3 as no pull
	McciArm_putRegMasked(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_PUPDR,
		MCCI_STM32H7_GPIO_PUPD_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(
			MCCI_STM32H7_GPIO_PUPD_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
			MCCI_STM32H7_GPIO_PUPD_NONE
			)
		);

	// set up GPIO port I3 as output
	McciArm_putRegMasked(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_MODER,
		MCCI_STM32H7_GPIO_MODE_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
		MCCI_BOOTLOADER_FIELD_SET_VALUE(
			MCCI_STM32H7_GPIO_MODE_P(MCCI_BOOTLOADER_LED_GPIO_PIN),
			MCCI_STM32H7_GPIO_MODE_OUT
			)
		);

	// clear I3
	McciArm_putReg(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_BSRR,
		MCCI_STM32H7_GPIO_BSRR_BR_P(MCCI_BOOTLOADER_LED_GPIO_PIN)
		);

	// set I3 and clear it, so we can see things on a scope
	McciArm_putReg(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_BSRR,
		MCCI_STM32H7_GPIO_BSRR_BS_P(MCCI_BOOTLOADER_LED_GPIO_PIN)
		);
	McciArm_putReg(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_BSRR,
		MCCI_STM32H7_GPIO_BSRR_BR_P(MCCI_BOOTLOADER_LED_GPIO_PIN)
		);

	// init SysTick
	McciArm_putReg(
		MCCI_CM7_SYSTICK_RVR,
		(64000000 / 1000)	/* system clock is 64MHz */
		);
	McciArm_putReg(MCCI_CM7_SYSTICK_CVR, 0);
	McciArm_putReg(
		MCCI_CM7_SYSTICK_CSR,
		MCCI_CM7_SYSTICK_CSR_CLKSOURCE |
		MCCI_CM7_SYSTICK_CSR_TICKINT |
		MCCI_CM7_SYSTICK_CSR_ENABLE
		);
	McciArm_putRegOr(
		MCCI_STM32H7_REG_RCC_APB4ENR,
		MCCI_STM32H7_REG_RCC_APB4ENR_SYSCFGEN
		);
	}

void
McciBootloaderBoard_Stm32h7b3_setLed(void)
	{
	McciArm_putReg(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_BSRR,
		MCCI_STM32H7_GPIO_BSRR_BS_P(MCCI_BOOTLOADER_LED_GPIO_PIN)
		);
	}

void
McciBootloaderBoard_Stm32h7b3_clearLed(void)
	{
	McciArm_putReg(
		MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_BSRR,
		MCCI_STM32H7_GPIO_BSRR_BR_P(MCCI_BOOTLOADER_LED_GPIO_PIN)
		);
	}

void
McciBootloaderBoard_Stm32h7b3_delayMs(uint32_t ms)
	{
	for (++ms; ms > 0; --ms)
		{
		while ((McciArm_getReg(MCCI_CM7_SYSTICK_CSR) &
			MCCI_CM7_SYSTICK_CSR_COUNTFLAG) == 0)
			;
		}
	}

static void
delayTick(void)
	{
	while ((McciArm_getReg(MCCI_CM7_SYSTICK_CSR) &
		MCCI_CM7_SYSTICK_CSR_COUNTFLAG) == 0)
		;
	}

void
McciBootloaderBoard_Stm32h7b3_fail(
	McciBootloaderError_t errorCode
	)
	{
	if (errorCode == McciBootloaderError_BootloaderNotValid)
		{
		fastBlinkForever();
		}
	else
		{
		unsigned timeToReboot;

		McciArm_disableInterrupts();
		timeToReboot = 60 * 1000;

		McciBootloaderBoard_Stm32h7b3_annunciatorIndicateState(errorCode);

		for (; timeToReboot > 0; --timeToReboot)
			{
			delayTick();
			McciBootloaderBoard_Stm32h7b3_handleSysTick();
			}

		McciArm_DataSynchBarrier();

		McciArm_putRegMasked(
			MCCI_CM7_SCB_AIRCR,
			MCCI_CM7_SCB_AIRCR_VECTKEY |
			MCCI_CM7_SCB_AIRCR_SYSRESETREQ,
			MCCI_CM7_SCB_AIRCR_VECTKEY_VALUE |
			MCCI_CM7_SCB_AIRCR_SYSRESETREQ
			);

		McciArm_DataSynchBarrier();
		while (true)
			/* spin till reset */;
		}
	}

static void fastBlinkForever(void)
	{
	uint32_t rOdr;

	rOdr = McciArm_getReg(MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_ODR);
	while (true)
		{
		// blink the led
		rOdr ^= UINT32_C(1) << MCCI_BOOTLOADER_LED_GPIO_PIN;
		McciArm_putReg(
			MCCI_BOOTLOADER_LED_GPIO + MCCI_STM32H7_GPIO_ODR,
			rOdr
			);
		McciBootloaderBoard_Stm32h7b3_delayMs(100);
		}
	}

/**** end of mccibootloaderboard_stm32h7b3_systeminit.c ****/
