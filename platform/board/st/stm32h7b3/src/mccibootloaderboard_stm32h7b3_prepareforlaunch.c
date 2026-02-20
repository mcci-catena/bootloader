/*

Module:	mccibootloaderboard_catenaabz_prepareforlaunch.c

Function:
	McciBootloaderBoard_Stm32h7b3_prepareForLaunch()

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

Name:	McciBootloaderBoard_Stm32h7b3_prepareForLaunch()

Function:
	Platform interface: prepare for launch

Definition:
	void McciBootloaderBoard_Stm32h7b3_prepareForLaunch(
		void
		);

Description:
	Return the board and the SOC to the boot state.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Stm32h7b3_prepareForLaunch(
	void
	)
	{
	// deinit SysTick
	McciArm_putRegClear(
		MCCI_STM32H7_REG_RCC_APB4ENR,
		MCCI_STM32H7_REG_RCC_APB4ENR_SYSCFGEN
		);
	McciArm_putReg(MCCI_CM7_SYSTICK_CSR, 0);

	McciBootloader_Stm32h7_prepareForLaunch();
	}

/**** end of mccibootloaderboard_catenaabz_prepareforlaunch.c ****/
