/*

Module:	mccibootloader_stm32l0_systemflash.c

Function:
	McciBootloader_Stm32L0_systemFlashErase() and
	McciBootloader_Stm32L0_systemFlashWrite()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/


#include "mcci_bootloader_stm32l0.h"
#include "mcci_stm32l0xx.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

bool
McciBootloader_Stm32L0_programHalfPage(
	uint32_t flash_addr,
	const uint32_t *pData
	);

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

bool
McciBootloader_Stm32L0_systemFlashErase(
	volatile const void *pBase,
	size_t nBytes
	)
	{
	bool result = true;

	// round nBytes up if necessary for partial pages.
	nBytes = (nBytes + MCCI_STM32L0_FLASH_PAGE_SIZE - 1) & ~(MCCI_STM32L0_FLASH_PAGE_SIZE - 1);

	// wait
	while (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_BSY)
		/* loop */;

	// unlock the PECR bit
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PEKEYR, MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK1);
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PEKEYR, MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK2);

	// unlock the PROG bit
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PRGKEYR, MCCI_STM32L0_REG_FLASH_PRGKEYR_UNLOCK1);
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PRGKEYR, MCCI_STM32L0_REG_FLASH_PRGKEYR_UNLOCK2);

	// loop throgh each page, erasing
	uint32_t p;
	size_t nPages;

	p = (uint32_t)pBase;
	nPages = nBytes / MCCI_STM32L0_FLASH_PAGE_SIZE;

	McciArm_putRegOr(
		MCCI_STM32L0_REG_FLASH_PECR,
		MCCI_STM32L0_REG_FLASH_PECR_ERASE | MCCI_STM32L0_REG_FLASH_PECR_PROG
		);

	for (; nPages > 0; p += MCCI_STM32L0_FLASH_PAGE_SIZE, --nPages)
		{
		// start the erase
		McciArm_putReg(p, 0);

		// wait for done
		while (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_BSY)
			/* loop */;

		// reset EOP
		if (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_EOP)
			McciArm_putRegClear(
				MCCI_STM32L0_REG_FLASH_SR,
				MCCI_STM32L0_REG_FLASH_SR_EOP
				);
		}

	// turn off PECR bits
	McciArm_putRegClear(
		MCCI_STM32L0_REG_FLASH_PECR,
		MCCI_STM32L0_REG_FLASH_PECR_ERASE | MCCI_STM32L0_REG_FLASH_PECR_PROG
		);

	// lock
	McciArm_putRegOr(MCCI_STM32L0_REG_FLASH_PECR, MCCI_STM32L0_REG_FLASH_PECR_PELOCK);
	return result;
	}

bool
__attribute__((__section__(".RamFunc")))
McciBootloader_Stm32L0_programHalfPage(
	uint32_t flash_addr,
	const uint32_t *pData
	)
	{
	McciArm_putRegOr(
		MCCI_STM32L0_REG_FLASH_PECR,
		(MCCI_STM32L0_REG_FLASH_PECR_PROG |
		 MCCI_STM32L0_REG_FLASH_PECR_FPRG)
		);

	unsigned i;
	for (i = 0; i < MCCI_STM32L0_FLASH_HALF_PAGE_SIZE; i += sizeof(uint32_t), ++pData)
		{
		McciArm_putReg(flash_addr + i, *pData);
		}

	// wait for done
	while (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_BSY)
		/* loop */;

	// reset EOP
	if (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_EOP)
		McciArm_putRegClear(
			MCCI_STM32L0_REG_FLASH_SR,
			MCCI_STM32L0_REG_FLASH_SR_EOP
			);

	// turn off PECR bits
	McciArm_putRegClear(
		MCCI_STM32L0_REG_FLASH_PECR,
		(MCCI_STM32L0_REG_FLASH_PECR_PROG |
		 MCCI_STM32L0_REG_FLASH_PECR_FPRG)
		);

	return true;
	}

bool
McciBootloader_Stm32L0_systemFlashWrite(
	volatile const void *pDest,
	const void *pSrc,
	size_t nBytes
	)
	{
	bool result;
	uint32_t srcAddr = (uint32_t)pSrc;
	if ((srcAddr & 3) != 0)
		return false;

	if ((nBytes % MCCI_STM32L0_FLASH_HALF_PAGE_SIZE) != 0)
		return false;

	uint32_t destAddr = (uint32_t)pDest;
	if ((destAddr % MCCI_STM32L0_FLASH_HALF_PAGE_SIZE) != 0)
		return false;

	const uint32_t *pSrcData;
	pSrcData = pSrc;

	const size_t nHalfPage = MCCI_STM32L0_FLASH_HALF_PAGE_SIZE;

	// wait
	while (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_BSY)
		/* loop */;

	// unlock
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PEKEYR, MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK1);
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PEKEYR, MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK2);

	// unlock the PROG bit
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PRGKEYR, MCCI_STM32L0_REG_FLASH_PRGKEYR_UNLOCK1);
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PRGKEYR, MCCI_STM32L0_REG_FLASH_PRGKEYR_UNLOCK2);

	result = true;
	for (; nBytes > 0;
	     nBytes -= nHalfPage,
	     destAddr += nHalfPage,
	     pSrcData += nHalfPage / sizeof(uint32_t)
	     )
		{
		// we really don't want to take an interrupt while programming.
		const uint32_t psw = McciArm_disableInterrupts();

		result = McciBootloader_Stm32L0_programHalfPage(destAddr, pSrcData);

		// reenable.
		McciArm_setPRIMASK(psw);

		if (! result)
			break;
		}

	// lock
	McciArm_putRegOr(MCCI_STM32L0_REG_FLASH_PECR, MCCI_STM32L0_REG_FLASH_PECR_PELOCK);
	return result;
	}

/**** end of mccibootloader_stm32l0_systemflash.c ****/
