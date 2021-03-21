/*

Module:	mccibootloaderplatform_startapp.c

Function:
	McciBootloaderPlatform_startApp()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader.h"

#include "mcci_bootloader_bits.h"
#include "mcci_bootloader_cm0plus.h"
#include <stdint.h>

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

Name:	McciBootloaderPlatform_startApp()

Function:
	Launch application from bootloader.

Definition:
	void McciBootloaderPlatform_startApp(
		const void *pAppBase
		);

Description:
	pAppBase points to the base of the application image in memory, which
	is assumed to conform to any platform-specific requirements. The
	application is launched. If the launch fails,
	McciBootloaderPlatform_fail() is invoked. This function does not
	return to the caller.

Returns:
	No explicit result.

Notes:
	On a Cortex M0+ or similar processor, pAppBase points to the vectors
	of the app being invoked. The first dword is the stack pointer, and
	the second dword is the start address.

	In a full implementation, the bootloader should shutdown all
	peripherals it has setup, and establish a default condition for
	launching the app. In principal, the app should be entered as if
	it had received control from a reset. This is to some degree a
	matter of taste and design rather than a logical requirement.

*/

#define FUNCTION "McciBootloaderPlatform_startApp"

void
McciBootloaderPlatform_startApp(
	const void *pAppBase
	)
	{
	const uint32_t * const pAppVectors = pAppBase;
	const uint32_t stack = pAppVectors[0];
	const uint32_t pc = pAppVectors[2];

	// set the stack pointer
	McciBootloaderArm_setMSP(stack);

	// set the vector address
	McciBootloaderArm_putReg(
		MCCI_CM0PLUS_SCB_VTOR, 
		(uint32_t) pAppVectors & MCCI_CM0PLUS_SCB_VTOR_TBLOFF
		);

	// go to the app.
	asm("bx %0"::"r"(pc));
	__builtin_unreachable();
	}

#undef FUNCTION


/**** end of mccibootloaderplatform_startapp.c ****/
