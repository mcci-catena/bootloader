/*

Module:	mccibootloaderboard_stm32h7b3_platforminterface.c

Function:
	gk_McciBootloaderPlatformInterface for STM32h7B3 boards.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	July 2021

*/

#include "mcci_bootloader_board_stm32h7b3.h"

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
	.pSystemInit = McciBootloaderBoard_Stm32h7b3_systemInit,
	.pPrepareForLaunch = McciBootloaderBoard_Stm32h7b3_prepareForLaunch,
	.pFail = McciBootloaderBoard_Stm32h7b3_fail,
	.pDelayMs = McciBootloaderBoard_Stm32h7b3_delayMs,
	.pGetUpdate = McciBootloaderBoard_Stm32h7b3_getUpdate,
	.pSetUpdate = McciBootloaderBoard_Stm32h7b3_setUpdate,
	.pSystemFlashErase = McciBootloader_Stm32h7_systemFlashErase,
	.pSystemFlashWrite = McciBootloader_Stm32h7_systemFlashWrite,
	.Storage =
		{
		.pInit = McciBootloaderBoard_Stm32h7b3_storageInit,
		.pRead = McciBootloaderBoard_Stm32h7b3_storageRead,
		.pGetPrimaryAddress = McciBootloaderBoard_Stm32h7b3_getPrimaryStorageAddress,
		.pGetFallbackAddress = McciBootloaderBoard_Stm32h7b3_getFallbackStorageAddress,
		},
	.Spi =
		{
		.pInit = NULL,
		.pTransfer = NULL,
		},
	.Annunciator =
		{
		.pInit = McciBootloaderBoard_Stm32h7b3_annunciatorInit,
		.pIndicateState = McciBootloaderBoard_Stm32h7b3_annunciatorIndicateState,
		},
	};

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/


/**** end of mccibootloaderboard_stm32h7b3_platforminterface.c ****/
