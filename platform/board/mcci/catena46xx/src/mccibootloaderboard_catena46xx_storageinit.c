/*

Module:	mccibootloaderboard_catena46xx_storageinit.c

Function:
	McciBootloaderBoard_Catena46xx_storageInit()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena46xx.h"

#include "mcci_bootloader_flash_mx25v8035f.h"

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

Name:	McciBootloaderBoard_Catena46xx_storageInit()

Function:
	Initialize the Catena46xx external storage.

Definition:
	typedef McciBootloaderPlatform_StorageInit_t
		McciBootloaderBoard_Catena46xx_storageInit;

	void McciBootloaderBoard_Catena46xx_storageInit(
		void
		);

Description:
	Initialize SPI, init the external flash, and we're ready.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Catena46xx_storageInit(
	void
	)
	{
	McciBootloaderPlatform_spiInit();
	McciBootloaderFlash_Mx25v8035f_storageInit();
	}


/**** end of mccibootloaderboard_catena46xx_storageinit.c ****/
