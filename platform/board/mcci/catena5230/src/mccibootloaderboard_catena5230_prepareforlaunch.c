/*

Module:	mccibootloaderboard_catena5230_prepareforlaunch.c

Function:
	McciBootloaderBoard_Catena5230_prepareForLaunch()

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_board_catena5230.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_board_catena_1sj.h"
#include "mcci_bootloader_device_i2c_bus_stm32l0.h"
#include "mcci_bootloader_device_npm1300.h"
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

Name:	McciBootloaderBoard_Catena5230_prepareForLaunch()

Function:
	Platform interface: prepare for launch of app on 5230.

Definition:
	void McciBootloaderBoard_Catena5230_prepareForLaunch(
		void
		);

Description:
	Return the board and the SOC to the boot state.
	Delegates to common Catena1SJ logic.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderBoard_Catena5230_prepareForLaunch(
	void
	)
	{
	const McciBootloaderDeviceI2cResult_t result =
		McciBootloaderDevice_NPM1300_writeRegister(
			g_McciBootloaderBoard_Catena5230_pNPM1300,
			MCCI_PMIC_NPM1300_REG_TASKLDSWCLR_2,
			1
			);

	if (result != McciBootloaderDeviceI2cResult_OK)
		{
		McciBootloaderPlatform_fail(McciBootloaderError_StoragePowerDownFailed);
		}

	// done with the PMIC
	(void) McciBootloaderDevice_end(&g_McciBootloaderBoard_Catena5230_pNPM1300->DeviceCast);

	// done with the I2C bus
	(void) McciBootloaderDevice_end(&g_McciBootloaderBoard_Catena5230_i2cBus2.DeviceCast);

	// tear down everything else.
	McciBootloaderBoard_Catena1sj_prepareForLaunch();
	}

/**** end of mccibootloaderboard_catena5230_prepareforlaunch.c ****/
