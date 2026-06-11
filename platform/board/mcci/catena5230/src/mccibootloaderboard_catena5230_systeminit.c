/*

Module:	mccibootloaderboard_catena5230_systeminit.c

Function:
	McciBootloaderBoard_Catena5230_systemInit().

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#include "mcci_bootloader_board_catena5230.h"

#include "mcci_bootloader_device_i2c_bus_stm32l0.h"
#include "mcci_bootloader_device_i2c_device_stm32l0.h"
#include "mcci_bootloader_device_npm1300.h"
#include "mcci_stm32l0xx.h"

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

McciBootloaderDeviceI2cBusStm32l0_t
g_McciBootloaderBoard_Catena5230_i2cBus2;

McciBootloaderDeviceI2cDeviceStm32l0_t
g_McciBootloaderBoard_Catena5220_i2cDevice_NPM1300;

McciBootloaderDeviceNpm1300_t *
g_McciBootloaderBoard_Catena5230_pNPM1300;

/*

Name:	McciBootloaderBoard_Catena5320_systemInit()

Function:
	System init platform method for Catena 5230 boards.

Definition:
	void McciBootloaderBoard_Catena5320_systemInit(
		void
		);

Description:
	This routine initializes the platform. First it does
	the common initialization, then sets up the I2C bus and
	finally the PMIC.

Returns:
	No explicit result.

Notes:
	Asserts if any failures occur.

*/

#define FUNCTION "McciBootloaderBoard_Catena5320_systemInit"

void
McciBootloaderBoard_Catena5320_systemInit(
	void
	)
	{
	// initialize things that are common for all Catena boards
	// based on the 1sj module.
	McciBootloaderBoard_Catena1sj_systemInit();

	// set up the i2c bus for talking to the PMIC
	McciBootloaderDeviceI2cBusStm32l0_t * const pI2cBus =
		&g_McciBootloaderBoard_Catena5230_i2cBus2;

	// initI2cBus will call the platform abort method for errors.
	McciBootloader_Stm32L0Interface_initI2cBus(
		pI2cBus, sizeof(*pI2cBus),
		MCCI_STM32L0_REG_I2C2,                                // base address of controller
		0x10B07EBA,                                           // timingr for 115k I2C
		MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED,    // no 400k
		MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED     // no 1m
		);

	// createAndAttach will also call the platform abort method for errors.
	g_McciBootloaderBoard_Catena5230_pNPM1300 =
		McciBootloaderDriver_NPM1300_createAndAttach(
			pI2cBus,
			&g_McciBootloaderBoard_Catena5220_i2cDevice_NPM1300,
			sizeof(g_McciBootloaderBoard_Catena5220_i2cDevice_NPM1300)
			);

	// the device driver is created and initialized, now
	// we set the registers for our platform.
	// we assume that the PMIC drivers exports McciBootloaderDriver_PmicNPM1300_Init_t,
	// which is a register/value pair.
	const static McciBootloaderDriver_NPM1300_Init_t pmicInitTable[] =
		{
		{ MCCI_PMIC_NPM1300_REG_BCHGVTERM,         0x08 },
		{ MCCI_PMIC_NPM1300_REG_BCHGVTERMR,        0x08 },
		{ MCCI_PMIC_NPM1300_REG_BCHGDISABLESET,    0x02 },
		{ MCCI_PMIC_NPM1300_REG_BCHGDISABLECLR,    0x01 },
		{ MCCI_PMIC_NPM1300_REG_BCHGISETMSB,       0xC8 },
		{ MCCI_PMIC_NPM1300_REG_BCHGISETLSB,       0x00 },
		{ MCCI_PMIC_NPM1300_REG_BCHGDISABLESET,    0x02 },
		{ MCCI_PMIC_NPM1300_REG_BCHGENABLESET,     0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCK1ENASET,       0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCK1ENACLR,       0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCK1NORMVOUT,     0x17 },
		{ MCCI_PMIC_NPM1300_REG_BUCKSWCTRLSEL,     0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCK2ENASET,       0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCK2ENACLR,       0x01 },
		{ MCCI_PMIC_NPM1300_REG_LDSW1LDOSEL,       0x01 },
		{ MCCI_PMIC_NPM1300_REG_LDSW1VOUTSEL,      0x17 },
		{ MCCI_PMIC_NPM1300_REG_LDSW2LDOSEL,       0x00 },
		{ MCCI_PMIC_NPM1300_REG_TASKLDSW2SET,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_TASKLDSW2CLR,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_VBUSINILIMSTARTUP, 0x0F },
		{ MCCI_PMIC_NPM1300_REG_LEDDRV0MODESEL,    0x01 },
		{ MCCI_PMIC_NPM1300_REG_LEDDRV1MODESEL,    0x00 },
		};

	McciBootloaderDevice_NPM1300_initializeRegisters(
		g_McciBootloaderBoard_Catena5230_pNPM1300,
		pmicInitTable,
		MCCIADK_LENOF(pmicInitTable)
		);

	// the PMIC is now set up correctly.
	}

#undef FUNCTION

/**** end of mccibootloaderboard_catena5230_systeminit.c ****/
