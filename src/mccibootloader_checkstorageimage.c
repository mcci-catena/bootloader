/*

Module:	mccibootloader_checkstorageimage.c

Function:
	McciBootloader_checkStorageImage()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader.h"

#include "mcci_bootloader_appinfo.h"
#include "mcci_bootloader_platform.h"
#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"

#include <string.h>

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

uint8_t
g_McciBootloader_imageBlock[4096];

/*

Name:	McciBootloader_checkStorageImage()

Function:
	Validate signature and layout of image from storage.

Definition:
	bool McciBootloader_checkStorageImage(
		McciBootloaderStorageAddress_t address,
		McciBootloader_AppInfo_t *pIncomingAppInfo, // OUT
		const mcci_tweetnacl_sign_publickey_t *pPublicKey
		);

Description:
	Read the header of the image and lightly validate it. Then
	scan through the image, calculating the SHA512, and finallly
	check the signature on the hash.

Returns:
	true for success, false for failure.

	If true, pIncomingAppInfo is set to the app info block read from the app.

Notes:
	This is slow, so we try to update the LED state with a progress
	indication.

*/

bool
McciBootloader_checkStorageImage(
	McciBootloaderStorageAddress_t address,
	McciBootloader_AppInfo_t *pIncomingAppInfo,
	const mcci_tweetnacl_sign_publickey_t *pPublicKey
	)
	{
	/* read the header */
	if (! McciBootloaderPlatform_storageRead(
		address,
		g_McciBootloader_imageBlock, sizeof(g_McciBootloader_imageBlock)
		))
		return false;

	const McciBootloader_AppInfo_t * const pAppInfoIn =
		McciBootloaderPlatform_getAppInfo(g_McciBootloader_imageBlock, sizeof(g_McciBootloader_imageBlock));

	if (pAppInfoIn == NULL)
		return false;

	*pIncomingAppInfo = *pAppInfoIn;

	uint32_t targetAddress = pIncomingAppInfo->targetAddress;
	uint32_t targetSize = pIncomingAppInfo->imagesize + pIncomingAppInfo->authsize;
	if (! McciBootloaderPlatform_checkImageValid(
			g_McciBootloader_imageBlock, sizeof(g_McciBootloader_imageBlock), targetAddress, targetSize
			))
		return false;

	mcci_tweetnacl_sha512_t imageHash;

	mcci_tweetnacl_hashblocks_sha512_init(&imageHash);

	// read up to, but not including, the hash
	McciBootloaderStorageAddress_t addressCurrent;
	McciBootloaderStorageAddress_t const addressEnd = 
		address +
		pIncomingAppInfo->imagesize +
		sizeof(mcci_tweetnacl_sign_publickey_t);

	/* loop post condition: nThisTime is the result of the last hash */
	uint32_t nRemaining = 0; /* initalize to zero because addressCurrent might be >= addressEnd */
	const uint8_t *pRemaining = g_McciBootloader_imageBlock;

	for (addressCurrent = address; addressCurrent < addressEnd; )
		{
		/* detect bizarre failures */
		if (nRemaining != 0)
			return false;

		/* consume one gulp */
		uint32_t nThisTime = addressEnd - addressCurrent;

		if (nThisTime > sizeof(g_McciBootloader_imageBlock))
			nThisTime = sizeof(g_McciBootloader_imageBlock);

		/* optimize: don't re-read block 0 of image */
		if (addressCurrent != address)
			{
			if (! McciBootloaderPlatform_storageRead(
				addressCurrent,
				g_McciBootloader_imageBlock,
				nThisTime
				))
				return false;
			}

		/* update the hash */
		nRemaining = mcci_tweetnacl_hashblocks_sha512(
			&imageHash,
			g_McciBootloader_imageBlock,
			nThisTime
			);

		/* advance pointer,  */
		uint32_t const nConsumed = nThisTime - nRemaining;
		addressCurrent += nConsumed;
		pRemaining = g_McciBootloader_imageBlock + nConsumed;
		}

	mcci_tweetnacl_hashblocks_sha512_finish(
		&imageHash,
		pRemaining,
		nRemaining,
		addressEnd - address
		);

	// read the signature block
	if (! McciBootloaderPlatform_storageRead(
		addressCurrent,
		g_McciBootloader_imageBlock,
		sizeof(McciBootloader_SignatureBlock_t)
		))
		return false;

	const size_t nsig = sizeof(mcci_tweetnacl_sign_signature_t);
	const size_t nsigned = sizeof(imageHash) + nsig;
	size_t nActual;
	mcci_tweetnacl_sha512_t signedHash;

	// set up a pointer for convenience
	const McciBootloader_SignatureBlock_t * const pSigBlock = (const void *)g_McciBootloader_imageBlock;

	// append the imageHash
	memcpy(
		g_McciBootloader_imageBlock + sizeof(McciBootloader_SignatureBlock_t),
		imageHash.bytes,
		sizeof(imageHash.bytes)
		);

	// result = non-zero for failure or zero for success.
	volatile mcci_tweetnacl_result_t result;

	// check the signature, which will update signedHash.
	result = mcci_tweetnacl_sign_open(
			/* output */ signedHash.bytes,
			&nActual,
			pSigBlock->signature.bytes,
			nsigned,
			pPublicKey
			);

	// constant time compares and checks.
	// make sure the size is right.
	result |= nActual ^ sizeof(signedHash);

	// make sure the hashes match
	result |= mcci_tweetnacl_verify_64(
			imageHash.bytes,
			signedHash.bytes
			);

	// Make sure the key in the image matches ours. It should but still...
	result |= mcci_tweetnacl_verify_32(
			pPublicKey->bytes,
			pSigBlock->publicKey.bytes
			);

	// finally return the result.
	return mcci_tweetnacl_result_is_success(result);
	}

/**** end of mccibootloader_checkstorageimage.c ****/
