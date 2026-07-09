/*

Module:	mccibootloaderboard_catena1sj_systeminit.c

Function:
	McciBootloaderBoard_Catena1sj_systemInit() and system init logic for
	MCCI Catenas based on Murata type-1SJ modules.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_board_catena_1sj.h"

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

/// the tick count for 1sj platforms
static volatile McciBootloader_Milliseconds_t s_tickCount;

/*

Name:	McciBootloaderBoard_Catena1sj_systemInit()

Function:
	Initialize MCCI Catena based on Murata 1SJ module for bootloader.

Definition:
	McciBootloaderPlatform_SystemInitFn_t
		McciBootloaderBoard_Catena1sj_systemInit;

	void McciBootloaderBoard_Catena1sj_systemInit(
		void
		);

Description:
	We set up the CPU for 32 MHz operation (using stm32l0 initialization).

	We then enable GPIOs for the LED (pin PB2).

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Catena1sj_systemInit(
	void
	)
	{
	McciBootloader_Stm32L0_systemInit();

	// enable GPIO port A & B
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_IOPENR,
		MCCI_STM32L0_REG_RCC_IOPENR_IOPAEN | MCCI_STM32L0_REG_RCC_IOPENR_IOPBEN
		);

	// set up GPIO port B2 as an output
	McciArm_putRegMasked(
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

void
McciBootloaderBoard_Catena1sj_setLed(void)
	{
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_BSRR,
		UINT32_C(1) << 2
		);
	}

void
McciBootloaderBoard_Catena1sj_clearLed(void)
	{
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_BRR,
		UINT32_C(1) << 2
		);
	}

void
McciBootloaderBoard_Catena1sj_delayMs(uint32_t ms)
	{
	// TODO(tmm@mcci.com): this won't really work if clock interrupts
	// are enabled. Condition this delay on "systick interrupts can happen";
	// use the loop if they cannot, watch s_tickCount if they can.
	for (++ms; ms > 0; --ms)
		{
		while ((McciArm_getReg(MCCI_CM0PLUS_SYSTICK_CSR) & MCCI_CM0PLUS_SYSTICK_CSR_COUNTFLAG) == 0)
			;

		++s_tickCount;
		}
	}

static void
delayTick(void)
	{
	McciBootloaderBoard_Catena1sj_delayMs(1);
	}

void
McciBootloaderBoard_Catena1sj_handleSysTick(void)
	{
	++s_tickCount;
	McciBootloaderBoard_Catena1sj_annunciatorHandleSysTick();
	}

McciBootloader_Milliseconds_t
McciBootloaderBoard_Catena1sj_getMilliseconds(void)
	{
	return s_tickCount;
	}

void
McciBootloaderBoard_Catena1sj_fail(
	McciBootloaderError_t errorCode
	)
	{
	if (errorCode == McciBootloaderError_BootloaderNotValid)
		// if the error is "corrupt boot loader", just do a fast blink.
		fastBlinkForever();
	else
		{
		// otherwise the bootloader is probably OK; display the error code for
		// 60 seconds, then attempt another reboot in case the problem was
		// transitory.
		unsigned timeToReboot;

		McciArm_disableInterrupts();

		// wait 60 seconds flashing error code before rebooting
		timeToReboot = 60 * 1000;

		// set the error code to be displayed
		McciBootloaderBoard_Catena1sj_annunciatorIndicateState(errorCode);

		// busy loop, flashing the code.
		for (; timeToReboot > 0; --timeToReboot)
			{
			delayTick();
			McciBootloaderBoard_Catena1sj_annunciatorHandleSysTick();
			}

		// make sure everything has gone out
		McciArm_DataSynchBarrier();

		// force a reset
		McciArm_putRegMasked(
			MCCI_CM0PLUS_SCB_AIRCR,
			MCCI_CM0PLUS_SCB_AIRCR_VECTKEY |
			MCCI_CM0PLUS_SCB_AIRCR_SYSRESETREQ,
			MCCI_CM0PLUS_SCB_AIRCR_VECTKEY_VALUE |
			MCCI_CM0PLUS_SCB_AIRCR_SYSRESETREQ
			);

		// make sure the reset gets to the register.
		McciArm_DataSynchBarrier();

		while (true)
			/* spin till reset */;
		}
	}

static void fastBlinkForever(void)
	{
	uint32_t rOdr = McciArm_getReg(MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_ODR);

	while (true)
		{
		// toggle the led
		rOdr ^= UINT32_C(1) << 2;
		McciArm_putReg(MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_ODR, rOdr);
		McciBootloaderBoard_Catena1sj_delayMs(100);
		}
	}

/**** end of mccibootloaderboard_catena1sj_systeminit.c ****/
