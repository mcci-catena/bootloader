/*

Module:	mcci_bootloader_cm7_appimage.h

Function:
	AppImage layout on CortexM7. Defined by bootloader so not part
	the CortexM7 header.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#ifndef _mcci_bootloader_cm7_appimage_h_
#define _mcci_bootloader_cm7_appimage_h_	/* prevent multiple includes */

#pragma once

#include "mcci_arm_cm7.h"
#include <stdint.h>
#include "mcci_bootloader_appinfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	Data Structures
|
\****************************************************************************/

/// \brief the Cortex M7 App header
typedef struct McciBootloader_CortexM7PageZeroContents_s
	{
	Mcci_CortexM7VectorsContents_t	CortexVectors;
	McciBootloader_AppInfo_t	AppInfo;
	} McciBootloader_CortexM7PageZeroContents_t;

typedef union McciBootloader_CortexM7PageZero_u
	{
	Mcci_CortexAppEntryContents_t		CortexAppEntry;		//< View instance as a CortexM7 AppEntry.
	Mcci_CortexAppEntry_t			CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	Mcci_CortexM7VectorsContents_t	 	CortexVectors;		//< View instance as vectors.
	Mcci_CortexM7Vectors_t	 		CortexVectorsCast;	//< Downcast to a CortexVectors_t without explicit casting
	McciBootloader_CortexM7PageZeroContents_t PageZero;		//< View instance as a PageZero.
	uint8_t					Bytes[1024 + 64];	//< padding to force size
	} __attribute__((__aligned__(256)))
	McciBootloader_CortexM7PageZero_t;


/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_cm7_appimage_h_ */
