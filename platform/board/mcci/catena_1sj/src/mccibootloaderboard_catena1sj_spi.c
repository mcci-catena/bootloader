/*

Module:	mccibootloaderboard_catena1sj_spi.c

Function:
	SPI (flash) driver for Catena boards based on Murata 1SJ and STM32L0.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_board_catena_1sj.h"
#include "mcci_stm32l0xx.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

#define	MCCI_CATENA1SJ_PA8_MASK	(UINT32_C(1) << 8)	// mask for PB8 in the various registers

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

Name:	McciBootloaderBoard_Catena1sj_spiInit()

Function:
	Initialize SPI subsystem for bootloader for Catenas based on 1SJ module.

Definition:
	McciBootloaderPlatform_SpiInitFn_t McciBootloaderBoard_Catena1sj_spiInit;

	void McciBootloaderBoard_Catena1sj_spiInit(
		void
		);

Description:
	SPI1 is initialized. We assume the following:

	SPI connections:
		PA8: nss	OUT			(manually driven)
		PB3: sclk	AF0	pulldown.
		PB4: miso	AF0
		PB5: mosi	AF0

	Clock: 16 MHz (SYSCLK/2).
	MSB first.
	clock polarity 0, phase 0

	The boot loader's architecture assumes that NSS is controlled by the "spi subsystem".
	On older Catena boards, NSS could be controlled by the SPI hardware. On this
	family of boards, NSS is wired to a GPIO, and must be manually controlled.
	This module therefore sets up PA8 as a suitable GPIO, initializes it to 1, and
	manually drives it active during SPI transfers.

Returns:
	No explicit result.

Notes:


*/


void
McciBootloaderBoard_Catena1sj_spiInit(void)
	{
	// set up the storage connections
	// PB8 is NSS so we need to set it up.  Initialize the data value before making it an output.
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_BSRR,
		MCCI_CATENA1SJ_PA8_MASK
		);

	// make PB8 an output.
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_MODER,
		(MCCI_STM32L0_GPIO_MODE_P(8)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(8), MCCI_STM32L0_GPIO_MODE_OUT))
		);

	// set up the SPI bits.
	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_MODER,
		(MCCI_STM32L0_GPIO_MODE_P(5) |
		 MCCI_STM32L0_GPIO_MODE_P(4) |
		 MCCI_STM32L0_GPIO_MODE_P(3)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(5), MCCI_STM32L0_GPIO_MODE_AF) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(4), MCCI_STM32L0_GPIO_MODE_AF) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_MODE_P(3), MCCI_STM32L0_GPIO_MODE_AF))
		);

	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_OSPEEDR,
		(MCCI_STM32L0_GPIO_OSPEED_P(8)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(8), MCCI_STM32L0_GPIO_OSPEED_HIGH))
		);

	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_OSPEEDR,
		(MCCI_STM32L0_GPIO_OSPEED_P(5) |
		 MCCI_STM32L0_GPIO_OSPEED_P(4) |
		 MCCI_STM32L0_GPIO_OSPEED_P(3)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(5), MCCI_STM32L0_GPIO_OSPEED_HIGH) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(4), MCCI_STM32L0_GPIO_OSPEED_HIGH) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_OSPEED_P(3), MCCI_STM32L0_GPIO_OSPEED_HIGH))
		);

	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_PUPDR,
		(MCCI_STM32L0_GPIO_PUPD_P(8)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(8), MCCI_STM32L0_GPIO_PUPD_NONE))
		);

	McciArm_putRegMasked(
		MCCI_STM32L0_REG_GPIOB + MCCI_STM32L0_GPIO_PUPDR,
		(MCCI_STM32L0_GPIO_PUPD_P(5) |
		 MCCI_STM32L0_GPIO_PUPD_P(4) |
		 MCCI_STM32L0_GPIO_PUPD_P(3)),
		(MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(5), MCCI_STM32L0_GPIO_PUPD_NONE) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(4), MCCI_STM32L0_GPIO_PUPD_NONE) |
		 MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_PUPD_P(3), MCCI_STM32L0_GPIO_PUPD_PULLDOWN))
		);

	// enable SPI1 at APB2
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB2ENR,
		MCCI_STM32L0_REG_RCC_APB2ENR_SPI1EN
		);

	// reset the SPI1 block
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB2RSTR,
		MCCI_STM32L0_REG_RCC_APB2RSTR_SPI1RST
		);
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_APB2RSTR,
		MCCI_STM32L0_REG_RCC_APB2RSTR_SPI1RST
		);

	// setup SPI_CR1
	// since we reset above, we don't have to worry about anything
	// except non-default settings
	McciArm_putRegOr(
		MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_CR1,
		(
		 MCCI_STM32L0_SPI_CR1_BR_2 |	// fastest
		 MCCI_STM32L0_SPI_CR1_MSTR |	// master mode
		 // NSS on this board is a plain GPIO (PA8), manually driven by
		 // spiTransfer() -- it is not connected to the SPI1 peripheral's
		 // own NSS/AF function. With SSM=0 (the reset default), the
		 // peripheral still watches its internal NSS signal and treats
		 // it going low, while master, as another device contending for
		 // the bus -- triggering MODF (mode fault), which immediately
		 // clears SPE and permanently disables the peripheral. SSM=1
		 // disables that hardware NSS monitoring; SSI=1 forces the
		 // internal NSS signal to a fixed high, matching "I am solely
		 // the master, chip-select is my own responsibility."
		 MCCI_STM32L0_SPI_CR1_SSM |	// software (not hardware) NSS management
		 MCCI_STM32L0_SPI_CR1_SSI	// force internal NSS high
		)
		);

	// setup SPI_CR2
	// since we reset above, we don't have to worry about anything
	// except non-default settings. And since we are using a non-default
	// NSS, manually managed, we don't want to write anything at all.
	// McciArm_putRegOr(
	//	MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_CR2,
	//	0		/* MCCI_STM32L0_SPI_CR2_SSOE would enable the nss output */
	//	);

	// setup I2SCFGR_I2SMOD
	// since we reset above, we don't need to do anything.
	// McciArm_putRegClear(
	//	MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_I2SCFGR,
	//	MCCI_STM32L0_SPI_I2SCFGR_I2SMOD
	//	);
	}

