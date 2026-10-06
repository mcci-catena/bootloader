/*

Module:	mccibootloaderdevice_begin.c

Function:
	Home of McciBootloaderDevice_begin()

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	July 2026

*/

#include "mcci_bootloader_device.h"

#include "mcci_bootloader_device_internal.h"

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

Name:	McciBootloaderDevice_begin()

Function:
	Start operation of a device.

Definition:
	bool McciBootloaderDevice_begin(
		McciBootloaderDevice_t *pDevice
		);

Description:
	pDevice points to the abstract-device view
	of a bootloader device. This function initiates
	use of the device, calling the device-specific
	methods if the device is not already up.

Returns:
	true for success, false for failure.

*/

#define FUNCTION "McciBootloaderDevice_begin"

bool
McciBootloaderDevice_begin(
	McciBootloaderDevice_t *pDevice
	)
	{
	if (pDevice->Device.pMethods == NULL)
		{
		/* not initialized */
		return false;
		}
	if (pDevice->Device.status.flags.fStarted)
		return true;

	McciBootloaderDevice_BeginFn_t * const pBegin =
		pDevice->Device.pMethods->pBegin;
	bool result;

	result = true;
	if (pBegin != NULL)
		result = (*pBegin)(pDevice);

	if (result)
		pDevice->Device.status.flags.fStarted = true;

	return result;
	}

#undef FUNCTION
