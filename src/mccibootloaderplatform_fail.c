/*

Module:	mccibootloaderplatform_fail.c

Function:
	McciBootloaderPlatform_fail()

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

/// \brief set to boot failure code.
McciBootloaderError_t g_McciBootloader_failureCode;

/*

Name:	McciBootloaderPlatform_fail()

Function:
	

Definition:
	void McciBootloaderPlatform_fail(
		McciBootloaderError_t error
		);

Description:
	Deal with a bootloader failure. Does not return.

Returns:
	No explicit result.

Notes:
	This version is the default stub; it just loops.

*/

#define FUNCTION "McciBootloaderPlatform_fail"

void
McciBootloaderPlatform_fail(
	McciBootloaderError_t error
	)
	{
	g_McciBootloader_failureCode = error;

	while(true)
		;
	}

#undef FUNCTION

/**** end of mccibootloaderplatform_fail.c ****/
