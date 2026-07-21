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

#include "mcci_bootloader.h"
#include "mcci_bootloader_device_i2c_bus_stm32l0.h"
#include "mcci_bootloader_device_i2c_device_stm32l0.h"
#include "mcci_bootloader_device_npm1300.h"
#include "mcci_npm1300.h"
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
g_McciBootloaderBoard_Catena5230_i2cDevice_NPM1300;

McciBootloaderDeviceNpm1300_t *
g_McciBootloaderBoard_Catena5230_pNPM1300;

/*

Name:	McciBootloaderBoard_Catena5230_systemInit()

Function:
	System init platform method for Catena 5230 boards.

Definition:
	void McciBootloaderBoard_Catena5230_systemInit(
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

#define FUNCTION "McciBootloaderBoard_Catena5230_systemInit"

void
McciBootloaderBoard_Catena5230_systemInit(
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
		&gk_McciBootloaderDeviceI2cBusStm32l0_Config_I2c2, 	// i2c controller info
		MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_100K,                                           // timingr for 100k I2C
		MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_400K,
		MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_1M
		);

	// set up the pins of the I2C bus (PB10, PB11)
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_MODER,
		(MCCI_STM32L0_GPIO_MODE_P(11) |
		 MCCI_STM32L0_GPIO_MODE_P(10)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(11), MCCI_STM32L0_GPIO_MODE_AF) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(10), MCCI_STM32L0_GPIO_MODE_AF))
		);

	// set up pins as AF6
	MCCIADK_C_ASSERT(MCCI_STM32L0_GPIO_AFRx_P(11) == MCCI_STM32L0_GPIO_AFRx_P(10));

	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_AFRx_P(11),
		(MCCI_STM32L0_GPIO_AFSEL_P(11) |
		 MCCI_STM32L0_GPIO_AFSEL_P(10)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_AFSEL_P(11), 6 /* I2C2 */) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_AFSEL_P(10), 6 /* I2C2 */))
		);

	// set up i2c pins as pull-up
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_PUPDR,
		(MCCI_STM32L0_GPIO_PUPD_P(11) |
		 MCCI_STM32L0_GPIO_PUPD_P(10)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(11), MCCI_STM32L0_GPIO_PUPD_PULLUP) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(10), MCCI_STM32L0_GPIO_PUPD_PULLUP))
		);

	// set up i2c pins as open drain
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_OTYPER,
		(MCCI_STM32L0_GPIO_OTYPE_P(11) |
		 MCCI_STM32L0_GPIO_OTYPE_P(10)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OTYPE_P(11), MCCI_STM32L0_GPIO_OTYPE_OD) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OTYPE_P(10), MCCI_STM32L0_GPIO_OTYPE_OD))
		);

	// set up i2c pins as medium speed, so we can run with 400k if
	// we want.
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_OSPEEDR,
		(MCCI_STM32L0_GPIO_OSPEED_P(11) |
		 MCCI_STM32L0_GPIO_OSPEED_P(10)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(11), MCCI_STM32L0_GPIO_OSPEED_MEDIUM) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(10), MCCI_STM32L0_GPIO_OSPEED_MEDIUM))
		);

	// createAndAttach will also call the platform abort method for errors.
	g_McciBootloaderBoard_Catena5230_pNPM1300 =
		McciBootloaderDevice_NPM1300_createAndAttach(
			&pI2cBus->I2cBusCast,
			&g_McciBootloaderBoard_Catena5230_i2cDevice_NPM1300.I2cDeviceCast,
			sizeof(g_McciBootloaderBoard_Catena5230_i2cDevice_NPM1300)
			);

	// the device driver is created and initialized, now
	// we set the registers for our platform.
	const static McciBootloaderDevice_NPM1300_Init_t pmicInitTable[] =
		{
		{ MCCI_PMIC_NPM1300_REG_BCHGVTERM,         0x08 },
		{ MCCI_PMIC_NPM1300_REG_BCHGVTERMR,        0x08 },
		{ MCCI_PMIC_NPM1300_REG_BCHGDISABLESET,    0x02 },
		{ MCCI_PMIC_NPM1300_REG_BCHGDISABLECLR,    0x01 },
		{ MCCI_PMIC_NPM1300_REG_BCHGISETMSB,       0xC8 },
		{ MCCI_PMIC_NPM1300_REG_BCHGISETLSB,       0x00 },
		{ MCCI_PMIC_NPM1300_REG_BCHGDISABLESET,    0x02 },
		{ MCCI_PMIC_NPM1300_REG_BCHGENABLESET,     0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCKENASET_1,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCKENACLR_1,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCKNORMVOUT_1,    0x17 },
		{ MCCI_PMIC_NPM1300_REG_BUCKSWCTRLSEL,     0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCKENASET_2,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_BUCKENACLR_2,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_LDSWLDOSEL_1,      0x01 },
		{ MCCI_PMIC_NPM1300_REG_LDSWVOUTSEL_1,     0x17 },
		{ MCCI_PMIC_NPM1300_REG_LDSWLDOSEL_2,      0x00 },
		{ MCCI_PMIC_NPM1300_REG_TASKLDSWSET_1,     0x01 },
		{ MCCI_PMIC_NPM1300_REG_TASKLDSWCLR_2,     0x01 },
		{ MCCI_PMIC_NPM1300_REG_VBUSINILIMSTARTUP, 0x0F },
		{ MCCI_PMIC_NPM1300_REG_LEDDRVMODESEL_0,   0x01 },
		{ MCCI_PMIC_NPM1300_REG_LEDDRVMODESEL_1,   0x00 },
		};

	const McciBootloaderDeviceI2cResult_t result =
		McciBootloaderDevice_NPM1300_initializeRegisters(
			g_McciBootloaderBoard_Catena5230_pNPM1300,
			pmicInitTable,
			MCCIADK_LENOF(pmicInitTable)
			);

	if (result != McciBootloaderDeviceI2cResult_OK)
		{
		McciBootloaderPlatform_fail(McciBootloaderError_PmicInitFailed);
		}

	// the PMIC is now set up correctly.
	}

#undef FUNCTION

/**** end of mccibootloaderboard_catena5230_systeminit.c ****/
