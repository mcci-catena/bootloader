/*

Module:	mccibootloader_stm32h7_prepareforlaunch.c

Function:
	McciBootloader_Stm32l0_prepareForLaunch()

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

Name:	McciBootloader_Stm32h7_prepareForLaunch()

Function:
	Return the STM32H7 to suitable config prior to launching app.

Definition:
	void McciBootloader_Stm32h7_prepareForLaunch(
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
McciBootloader_Stm32h7_prepareForLaunch(
	void
	)
	{
	// reset the low-level peripherals (just in case)
	}

/**** end of mccibootloader_stm32h7_prepareforlaunch.c ****/
