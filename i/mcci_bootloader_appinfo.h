/*

Module:	mcci_bootloader_appinfo.h

Function:
	McciBootloader_AppInfo_t and McciBootloader_SignatureBlock_t

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_appinfo_h_
#define _mcci_bootloader_appinfo_h_	/* prevent multiple includes */

#pragma once

#include "mcci_bootloader_types.h"
#include <stdint.h>
#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	Data Structures
|
\****************************************************************************/

///
/// \brief Application information block
///
/// \details
///	This information block appears at a well known location somewhere
///	in each app image. It's intended to be somewhat architecturally
///	neutral, but until we have two supported architectures, we
///	won't really have a basis for discussion.
///
struct McciBootloader_AppInfo_s
	{
	uint32_t	magic;				///< the format identifier.
	uint32_t	size;				///< size of this structure, in bytes
	uint32_t	targetAddress;			///< the target load address
	uint32_t	imagesize;			///< size of the app, in bytes.
							///   Must be multiple of 4.
	uint32_t	authsize;			///< size of authentication data.
							/// Overall image size is imagesize
							///   + authsize
	uint32_t	version;			///< version of the image (semantic version)
	uint64_t	timestamp;			///< Posix timestamp of image
	uint8_t		comment[16];			///< optional comment (UTF-8) describing this image.
	uint8_t		reserved56[16];			///< reserved for future use.
	};

#define	MCCI_BOOTLOADER_APP_INFO_MAGIC	(('M' << 0) | ('A' << 8) | ('P' << 16) | ('0' << 24))

///
/// \brief Application signature block
///
/// \details
///	This signature block appears at the end of the flash image, and contains
///	the public key by which it was signed, the hash of the image, and the
///	signature for the hash.
///
struct McciBootloader_SignatureBlock_s
	{
	mcci_tweetnacl_sign_publickey_t		publicKey;	///< the public key used for the signature
	mcci_tweetnacl_sha512_t			hash;		///< the SHA-512 hash
	mcci_tweetnacl_sign_signature_t		signature;	///< the first 64 bytes of sign(hash, publicKey)
	};

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_appinfo_h_ */
