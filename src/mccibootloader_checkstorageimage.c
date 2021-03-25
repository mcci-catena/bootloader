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

const mcci_tweetnacl_sign_publickey_t
gk_McciBootloader_PublicKey =
	{
	.bytes = {
		0x76, 0x87, 0x02, 0x14, 0x00, 0x42, 0xe7, 0x2d,
		0xe6, 0xa7, 0xab, 0x82, 0x45, 0x4b, 0xc2, 0x63,
		0xa8, 0xb1, 0x8b, 0xe0, 0xcc, 0xef, 0xd3, 0xae,
		0x6c, 0x4f, 0xea, 0xb2, 0xe1, 0x1a, 0x4f, 0x1f,
		}
	};

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
		McciBootloaderStorageAddress_t address
		);

Description:
	Read the header of the image and lightly validate it. Then
	scan through the image, calculating the SHA512, and finallly
	check the signature on the hash.

Returns:
	true for success, false for failure.

Notes:
	This is slow, so we try to update the LED state with a progress
	indication.

*/

bool
McciBootloader_checkStorageImage(
	McciBootloaderStorageAddress_t address
	)
	{
	/* read the header */
	if (! McciBootloaderPlatform_storageRead(
		address,
		g_McciBootloader_imageBlock, sizeof(g_McciBootloader_imageBlock)
		))
		return false;

	const McciBootloader_AppInfo_t * const pAppInfo =
		McciBootloaderPlatform_getAppInfo(g_McciBootloader_imageBlock, sizeof(g_McciBootloader_imageBlock));

	if (pAppInfo == NULL)
		return false;

	McciBootloader_AppInfo_t appInfo;

	appInfo = *pAppInfo;

	uint32_t targetAddress = pAppInfo->targetAddress;
	uint32_t targetSize = pAppInfo->imagesize + pAppInfo->authsize;
	if (! McciBootloaderPlatform_checkImageValid(
			g_McciBootloader_imageBlock, sizeof(g_McciBootloader_imageBlock), targetAddress, targetSize
			))
		return false;

	mcci_tweetnacl_sha512_t imageHash;

	mcci_tweetnacl_hashblocks_sha512_init(&imageHash);

	// read up to, but not including, the signature
	McciBootloaderStorageAddress_t addressCurrent;
	McciBootloaderStorageAddress_t const addressEnd = address + appInfo.imagesize;
	
	for (addressCurrent = address; addressCurrent < addressEnd; )
		{
		uint32_t nThisTime = addressEnd - addressCurrent;
		if (nThisTime > sizeof(g_McciBootloader_imageBlock))
			nThisTime = sizeof(g_McciBootloader_imageBlock);
		if (addressCurrent != address)
			{
			if (! McciBootloaderPlatform_storageRead(
				addressCurrent,
				g_McciBootloader_imageBlock,
				nThisTime
				))
				return false;
			}

		mcci_tweetnacl_hashblocks_sha512(
			&imageHash,
			g_McciBootloader_imageBlock,
			nThisTime
			);

		addressCurrent += nThisTime;
		}

	const size_t nsig = mcci_tweetnacl_sign_signature_size();
	const size_t nsigned = sizeof(imageHash) + nsig;
	size_t nActual;
	mcci_tweetnacl_sha512_t signedHash;

	// read the signature into the buffer
	if (nsigned > sizeof(g_McciBootloader_imageBlock))
		return false;

	if (! McciBootloaderPlatform_storageRead(
		addressCurrent,
		g_McciBootloader_imageBlock,
		nsigned
		))
		return false;

	// result = non-zero for failure or zero for success.
	mcci_tweetnacl_result_t result;

	result = mcci_tweetnacl_sign_open(
				signedHash.bytes,
				&nActual,
				g_McciBootloader_imageBlock,
				nsigned,
				&gk_McciBootloader_PublicKey
				);

	// constant time compare.
	result |= nActual ^ sizeof(signedHash);
	result |= mcci_tweetnacl_verify_64(
				imageHash.bytes,
				signedHash.bytes
				);

	return mcci_tweetnacl_result_is_success(result);
	}

/**** end of mccibootloader_checkstorageimage.c ****/