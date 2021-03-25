/*

Module:	mccibootloaderboard_catena4801_platforminterface.c

Function:
	gk_McciBootloaderPlatformInterface for MCCI Catena 4801 boards.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena4801.h"

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
	.pSystemInit = McciBootloaderBoard_CatenaAbz_systemInit,
	.pPrepareForLaunch = McciBootloaderBoard_CatenaAbz_prepareForLaunch,
	.pFail = McciBootloaderBoard_CatenaAbz_fail,
	.pDelayMs = McciBootloaderBoard_CatenaAbz_delayMs,
	.pGetUpdate = McciBootloaderBoard_CatenaAbz_getUpdate,
	.pSetUpdate = McciBootloaderBoard_CatenaAbz_setUpdate,
	.Storage =
		{
		.pInit = McciBootloaderBoard_Catena4801_storageInit,
		.pRead = McciBootloaderFlash_Mx25v8035f_storageRead,
		.pGetPrimaryAddress = McciBootloaderBoard_CatenaAbz_getPrimaryStorageAddress,
		.pGetFallbackAddress = McciBootloaderBoard_CatenaAbz_getFallbackStorageAddress,
		},
	.Spi =
		{
		.pInit = McciBootloaderBoard_CatenaAbz_spiInit,
		.pTransfer = McciBootloaderBoard_CatenaAbz_spiTransfer,
		},
	.Annunciator =
		{
		.pInit = McciBootloaderBoard_CatenaAbz_annunciatorInit,
		.pIndicateState = McciBootloaderBoard_CatenaAbz_annunciatorIndicateState,
		},
	};

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/



/**** end of mccibootloaderboard_catenaabz_platforminterface.c ****/
