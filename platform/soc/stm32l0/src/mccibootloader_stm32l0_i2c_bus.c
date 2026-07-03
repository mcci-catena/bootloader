/*

Module:	mccibootloader_stm32l0_i2c_bus.c

Function:
	I2C bus driver code for STM32L0

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	July 2026

*/

#include "mcci_bootloader_device_i2c_bus_stm32l0.h"

#include "mcci_bootloader.h"
#include "mcci_bootloader_platform.h"
#include "mcci_stm32l0xx.h"
#include "mcci_arm_cm0plus.h"

#include <string.h>

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

#ifndef	MCCI_BOOTLOADER_STM32L0_I2C_TIME_OUT_MS
# define MCCI_BOOTLOADER_STM32L0_I2C_TIME_OUT_MS	100
#endif

typedef enum McciBootloaderI2cBusStm32l0_Status_e
	{
	McciBootloaderI2cBusStm32l0_Status_Busy = 0,
	McciBootloaderI2cBusStm32l0_Status_Done,
	McciBootloaderI2cBusStm32l0_Status_Stopped,
	McciBootloaderI2cBusStm32l0_Status_ArbitrationLost,
	McciBootloaderI2cBusStm32l0_Status_TimeOut,
	McciBootloaderI2cBusStm32l0_Status_BusError,
	McciBootloaderI2cBusStm32l0_Status_NotBusy,
	McciBootloaderI2cBusStm32l0_Status_NackError,
	} McciBootloaderI2cBusStm32l0_Status_t;

static McciBootloaderDevice_BeginFn_t		i2cBusBegin;
static McciBootloaderDevice_EndFn_t		i2cBusEnd;
static McciBootloaderDeviceI2cBus_ReadFn_t	i2cBusRead;
static McciBootloaderDeviceI2cBus_WriteFn_t	i2cBusWrite;

// temporary declaration so we can compile before implementation
// of getMilliseconds() in platform:
McciBootloader_Milliseconds_t
McciBootloaderPlatform_getMilliseconds(void);

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

static const McciBootloaderDeviceMethods_t i2cBusDeviceMethods =
	{
	.pBegin = i2cBusBegin,
	.pEnd = i2cBusEnd
	};

static const McciBootloaderDeviceI2cBusMethods_t i2cBusMethods =
	{
	.pRead = i2cBusRead,
	.pWrite = i2cBusWrite
	};

static const McciBootloaderDeviceI2cBusStm32l0_Masks_t skBusMasks[] =
	{
		{
		.baseAddress = MCCI_STM32L0_REG_I2C1,
		.CCIPR_select =
			{
			.mask = MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL,
			.value = MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL_HSI16
			},
		.APB1ENR_mask = MCCI_STM32L0_REG_RCC_APB1ENR_I2C1EN,
		.APB1RSTR_mask = MCCI_STM32L0_REG_RCC_APB1RSTR_I2C1RST,
		},
		{
		.baseAddress = MCCI_STM32L0_REG_I2C2,
		.CCIPR_select =
			{
			.mask = 0,	// I2C2 doesn't support clock selection
			.value = 0	// value doesn't matter, since mask is zero.
			},
		.APB1ENR_mask = MCCI_STM32L0_REG_RCC_APB1ENR_I2C2EN,
		.APB1RSTR_mask = MCCI_STM32L0_REG_RCC_APB1RSTR_I2C2RST,
		},
		{
		.baseAddress = MCCI_STM32L0_REG_I2C3,
		.CCIPR_select =
			{
			.mask = MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL,
			.value = MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL_HSI16
			},
		.APB1ENR_mask = MCCI_STM32L0_REG_RCC_APB1ENR_I2C3EN,
		.APB1RSTR_mask = MCCI_STM32L0_REG_RCC_APB1RSTR_I2C3RST,
		},
	};

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/


/*

Name:	McciBootloader_Stm32L0Interface_initI2cBus()

Function:
	Initialize an I2C bus controller driver on an STM32L0.

Definition:
	McciBootloaderDeviceI2cBus_t *
		McciBootloader_Stm32L0Interface_initI2cBus(
			void *pRamForBus,	// RAM to use for instance data
			size_t sizeForBus,	// size of RAM
			uint32_t baseAddress,	// base address of controller
			uint32_t timingr100k,	// value to use for 100k operations
			uint32_t timingr400k,	// value to use for 400k operations
			uint32_t timingr1m	// value to use for 1MHz operations
			);

Description:
	The device instance is initialized using the information passed in.
	The actual pin assignment is left to the caller.

Returns:
	Pointer to allocated and initialized device object.

Notes:


*/

