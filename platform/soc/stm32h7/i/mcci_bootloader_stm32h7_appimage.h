/*

Module:	mcci_bootloader_stm32h7_appimage.h

Function:
	AppImage layout on STM32 H7. Defined by bootloader so not part
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

#ifndef _mcci_bootloader_stm32h7_appimage_h_
#define _mcci_bootloader_stm32h7_appimage_h_	/* prevent multiple includes */

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

///
/// \brief STM32 H7 interrupt vectors (low level view)
///
/// This structure represents the vectors page as an array of 240 32-bit vectors.
/// It's used mostly for initialization and for building up larger structures.
///
typedef struct Mcci_Stm32H7VectorsContents_s
	{
	uint32_t	vectors[240];
	} Mcci_Stm32H7VectorsContents_t;

///
/// \brief STM32 H7 interrupt vector object
///
/// This union wraps the interrupt vector contents, both so we can always
/// reference fields with consistent names (`AppEntry.stack` etc.), and to allow
/// us to view the vectors as either an AppEntry description or a table of
/// vectors.
///
typedef union Mcci_Stm32H7Vectors_u
	{
	Mcci_CortexAppEntryContents_t	CortexAppEntry;		//< View instance as a CortexM7 AppEntry.
	Mcci_CortexAppEntry_t		CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	Mcci_Stm32H7VectorsContents_t	CortexVectors;		//< View instance as vectors.
	} Mcci_Stm32H7Vectors_t;

/// \brief the Cortex M7 App header
typedef struct McciBootloader_Stm32H7PageZeroContents_s
	{
	Mcci_Stm32H7VectorsContents_t	CortexVectors;
	McciBootloader_AppInfo_t	AppInfo;
	} McciBootloader_Stm32H7PageZeroContents_t;

typedef union McciBootloader_Stm32H7PageZero_u
	{
	Mcci_CortexAppEntryContents_t		CortexAppEntry;		//< View instance as a CortexM7 AppEntry.
	Mcci_CortexAppEntry_t			CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	Mcci_Stm32H7VectorsContents_t	 	CortexVectors;		//< View instance as vectors.
	Mcci_Stm32H7Vectors_t	 		CortexVectorsCast;	//< Downcast to a CortexVectors_t without explicit casting
	McciBootloader_Stm32H7PageZeroContents_t PageZero;		//< View instance as a PageZero.
	uint8_t					Bytes[1024];		//< padding to force size
	} __attribute__((__aligned__(256)))
	McciBootloader_Stm32H7PageZero_t;


/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_stm32h7_appimage_h_ */
