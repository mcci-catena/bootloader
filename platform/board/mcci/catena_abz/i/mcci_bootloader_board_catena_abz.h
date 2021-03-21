/*

Module:	mcci_bootloader_board_catena_abz.h

Function:
	Top-level platform interface for MCCI Catenas based on the
	Murata type-ABZ module with the STM32L0.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_board_catena_abz_h_
#define _mcci_bootloader_board_catena_abz_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_bootloader_platform_h_
# include "mcci_bootloader_platform.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/****************************************************************************\
|
|	API functions.
|
\****************************************************************************/

McciBootloaderPlatform_SystemInitFn_t 
McciBootloaderBoard_CatenaAbz_systemInit;

McciBootloaderPlatform_PrepareForLaunchFn_t
McciBootloaderBoard_CatenaAbz_prepareForLaunch;

McciBootloaderPlatform_FailFn_t MCCI_BOOTLOADER_NORETURN_PFX
McciBootloaderBoard_CatenaAbz_fail 
MCCI_BOOTLOADER_NORETURN_SFX;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_catena_abz_h_ */
