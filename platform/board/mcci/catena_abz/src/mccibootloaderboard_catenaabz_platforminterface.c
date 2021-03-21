/*

Module:	mccibootloaderboard_catenaabz_platforminterface.c

Function:
	gk_McciBootloaderPlatformInterface for Catena ABZ boards.

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

const McciBootloaderPlatform_Interface_t
gk_McciBootloaderPlatformInterface =
	{
	.pSystemInit = McciBootloaderBoard_CatenaAbz_systemInit,
	.pPrepareForLaunch = McciBootloaderBoard_CatenaAbz_prepareForLaunch,
	.pFail = McciBootloaderBoard_CatenaAbz_fail,
	};

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/



/**** end of mccibootloaderboard_catenaabz_platforminterface.c ****/
