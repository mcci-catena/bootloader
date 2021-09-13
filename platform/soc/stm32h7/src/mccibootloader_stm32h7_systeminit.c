/*

Module:	mccibootloader_stm32h7_systeminit.c

Function:
	McciBootloader_Stm32h7_systemInit()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	July 2021

*/

#include "mcci_bootloader_stm32h7.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_platform.h"
#include "mcci_stm32h7xx.h"

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

Name:	McciBootloader_Stm32h7_systemInit()

Function:
	Configure STM32H7 core for MCCI bootloader

Definition:
	void McciBootloader_Stm32h7_systemInit(
		void
		);

Description:
	Configure the STM32H7 core to run at 32 MHz, with the other
	clocks configured in a suitable default way. Set up SYSTICK
	to roll over every MS.  Enable HSI16 clock, PLL, LSE.

Returns:
	No explicit result.

Notes:
	Assumes we have a 32 kHz crystal for the LSE clock.

*/

#define FUNCTION "McciBootloader_Stm32h7_systemInit"

#define	MCCI_STM32H7_PWR_SUPPLY_CONFIG_MASK	\
	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL |	\
	 MCCI_STM32H7_REG_PWR_CR3_SMPSEXTHP |	\
	 MCCI_STM32H7_REG_PWR_CR3_SMPSEN |	\
	 MCCI_STM32H7_REG_PWR_CR3_LDOEN |	\
	 MCCI_STM32H7_REG_PWR_CR3_BYPASS)

#define	MCCI_STM32H7_PWR_SUPPLY_LDO		MCCI_STM32H7_REG_PWR_CR3_LDOEN
#define	MCCI_STM32H7_PWR_SUPPLY_DIRECT_SMPS	MCCI_STM32H7_REG_PWR_CR3_SMPSEN
#define	MCCI_STM32H7_PWR_SUPPLY_SMPS_1V8_LDO	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_1_8V | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEN | \
						 MCCI_STM32H7_REG_PWR_CR3_LDOEN)
#define	MCCI_STM32H7_PWR_SUPPLY_SMPS_2V5_LDO	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_2_5V | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEN | \
						 MCCI_STM32H7_REG_PWR_CR3_LDOEN)
#define	MCCI_STM32H7_PWR_SUPPLY_SMPS_1V8_EXT	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_1_8V | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEN | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEXTHP | \
						 MCCI_STM32H7_REG_PWR_CR3_BYPASS)
#define	MCCI_STM32H7_PWR_SUPPLY_SMPS_2V5_EXT	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_2_5V | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEN | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEXTHP | \
						 MCCI_STM32H7_REG_PWR_CR3_BYPASS)
#define	MCCI_STM32H7_PWR_SUPPLY_SMPS_1V8_EXTLDO	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_1_8V | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEN | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEXTHP | \
						 MCCI_STM32H7_REG_PWR_CR3_LDOEN)
#define	MCCI_STM32H7_PWR_SUPPLY_SMPS_2V5_EXTLDO	(MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_2_5V | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEN | \
						 MCCI_STM32H7_REG_PWR_CR3_SMPSEXTHP | \
						 MCCI_STM32H7_REG_PWR_CR3_LDOEN)
#define	MCCI_STM32H7_PWR_SUPPLY_EXTERNAL_SOURCE	MCCI_STM32H7_REG_PWR_CR3_BYPASS

#ifndef	MCCI_STM32H7_PWR_SUPPLY_CONFIG	/* PARAM */
# define MCCI_STM32H7_PWR_SUPPLY_CONFIG	MCCI_STM32H7_PWR_SUPPLY_LDO
#endif

