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
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_platform.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_cm0plus_appimage.h"

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
	bool McciBootloaderPlatform_checkImageValid(
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
	true if the image passes all the checks, false if it fails any.

Notes:
	

*/

bool
McciBootloaderPlatform_checkImageValid(
	const void *pHeader,
	size_t nHeader,
	uintptr_t targetAddress,
	size_t targetSize
	)
	{
	const McciBootloader_CortexPageZero_t * const pPageZero = pHeader;

	if (nHeader < sizeof(*pPageZero))
		return false;

	/* check the stack pointer */
		{
		uint32_t pStack = pPageZero->CortexAppEntry.stack;

		if (pStack & 3)
			return false;
		
		/* stack pointer must be reasonable */
		if (pStack < (uint32_t) &g_McciBootloader_RamBase + 16)
			return false;
		if ((uint32_t) &g_McciBootloader_RamTop < pStack)
			return false;
		}

	/* check the program counter */
		{
		uint32_t pEntry = pPageZero->CortexAppEntry.entry;

		/* must be odd-aligned indicating Thumb instructions */
		if ((pEntry & 1) == 0)
			return false;

		/* must be in the target region */
		pEntry &= ~UINT32_C(1);
		if (pEntry < targetAddress + sizeof(*pPageZero))
			return false;

		if (targetAddress + targetSize <= pEntry)
			return false;
		}

	/* check that the image fits */
	if (targetAddress != (uint32_t) &gk_McciBootloader_AppBase)
		return false;

	if ((uint32_t) &gk_McciBootloader_AppTop - targetAddress > targetSize)
		return false;

	const McciBootloader_AppInfo_t * const pAppInfo = 
		McciBootloaderPlatform_getAppInfo(
			pPageZero, sizeof(*pPageZero)
			);

	if (pAppInfo == NULL)
		return false;

	if (pAppInfo->targetAddress != targetAddress)
		return false;

	if (pAppInfo->authsize != mcci_tweetnacl_sign_signature_size() + 
					sizeof(mcci_tweetnacl_sha512_t))
		return false;

	if (pAppInfo->imagesize + pAppInfo->authsize > targetSize)
		return false;

	return true;
	}

/**** end of mccibootloaderplatform_checkimagevalid.c ****/
