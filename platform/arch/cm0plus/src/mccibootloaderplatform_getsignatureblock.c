/*

Module:	mccibootloaderplatform_getsignatureblock.c

Function:
	McciBootloaderPlatform_getSignatureBlock()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	April 2021

*/


#include "mcci_bootloader_platform.h"

#include "mcci_bootloader_appinfo.h"

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

Name:	McciBootloaderPlatform_getSignatureBlock()

Function:
	Fetch pointer to signature block given appinfo block.

Definition:
	McciBootloader_SignatureBlock_t McciBootloaderPlatform_getSignatureBlock(
		const McciBootloader_AppInfo_t *pAppInfo
		);

Description:
	The address of the signature block is computed based on the contents of
	the app info block.

Returns:
	Pointer to signature block, or NULL if incoming arg is NULL.

Notes:
	The address is computed relative to the targetAddress in the app info
	block. The AppInfo block might not be in its target location.

*/

#define FUNCTION "McciBootloaderPlatform_getSignatureBlock"

const McciBootloader_SignatureBlock_t *
McciBootloaderPlatform_getSignatureBlock(
	const McciBootloader_AppInfo_t *pAppInfo
	)
	{
	if (pAppInfo == NULL)
		return NULL;

	return (const McciBootloader_SignatureBlock_t *)(
			pAppInfo->targetAddress + pAppInfo->imagesize
			);
	}

#undef FUNCTION

/**** end of mccibootloaderplatform_getsignatureblock.c ****/
