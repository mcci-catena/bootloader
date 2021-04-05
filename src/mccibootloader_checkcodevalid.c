/* mccibootloader_checkcodevalid.c	Tue Jul 14 2020 11:31:05 tmm */

/*

Module:  mccibootloader_checkcodevalid.c

Function:
	McciBootloader_checkCodeValid().

Version:
	V0.1.0	Tue Jul 14 2020 11:31:05 tmm	Edit level 1

Copyright notice:
	This file copyright (C) 2020 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.

Author:
	Terry Moore, MCCI Corporation	July 2020

Revision history:
   0.1.0  Tue Jul 14 2020 11:31:05  tmm
	Module created.

*/

#include "mcci_bootloader.h"

#include "mcci_bootloader_appinfo.h"
#include "mcci_bootloader_platform.h"
#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"

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

Name:	McciBootloader_checkCodeValid()

Function:
	Check whether a region of code is valid.

Definition:
	bool McciBootloader_checkCodeValid(
		const void *pBase,
		size_t nBytes
		);

Description:
	This function validates a NOR-flash app image to
	confirm that it looks like a valid image for this
	device.

	We check the following conditions.

	* The pointer must be properly aligned so that we
	  can set the vector table to the address (multiple
	  of 256).
	* The first dword in the image (the stack pointer)
	  must be DWORD aligned and must point into system RAM.
	* There must be a valid header at the beginning of the
	  region -- the first 64+128 bytes are the vector image
	  image; the next 4 bytes specify the size of the image,
	  in bytes. This size must be less then or equal to
	  `nBytes`.
	* The signature of the region must be valid. (This
	  is initially a CRC32, but may change to ED25519,
	  if that doesn't bloat the bootloader.
	* The reset vector must be odd (Thumb mode) and
	  must point into the image.

	We assume the image is completely visible, but
	in order to share code with the SPI flash validation
	we locate regions and then call subroutines.

Returns:
	This function returns true if the image is valid,
	false otherwise.

*/

bool
McciBootloader_checkCodeValid(
	const void *pBase,
	size_t nBytes
	)
	{
	// compute the hash over pBase
	mcci_tweetnacl_sha512_t hash;
	mcci_tweetnacl_result_t invalid;
	const McciBootloader_AppInfo_t *pAppInfo;

	// check whether the image is valid.
	pAppInfo = McciBootloaderPlatform_checkImageValid(pBase, nBytes, (uintptr_t)pBase, nBytes);
	if (pAppInfo == NULL)
		return false;

	// compute the hash
	mcci_tweetnacl_hash_sha512(
		&hash,
		pBase,
		pAppInfo->imagesize + sizeof(mcci_tweetnacl_sign_publickey_t)
		);

	// find the signature block
	const McciBootloader_SignatureBlock_t * const pSigBlock =
		(const void *)((const uint8_t *)pBase + pAppInfo->imagesize);

	invalid = mcci_tweetnacl_verify_64(
				hash.bytes,
				pSigBlock->hash.bytes
				);

	return mcci_tweetnacl_result_is_success(invalid);
	}
