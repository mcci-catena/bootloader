/*

Module:	mccibootloaderdevice_npm1300_writeregister.c

Function:
	McciBootloaderDevice_NPM1300_writeRegister()

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


/*

Name:	McciBootloaderDevice_NPM1300_writeRegister()

Function:
	Write a single register value to the NPM1300 PMIC.

Definition:
	McciBootloaderDeviceI2cResult_t
		McciBootloaderDevice_NPM1300_writeRegister(
			McciBootloaderDeviceNpm1300_t *pPmic,
			uint16_t wAddress,
			uint8_t bValue
			);

Description:
	A three byte sequence, consisting of bits 15..8 of wAddress,
	bits 7..0 of wAddress, and bValue, is written to the NPM1300
	as a single transaction.

Returns:
	McciBootloaderDeviceI2cResult_OK for success, some other value for
	failure.

Notes:
	If the I2C bus returns success, but the number of bytes transferred
	doesn't match expectations, this routine returns
	McciBootloaderDeviceI2cResult_BusError.

*/

McciBootloaderDeviceI2cResult_t
McciBootloaderDevice_NPM1300_writeRegister(
	McciBootloaderDeviceNpm1300_t *pPmic,
	uint16_t wAddress,
	uint8_t bValue
	)
	{
	// 2 bytes for addess, one for value.
	// Address on bus is big-endian, per figures 46 and 47 of Nordic
	// NPM1300-QEAA-R.pdf, section 7.1
	const uint8_t messageBuf[3] =
		{
		[0] = (uint8_t) (wAddress >> 8),
		[1] = (uint8_t) (wAddress & 0xFFu),
		[2] = bValue,
		};
	size_t nActual;

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
		return McciBootloaderDeviceI2cResult_BusError;

	return McciBootloaderDeviceI2cResult_OK;
	}
