/*

Module:	mcci_bootloader_platform.h

Function:
	Definitions for the platform API

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_platform_h_
#define _mcci_bootloader_platform_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_platform_types_h_
# include "mcci_bootloader_platform_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/// \brief interface structure to platform functions
struct McciBootloaderPlatform_Interface_s
	{
	McciBootloaderPlatform_SystemInitFn_t		*pSystemInit;		///< System init provider function
	McciBootloaderPlatform_PrepareForLaunchFn_t	*pPrepareForLaunch;	///< Prepare to launch application
	McciBootloaderPlatform_FailFn_t			*pFail;			///< Stop the boot, due to a failure
	};

extern const McciBootloaderPlatform_Interface_t
gk_McciBootloaderPlatformInterface;

static inline void
McciBootloaderPlatform_systemInit(void)
	{
	(*gk_McciBootloaderPlatformInterface.pSystemInit)();
	}

static inline void
McciBootloaderPlatform_prepareForLaunch(void)
	{
	(*gk_McciBootloaderPlatformInterface.pPrepareForLaunch)();
	}

void
MCCI_BOOTLOADER_NORETURN_PFX
McciBootloaderPlatform_fail(
	McciBootloaderError_t errorCode
	) MCCI_BOOTLOADER_NORETURN_SFX;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_platform_h_ */
