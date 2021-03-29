/*

Module:	mcci_bootloader_stm32l0.h

Function:
	MCCI Bootloader STM32L0 functions

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_stm32l0_h_
#define _mcci_bootloader_stm32l0_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_arm_cm0plus_h_
# include "mcci_arm_cm0plus.h"
#endif

#ifndef _mcci_bootloader_cm0plus_appimage_h_
# include "mcci_bootloader_cm0plus_appimage.h"
#endif

#ifndef _mcci_bootloader_platform_types_h_
# include "mcci_bootloader_platform_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/****************************************************************************\
|
|	API functions
|
\****************************************************************************/

void
McciBootloader_Stm32L0_systemInit(
	void
	);

void
McciBootloader_Stm32L0_prepareForLaunch(
	void
	);

extern const McciBootloader_CortexPageZero_t
gk_McciBootloader_CortexVectors;

McciBootloaderPlatform_SystemFlashEraseFn_t
McciBootloader_Stm32L0_systemFlashErase;

McciBootloaderPlatform_SystemFlashWriteFn_t
McciBootloader_Stm32L0_systemFlashWrite;

MCCI_BOOTLOADER_END_DECLS
#endif /* _mcci_bootloader_stm32l0_h_ */
