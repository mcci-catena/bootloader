/*

Module:	mccibootloaderdevice_end.c

Function:
	Home of McciBootloaderDevice_end()

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

Name:	McciBootloaderDevice_end()

Function:
	Stop operation of a device.

Definition:
	bool McciBootloaderDevice_end(
		McciBootloaderDevice_t *pDevice
		);

Description:
	pDevice points to the abstract-device view
	of a bootloader device. This function terminates
	use of the device, calling the device-specific
	methods if the device is not already stopped.

Returns:
	true for success, false for failure.

*/

bool
McciBootloaderDevice_end(
	McciBootloaderDevice_t *pDevice
	)
	{
	if (pDevice->Device.pMethods == NULL)
		{
		/* not initialized */
		return false;
		}
	if (! pDevice->Device.status.flags.fStarted)
		return true;

	McciBootloaderDevice_EndFn_t * const pEnd =
		pDevice->Device.pMethods->pEnd;
	bool result;

	result = true;
	if (pEnd != NULL)
		result = (*pEnd)(pDevice);

	if (result)
		pDevice->Device.status.flags.fStarted = false;

	return result;
	}
