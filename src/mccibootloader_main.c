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

#include "mcci_bootloader_appinfo.h"
#include "mcci_bootloader_platform.h"

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

McciBootloader_AppInfo_t g_McciBootloader_appInfo;

/*

Name:  McciBootloader_main()

Function:
	Entry point for MCCI STM32 bootloader.

Definition:
	void McciBootloader_main(void);

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
        specific things.  As usual at MCCI, we avoid #if.

        Functions named McciBootloaderPlatform_* map (via static
        inline) to code that is specific to the targeted platform.
        The MCCI implementation uses our usual style of function
        pointers and drivers; but the table is static.

        It takes a long time to verify a ed25519 signature on the STM32L0;
        so we only check signatures when deciding whether to update
        the flash. Otherwise we check the SHA512. The program format
        still includes the signature, but we only check this when
        deciding whether to apply it to the flash.

        The sequence is as follows:

        1. If the boardloader hash is not valid, we stop with a failure code.
        2. Otherwise, there is a saved boot loader state. The state can be
           either "update" or "go".  If state is "go", we compute the
           hash on the application image; if it's valid, we launch it.
        3. The flag is set to "update", or the application is invalid, so we ask
           the platform to enable the flash
           driver. (This may bring up power to the flash chip, bring up the
           SPI bus, etc.)  We also ask the driver to enable notifications
           as this is going to take a while.
        4. We read through the flash application image.
           (Including hash and signature.) This involves reading 4k at a
           time and doing the signature check.
        5. If the flash app image is not valid, and the application image
           is valid, we reset the update flag and launch the application.
        6. If the flash image is valid, we erase the flash, clear the update
           flag, then program the new image into the app flash. When done,
           we check the hash. If not valid, we continue to the next step.
        7. If the flash app image is not valid, and the application image is
           not valid, we repeat step 4 using the "safety app" image. If the
           "safety app" is valid, we repeat step 6 with the safety app. If
           that fails, we fail with an indication (as at step 1).

        States we're trying to establish:

        Case    Boot    App     Flag    Flash   Safe    State
         (1)    NG      -       -       -       -       Halt with indication
         (2)    OK      OK      N       -       -       Launch app
         (3)    OK      OK      Y       NG      -       Launch app, clear flag
         (4)    OK      OK      Y       OK      -       Load flash, clear flag & reevaluate
                                                         (Power failure during flash will
                                                          bring us up in some App NG state)
         (5)    OK      NG      -       OK      -       Load flash, clear flag & reevaluate
         (6)    OK      NG      -       NG      OK      Load fallback flash, clear flag & and reevaluate
         (7)    OK      NG      -       NG      NG      Halt with indication

*/

void
McciBootloader_main(void)
        {
        const uint32_t bootloaderSize = McciBootloader_codeSize(&gk_McciBootloader_BootBase, &gk_McciBootloader_BootTop);
        /* run the platform entry code. This must be minimal, if it exists at all */
        McciBootloaderPlatform_entry();

        /* our first job is to check the hash of the boot loader */
        if (! McciBootloader_checkCodeValid(
                        &gk_McciBootloader_BootBase,
                        bootloaderSize
                        ))
                {
                /* Case (1): boot loader isn't valid */
                McciBootloaderPlatform_fail(McciBootloaderError_BootloaderNotValid);
                }

        /* next, we check the hash of the application */
        bool const appOk = McciBootloader_checkCodeValid(
                                &gk_McciBootloader_AppBase,
                                McciBootloader_codeSize(&gk_McciBootloader_AppBase, &gk_McciBootloader_AppTop)
                                );

        /* check the update flag */
        bool fFirmwareUpdatePending;

        fFirmwareUpdatePending = McciBootloaderPlatform_getUpdateFlag();
        if (appOk && ! fFirmwareUpdatePending)
                {
                /* Case (2): looks like we're good to launch the application */
                McciBootloaderPlatform_startApp(&gk_McciBootloader_AppBase);
                }

        /* initialize the storage and annunciator drivers */
        McciBootloaderPlatform_storageInit();
        McciBootloaderPlatform_annunciatorInit();

        /* check the app image */
        do      {
                /* because of power failures, don't clear the update-image flag just yet */

                /* start with the primary image */
                McciBootloaderStorageAddress_t const hPrimary = McciBootloaderPlatform_getPrimaryStorageAddress();

                /* indicate that we're checking the storage */
                McciBootloaderPlatform_annunciatorIndicateState(
                        McciBootloaderState_CheckingPrimaryStorageHash
                        );

                const bool fImageOk = McciBootloader_checkStorageImage(
                                                hPrimary,
                                                &g_McciBootloader_appInfo,
                                                &McciBootloaderPlatform_getAppInfo(&gk_McciBootloader_BootBase, bootloaderSize)->publicKey
                                                );

                /* check for Case (3) */
                if (appOk && !fImageOk)
                        {
                        /* case (3): looks like we're good to launch the application */
                        /* consume the storage flag; don't check again until asked */
                        McciBootloaderPlatform_setUpdateFlag(false);
                        McciBootloaderPlatform_startApp(&gk_McciBootloader_AppBase);
                        }

                /* case (4) or (5), maybe */
                McciBootloaderError_t programResult;

                /* as soon as we've erased the app, we'll reset the storage flag inside the routine below */
                programResult = McciBootloader_programAndCheckFlash(
                                        hPrimary,
                                        &g_McciBootloader_appInfo
                                        );
                if (programResult == McciBootloaderError_OK)
                        {
                        /* definitely (4) or (5): launch the application */
                        McciBootloaderPlatform_startApp(&gk_McciBootloader_AppBase);
                        }
                else
                        {
                        McciBootloaderPlatform_fail(programResult);
                        }

                /* otherwise app is invalid so try the fallback image */
                } while (0);

        /* case (6) or (7) */
        do      {
                McciBootloaderStorageAddress_t const hFallback = McciBootloaderPlatform_getFallbackStorageAddress();

                McciBootloaderError_t fImageOk;

                fImageOk = McciBootloaderError_OK;
                if (! McciBootloader_checkStorageImage(
                        hFallback,
                        &g_McciBootloader_appInfo,
                        &McciBootloaderPlatform_getAppInfo(&gk_McciBootloader_BootBase, bootloaderSize)->publicKey
                        )
                    )
                        {
                        fImageOk = McciBootloaderError_NoAppImage;
                        }

                if (fImageOk == McciBootloaderError_OK)
                        {
                        fImageOk = McciBootloader_programAndCheckFlash(
                                                hFallback,
                                                &g_McciBootloader_appInfo
                                                );
                        }

                if (fImageOk == McciBootloaderError_OK)
                        {
                        /* case (6) */
                        McciBootloaderPlatform_startApp(&gk_McciBootloader_AppBase);
                        }

                /* case (7) */
                McciBootloaderPlatform_fail(McciBootloaderError_NoAppImage);
                } while (0);
        }
