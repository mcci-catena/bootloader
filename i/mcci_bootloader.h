/* mcci_bootloader.h	Tue Jul 14 2020 11:31:05 tmm */

/*

Module:  mcci_bootloader.h

Function:
	Main header file for MCCI bootloader for STM32L0

Version:
	V0.1.0	Tue Jul 14 2020 11:31:05 tmm	Edit level 1

Copyright notice:
	This file copyright (C) 2020 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.

Author:
	Terry Moore, MCCI Corporation	July 2020

Revision history:
   0.1.0  Tue Jul 14 2020 11:31:05  tmm
	Module created.

*/

#ifndef _MCCI_BOOTLOADER_H_		/* prevent multiple includes */
#define _MCCI_BOOTLOADER_H_

#ifndef _MCCI_BOOTLOADER_TYPES_H_
# include "mcci_bootloader_types.h"
#endif

MCCIADK_BEGIN_DECLS

/****************************************************************************\
|
|	Boot eror codes
|
\****************************************************************************/

enum McciBootloaderError_e
	{
	McciBootloaderError_OK = 0,
	McciBootLoaderError_BootLoaderNotValid,
	McciBootLoaderError_AppNotValid,
	};
typedef uint8_t McciBootloaderError_t;

/****************************************************************************\
|
|	Parameters from link script
|
\****************************************************************************/

extern const void *gk_McciBootloader_SelfBase;
extern const void *gk_McciBootloader_SelfTop;
extern const void *gk_McciBootloader_AppBase;
extern const void *gk_McciBootloader_AppTop;

/****************************************************************************\
|
|	Various utilities
|
\****************************************************************************/

/*

Name:	McciBootloader_codeSize()

Function:
	Return size of code region given pointers

Definition:
	size_t McciBootloader_codeSize(
		const void *base,
		const void *top
		);

Description:
	`base` points to the first byte in the region; `top`
	points one byte past the last byte in the region. The result is the number
	of bytes in the region. Note that a zero-size region
	is indicated by top being equal to base (as a uint8_t),
	and it's not possible to represent a region that's larger
	than SIZE_MAX.

Returns:
	Number of bytes in region.

Notes:
	The result can't represent the entire address space.

*/

static inline
size_t McciBootloader_codeSize(const void *base, const void *top)
        {
        return (const uint8_t *)top - (const uint8_t *)base;
        }

MCCIADK_END_DECLS
#endif /* _MCCI_BOOTLOADER_H_ * /
