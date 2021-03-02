/* mccibootloader_main.h	Tue Jul 14 2020 11:31:05 tmm */

/*

Module:  mccibootloader_main.h

Function:
	Format of on-media data for the MCCI bootloader.

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


/*

Name:  McciBootloader_Main()

Function:
	Entry point for MCCI STM32 bootloader.

Definition:
	void McciBootloader_Main(void);

Description:
	This function is called by the ROM boot loader, and implements
        the MCCI SPI flash bootloading functionality for MCCI
        Catena baords based on the STM32L0.

        Input parameters come from the linker via symbols defined in
        the ld script for the linker.

Returns:
	No explicit result. Doesn't return.

Implementation notes:
        Our reuse model is to have non-portable code at the
        outer edges, and (potentially) portable code as library
        functions. So the logic for parsing the flash structure,
        checking the signature on the flash, etc., is in pure
        functions that shoudl have no hardware dependency. Those
        modules should not #include anything that is STM32L0-
        specific. The outer drivers are allowed to do STM32L0-
        specific things.  As usual at MCCI, we avoid #if, but
        we allow the outer drivers to use #if as needed, to 
        minimize code footprint.

        Functions named McciBootloaderPlatform_* are expected
        to map (possibly via static inline) to code that is
        specific to the targeted platform. 

*/

void
McciBootloader_Main(void)
        {
        /* run the platform entry code. This must be minimal, if it exists at all */
        McciBootloaderPlatform_Entry();

        /* our first job is to check the signature of the boot loader */
        if (! McciBootloader_checkCodeValid(&gk_McciBootloader_SelfBase, McciBootloader_codeSize(&gk_McciBootloader_SelfBase, &gk_McciBootloader_SelfTop)))
                {
                /* boot loader isn't valid */
                McciBootloaderPlatform_fail(McciBootLoaderError_BootLoaderNotValid);
                }

        /* next, we check the signature of the application */
        if (! McciBootloader_checkCodeValid(&gk_McciBootloader_AppBase, McciBootloader_codesize(&gk_McciBootloader_AppBase, &gk_McciBootloader_AppTop)))
                {
                /* application isn't valid -- we don't know how to read flash yet */
                McciBootloaderPlatform_fail(McciBootLoaderError_AppNotValid);
                }

        /* looks like we're good to launch the application */
        McciBootloaderPlatform_startApp(&gk_McciBootloader_AppBase);
        }
