/*

Module:	mccibootloaderboard_catenaabz_spi.c

Function:
	SPI driver for Catena boards based on Murata ABZ and STM32L0.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena_abz.h"
#include "mcci_stm32l0xx.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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

Name:	McciBootloaderBoard_CatenaAbz_spiInit()

Function:
	Initialize SPI subsystem for bootloader for Catenas based on ABZ module.

Definition:
	McciBootloaderPlatform_SpiInitFn_t McciBootloaderBoard_CatenaAbz_spiInit;

	void McciBootloaderBoard_CatenaAbz_spiInit(
		void
		);

Description:
	SPI2 is initialized. We assume the following:	

	SPI connections:
		PB12: nss	AF0
		PB13: sclk	AF0	pulldown.
		PB14: miso	AF0
		PB15: mosi	AF0

	Clock: 16 MHz (SYSCLK/2).
	MSB first.
	clock polarity 0, phase 0

Returns:
	No explicit result.

Notes:
	

*/


void
McciBootloaderBoard_CatenaAbz_spiInit(void)
	{
	// set up the storage connections
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_MODER,
		(MCCI_STM32L0_GPIO_MODE_P(15) |
		 MCCI_STM32L0_GPIO_MODE_P(14) |
		 MCCI_STM32L0_GPIO_MODE_P(13) |
		 MCCI_STM32L0_GPIO_MODE_P(12)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(15), MCCI_STM32L0_GPIO_MODE_AF) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(14), MCCI_STM32L0_GPIO_MODE_AF) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(13), MCCI_STM32L0_GPIO_MODE_AF) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(12), MCCI_STM32L0_GPIO_MODE_AF))
		);
	
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_OSPEEDR,
		(MCCI_STM32L0_GPIO_OSPEED_P(15) |
		 MCCI_STM32L0_GPIO_OSPEED_P(14) |
		 MCCI_STM32L0_GPIO_OSPEED_P(13) |
		 MCCI_STM32L0_GPIO_OSPEED_P(12)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(15), MCCI_STM32L0_GPIO_OSPEED_HIGH) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(14), MCCI_STM32L0_GPIO_OSPEED_HIGH) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(13), MCCI_STM32L0_GPIO_OSPEED_HIGH) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(12), MCCI_STM32L0_GPIO_OSPEED_HIGH))
		);

	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_PUPDR,
		(MCCI_STM32L0_GPIO_PUPD_P(15) |
		 MCCI_STM32L0_GPIO_PUPD_P(14) |
		 MCCI_STM32L0_GPIO_PUPD_P(13) |
		 MCCI_STM32L0_GPIO_PUPD_P(12)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(15), MCCI_STM32L0_GPIO_PUPD_NONE) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(14), MCCI_STM32L0_GPIO_PUPD_NONE) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(13), MCCI_STM32L0_GPIO_PUPD_PULLDOWN) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(12), MCCI_STM32L0_GPIO_PUPD_NONE))
		);

	// enable SPI2
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB1ENR,
		MCCI_STM32L0_REG_RCC_APB1ENR_SPI2EN
		);
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB1RSTR,
		MCCI_STM32L0_REG_RCC_APB1RSTR_SPI2RST
		);

	// set SPI_CR2
	McciArm_putRegClearSet(
		MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_CR1,
		(
		 MCCI_STM32L0_SPI_CR1_BIDIMODE |
		 MCCI_STM32L0_SPI_CR1_CRCEN |
		 MCCI_STM32L0_SPI_CR1_SSM |
		 MCCI_STM32L0_SPI_CR1_LSBFIRST |
		 MCCI_STM32L0_SPI_CR1_SSM |		/* per STM32L0 manual page 830; SSM 0/SSI 1 drives when SSE */
		 MCCI_STM32L0_SPI_CR1_SPE |		/* disable while programming */
		 MCCI_STM32L0_SPI_CR1_BR |		/* all the baud-rate bits */
		 MCCI_STM32L0_SPI_CR1_CPOL |
		 MCCI_STM32L0_SPI_CR1_CPHA
		),
		(
		 MCCI_STM32L0_SPI_CR1_SSI |	/* the ST HAL sets this for master */
		 MCCI_STM32L0_SPI_CR1_MSTR
		)
		);

	McciArm_putReg(
		MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_CR2,
		0
		);

	McciArm_putRegClear(
		MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_I2SCFGR,
		MCCI_STM32L0_SPI_I2SCFGR_I2SMOD
		);

	}

/*

Name:	McciBootloaderBoard_CatenaAbz_spiTransfer()

Function:
	Implementation of spi_transfer method for CatenaABZ family.

Definition:
	typedef McciBootloaderPlatform_SpiTransferFn_t
		McciBootloaderBoard_CatenaAbz_spiTransfer;

	void McciBootloaderBoard_CatenaAbz_spiTransfer(
		uint8_t *pRx,
		const uint8_t *pTx,
		size_t nBytes,
		bool fContinue
		);

Description:
	This API writes and reads data from the SPI bus, optionally leaving the
	target device selected.

	nBytes bytes of data are transferred from the buffer atpTx to the SPI
	bus, and received from the SPI bus to pRx.

	The API defines pRx and pTx as optional; if NULL, bytes are discarded
	or zeroes inserted, respectively.

Returns:
	No explicit result.

Notes:
	

*/

// do a transfer
void
McciBootloaderBoard_CatenaAbz_spiTransfer(
	uint8_t *pRx,
	const uint8_t *pTx,
	size_t nBytes,
	bool fContinue
	)
	{
	uint8_t txdata;

	McciArm_putRegOr(
		MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_CR1,
		MCCI_STM32L0_SPI_CR1_SPE
		);
	txdata = 0;
	for (; nBytes > 0; --nBytes)
		{
		while (! (McciArm_getReg(MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_SR) & MCCI_STM32L0_SPI_SR_TXE))
			;

		if (pTx)
			txdata = *pTx++;

		McciArm_putReg(MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_DR, txdata);

		while (! (McciArm_getReg(MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_SR) & MCCI_STM32L0_SPI_SR_RXNE))
			;

		uint32_t const rxData = McciArm_getReg(MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_DR);
		if (pRx)
			*pRx++ = (uint8_t)rxData;
		}

	if (! fContinue)
		{
		McciArm_putRegClear(
			MCCI_STM32L0_REG_SPI2 + MCCI_STM32L0_SPI_CR1,
			MCCI_STM32L0_SPI_CR1_SPE
			);
		}
	}

/**** end of mccibootloaderboard_catenaabz_spi.c ****/
