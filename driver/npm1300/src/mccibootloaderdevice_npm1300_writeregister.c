/*

Module:	mccibootloaderdevice_npm1300_writeregister.c

Function:
	McciBootloaderDevice_NPM1300_writeRegister()

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
McciBootloaderDevice_NPM1300_writeRegister(
	McciBootloaderDeviceNpm1300_t *pPmic,
	uint16_t wAddress,
	uint8_t bValue
	)
	{
	uint8_t messageBuf[3];	// 2 bytes for addess, one for value
	size_t nActual;

	// wAddress is big-endian, per figures 46 and 47 of Nordic
	// NPM1300-QEAA-R.pdf, section 7.1
	messageBuf[0] = (uint8_t) (wAddress >> 8);
	messageBuf[1] = (uint8_t) (wAddress & 0xFFu);
	messageBuf[2] = bValue;

	McciBootloaderDeviceI2cResult_t const result =
		(*pPmic->Npm1300.pI2cDevice->I2cDevice.pMethods->pWrite)(
			pPmic->Npm1300.pI2cDevice,
			messageBuf,
			sizeof(messageBuf),
			&nActual
			);

	if (result != McciBootloaderDeviceI2cResult_OK)
		return result;
	if (nActual != sizeof(messageBuf))
		return McciBootloaderDeviceI2cResult_InternalError;

	return McciBootloaderDeviceI2cResult_OK;
	}
