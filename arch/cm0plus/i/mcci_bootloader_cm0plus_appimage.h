/*

Module:	mcci_bootloader_cm0plus_appimage.h

Function:
	AppImage layout on CortexM0. Defined by bootloader so not part
	the CortexM0 header.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_cm0plus_appimage_h_
#define _mcci_bootloader_cm0plus_appimage_h_	/* prevent multiple includes */

#pragma once

#include "mcci_bootloader_cm0plus.h"
#include "mcciadk_guid.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	Data Structures
|
\****************************************************************************/

///
/// \brief Application information block
///
/// \details
///	This information block appears at a well known location somewhere
///	in each app image. It's intended to be somewhat architecturaly
///	neutral, but until we have two supported architectures, we
///	won't really have a basis for discussion.
///
typedef struct
	{
	uint32_t	magic;		//< the format identifier.
	uint32_t	size;		//< size of this stucture, in bytes
	uint32_t	targetAddress;	//< the target load address
	uint32_t	imagesize;	//< size of the app, in bytes.
					//   Must be multiple of 4.
	uint32_t	authsize;	//< size of authentication data.
					// Overall image size is imagesize
					//   + authsize
	uint32_t	gpsTimestamp;	//< GPS timestamp of image
	MCCIADK_GUID	appGuid;	//< application ID
	uint32_t	version;	//< version of the image (semantic version)
	} McciBootloader_AppInfo_t;

/// \brief the Cortex M0 App header
typedef struct McciBootloader_CortexPageZeroContents_s
	{
	Mcci_CortexVectorsContents_t	Hdr;
	McciBootloader_AppInfo_t		AppEntry;
	} McciBootloader_CortexPageZeroContents_t;

typedef union McciBootloader_CortexPageZero_u
	{
	Mcci_CortexAppEntryContents_t		CortexAppEntry;		//< View instance as a CortexM0 AppEntry.
	Mcci_CortexAppEntry_t			CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	Mcci_CortexVectorsContents_t	 	CortexVectors;		//< View instance as vectors.
	Mcci_CortexVectors_t	 		CortexVectorsCast;	//< Downcast to a CortexVectors_t without explicit casting
	McciBootloader_CortexPageZeroContents_t PageZero;		//< View instance as a PageZero.
	uint8_t					Bytes[256];		//< padding to force size
	} McciBootloader_CortexPageZero_t;

/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_cm0plus_appimage_h_ */
