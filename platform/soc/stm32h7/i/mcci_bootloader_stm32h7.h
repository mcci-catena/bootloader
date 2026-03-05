/*

Module:	mcci_bootloader_stm32h7.h

Function:
	MCCI Bootloader STM32 H7 functions

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_stm32h7_h_
#define _mcci_bootloader_stm32h7_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_arm_cm7_h_
# include "mcci_arm_cm7.h"
#endif

#ifndef _mcci_bootloader_stm32h7_appimage_h_
# include "mcci_bootloader_stm32h7_appimage.h"
#endif

#ifndef _mcci_bootloader_platform_types_h_
# include "mcci_bootloader_platform_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/****************************************************************************\
|
|	Globals
|
\****************************************************************************/

///
/// \brief the Stm32 H7 vectors for the boot loader.
///
/// \details
///	The vectors are put in section \c .McciBootloader_Vectors -- be
///	sure to research the link script when making changes here.
///
/// \see mccibootloader.ld
///
extern const McciBootloader_Stm32H7PageZero_t
gk_McciBootloader_CortexVectors
__attribute__((__section__(".McciBootloader_Vectors")));

///
/// \brief the application signature block
///
/// \details
///	The signature block is put in section \c .McciBootloader_Signature -- be
///	sure to research the link script when making changes here.
///
/// \see mccibootloader.ld
///
extern const McciBootloader_SignatureBlock_t
gk_McciBootloader_SignatureBlock
__attribute__((__section__(".McciBootloader_Signature")));

/****************************************************************************\
|
|	API functions
|
\****************************************************************************/

void
McciBootloader_Stm32h7_systemInit(
	void
	);

void
McciBootloader_Stm32h7_prepareForLaunch(
	void
	);

McciBootloaderPlatform_SystemFlashEraseFn_t
McciBootloader_Stm32h7_systemFlashErase;

McciBootloaderPlatform_SystemFlashWriteFn_t
McciBootloader_Stm32h7_systemFlashWrite;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_stm32h7_h_ */
