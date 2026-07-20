/*

Module:	mccibootloaderdevice_npm1300_createandattach.c

Function:
	McciBootloaderDevice_NPM1300_createAndAttach()

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	July 2026

*/

#include "mcci_bootloader_device_npm1300.h"

#include "mcci_bootloader_device_i2c_bus.h"
#include "mcci_bootloader_device_i2c_device.h"
#include "mcci_bootloader_device_internal.h"
#include "mcci_npm1300.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static McciBootloaderDevice_BeginFn_t npm1300_begin;
static McciBootloaderDevice_EndFn_t npm1300_end;


/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

static const McciBootloaderDeviceMethods_t sk_npm1300_deviceMethods =
	{
	.pBegin = npm1300_begin,
	.pEnd = npm1300_end
	};

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

/// the device object for the NPM 1300
static McciBootloaderDeviceNpm1300_t s_npm1300;

/*

Name:	McciBootloaderDevice_NPM1300_createAndAttach()

Function:
	Initialize and attach an I2C device object for the NPM1300 PMIC.

Definition:
	McciBootloaderDeviceNpm1300_t *
		McciBootloaderDevice_NPM1300_createAndAttach(
			McciBootloaderDeviceI2cBus_t		*pI2cBus,
			McciBootloaderDeviceI2cDevice_t		*pI2cDeviceForPmic,
			size_t					sizeI2cDeviceForPmic
			)

Description:
	An I2C device object is initialized and attached to the specified
	I2C bus, using the memory provided at pI2cDeviceForPmic, which
	must be of size sizeI2cDeviceForPmic bytes.

Returns:
	Pointer to (statically allocated) NPM1300 device object, or NULL
	if there's an error.

Notes:
	Only one object is statically allocated, so it's an error to call
	this more than onece.

*/

McciBootloaderDeviceNpm1300_t *
McciBootloaderDevice_NPM1300_createAndAttach(
	McciBootloaderDeviceI2cBus_t		*pI2cBus,
	McciBootloaderDeviceI2cDevice_t		*pI2cDeviceForPmic,
	size_t					sizeI2cDeviceForPmic
	)
	{
	McciBootloaderDeviceNpm1300_t * const pNpm1300 = &s_npm1300;
	McciBootloaderDeviceI2cResult_t result;
	bool fBeginStatus;

	if (pNpm1300->Device.pMethods != NULL)
		// already inititialized.
		return NULL;

	// we need to ask the bus driver to init the device
	result = pI2cBus->I2cBus.pMethods->pAddDevice(
			pI2cBus,
			pI2cDeviceForPmic,
			sizeI2cDeviceForPmic,
			MCCI_PMIC_NPM1300_I2C_ADDRESS,
			McciBootloaderDeviceI2cSpeed_100k
			);

	if (result != McciBootloaderDeviceI2cResult_OK)
		return NULL;

	// do a begin on the device
	fBeginStatus = McciBootloaderDevice_begin(
			&pI2cDeviceForPmic->DeviceCast
			);

	if (! fBeginStatus)
		return NULL;

	pNpm1300->Device.pMethods = &sk_npm1300_deviceMethods;
	pNpm1300->Npm1300.pI2cDevice = pI2cDeviceForPmic;

	return pNpm1300;
	}

/*
|| we need to have a begin function.
|| createAndAttach does a begin, but caller might call and and then begin, so we make
|| this regular.
*/
static bool
npm1300_begin(McciBootloaderDevice_t *pDevice)
	{
	McciBootloaderDeviceNpm1300_t * const pNpm1300 = McciBootloaderDevice_getDeviceNpm1300(pDevice);
	McciBootloaderDeviceI2cDevice_t * const pI2cDevice =
			pNpm1300->Npm1300.pI2cDevice;

	const bool fI2cBeginResult = McciBootloaderDevice_begin(&pI2cDevice->DeviceCast);

	if (! fI2cBeginResult)
		return false;

	// now we can talk to I2C: we could do a probe.
	McciBootloaderDeviceI2cResult_t i2cResult;
	size_t nWritten;

	i2cResult = pI2cDevice->I2cDevice.pMethods->pWrite(
			pI2cDevice,
			NULL, 0,
			&nWritten
			);

	if (i2cResult != McciBootloaderDeviceI2cResult_OK)
		{
		// stop the bus's device
		(void) McciBootloaderDevice_end(&pI2cDevice->DeviceCast);

		// PMIC failed to probe.
		return false;
		}

	// mark as started
	return true;
	}

static bool
npm1300_end(McciBootloaderDevice_t *pDevice)
	{
	McciBootloaderDeviceNpm1300_t * const pNpm1300 = McciBootloaderDevice_getDeviceNpm1300(pDevice);
	McciBootloaderDeviceI2cDevice_t * const pI2cDevice =
			pNpm1300->Npm1300.pI2cDevice;

	(void) McciBootloaderDevice_end(&pI2cDevice->DeviceCast);

	return true;
	}

/**** end of mccibootloaderdevice_npm1300_createandattach.c ****/
