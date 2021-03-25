/*

Module:	mccibootloaderplatform_entry.c

Function:
	McciBootloaderPlatform_entry()

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

#include "mcci_bootloader_platform.h"
#include <string.h>

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

Name:	McciBootloaderPlatform_entry()

Function:
	Perform platform-specific initialization.

Definition:
	void McciBootloaderPlatform_entry(
		void
		);

Description:
	This routine initalizes zero RAM, copies init data to RAM, and sets
	up the hardawre. Key hardware setup: clocks, potentially the debug UART,
	and brown-out detect.

Returns:
	No explicit result.

Notes:


*/

#define FUNCTION "McciBootloaderPlatform_entry()"

void
McciBootloaderPlatform_entry(
	void
	)
	{
	const size_t nData = McciBootloader_codeSize(&g_McciBootloader_DataBase, &g_McciBootloader_DataTop);
	const size_t nBss = McciBootloader_codeSize(&g_McciBootloader_BssBase, &g_McciBootloader_BssTop);

	/* copy the initialized data */
	memcpy(&g_McciBootloader_DataBase, &gk_McciBootloader_DataImageBase, nData);

	/* zero BSS */
	memset(&g_McciBootloader_BssBase, 0, nBss);

	/* call the platform init function */
	McciBootloaderPlatform_systemInit();
	}

#undef FUNCTION

/**** end of mccibootloaderplatform_entry.c ****/
