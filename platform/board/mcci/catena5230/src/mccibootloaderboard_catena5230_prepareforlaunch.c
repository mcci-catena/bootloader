/*

Module:	mccibootloaderboard_catena5230_prepareforlaunch.c

Function:
	McciBootloaderBoard_Catena5230_prepareForLaunch()

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_board_catena5230.h"
#include "mcci_bootloader_board_catena_1sj.h"

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

Name:	McciBootloaderBoard_Catena5230_prepareForLaunch()

Function:
	Platform interface: prepare for launch of app on 5230.

Definition:
	void McciBootloaderBoard_Catena5230_prepareForLaunch(
		void
		);

Description:
	Return the board and the SOC to the boot state.
	Delegates to common Catena1SJ logic.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Catena5230_prepareForLaunch(
	void
	)
	{
	McciBootloaderBoard_Catena1sj_prepareForLaunch();
	}


/**** end of mccibootloaderboard_catena5230_prepareforlaunch.c ****/
