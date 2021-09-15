/*

Module:	mccibootloaderboard_catenaabz_storage.c

Function:
	Storage driver for STM32H7B3 boards

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
#include <string.h>

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
McciBootloaderBoard_Stm32h7b3_getPrimaryStorageAddress(
	void
	)
	{
	return (McciBootloaderStorageAddress_t) &gk_McciBootloader_UpdateBase;
	}

McciBootloaderStorageAddress_t
McciBootloaderBoard_Stm32h7b3_getFallbackStorageAddress(
	void
	)
	{
	return (McciBootloaderStorageAddress_t) &gk_McciBootloader_FallbackBase;
	}

void
McciBootloaderBoard_Stm32h7b3_storageInit(
	void
	)
	{
	}

/*

Name:	McciBootloaderBoard_Stm32h7b3_storageRead()

Function:
	Read a buffer from the specified flash byte address

Definition:
	bool McciBootloaderBoard_Stm32h7b3_storageRead(
		McciBootloaderStorageAddress_t Address,
		uint8_t *pBuffer,
		size_t nBuffer
		);

Description:
	This function reads a buffer from the specified flash
	byte offset. There are no alignment constraings.

Returns:
	true if success

*/

bool
McciBootloaderBoard_Stm32h7b3_storageRead(
	McciBootloaderStorageAddress_t Address,
	uint8_t *pBuffer,
	size_t nBuffer
	)
	{
	if (! MCCI_STM32H7_FLASH_IS_VALID(Address))
		return false;

	memcpy(pBuffer, (void *) Address, nBuffer);
	return true;
	}

/**** end of mccibootloaderboard_catenaabz_storage.c ****/
