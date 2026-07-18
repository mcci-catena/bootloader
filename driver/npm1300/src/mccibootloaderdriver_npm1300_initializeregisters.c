/* mccibootloaderdriver_npm1300_initializeregisters.c	Fri Jul 17 2026 21:22:07 tmm */

/*

Module:	mccibootloaderdriver_npm1300_initializeregisters.c

Function:
	McciBootloaderDriver_NPM1300_initializeRegisters()

Version:
	Vx.yy	Fri Jul 17 2026 21:22:07 tmm	Edit level 1

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

*/

#include "mcci_bootloader_device_npm1300.h"

#include "mcci_bootloader_device_i2c_device.h"

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

McciBootloaderDeviceI2cResult_t
McciBootloaderDevice_NPM1300_initializeRegisters(
	McciBootloaderDeviceNpm1300_t *pPmic,
	const McciBootloaderDriver_NPM1300_Init_t *pvInitValues,
	size_t nInitValues
	)
	{
	for (; nInitValues > 0; ++pvInitValues, --nInitValues)
		{
		uint8_t messageBuf[3];	// 2 bytes for addess, one for value
		uint16_t const address = pvInitValues->address;
		size_t nActual;

		// address is big-endian, per figures 46 and 47 of Nordic
		// NPM1300-QEAA-R.pdf, section 7.1
		messageBuf[0] = (uint8_t) (address >> 8);
		messageBuf[1] = (uint8_t) (address & 0xFFu);
		messageBuf[2] = pvInitValues->value;

		McciBootloaderDeviceI2cResult_t const result =
			(*pPmic->Npm1300.pI2cDevice->I2cDevice.pMethods->pWrite)(
				pPmic->Npm1300.pI2cDevice,
				messageBuf,
				sizeof(messageBuf),
				&nActual
				);

		if (result != McciBootloaderDeviceI2cResult_OK)
			return result;
		}

	return McciBootloaderDeviceI2cResult_OK;
	}


/**** end of mccibootloaderdriver_npm1300_initializeregisters.c ****/
