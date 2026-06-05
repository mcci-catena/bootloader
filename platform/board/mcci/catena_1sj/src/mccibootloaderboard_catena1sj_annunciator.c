/*

Module:	mccibootloaderboard_catena1sj_annunciator.c

Function:
	Annunciator (LED flashing) functions for 1SJ-based Catena boards.

Copyright notice:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_board_catena_1sj.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_led_annunciator.h"

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

Name:	McciBootloaderBoard_Catena1sj_annunciatorInit()

Function:
	Initialize the annunciator for Catena 1sj boards.

Definition:
	void McciBootloaderBoard_Catena1sj_annunciatorInit(
		void
		);

Description:
	Set up the LED that displays system boot status.

Returns:
	No explicit result

Notes:
	Uses the 2026-era opt-in McciBootloader_LED_Annunciator_t framework.

	Note that interrupts are enabled here. So if you call this and never
	come back, look for hot interrupt problems.

*/

#define FUNCTION "McciBootloaderBoard_Catena1sj_annunciatorInit"

void
McciBootloaderBoard_Catena1sj_annunciatorInit(
	void
	)
	{
	McciBootloader_LED_annunciatorInit();

	// enable interrupts.
	McciArm_setPRIMASK(0);
	}

#undef FUNCTION


/**** end of mccibootloaderboard_catena1sj_annunciator.c ****/
