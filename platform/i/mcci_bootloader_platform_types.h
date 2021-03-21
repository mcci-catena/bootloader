/*

Module:	mcci_bootloader_platform_types.h

Function:
	Types for MCCI bootloader platform interface

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_platform_types_h_
#define _mcci_bootloader_platform_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

///
/// \brief function type for platform intialization function
///
/// \details Functions of this type are called by the bootloader after
///	RAM has been initialized. The function should set the system
///	clock speed set up any "always needed" peripherals.
///
typedef	void (McciBootloaderPlatform_SystemInitFn_t)(void);

///
/// \brief function type for preparing to launch an application
///
/// \details The bootloader calls this function just before jumping
///	to the application. The function is required to return the 
///	platform to a reset-like state (making the bootloader
///	maximally transparent).
///
typedef	void (McciBootloaderPlatform_PrepareForLaunchFn_t)(void);

///
/// \brief function for reporting a fatal error
///
/// \param [in] errorCode failure reason.
///
/// \details If a fatal error occurs during the boot, the bootloader
///	calls this function, which must not return. If possible, the
///	function displays the errorCode in a platform-specific way.
///
typedef void MCCI_BOOTLOADER_NORETURN_PFX
	(McciBootloaderPlatform_FailFn_t)(
		McciBootloaderError_t errorCode
		) MCCI_BOOTLOADER_NORETURN_SFX;

/// \brief interface structure
typedef struct McciBootloaderPlatform_Interface_s
McciBootloaderPlatform_Interface_t;

MCCI_BOOTLOADER_END_DECLS
#endif /* _mcci_bootloader_platform_types_h_ */