void
McciBootloader_Stm32h7_systemInit(void)
	{
	// mask off interrupts, discarding prior state.
	(void) McciArm_disableInterrupts();

	// presumably we got here via the boot vector, but load the
	// vector table anyway
	McciArm_putReg(
		MCCI_CM7_SCB_VTOR,
		(uint32_t) &gk_McciBootloader_CortexVectors
		);

	// use reset things to defaults
	uint32_t r;

	/* Increase flash wait states */
	r = McciArm_getReg(MCCI_STM32H7_REG_FLASH_ACR);
	if ((r & MCCI_STM32H7_REG_FLASH_ACR_LATENCY) <
	    MCCI_STM32H7_REG_FLASH_ACR_LATENCY_V(3))
		{
		McciArm_putReg(
			MCCI_STM32H7_REG_FLASH_ACR,
			(r & ~MCCI_STM32H7_REG_FLASH_ACR_LATENCY) |
			MCCI_STM32H7_REG_FLASH_ACR_LATENCY_V(3)
			);
		}

	/* Set HSION */
	McciArm_putRegOr(
		MCCI_STM32H7_REG_RCC_CR,
		MCCI_STM32H7_REG_RCC_CR_HSION
		);

	/* Reset CFGR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_CFGR, 0);

	/* Reset HSEON, HSECSSON, CSION, HSI48ON, CSIKERON, PLL1ON, PLL2ON and PLL3ON */
	r = McciArm_getReg(MCCI_STM32H7_REG_RCC_CR);
	McciArm_putReg(MCCI_STM32H7_REG_RCC_CR, r & 0xEAF6ED7FU);

	/* Decrease flash wait states */
	r = McciArm_getReg(MCCI_STM32H7_REG_FLASH_ACR);
	if ((r & MCCI_STM32H7_REG_FLASH_ACR_LATENCY) >
	    MCCI_STM32H7_REG_FLASH_ACR_LATENCY_V(3))
		{
		McciArm_putReg(
			MCCI_STM32H7_REG_FLASH_ACR,
			(r & ~MCCI_STM32H7_REG_FLASH_ACR_LATENCY) |
			MCCI_STM32H7_REG_FLASH_ACR_LATENCY_V(3)
			);
		}

	/* Reset CDCFGR1, CDCFGR2 and SRDCFGR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_CDCFGR1, 0);
	McciArm_putReg(MCCI_STM32H7_REG_RCC_CDCFGR2, 0);
	McciArm_putReg(MCCI_STM32H7_REG_RCC_SRDCFGR, 0);

	/* Reset PLLCKSELR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLLCKSELR, 0x02020200);
	
	/* Reset PLLCFGR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLLCFGR, 0x01FF0000);

	/* Reset PLL1DIVR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLL1DIVR, 0x01010280);

	/* Reset PLL1FRACR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLL1FRACR, 0x00000000);
	
	/* Reset PLL2DIVR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLL2DIVR, 0x01010280);
	
	/* Reset PLL2FRACR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLL2FRACR, 0x00000000);
	
	/* Reset PLL3DIVR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLL3DIVR, 0x01010280);
	
	/* Reset PLL3FRACR register */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_PLL3FRACR, 0x00000000);
	
	/* Reset HSEBYP bit */
	r = McciArm_getReg(MCCI_STM32H7_REG_RCC_CR);
	McciArm_putReg(MCCI_STM32H7_REG_RCC_CR, r & 0xFFFBFFFFU);
	
	/* Disable all interrupts */
	McciArm_putReg(MCCI_STM32H7_REG_RCC_CIER, 0x00000000);

#ifdef	MCCI_STM32H7_INIT_POWER_SUPPLY
	r = McciArm_getReg(MCCI_STM32H7_REG_PWR_CR3);
	if ((r & (MCCI_STM32H7_REG_PWR_CR3_SMPSEN |
		  MCCI_STM32H7_REG_PWR_CR3_LDOEN |
		  MCCI_STM32H7_REG_PWR_CR3_BYPASS)) !=
	    (MCCI_STM32H7_REG_PWR_CR3_SMPSEN |
	     MCCI_STM32H7_REG_PWR_CR3_LDOEN))
		{
		if ((r & MCCI_STM32H7_PWR_SUPPLY_CONFIG_MASK) !=
		    MCCI_STM32H7_PWR_SUPPLY_CONFIG)
			{
			/* can't apply new supply config */
			}
		else
			{
			/* matched supply config */
			}
		}
	else
		{
		McciArm_putReg(
			MCCI_STM32H7_REG_PWR_CR3,
			(r & ~MCCI_STM32H7_PWR_SUPPLY_CONFIG_MASK) |
			MCCI_STM32H7_PWR_SUPPLY_CONFIG
			);

		do	{
			r = McciArm_getReg(MCCI_STM32H7_REG_PWR_CSR1);
			} while ((r & MCCI_STM32H7_REG_PWR_CSR1_ACTVOSRDY) == 0);

		if ((MCCI_STM32H7_PWR_SUPPLY_CONFIG == MCCI_STM32H7_PWR_SUPPLY_SMPS_1V8_EXT) ||
		    (MCCI_STM32H7_PWR_SUPPLY_CONFIG == MCCI_STM32H7_PWR_SUPPLY_SMPS_2V5_EXT) ||
		    (MCCI_STM32H7_PWR_SUPPLY_CONFIG == MCCI_STM32H7_PWR_SUPPLY_SMPS_1V8_EXTLDO) ||
		    (MCCI_STM32H7_PWR_SUPPLY_CONFIG == MCCI_STM32H7_PWR_SUPPLY_SMPS_2V5_EXTLDO))
			{
			do	{
				r = McciArm_getReg(MCCI_STM32H7_REG_PWR_CR3);
				} while ((r & MCCI_STM32H7_REG_PWR_CR3_SMPSEXTRDY) == 0);
			}
		}

	r = McciArm_getReg(MCCI_STM32H7_REG_PWR_SRDCR);
	McciArm_putReg(
		MCCI_STM32H7_REG_PWR_SRDCR,
		(r & ~MCCI_STM32H7_REG_PWR_SRDCR_VOS) |
		MCCI_STM32H7_REG_PWR_SRDCR_VOS_SCALE1
		);

	do	{
		r = McciArm_getReg(MCCI_STM32H7_REG_PWR_SRDCR);
		} while ((r & MCCI_STM32H7_REG_PWR_SRDCR_VOSRDY) == 0);
#endif	/* MCCI_STM32H7_INIT_POWER_SUPPLY */
	}

#undef FUNCTION

/**** end of mccibootloader_stm32h7_systeminit.c ****/
