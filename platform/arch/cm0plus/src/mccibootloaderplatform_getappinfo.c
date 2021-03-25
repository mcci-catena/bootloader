/*

Module:	mccibootloaderplatform_getappinfo.c

Function:
	McciBootloaderPlatform_getAppInfo()

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
#include "mcci_bootloader_appinfo.h"
#include "mcci_bootloader_cm0plus_appimage.h"

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

Name:	McciBootloaderPlatform_getAppInfo()

Function:
	Find the app info structure in a header

Definition:
	const McciBootloader_AppInfo_t *
		McciBootloaderPlatform_getAppInfo(
			const void *pHeader,
			size_t nHeader
			);

Description:
	Given a pointer to the header of an image (not necessarily at
	its final location), and a count of the buffer bytes, this function
	returns a pointer to the McciBootloader_AppInfo_t header structure.

Returns:
	Non-null if the app info structure was found and passes the checks,
	NULL otherwise.

Notes:
	

*/

const McciBootloader_AppInfo_t *
McciBootloaderPlatform_getAppInfo(
	const void *pHeader,
	size_t nHeader
	)
	{
	const McciBootloader_CortexPageZero_t * const pPageZero = pHeader;

	if (nHeader < sizeof(*pPageZero))
		return NULL;

	const McciBootloader_AppInfo_t * const pAppInfo =
			&pPageZero->PageZero.AppEntry;

	if (pAppInfo->magic != MCCI_BOOTLOADER_APP_INFO_MAGIC)
		return NULL;

	if (pAppInfo->size != sizeof(*pAppInfo))
		return NULL;

	return pAppInfo;
	}

/**** end of mccibootloaderplatform_getappinfo.c ****/
