/*

Module:	mccibootloader_stm32h7_systemflash.c

Function:
	McciBootloader_Stm32h7_systemFlashErase() and
	McciBootloader_Stm32h7_systemFlashWrite()

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	July 2021

*/

#include "mcci_bootloader_stm32h7.h"
#include "mcci_stm32h7xx.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

#define	MCCI_STM32H7_REG_FLASH_SR_ERRORS	\
	(/*MCCI_STM32H7_REG_FLASH_SR_CRCRDERR |*/	\
	 MCCI_STM32H7_REG_FLASH_SR_DBECCERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_SNECCERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_RDSERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_RDPERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_INCERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_STRBERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_PGSERR |	\
	 MCCI_STM32H7_REG_FLASH_SR_WRPERR)

void
McciBootloader_Stm32h7_Lock(
	uint32_t	flash_addr
	);

void
McciBootloader_Stm32h7_Unlock(
	uint32_t	flash_addr
	);

bool
McciBootloader_Stm32h7_waitForDone(
	uint32_t	flash_addr
	);

bool
McciBootloader_Stm32h7_EraseSector(
	uint32_t	flash_addr
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
McciBootloader_Stm32h7_systemFlashErase(
	volatile const void *	pBase,
	size_t			nBytes
	)
	{
	uint32_t	p;
	uint32_t	pEnd;
	size_t		nSectors;
	bool		status;

	p = (uint32_t) pBase;
	if (! MCCI_STM32H7_FLASH_IS_VALID(p))
		return false;

	// round nBytes up if necessary for partial sectors.
	nBytes = (nBytes + MCCI_STM32H7_FLASH_SECTOR_SIZE - 1) &
		 ~(MCCI_STM32H7_FLASH_SECTOR_SIZE - 1);
	nSectors = nBytes / MCCI_STM32H7_FLASH_SECTOR_SIZE;
	pEnd = p + nBytes - MCCI_STM32H7_FLASH_SECTOR_SIZE;

	// wait
	McciBootloader_Stm32h7_waitForDone(p);

	// unlock
	McciBootloader_Stm32h7_Unlock(p);
	McciBootloader_Stm32h7_Unlock(pEnd);

	for (status = true; nSectors > 0; --nSectors)
		{
		// start the erase
		status = McciBootloader_Stm32h7_EraseSector(p);
		if (! status)
			{
			break;
			}

		p += MCCI_STM32H7_FLASH_SECTOR_SIZE;
		}

	// lock
	McciBootloader_Stm32h7_Lock((uint32_t) pBase);
	McciBootloader_Stm32h7_Lock(pEnd);
	return status;
	}

bool
McciBootloader_Stm32h7_waitForDone(
	uint32_t	flash_addr
	)
	{
	uint32_t	rSR;
	uint32_t	r;

	if (MCCI_STM32H7_FLASH_IS_BANK2(flash_addr))
		{
		rSR = MCCI_STM32H7_REG_FLASH_SR2;
		}
	else
		{
		rSR = MCCI_STM32H7_REG_FLASH_SR1;
		}

	do	{
		r = McciArm_getReg(rSR);
		} while (r & (MCCI_STM32H7_REG_FLASH_SR_QW |
			      MCCI_STM32H7_REG_FLASH_SR_BSY));

	/* Clear status */
	McciArm_putReg(
		rSR + 4,
		r & (MCCI_STM32H7_REG_FLASH_SR_ERRORS |
		     MCCI_STM32H7_REG_FLASH_SR_EOP)
		);
	return (r & MCCI_STM32H7_REG_FLASH_SR_ERRORS) ? false : true;
	}

void
McciBootloader_Stm32h7_Lock(
	uint32_t	flash_addr
	)
	{
	uint32_t	rCR;
	uint32_t	r;

	if (MCCI_STM32H7_FLASH_IS_BANK2(flash_addr))
		{
		rCR = MCCI_STM32H7_REG_FLASH_CR2;
		}
	else
		{
		rCR = MCCI_STM32H7_REG_FLASH_CR1;
		}

	r = McciArm_getReg(rCR);
	if ((r & MCCI_STM32H7_REG_FLASH_CR_LOCK) == 0)
		{
		McciArm_putReg(rCR, r | MCCI_STM32H7_REG_FLASH_CR_LOCK);
		}
	}

void
McciBootloader_Stm32h7_Unlock(
	uint32_t	flash_addr
	)
	{
	uint32_t	r;

	if (MCCI_STM32H7_FLASH_IS_BANK2(flash_addr))
		{
		r = McciArm_getReg(MCCI_STM32H7_REG_FLASH_CR2);
		if (r & MCCI_STM32H7_REG_FLASH_CR_LOCK)
			{
			McciArm_putReg(
				MCCI_STM32H7_REG_FLASH_KEYR2,
				MCCI_STM32H7_REG_FLASH_KEYR_UNLOCK1
				);
			McciArm_putReg(
				MCCI_STM32H7_REG_FLASH_KEYR2,
				MCCI_STM32H7_REG_FLASH_KEYR_UNLOCK2
				);
			}
		}
	else
		{
		r = McciArm_getReg(MCCI_STM32H7_REG_FLASH_CR1);
		if (r & MCCI_STM32H7_REG_FLASH_CR_LOCK)
			{
			McciArm_putReg(
				MCCI_STM32H7_REG_FLASH_KEYR1,
				MCCI_STM32H7_REG_FLASH_KEYR_UNLOCK1
				);
			McciArm_putReg(
				MCCI_STM32H7_REG_FLASH_KEYR1,
				MCCI_STM32H7_REG_FLASH_KEYR_UNLOCK2
				);
			}
		}
	}

bool
McciBootloader_Stm32h7_EraseSector(
	uint32_t	flash_addr
	)
	{
	uint32_t	rCR;
	uint32_t	sector;
	bool		status;

	if (MCCI_STM32H7_FLASH_IS_BANK2(flash_addr))
		{
		rCR = MCCI_STM32H7_REG_FLASH_CR2;
		}
	else
		{
		rCR = MCCI_STM32H7_REG_FLASH_CR1;
		}

	sector = MCCI_STM32H7_FLASH_GET_SECTOR(flash_addr);
	McciArm_putRegClear(rCR, MCCI_STM32H7_REG_FLASH_CR_SSN);
	McciArm_putRegOr(
		rCR,
		MCCI_STM32H7_REG_FLASH_CR_SER |
		MCCI_STM32H7_REG_FLASH_CR_SSN_N(sector) |
		MCCI_STM32H7_REG_FLASH_CR_START
		);

	status = McciBootloader_Stm32h7_waitForDone(flash_addr);

	McciArm_putRegClear(
		rCR,
		MCCI_STM32H7_REG_FLASH_CR_SER | MCCI_STM32H7_REG_FLASH_CR_SSN
		);
	return status;
	}

bool
McciBootloader_Stm32h7_systemFlashWrite(
	volatile const void *	pDest,
	const void *		pSrc,
	size_t			nBytes
	)
	{
	bool			result;
	uint32_t		srcAddr;
	uint32_t		destAddr;
	uint32_t		destEndAddr;
	volatile uint32_t *	pFlashAddr;
	const uint32_t *	pSrcData;

	srcAddr = (uint32_t) pSrc;
	if ((srcAddr & 3) != 0)
		return false;

	if ((nBytes % MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE) != 0)
		return false;

	destAddr = (uint32_t) pDest;
	if ((destAddr % MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE) != 0)
		return false;

	destEndAddr = destAddr + nBytes - MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE;

	pFlashAddr = (volatile uint32_t *) destAddr;
	pSrcData = (const uint32_t *) srcAddr;

	// wait
	McciBootloader_Stm32h7_waitForDone(destAddr);

	// unlock
	McciBootloader_Stm32h7_Unlock(destAddr);
	McciBootloader_Stm32h7_Unlock(destEndAddr);

	for (result = true;
	     nBytes > 0;
	     nBytes -= MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE)
		{
		uint32_t	rCR;
		uint32_t	i;

		if (MCCI_STM32H7_FLASH_IS_BANK2(destAddr))
			{
			rCR = MCCI_STM32H7_REG_FLASH_CR2;
			}
		else
			{
			rCR = MCCI_STM32H7_REG_FLASH_CR1;
			}

		McciArm_putRegOr(rCR, MCCI_STM32H7_REG_FLASH_CR_PG);

		McciArm_InstructionSynchBarrier();
		McciArm_DataSynchBarrier();

		for (i = 0; i < (MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE / sizeof(uint32_t)); ++i)
			{
			*pFlashAddr++ = *pSrcData++;
			}

		McciArm_InstructionSynchBarrier();
		McciArm_DataSynchBarrier();

		// wait for done
		result = McciBootloader_Stm32h7_waitForDone(destAddr);

		McciArm_putRegClear(rCR, MCCI_STM32H7_REG_FLASH_CR_PG);

		if (! result)
			{
			break;
			}

		destAddr += MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE;
		}

	// lock
	McciBootloader_Stm32h7_Lock((uint32_t) pDest);
	McciBootloader_Stm32h7_Lock(destEndAddr);
	return result;
	}

/**** end of mccibootloader_stm32h7_systemflash.c ****/
