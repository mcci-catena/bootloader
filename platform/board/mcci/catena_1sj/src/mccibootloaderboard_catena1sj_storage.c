/*

Module:	mccibootloaderboard_catena1sj_storage.c

Function:
	Storage driver for type 1SJ Catenas.

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

McciBootloaderStorageAddress_t
McciBootloaderBoard_Catena1sj_getPrimaryStorageAddress(
	void
	)
	{
	return MCCI_BOOTLOADER_BOARD_CATENA_1SJ_STORAGE_UPDATE_BASE;
	}

McciBootloaderStorageAddress_t
McciBootloaderBoard_Catena1sj_getFallbackStorageAddress(
	void
	)
	{
	return MCCI_BOOTLOADER_BOARD_CATENA_1SJ_STORAGE_FALLBACK_BASE;
	}

/**** end of mccibootloaderboard_catena1sj_storage.c ****/
