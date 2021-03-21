/*

Module:	mccibootloader_stm32l0_systeminit.c

Function:
	McciBootloader_Stm32L0_systemInit()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "include file declaring exports.h"

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

Name:	McciBootloader_Stm32L0_systemInit()

Function:
	Configure STM32L0 core for MCCI bootloader

Definition:
	void McciBootloader_Stm32L0_systemInit(
		void
		);

Description:
	Configure the STM32L0 core to run at 32 MHz, with the other
	clocks configured in a suitable default way. Set up SYSTICK
	to roll over every MS.  Enable HSI16 clock, PLL, LSE.

Returns:
	No explicit result.

Notes:
	Assumes we have a 32 kHz crystal for the LSE clock.

*/

#define FUNCTION "McciBootloader_Stm32L0_systemInit"

void
McciBootloader_Stm32L0_systemInit(void)
	{
	// reset things to defaults
	// make sure MSI is on
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_CR,
		 MCCI_STM32L0_REG_RCC_CR_MSION
		);

	// switch to MSI, and turn off other oscillators
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_CFGR,
		 MCCI_STM32L0_REG_RCC_CFGR_MCOPRE |
		 MCCI_STM32L0_REG_RCC_CFGR_MCOSEL |
		 MCCI_STM32L0_REG_RCC_CFGR_PPRE2 |
		 MCCI_STM32L0_REG_RCC_CFGR_PPRE1 |
		 MCCI_STM32L0_REG_RCC_CFGR_HPRE |
		 MCCI_STM32L0_REG_RCC_CFGR_SW
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

	// presumably we got here via the boot vector, but load the
	// vector table anyway
	McciArm_putReg(
		MCCI_CM0PLUS_SCB_VTOR,
		(uint32_t) &gk_McciBootloader_CortexVectors
		);

	// enable pre-read, pre-fetch,
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_FLASH_ACR,
		 MCCI_STM32L0_REG_FLASH_ACR_DISAB_BUF,
		 MCCI_STM32L0_REG_FLASH_ACR_PRE_READ |
		 MCCI_STM32L0_REG_FLASH_ACR_PRFTEN
		);

	// reset the low-level peripherals (just in case)
	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB1RSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB1RSTR, 0);

	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB2RSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_APB2RSTR, 0);

	McciArm_putReg(MCCI_STM32L0_REG_RCC_AHBRSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_AHBRSTR, 0);

	McciArm_putReg(MCCI_STM32L0_REG_RCC_IOPRSTR, ~UINT32_C(0));
	McciArm_putReg(MCCI_STM32L0_REG_RCC_IOPRSTR, 0);

	// check clock state
	const uint32_t rCfgr = McciArm_getReg(MCCI_STM32L0_REG_RCC_CFGR);
	if ((rCfgr & MCCI_STM32L0_REG_RCC_CFGR_SW) != MCCI_STM32L0_REG_RCC_CFGR_SW_MSI)
		McciBootloaderPlatform_fail(McciBootloaderError_ResetClockNotValid);

	// we probably need to turn on the clock to the power register
	bool const turnOnPWR = !(McciArm_getReg(MCCI_STM32L0_REG_RCC_APB1ENR) & MCCI_STM32L0_REG_RCC_APB1ENR_PWREN);
	if (turnOnPWR)
		McciArm_putRegOr(MCCI_STM32L0_REG_RCC_APB1ENR, MCCI_STM32L0_REG_RCC_APB1ENR_PWREN);

	// set up the clock -- set regulator to allow 32 MHz
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_PWR_CR,
		MCCI_STM32L0_REG_PWR_CR_VOS,
		MCCI_STM32L0_REG_PWR_CR_VOS_1V8
		);
	
	// turn on HSI
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_CR,
		MCCI_STM32L0_REG_RCC_CR_HSI16ON
		);

	// wait for it to come up.
	while (! (McciArm_getReg(MCCI_STM32L0_REG_RCC_CR) & MCCI_STM32L0_REG_RCC_CR_HSI16RDYF))
		;

	// set the calibration value
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_RCC_ICSCR,
		MCCI_STM32L0_REG_RCC_ICSCR_HSI16TRIM,
		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_HSI16TRIM, 18)
		);

	// get access to the backup domain
	bool const enableDbp = ! (McciArm_getReg(MCCI_STM32L0_REG_PWR_CR) & MCCI_STM32L0_REG_PWR_CR_DBP);
	if (enableDbp)
		{
		McciArm_putRegOr(MCCI_STM32L0_REG_PWR_CR, MCCI_STM32L0_REG_PWR_CR_DBP);
		while (! (McciArm_getReg(MCCI_STM32L0_REG_PWR_CR) & MCCI_STM32L0_REG_PWR_CR_DBP))
			/* wait */;
		}

	// turn on the LSE clock
	McciArm_orReg(MCCI_STM32L0_REG_RCC_CSR, MCCI_STM32L0_REG_RCC_CSR_LSEON);

	// wait for it to come up.
	while (! (McciArm_getReg(MCCI_STM32L0_REG_RCC_CSR) & MCCI_STM32L0_REG_RCC_CSR_LSERDY))
		/* loop */;

	// release backup domain
	if (enableDbp)
		{
		McciArm_putRegClear(MCCI_STM32L0_REG_PWR_CR, MCCI_STM32L0_REG_PWR_CR_DBP);
		}

	// set up the PLL to get us to 32 MHz. It's off, but make sure
	while (McciArm_getReg(MCCI_STM32L0_REG_RCC_CR) & MCCI_STM32L0_REG_RCC_CR_PLLRDY)
		/* loop */;

	// set PLL to 2x HSI == 32 MHz
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_RCC_CFGR,
		(MCCI_STM32L0_REG_RCC_CFGR_PLLDIV |
		 MCCI_STM32L0_REG_RCC_CFGR_PLLMUL |
		 MCCI_STM32L0_REG_RCC_CFGR_PLLSRC),
		(MCCI_STM32L0_REG_RCC_CFGR_PLLDIV_2 |
		 MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_4 |
		 MCCI_STM32L0_REG_RCC_CFGR_PLLSRC_HSI16)
		);
	
	// enable the PLL
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_CR,
		MCCI_STM32L0_REG_RCC_CR_PLLON
		);

	// wait for it to come up.
	while (! (McciArm_getReg(MCCI_STM32L0_REG_RCC_CR) & MCCI_STM32L0_REG_RCC_CR_PLLRDY))
		;

	//---- now that oscillators are configured and ready, change clock sources ----
	// set flash latency to one wait state
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_FLASH_ACR,
		MCCI_STM32L0_REG_FLASH_ACR_LATENCY,
		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_ACR_LATENCY, 1)
		);

	// initialize *HCLK, SYSCLK, PCLK1, PCLK2
	// HPRE is zero from above.

	// initialize HCLK, *SYSCLK, PCLK1, PCLK2
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_RCC_CFGR,
		MCCI_STM32L0_REG_RCC_CFGR_SW,
		MCCI_STM32L0_REG_RCC_CFGR_SW_PLL
		);

	/// wait for clock to switch
	while ((McciArm_getReg(MCCI_STM32L0_REG_RCC_CFGR) & MCCI_STM32L0_REG_RCC_CFGR_SWS) != MCCI_STM32L0_REG_RCC_CFGR_SWS_PLL)
		/* loop */;

	// divisors for PCLK1, PCLK2 are initially 1 from above
	// set up systick, as we may need it; set for 1 ms ticks
	McciArm_putReg(MCCI_CM0PLUS_SYSTICK_RVR, (UINT32_C(32)*1000*1000)/1000 - 1);
	McciArm_putReg(MCCI_CM0PLUS_SYSTICK_CVR, 0);
	McciArm_putReg(
		MCCI_CM0PLUS_SYSTICK_CSR,
		(MCCI_CM0PLUS_SYSTICK_CSR_CLKSOURCE |
		 MCCI_CM0PLUS_SYSTICK_CSR_TICKINT |
		 MCCI_CM0PLUS_SYSTICK_CSR_ENABLE)
		);

	// set the priority of systick to maximum.
	McciArm_putRegClearSet(
		McciCm0Plus_SCB_SHPR_getRegister(MCCI_CM0PLUS_PRI_INDEX_SYSTICK),
		McciCm0Plus_SCB_SHPR_getMask(MCCI_CM0PLUS_PRI_INDEX_SYSTICK),
		~UINT32_C(0)
		);
	}

#undef FUNCTION


/**** end of mccibootloader_stm32l0_systeminit.c ****/