McciBootloaderDeviceI2cBus_t *
McciBootloader_Stm32L0Interface_initI2cBus(
	void *pRamForBus,
	size_t sizeForBus,
	uint32_t baseAddress,
	uint32_t timingr100k,
	uint32_t timingr400k,
	uint32_t timingr1m
	)
	{
	const McciBootloaderDeviceI2cBusStm32l0_Masks_t *pMasks;

	// check parameters
	if (sizeForBus < sizeof(McciBootloaderDeviceI2cBusStm32l0_t))
		McciBootloaderPlatform_fail(McciBootloaderError_InternalConsistency);

	if (timingr100k == MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED ||
	    timingr400k != MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED ||
	    timingr1m != MCCI_BOOTLOADER_STM32L0_I2C_TIMINGR_NOT_SUPPORTED)
		McciBootloaderPlatform_fail(McciBootloaderError_InternalConsistency);

	pMasks = NULL;
	for (unsigned i = 0; i < MCCIADK_LENOF(skBusMasks); ++i)
		{
		if (skBusMasks[i].baseAddress == baseAddress)
			{
			pMasks = &skBusMasks[i];
			break;
			}
		}

	if (pMasks == NULL)
		{
		McciBootloaderPlatform_fail(McciBootloaderError_InternalConsistency);
		}

	// initialize the object
	memset(pRamForBus, 0, sizeForBus);

	// fill it in
	McciBootloaderDeviceI2cBusStm32l0_t * const pI2cBus = pRamForBus;

	pI2cBus->Device.pMethods = &i2cBusDeviceMethods;
	pI2cBus->I2cBus.pMethods = &i2cBusMethods;
	pI2cBus->Stm32l0.pMasks = pMasks;
	pI2cBus->Stm32l0.timingr100k = timingr100k;

	// initialize
	if (! (*pI2cBus->Device.pMethods->pBegin)(&pI2cBus->DeviceCast))
		McciBootloaderPlatform_fail(McciBootloaderError_I2cBegin);

	return &pI2cBus->I2cBusCast;
	}

/*

Name:	McciBootloaderDeviceI2cBusStm32l0_t::i2cBusBegin()

Function:
	Initialize the I2C bus function and hardware.

Definition:
	static McciBootloaderDevice_BeginFn_t i2cBusBegin;

	static bool
	i2cBusBegin(
		McciBootloaderDevice_t *pDevice
		);

Description:
	Sets up the hardware for I2C operation.

Returns:
	true for success, false for failure

Notes:
	Cannot actually fail in this implementation.

*/

static bool
i2cBusBegin(
	McciBootloaderDevice_t *pDevice
	)
	{
	McciBootloaderDeviceI2cBusStm32l0_t * const pI2cBus = McciBootloader_Device_getI2cBusStm32l0(pDevice);
	uint32_t const baseAddress = pI2cBus->Stm32l0.pMasks->baseAddress;

	// select the clock source
	if (pI2cBus->Stm32l0.pMasks->CCIPR_select.mask != 0)
		{
		McciArm_putRegMasked(
			MCCI_STM32L0_REG_RCC_CCIPR,
			pI2cBus->Stm32l0.pMasks->CCIPR_select.mask,
			pI2cBus->Stm32l0.pMasks->CCIPR_select.value
			);
		}

	// enable the peripheral
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB1ENR,
		pI2cBus->Stm32l0.pMasks->APB1ENR_mask
		);

	// reset it
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB1RSTR,
		pI2cBus->Stm32l0.pMasks->APB1RSTR_mask
		);

	// un-reset it
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_APB1RSTR,
		pI2cBus->Stm32l0.pMasks->APB1RSTR_mask
		);

	// set up timing register
	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_TIMINGR,
		pI2cBus->Stm32l0.timingr100k
		);

	return true;
	}

/*

Name:	McciBootloaderDeviceI2cBusStm32l0_t::i2cBusEnd()

Function:
	Deinitialize the I2C bus function and hardware.

Definition:
	static McciBootloaderDevice_EndFn_t i2cBusEnd;

	static bool
	i2cBusEnd(
		McciBootloaderDevice_t *pDevice
		);

Description:
	Tears down the hardware for I2C operation.

Returns:
	true for success, false for failure

Notes:
	Cannot actually fail in this implementation.

*/


