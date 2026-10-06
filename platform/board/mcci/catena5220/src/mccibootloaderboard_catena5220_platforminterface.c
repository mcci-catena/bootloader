/*

Module:	mccibootloaderboard_catena5220_platforminterface.c

Function:
	gk_McciBootloaderPlatformInterface for MCCI Catena 5220 boards.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Pranau Ravikumar, MCCI Corporation	September 2026

*/

#include "mcci_bootloader_board_catena5220.h"

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

const McciBootloaderPlatform_Interface_t
gk_McciBootloaderPlatformInterface =
	{
	.pSystemInit = McciBootloaderBoard_Catena1sj_systemInit,
	.pPrepareForLaunch = McciBootloaderBoard_Catena1sj_prepareForLaunch,
	.pFail = McciBootloaderBoard_Catena1sj_fail,
	.pDelayMs = McciBootloaderBoard_Catena1sj_delayMs,
	.pGetMilliseconds = McciBootloaderBoard_Catena1sj_getMilliseconds,
	.pGetUpdate = McciBootloaderBoard_Catena1sj_getUpdate,
	.pSetUpdate = McciBootloaderBoard_Catena1sj_setUpdate,
	.pSystemFlashErase = McciBootloader_Stm32L0_systemFlashErase,
	.pSystemFlashWrite = McciBootloader_Stm32L0_systemFlashWrite,
	.Storage =
		{
		.pInit = McciBootloaderBoard_Catena5220_storageInit,
		.pRead = McciBootloaderFlash_Mx25v8035f_storageRead,
		.pGetPrimaryAddress = McciBootloaderBoard_Catena1sj_getPrimaryStorageAddress,
		.pGetFallbackAddress = McciBootloaderBoard_Catena1sj_getFallbackStorageAddress,
		},
	.Spi =
		{
		.pInit = McciBootloaderBoard_Catena1sj_spiInit,
		.pTransfer = McciBootloaderBoard_Catena1sj_spiTransfer,
		},
	.Annunciator =
		{
		.pInit = McciBootloaderBoard_Catena1sj_annunciatorInit,
		.pIndicateState = McciBootloaderBoard_Catena1sj_annunciatorIndicateState,
		},
	};

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/



/**** end of mccibootloaderboard_catena5220_platforminterface.c ****/
