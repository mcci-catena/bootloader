/*

Module:	mcci_bootloader_board_catena5230.h

Function:
	Definitions for bootloader on MCCI Catena 5230.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_board_catena5230_h_
#define _mcci_bootloader_board_catena5230_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_platform_h_
# include "mcci_bootloader_platform.h"
#endif

#ifndef _mcci_bootloader_board_catena_1sj_h_
# include "mcci_bootloader_board_catena_1sj.h"
#endif

#ifndef _mcci_bootloader_device_i2c_bus_stm32l0_types_
# include "mcci_bootloader_device_i2c_bus_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_device_stm32l0_types_h_
# include "mcci_bootloader_device_i2c_device_stm32l0_types.h"
#endif

#ifndef _mcci_bootloader_device_npm1300_types_h_
# include "mcci_bootloader_device_npm1300_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

McciBootloaderPlatform_SystemInitFn_t
McciBootloaderBoard_Catena5230_systemInit;

McciBootloaderPlatform_PrepareForLaunchFn_t
McciBootloaderBoard_Catena5230_prepareForLaunch;

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderBoard_Catena5230_storageInit;

extern McciBootloaderDeviceI2cBusStm32l0_t
g_McciBootloaderBoard_Catena5230_i2cBus2;

extern McciBootloaderDeviceI2cDeviceStm32l0_t
g_McciBootloaderBoard_Catena5220_i2cDevice_NPM1300;

extern McciBootloaderDeviceNpm1300_t *
g_McciBootloaderBoard_Catena5230_pNPM1300;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_catena5230_h_ */