static bool
i2cBusEnd(
	McciBootloaderDevice_t *pDevice
	)
	{
	McciBootloaderDeviceI2cBusStm32l0_t * const pI2cBus = McciBootloader_Device_getI2cBusStm32l0(pDevice);
	// uint32_t const baseAddress = pI2cBus->Stm32l0.pMasks->baseAddress;

	// reset it
	McciArm_putRegOr(
		MCCI_STM32L0_REG_RCC_APB1RSTR,
		pI2cBus->Stm32l0.pMasks->APB1RSTR_mask
		);

	// un-reset it
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_APB1RSTR,
		pI2cBus->Stm32l0.pMasks->APB1RSTR_mask
		);

	// disable the peripheral
	McciArm_putRegClear(
		MCCI_STM32L0_REG_RCC_APB1ENR,
		pI2cBus->Stm32l0.pMasks->APB1ENR_mask
		);

	return true;
	}

static size_t
i2cBusRead(
	McciBootloaderDeviceI2cBus_t *pBus,
	McciBootloaderDeviceI2cAddress_t i2cAddress,
	uint8_t *pBuffer,
	size_t nBuffer
	)
	{
	const size_t nBuffer_orig = nBuffer;
	McciBootloaderDeviceI2cBusStm32l0_t * const pI2cBus = McciBootloader_DeviceI2cBus_getI2cBusStm32l0(pBus);
	uint32_t const baseAddress = pI2cBus->Stm32l0.pMasks->baseAddress;
	McciBootloader_Milliseconds_t tStart;
	McciBootloaderI2cBusStm32l0_Status_t status;

	if (nBuffer > 0xFF)
		McciBootloaderPlatform_fail(McciBootloaderError_InternalConsistency);

	// nBuffer == 0 is a read probe.

	uint32_t cr2;

	cr2 = MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_I2C_CR2_SADD, i2cAddress << 1)
	    | MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_I2C_CR2_NBYTES, nBuffer)
	    | MCCI_STM32L0_I2C_CR2_AUTOEND
	    | MCCI_STM32L0_I2C_CR2_RD_WRN
	    ;

	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_CR1,
		MCCI_STM32L0_I2C_CR1_PE
		);

	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_CR2,
		cr2
		);

	// set the start bit
	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_CR2,
		cr2 | MCCI_STM32L0_I2C_CR2_START
		);

	// now, wait for RXNE to be set
	tStart = McciBootloaderPlatform_getMilliseconds();

	status = McciBootloaderI2cBusStm32l0_Status_Busy;
	while (status == McciBootloaderI2cBusStm32l0_Status_Busy)
		{
		if (McciBootloaderPlatform_getMilliseconds() - tStart > MCCI_BOOTLOADER_STM32L0_I2C_TIME_OUT_MS)
			{
			status = McciBootloaderI2cBusStm32l0_Status_TimeOut;
			break;
			}

		uint32_t const isr = McciArm_getReg(
			baseAddress + MCCI_STM32L0_I2C_ISR
			);

		if (isr & MCCI_STM32L0_I2C_ISR_ARLO)
			{
			status = McciBootloaderI2cBusStm32l0_Status_ArbitrationLost;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_RXNE && nBuffer != 0)
			{
			*pBuffer = (uint8_t) McciArm_getReg(baseAddress + MCCI_STM32L0_I2C_RXDR);
			++pBuffer, --nBuffer;

			// restart the timer
			tStart = McciBootloaderPlatform_getMilliseconds();
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_STOPF)
			{
			// AUTOEND: STOPF means we're done.
			status = McciBootloaderI2cBusStm32l0_Status_Done;
			}
		else if (isr & MCCI_STM32L0_I2C_ISR_NACKF)
			{
			status = McciBootloaderI2cBusStm32l0_Status_NackError;
			}
		// otherwise go on... we'll time out eventually
		}

	/* turn off the bus */
	McciArm_putRegClear(
		baseAddress + MCCI_STM32L0_I2C_CR1,
		MCCI_STM32L0_I2C_CR1_PE
		);

	return nBuffer_orig - nBuffer;
	}

