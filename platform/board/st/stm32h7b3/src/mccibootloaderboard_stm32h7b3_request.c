/*

Module:	mccibootloaderboard_stm32h7b3_request.c

Function:
	Request variables and accessors for bootloader for STM32H7B3 boards

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#include "mcci_bootloader_board_stm32h7b3.h"
#include "mcci_stm32h7xx.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

extern void *gk_McciBootloader_RequestBase;


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

static
McciBootloaderBoard_Stm32h7b3_Request_t
sg_McciBootloaderBoard_Stm32h7b3_RequestNo =
	{
	.MagicBegin = MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_BEGIN,
	.fUpdateRequest = 0,
	.MagicEnd = MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_END
	};

static
McciBootloaderBoard_Stm32h7b3_Request_t
sg_McciBootloaderBoard_Stm32h7b3_RequestYes =
	{
	.MagicBegin = MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_BEGIN,
	.fUpdateRequest = MCCI_BOOTLOADER_STM32H7B3_REQUEST_UPDATE_REQUEST,
	.MagicEnd = MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_END
	};

McciBootloaderBoard_Stm32h7b3_Request_t *
McciBootloaderBoard_Stm32h7b3_getRequestPointer(void)
	{
	McciBootloaderBoard_Stm32h7b3_Request_t *pRequest;

	/* convert to a pointer to the request */
	pRequest = (McciBootloaderBoard_Stm32h7b3_Request_t *)
			&gk_McciBootloader_RequestBase;
	if (pRequest->MagicBegin == MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_BEGIN &&
	    pRequest->MagicEnd == MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_END)
		{
		return pRequest;
		}
	else
		{
		return &sg_McciBootloaderBoard_Stm32h7b3_RequestNo;
		}
	}

bool
McciBootloaderBoard_Stm32h7b3_getUpdate(void)
	{
	const McciBootloaderBoard_Stm32h7b3_Request_t * const
		pRequest = McciBootloaderBoard_Stm32h7b3_getRequestPointer();

	if (pRequest->fUpdateRequest == MCCI_BOOTLOADER_STM32H7B3_REQUEST_UPDATE_REQUEST)
		return true;
	else
		return false;
	}

void
McciBootloaderBoard_Stm32h7b3_setUpdate(bool fRequest)
	{
	const McciBootloaderBoard_Stm32h7b3_Request_t *pRequest;
	uint32_t value;
	volatile const void *pRequestBase;

	pRequest = McciBootloaderBoard_Stm32h7b3_getRequestPointer();
	value = fRequest ? MCCI_BOOTLOADER_STM32H7B3_REQUEST_UPDATE_REQUEST : 0;

	// if it's already set to the right value, just return.
	if (pRequest->fUpdateRequest == value)
		return;

	pRequestBase = &gk_McciBootloader_RequestBase;
	McciBootloader_Stm32h7_systemFlashErase(pRequestBase, sizeof(*pRequest));
	if (fRequest)
		{
		pRequest = &sg_McciBootloaderBoard_Stm32h7b3_RequestYes;
		McciBootloader_Stm32h7_systemFlashWrite(
			pRequestBase,
			pRequest,
			sizeof(*pRequest)
			);
		}
	}

/**** end of mccibootloaderboard_stm32h7b3_request.c ****/
