/*

Module:	mccibootloaderboard_catena51xx_storageinit.c

Function:
	McciBootloaderBoard_Catena51xx_storageInit()

Copyright and License:
	This file copyright (C) 2023 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Dhinesh Kumar Pitchai, MCCI Corporation	October 2023

*/

#include "mcci_bootloader_board_catena51xx.h"

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

Name:	McciBootloaderBoard_Catena51xx_storageInit()

Function:
	Initialize the Catena51xx external storage.

Definition:
	typedef McciBootloaderPlatform_StorageInit_t
		McciBootloaderBoard_Catena51xx_storageInit;

	void McciBootloaderBoard_Catena51xx_storageInit(
		void
		);

Description:
	Initialize SPI, init the external flash, and we're ready.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Catena51xx_storageInit(
	void
	)
	{
	McciBootloaderPlatform_spiInit();
	McciBootloaderFlash_Mx25v8035f_storageInit();
	}


/**** end of mccibootloaderboard_catena51xx_storageinit.c ****/
