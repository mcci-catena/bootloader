/*

Module:	mccibootloader_programandcheckflash.c

Function:
	McciBootloader_programAndCheckflash()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader.h"

#include "mcci_bootloader_appinfo.h"
#include "mcci_bootloader_platform.h"

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

Name:	McciBootloader_programAndCheckFlash()

Function:
	Program internal flash from storage image

Definition:
	McciBootloaderError_t McciBootloader_programAndCheckFlash(
		McciBootloaderStorageAddress_t storageAddress,
		const McciBootloader_AppInfo_t *pAppInfo
		);

Description:
	Copy the selected image to internal flash in the following
	sequence.

	1. Erase the current contents of internal flash
	2. Read through the image one buffer at a time, programming
	   the internal flash
	3. Check the hash on the image

Returns:
	McciBootloaderError_t_OK only if the image was programmed and
	the hash matches; otherwise a failure code.

Notes:


*/

McciBootloaderError_t
McciBootloader_programAndCheckFlash(
	McciBootloaderStorageAddress_t storageAddress,
	const McciBootloader_AppInfo_t *pAppInfo
	)
	{
	volatile const uint8_t * const targetAddress = (volatile const uint8_t *) pAppInfo->targetAddress;
	size_t const overallSizeTight = pAppInfo->imagesize + pAppInfo->authsize;
	const size_t blockSize = sizeof(g_McciBootloader_imageBlock);
	size_t const overallSize = (overallSizeTight + blockSize - 1) & ~(blockSize - 1);

	// erase in 4k chunks, to match program size.
	if (! McciBootloaderPlatform_systemFlashErase(
		targetAddress, overallSize
		))
		return McciBootloaderError_EraseFailed;

	// program in 4k chunks, up to the block that includes the
	// last byte of the signature
	McciBootloaderStorageAddress_t const addressEnd =
		storageAddress + overallSize;

	McciBootloaderStorageAddress_t addressCurrent;
	volatile const uint8_t *targetCurrent;

	for (addressCurrent = storageAddress, targetCurrent = targetAddress;
	     addressCurrent < addressEnd;
	     addressCurrent += blockSize, targetCurrent += blockSize)
		{
		/* read a block */
		if (! McciBootloaderPlatform_storageRead(
			addressCurrent,
			g_McciBootloader_imageBlock,
			blockSize
			))
			{
			return McciBootloaderError_ReadFailed;
			}

		/* program this block */
		if (! McciBootloaderPlatform_systemFlashWrite(
			targetCurrent,
			g_McciBootloader_imageBlock,
			blockSize
			))
			{
			return McciBootloaderError_FlashWriteFailed;
			}
		}

	/* finally, check the image */
	if (! McciBootloader_checkCodeValid(
		(const void *)targetAddress, overallSize
		))
		{
		return McciBootloaderError_FlashVerifyFailed;
		}

	return McciBootloaderError_OK;
	}

/**** end of mccibootloader_programandcheckflash.c ****/
