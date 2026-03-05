/*

Module:	mccibootloaderplatform_checkimagevalid.c

Function:
	McciBootloaderPlatform_checkImageValid()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#include "mcci_bootloader_platform.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_cm7_appimage.h"

#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"

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

Name:	McciBootloaderPlatform_checkImageValid()

Function:
	Validate an image header according to the architectural rules.

Definition:
	const McciBootloader_AppInfo_t *
		McciBootloaderPlatform_checkImageValid(
			const void *pHeader,
			size_t nHeader,
			uintptr_t targetAddress,
			size_t targetSize
			);

Description:
	Given a pointer to the header of an image (not necessarily at
	its final location), a count of the image bytes, and a description
	of where the image is intended to live, this function confirms
	that the image is valid for execution.

Returns:
	non-NULL pointer to the AppInfo block if the image passes all the
	checks, NLL if it fails any.

Notes:


*/

const McciBootloader_AppInfo_t *
McciBootloaderPlatform_checkImageValid(
	const void *pHeader,
	size_t nHeader,
	uintptr_t targetAddress,
	size_t targetSize
	)
	{
	const McciBootloader_CortexM7PageZero_t * const pPageZero = pHeader;

	if (nHeader < sizeof(*pPageZero))
		return NULL;

	/* check the stack pointer */
		{
		uint32_t pStack = pPageZero->CortexAppEntry.stack;

		if (pStack & 3)
			return NULL;

		/* stack pointer must be reasonable */
		if (pStack < (uint32_t) &g_McciBootloader_SocRamBase + 16)
			return NULL;
		if ((uint32_t) &g_McciBootloader_SocRamTop < pStack)
			return NULL;
		}

	/* check the program counter */
		{
		uint32_t pEntry = pPageZero->CortexAppEntry.entry;

		/* must be odd-aligned indicating Thumb instructions */
		if ((pEntry & 1) == 0)
			return NULL;

		/* must be in the target region */
		pEntry &= ~UINT32_C(1);
		if (pEntry < targetAddress + sizeof(*pPageZero))
			return NULL;

		if (targetAddress + targetSize <= pEntry)
			return NULL;
		}

	const McciBootloader_AppInfo_t * const pAppInfo =
		McciBootloaderPlatform_getAppInfo(
			pPageZero, sizeof(*pPageZero)
			);

	if (pAppInfo == NULL)
		return NULL;

	if (pAppInfo->targetAddress != targetAddress)
		return NULL;

	if (pAppInfo->authsize != sizeof(McciBootloader_SignatureBlock_t))
		return NULL;

	if (pAppInfo->imagesize + pAppInfo->authsize > targetSize)
		return NULL;

	return pAppInfo;
	}

/**** end of mccibootloaderplatform_checkimagevalid.c ****/