static size_t
i2cBusWrite(
	McciBootloaderDeviceI2cBus_t *pBus,
	McciBootloaderDeviceI2cAddress_t i2cAddress,
	const uint8_t *pBuffer,
	size_t nBuffer
	)
	{
	const size_t nBuffer_orig = nBuffer;
	McciBootloaderDeviceI2cBusStm32l0_t * const pI2cBus = McciBootloader_DeviceI2cBus_getI2cBusStm32l0(pBus);
	uint32_t const baseAddress = pI2cBus->Stm32l0.pMasks->baseAddress;
	McciBootloader_Milliseconds_t tStart;
	McciBootloaderI2cBusStm32l0_Status_t status;

	if (nBuffer > 0xFF)
		McciBootloaderPlatform_fail(McciBootloaderError_InternalConsistency);

	// nBuffer == 0 is a write probe

	uint32_t cr2;

	cr2 = MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_I2C_CR2_SADD, i2cAddress << 1)
	    | MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_I2C_CR2_NBYTES, nBuffer)
	    | MCCI_STM32L0_I2C_CR2_AUTOEND
	    ;

	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_CR1,
		MCCI_STM32L0_I2C_CR1_PE
		);

	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_CR2,
		cr2
		);

	// set the start bit
	McciArm_putReg(
		baseAddress + MCCI_STM32L0_I2C_CR2,
		cr2 | MCCI_STM32L0_I2C_CR2_START
		);

	// Initialize timeout and prepare for loop.
	// These are essentially the precondition establishments
	// of a for (;;) loop.
	tStart = McciBootloaderPlatform_getMilliseconds();

	status = McciBootloaderI2cBusStm32l0_Status_Busy;

	// wait for the bus busy indication to come on; that's different from "loop is busy"
	// status.
	while (status == McciBootloaderI2cBusStm32l0_Status_Busy)
		{
		if (McciBootloaderPlatform_getMilliseconds() - tStart > MCCI_BOOTLOADER_STM32L0_I2C_TIME_OUT_MS)
			{
			status = McciBootloaderI2cBusStm32l0_Status_TimeOut;
			break;
			}

		uint32_t const isr = McciArm_getReg(
			baseAddress + MCCI_STM32L0_I2C_ISR
			);

		if (isr & MCCI_STM32L0_I2C_ISR_BUSY)
			{
			// go on to main loop.
			break;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_ARLO)
			{
			status = McciBootloaderI2cBusStm32l0_Status_ArbitrationLost;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_BERR)
			{
			status = McciBootloaderI2cBusStm32l0_Status_BusError;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_NACKF)
			{
			status = McciBootloaderI2cBusStm32l0_Status_NackError;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_STOPF)
			{
			status = McciBootloaderI2cBusStm32l0_Status_Done;
			}

		// otherwise keep waiting for busy to come on.
		}

	while (status == McciBootloaderI2cBusStm32l0_Status_Busy)
		{
		if (McciBootloaderPlatform_getMilliseconds() - tStart > MCCI_BOOTLOADER_STM32L0_I2C_TIME_OUT_MS)
			{
			status = McciBootloaderI2cBusStm32l0_Status_TimeOut;
			break;
			}

		uint32_t const isr = McciArm_getReg(
			baseAddress + MCCI_STM32L0_I2C_ISR
			);

		if (isr & MCCI_STM32L0_I2C_ISR_ARLO)
			{
			status = McciBootloaderI2cBusStm32l0_Status_ArbitrationLost;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_BERR)
			{
			status = McciBootloaderI2cBusStm32l0_Status_BusError;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_NACKF)
			{
			status = McciBootloaderI2cBusStm32l0_Status_NackError;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_STOPF)
			{
			status = McciBootloaderI2cBusStm32l0_Status_Done;
			}

		else if (isr & MCCI_STM32L0_I2C_ISR_TXE)
			{
			if (nBuffer == 0)
				{
				// we're waiting for STOPF due to AUTOEND.
				}
			else
				{
				McciArm_putReg(baseAddress + MCCI_STM32L0_I2C_TXDR, *pBuffer);
				++pBuffer, --nBuffer;

				// restart the timer
				tStart = McciBootloaderPlatform_getMilliseconds();
				}
			}

		// otherwise go on... we'll time out eventually
		}

	/* turn off the bus */
	McciArm_putRegClear(
		baseAddress + MCCI_STM32L0_I2C_CR1,
		MCCI_STM32L0_I2C_CR1_PE
		);

	return nBuffer_orig - nBuffer;
	}

/**** end of mccibootloader_stm32l0_i2c_bus.c ****/
