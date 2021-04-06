/*

Module:	mccibootloaderflash_mx25v8035f.c

Function:
	Bootloader driver for MX25V8035F (and similar) chips.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_flash_mx25v8035f.h"

#include "flash_mx25v8035f.h"
#include "mcci_bootloader_platform.h"
#include "mcci_bootloader.h"
#include "mcci_flash_sfdp.h"

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

Name:	McciBootloaderFlash_Mx25v8035f_storageInit()

Function:
	Initialize the flash chip by sending a reset.

Definition:
	void McciBootloaderFlash_Mx25v8035f_storageInit(
		void
		);

Description:
	Assuming the SPI bus is up and ready, we send reset enable,
	followed by reset; then we delay for 100ms.

Returns:
	No explicit result.

Notes:


*/

void
McciBootloaderFlash_Mx25v8035f_storageInit(
	void
	)
	{
	static const uint8_t kcResetEn[] = { MX25V8035F_CMD_RSTEN };
	static const uint8_t kcReset[] = { MX25V8035F_CMD_RST };

	// send the reset enable command.
	McciBootloaderPlatform_spiTransfer(
			/* RX */ NULL,
			kcResetEn,
			sizeof(kcResetEn),
			/* continue? */ false
			);

	// send the reset command.
	McciBootloaderPlatform_spiTransfer(
			/* RX */ NULL,
			kcReset,
			sizeof(kcReset),
			/* continue? */ false
			);

	// wait for flash to come back.
	McciBootloaderPlatform_delayMs(100);

	// read SFDP: address 3 plus a dummy byte.
	static const uint8_t kcRdSfdp[5] = { MX25V8035F_CMD_RDSFDP,  0, 0, 0, 0 };

	// read the SFDP
	McciBootloaderPlatform_spiTransfer(
			/* RX */ NULL,
			kcRdSfdp,
			sizeof(kcRdSfdp),
			/* continue? */ true
			);

	// get the data
	struct	{
		mcci_flash_sfdp_header_t header;
		mcci_flash_sfdp_param_t  param[2];
		} sfdpData;

	McciBootloaderPlatform_spiTransfer(
			/* RX */ (uint8_t *)&sfdpData,
			/* TX */ NULL,
			sizeof(sfdpData),
			/* continue? */ false
			);

	if (McciFlashSfdpHeader_getSignature(&sfdpData.header) != MCCI_FLASH_SFDP_HEADER_SIGNATURE)
		{
		McciBootloaderPlatform_fail(McciBootloaderError_FlashNotFound);
		}
	if (McciFlashSfdpHeader_getVersion(&sfdpData.header) < MCCI_FLASH_SFDP_HEADER_PROPERTY_VERSION_JES216B)
		{
		McciBootloaderPlatform_fail(McciBootloaderError_FlashNotSupported);
		}
	}

/*

Name:	McciBootloaderFlash_Mx25v8035f_storageRead()

Function:
	Read a buffer from the specified flash byte address

Definition:
	void McciBootloaderFlash_Mx25v8035f_read(
		McciBootloaderStorageAddress_t Address,
		uint8_t *pBuffer,
		size_t nBuffer
		);

Description:
	This function reads a buffer from the specified flash
	byte offset. There are no alignment constraings.

Returns:
	No explicit result.

*/

bool
McciBootloaderFlash_Mx25v8035f_storageRead(
	McciBootloaderStorageAddress_t Address,
	uint8_t *pBuffer,
	size_t nBuffer
	)
	{
	uint8_t cmd[4];

	cmd[0] = MX25V8035F_CMD_READ;
	cmd[1] = (Address >> 16) & 0xFF;
	cmd[2] = (Address >> 8) & 0xFF;
	cmd[3] = Address & 0xFF;

	McciBootloaderPlatform_spiTransfer(
		/* RX */ NULL,
		/* TX */ cmd,
		/* size */ sizeof(cmd),
		/* continue? */ true
		);
	McciBootloaderPlatform_spiTransfer(
		pBuffer,
		NULL,
		nBuffer,
		/* continue? */ false
		);

	return true;
	}

/**** end of mccibootloaderflash_mx25v8035f.c ****/
