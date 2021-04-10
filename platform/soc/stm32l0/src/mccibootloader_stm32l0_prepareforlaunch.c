/*

Module:	mccibootloader_stm32l0_prepareforlaunch.c

Function:
	McciBootloader_Stm32l0_prepareForLaunch()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_stm32l0.h"

#include "mcci_stm32l0xx.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/



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

Name:	McciBootloader_Stm32L0_prepareForLaunch()

Function:
	Return the STM32L0 to suitable config prior to launching app.

Definition:
	void McciBootloader_Stm32L0_prepareForLaunch(
		void
		);

Description:
	Reset all the peripherals, and switch back to default MSI clock.

Returns:
	No explicit result.

Notes:
	We don't scrub every possible bit.

*/

void
McciBootloader_Stm32L0_prepareForLaunch(
	void
	)
	{
	// reset the low-level peripherals (just in case)
	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB1RSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB1RSTR, 0);

	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB2RSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB2RSTR, 0);

	McciArm_putReg(MCCI_STM32L0_REG_RCC_AHBRSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_AHBRSTR, 0);

	McciArm_putReg(MCCI_STM32L0_REG_RCC_IOPRSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_IOPRSTR, 0);

	// stop systick
	McciArm_putRegClear(
		MCCI_CM0PLUS_SYSTICK_CSR,
		(MCCI_CM0PLUS_SYSTICK_CSR_TICKINT |
		 MCCI_CM0PLUS_SYSTICK_CSR_ENABLE)
		);

	// reset things to defaults
	// scale MSI to 4194k
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_RCC_ICSCR,
		(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE),
		(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_4194k)
		);

	// make sure MSI is on
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_CR,
		 MCCI_STM32L0_REG_RCC_CR_MSION
		);

	// wait for it to come up.
	while (! (McciArm_getReg(MCCI_STM32L0_REG_RCC_CR) & MCCI_STM32L0_REG_RCC_CR_MSIRDY))
		;

	// switch to MSI
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CFGR,
		 MCCI_STM32L0_REG_RCC_CFGR_SW
		);

	/// wait for clock to switch
	while ((McciArm_getReg(MCCI_STM32L0_REG_RCC_CFGR) & MCCI_STM32L0_REG_RCC_CFGR_SWS) != MCCI_STM32L0_REG_RCC_CFGR_SWS_MSI)
		/* loop */;

	// turn off other oscillators
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CFGR,
		 MCCI_STM32L0_REG_RCC_CFGR_MCOPRE |
		 MCCI_STM32L0_REG_RCC_CFGR_MCOSEL |
		 MCCI_STM32L0_REG_RCC_CFGR_PPRE2 |
		 MCCI_STM32L0_REG_RCC_CFGR_PPRE1 |
		 MCCI_STM32L0_REG_RCC_CFGR_HPRE
		);

	// turn off HSI, HSE, PLL, etc.
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CR,
		 MCCI_STM32L0_REG_RCC_CR_PLLON |
		 MCCI_STM32L0_REG_RCC_CR_CSSHSEON |
		 MCCI_STM32L0_REG_RCC_CR_HSEON |
		 MCCI_STM32L0_REG_RCC_CR_HSI16DIVEN |
		 MCCI_STM32L0_REG_RCC_CR_HSI16ON
		);

	// turn off HSI48
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CRRCR,
		 MCCI_STM32L0_REG_RCC_CRRCR_HSI48ON
		);

	// now HSE is off so we can turn off HSEBYP
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CR,
		 MCCI_STM32L0_REG_RCC_CR_HSEBYP
		);

	// clear out the PLL stuff
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CFGR,
		 MCCI_STM32L0_REG_RCC_CFGR_PLLDIV |
		 MCCI_STM32L0_REG_RCC_CFGR_PLLMUL |
		 MCCI_STM32L0_REG_RCC_CFGR_PLLSRC
		);

	McciArm_putReg(
		MCCI_STM32L0_REG_RCC_CIER,
		0
		);

	// Set ACR back to reset state: pre-read disabled, read buf enable,
	// run mode == IDLE, RUN_PD == IDLE SLEEP_PD == IDLE, prefetch disabled,
	// zero wait state. And this also locks the RUN_PD bit.
	McciArm_putRegClear(
		MCCI_STM32L0_REG_FLASH_ACR,
		 MCCI_STM32L0_REG_FLASH_ACR_DISAB_BUF |
		 MCCI_STM32L0_REG_FLASH_ACR_PRE_READ |
		 MCCI_STM32L0_REG_FLASH_ACR_RUN_PD |
		 MCCI_STM32L0_REG_FLASH_ACR_SLEEP_PD |
		 MCCI_STM32L0_REG_FLASH_ACR_PRFTEN |
		 MCCI_STM32L0_REG_FLASH_ACR_LATENCY
		);
	}

/**** end of mccibootloader_stm32l0_prepareforlaunch.c ****/