/*

Name:	McciBootloaderBoard_Catena1sj_spiTransfer()

Function:
	Implementation of spi_transfer method for Catena1SJ family.

Definition:
	typedef McciBootloaderPlatform_SpiTransferFn_t
		McciBootloaderBoard_Catena1sj_spiTransfer;

	void McciBootloaderBoard_Catena1sj_spiTransfer(
		uint8_t *pRx,
		const uint8_t *pTx,
		size_t nBytes,
		bool fContinue
		);

Description:
	This API writes and reads data from the SPI bus, optionally leaving the
	target device selected.

	nBytes bytes of data are transferred from the buffer at pTx to the SPI
	bus, and received from the SPI bus to pRx.

	The API defines pRx and pTx as optional; if NULL, bytes are discarded
	or zeroes inserted, respectively.

Returns:
	No explicit result.

Notes:


*/

// do a transfer
void
McciBootloaderBoard_Catena1sj_spiTransfer(
	uint8_t *pRx,
	const uint8_t *pTx,
	size_t nBytes,
	bool fContinue
	)
	{
	uint8_t txdata;

	// drive NSS low.
	McciArm_putReg(
		MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_BRR,
		MCCI_CATENA1SJ_PA8_MASK
		);

	McciArm_putRegOr(
		MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_CR1,
		MCCI_STM32L0_SPI_CR1_SPE
		);
	txdata = 0;
	for (; nBytes > 0; --nBytes)
		{
		while (! (McciArm_getReg(MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_SR) & MCCI_STM32L0_SPI_SR_TXE))
			;

		if (pTx)
			txdata = *pTx++;

		McciArm_putReg(MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_DR, txdata);

		while (! (McciArm_getReg(MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_SR) & MCCI_STM32L0_SPI_SR_RXNE))
			;

		uint32_t const rxData = McciArm_getReg(MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_DR);
		if (pRx)
			*pRx++ = (uint8_t)rxData;
		}

	if (! fContinue)
		{
		McciArm_putRegClear(
			MCCI_STM32L0_REG_SPI1 + MCCI_STM32L0_SPI_CR1,
			MCCI_STM32L0_SPI_CR1_SPE
			);

		// drive NSS high.
		McciArm_putReg(
			MCCI_STM32L0_REG_GPIOA + MCCI_STM32L0_GPIO_BSRR,
			MCCI_CATENA1SJ_PA8_MASK
			);
		}
	}

/**** end of mccibootloaderboard_catena1sj_spi.c ****/
