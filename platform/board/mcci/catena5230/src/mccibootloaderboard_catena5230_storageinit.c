/*

Module:	mccibootloaderboard_catena5230_storageinit.c

Function:
	McciBootloaderBoard_Catena5230_storageInit()

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	July 2026

*/

#include "mcci_bootloader_board_catena5230.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_device_npm1300.h"
#include "mcci_bootloader_flash_mx25v8035f.h"
#include "mcci_npm1300.h"

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

Name:	McciBootloaderBoard_Catena5230_storageInit()

Function:
	Initialize the Catena5230 external storage.

Definition:
	typedef McciBootloaderPlatform_StorageInit_t
		McciBootloaderBoard_Catena5230_storageInit;

	void McciBootloaderBoard_Catena5230_storageInit(
		void
		);

Description:
	Initialize SPI, init the external flash, and we're ready.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Catena5230_storageInit(
	void
	)
	{
	static const McciBootloaderDevice_NPM1300_Init_t ldsw2_enable[] =
		{
		{ .address = MCCI_PMIC_NPM1300_REG_LDSWLDOSEL_2, .value = 0 },
		{ .address = MCCI_PMIC_NPM1300_REG_TASKLDSWSET_2, .value = 1 },
		};

	// turn on the power supply.
	McciBootloaderDeviceI2cResult_t const result =
		McciBootloaderDevice_NPM1300_initializeRegisters(
			g_McciBootloaderBoard_Catena5230_pNPM1300,
			ldsw2_enable,
			MCCIADK_LENOF(ldsw2_enable)
			);

	// fail if the I2C transfer failed.
	if (result != McciBootloaderDeviceI2cResult_OK)
		{
		McciBootloaderPlatform_fail(McciBootloaderError_StoragePowerUpFailed);
		}

	// give the power supply 50ms to turn on.
	McciBootloaderPlatform_delayMs(50);

	McciBootloaderPlatform_spiInit();
	McciBootloaderFlash_Mx25v8035f_storageInit();
	}

/**** end of mccibootloaderboard_catena5230_storageinit.c ****/
