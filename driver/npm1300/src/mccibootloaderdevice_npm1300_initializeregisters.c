/*

Module:	mccibootloaderdevice_npm1300_initializeregisters.c

Function:
	McciBootloaderDevice_NPM1300_initializeRegisters()

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
	const McciBootloaderDevice_NPM1300_Init_t *pvInitValues,
	size_t nInitValues
	)
	{
	for (; nInitValues > 0; ++pvInitValues, --nInitValues)
		{
		McciBootloaderDeviceI2cResult_t const result =
			McciBootloaderDevice_NPM1300_writeRegister(
				pPmic, pvInitValues->address, pvInitValues->value
				);

		if (result != McciBootloaderDeviceI2cResult_OK)
			return result;
		}

	return McciBootloaderDeviceI2cResult_OK;
	}

/**** end of mccibootloaderdevice_npm1300_initializeregisters.c ****/
