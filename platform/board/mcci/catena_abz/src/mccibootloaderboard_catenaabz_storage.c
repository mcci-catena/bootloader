/*

Module:	mccibootloaderboard_catenaabz_storage.c

Function:
	Storage driver for type ABZ Catenas.

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



/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

McciBootloaderStorageAddress_t
McciBootloaderBoard_CatenaAbz_getPrimaryStorageAddress(
	void
	)
	{
	return MCCI_BOOTLOADER_BOARD_CATENA_ABZ_STORAGE_UPDATE_BASE;
	}

McciBootloaderStorageAddress_t
McciBootloaderBoard_CatenaAbz_getFallbackStorageAddress(
	void
	)
	{
	return MCCI_BOOTLOADER_BOARD_CATENA_ABZ_STORAGE_FALLBACK_BASE;
	}

/**** end of mccibootloaderboard_catenaabz_storage.c ****/
