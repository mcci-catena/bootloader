/*

Module:	mcci_stm32l0xx.h

Function:
	Register definitions for STM32L0xx CPUs

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_stm32l0xx_h_
#define _mcci_stm32l0xx_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_bits_h_
# include "mcci_bootloader_bits.h"
#endif

#ifndef _mcci_arm_cm0plus_h_
# include "mcci_arm_cm0plus.h"
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	Register addresses
|
\****************************************************************************/

/// \name STM32L0xx top-level address breakdown
///	@{
#define	MCCI_STM32L0_MEMORY_FLASH	UINT32_C(0x08000000)	///< Flash program memory (up to 192K)
#define	MCCI_STM32L0_MEMORY_EEPROM	UINT32_C(0x08080000)	///< Data EEPROM (up to 6K)
#define	MCCI_STM32L0_MEMORY_SYSTEM	UINT32_C(0x1FF00000)	///< System memory (8K)
#define	MCCI_STM32L0_OPTIONS_USER	UINT32_C(0x1FF80000)	///< User option bytes (32)
#define	MCCI_STM32L0_OPTIONS_FACTORY	UINT32_C(0x1FF80020)	///< Factory option bytes (96)
#define	MCCI_STM32L0_MEMORY_SRAM	UINT32_C(0x20000000)	///< SRAM (up to 20K)
#define	MCCI_STM32L0_REG_TIMER2		UINT32_C(0x40000000)	///< Section 20.5: TIMx register map (1K)
#define	MCCI_STM32L0_REG_TIMER3		UINT32_C(0x40000400)	///< Section 20.5: TIMx register map (1K)
#define	MCCI_STM32L0_REG_TIMER6		UINT32_C(0x40001000)	///< Section 22.4.9: TIM6/7 register map (1K)
#define	MCCI_STM32L0_REG_TIMER7		UINT32_C(0x40001400)	///< Section 22.4.9: TIM6/7 register map (1K)
#define	MCCI_STM32L0_REG_RTC		UINT32_C(0x40002800)	///< Section 26.7.21: RTC + BKUP register map (1K)
#define	MCCI_STM32L0_REG_WWDG		UINT32_C(0x40002C00)	///< Section 25.4.4: WWDG register map (1K)
#define	MCCI_STM32L0_REG_IWDG		UINT32_C(0x40003000)	///< Section 24.4.6: IWDG register map (1K)
#define	MCCI_STM32L0_REG_SPI2		UINT32_C(0x40003800)	///< Section 30.7.10: SPI register map (1K)
#define	MCCI_STM32L0_REG_USART2		UINT32_C(0x40004400)	///< Section 28.8.12: USART register map (1K)
#define	MCCI_STM32L0_REG_LPUART1	UINT32_C(0x40004800)	///< Section 29.7.10: LPUART register map (1K)
#define	MCCI_STM32L0_REG_USART4		UINT32_C(0x40004C00)	///< Section 28.8.12: USART register map (1K)
#define	MCCI_STM32L0_REG_USART5		UINT32_C(0x40005000)	///< Section 28.8.12: USART register map (1K)
#define	MCCI_STM32L0_REG_I2C1		UINT32_C(0x40005400)	///< Section 27.7.12: I2C register map (1K)
#define	MCCI_STM32L0_REG_I2C2		UINT32_C(0x40005800)	///< Section 27.7.12: I2C register map (1K)
#define	MCCI_STM32L0_REG_USB_FS		UINT32_C(0x40005C00)	///< Section 31.6.3: USB register map (1K)
#define	MCCI_STM32L0_REG_USB_SRAM	UINT32_C(0x40006000)	///< USB (SRAM 512x16bit) (2K)
#define	MCCI_STM32L0_REG_CRS		UINT32_C(0x40006C00)	///< Section 8.6.5: CRS register map (1K)
#define	MCCI_STM32L0_REG_PWR		UINT32_C(0x40007000)	///< Section 6.4.3: PWR register map (1K)
#define	MCCI_STM32L0_REG_DAC1		UINT32_C(0x40007400)	///< Section 15.10.15: DAC register map (1K)
#define	MCCI_STM32L0_REG_I2C3		UINT32_C(0x40007800)	///< Section 27.7.12: I2C register map (1K)
#define	MCCI_STM32L0_REG_LPTIM1		UINT32_C(0x40007C00)	///< Section 23.6.9: LPTIM register map (1K)
#define	MCCI_STM32L0_REG_SYSCFG_COMP	UINT32_C(0x40010000)	///< Section 10.2.8: SYSCFG register map, Section 16.5.3: COMP register map (1K)
#define	MCCI_STM32L0_REG_EXTI		UINT32_C(0x40010400)	///< Section 13.5.7: EXTI register map (1K)
#define	MCCI_STM32L0_REG_TIM21		UINT32_C(0x40010800)	///< Section 21.4.16: TIM21/22 register map (1K)
#define	MCCI_STM32L0_REG_TIM22		UINT32_C(0x40011400)	///< Section 21.4.16: TIM21/22 register map (1K)
#define	MCCI_STM32L0_REG_FIREWALL	UINT32_C(0x40011C00)	///< Section 5.4.8: Firewall register map (1K)
#define	MCCI_STM32L0_REG_ADC1		UINT32_C(0x40012400)	///< Section 14.12.12: ADC register map (1K)
#define	MCCI_STM32L0_REG_SPI1		UINT32_C(0x40013000)	///< Section 30.7.10: SPI register map (1K)
#define	MCCI_STM32L0_REG_USART1		UINT32_C(0x40013800)	///< Section 28.8.12: USART register map (1K)
#define	MCCI_STM32L0_REG_DBG		UINT32_C(0x40015800)	///< Section 32.10: DBG register map (1K)
#define	MCCI_STM32L0_REG_DMA1		UINT32_C(0x40020000)	///< Section 11.4.8: DMA register map (1K)
#define	MCCI_STM32L0_REG_RCC		UINT32_C(0x40021000)	///< Section 7.3.22: RCC register map (1K)
#define	MCCI_STM32L0_REG_FLASH		UINT32_C(0x40022000)	///< Section 3.7.11: Flash register map (1K)
#define	MCCI_STM32L0_REG_CRC		UINT32_C(0x40023000)	///< Section 4.4.6: CRC register map (1K)
#define	MCCI_STM32L0_REG_TSC		UINT32_C(0x40024000)	///< Section 17.6.11: TSC register map (1K)
#define	MCCI_STM32L0_REG_RNG		UINT32_C(0x40025000)	///< Section 19.8.4: RNG register map (1K)
#define	MCCI_STM32L0_REG_AES		UINT32_C(0x40026000)	///< Section 18.12.13: AES register map (1K)
#define	MCCI_STM32L0_REG_GPIOA		UINT32_C(0x50000000)	///< Section 9.4.12: GPIO register map (1K)
#define	MCCI_STM32L0_REG_GPIOB		UINT32_C(0x50000400)	///< Section 9.4.12: GPIO register map (1K)
#define	MCCI_STM32L0_REG_GPIOC		UINT32_C(0x50000800)	///< Section 9.4.12: GPIO register map (1K)
#define	MCCI_STM32L0_REG_GPIOD		UINT32_C(0x50000C00)	///< Section 9.4.12: GPIO register map (1K)
#define	MCCI_STM32L0_REG_GPIOE		UINT32_C(0x50001000)	///< Section 9.4.12: GPIO register map (1K)
#define	MCCI_STM32L0_REG_GPIOH		UINT32_C(0x50001C00)	///< Section 9.4.12: GPIO register map (1K)
///	@}

/****************************************************************************\
|
|	Option bytes, etc
|
\****************************************************************************/

/// \name User option bytes
///	@{
#define MCCI_STM32L0_OPTIONS_USER_FLASH_OPTR_LOW	(MCCI_STM32L0_OPTIONS_USER + 0x00)
#define MCCI_STM32L0_OPTIONS_USER_FLASH_OPTR_HIGH	(MCCI_STM32L0_OPTIONS_USER + 0x04)
#define MCCI_STM32L0_OPTIONS_USER_FLASH_WRPROT1_LOW	(MCCI_STM32L0_OPTIONS_USER + 0x08)
#define MCCI_STM32L0_OPTIONS_USER_FLASH_WRPROT1_HIGH	(MCCI_STM32L0_OPTIONS_USER + 0x0C)
#define MCCI_STM32L0_OPTIONS_USER_FLASH_WRPROT2		(MCCI_STM32L0_OPTIONS_USER + 0x10)

/// \brief create an option dword from a 16-bit value (high 16 bits inverted copy of low)
#define MCCI_STM32L0_OPTIONS_MAKE_DWORD(v)	((~(uint32_t)(v) << 16) | (uint16_t)(v))
///	@}

/// \name System values in system option memory
///	@{
#define	MCCI_STM32L0_OPTIONS_SYSTEM_FLASH_SIZE_16	UINT32_C(0x1FF8007C)	///< memory size in k bytes (16 bits)

/// \brief convert flash_size_16 value to bytes
#define	MCCI_STM32L0_OPTIONS_SYSTEM_FLASH_SIZE_TO_BYTES(h)	\
	(((h) & UINT32_C(0xFFFF)) * 1024)

#define	MCCI_STM32L0_OPTIONS_U_ID_0	UINT32_C(0x1FF80050)			///< register address: unique ID bits 31:0
#define	MCCI_STM32L0_OPTIONS_U_ID_4	(MCCI_STM32L0_OPTIONS_U_ID_0 + 0x04)	///< register address: unique ID bits 63:32
#define	MCCI_STM32L0_OPTIONS_U_ID_8	(MCCI_STM32L0_OPTIONS_U_ID_0 + 0x014)	///< register address: unique ID bits 95:64
///	@}
 
/****************************************************************************\
|
|	Flash Control Registers (3.7)
|
\****************************************************************************/

/// \name FLASH registers
///	@{
#define MCCI_STM32L0_REG_FLASH_ACR	(MCCI_STM32L0_REG_FLASH + 0x00)	///< Flash access control register
#define MCCI_STM32L0_REG_FLASH_PECR	(MCCI_STM32L0_REG_FLASH + 0x04)	///< Flash program and erase control register
#define MCCI_STM32L0_REG_FLASH_PDKEYR	(MCCI_STM32L0_REG_FLASH + 0x08)	///< Flash power-down key register
#define MCCI_STM32L0_REG_FLASH_PEKEYR	(MCCI_STM32L0_REG_FLASH + 0x0C)	///< Flash PECR unlock key register
#define MCCI_STM32L0_REG_FLASH_PRGKEYR	(MCCI_STM32L0_REG_FLASH + 0x10)	///< Flash program/erase key register
#define MCCI_STM32L0_REG_FLASH_OPTKEYR	(MCCI_STM32L0_REG_FLASH + 0x14)	///< Flash option bytes unlock key register
#define MCCI_STM32L0_REG_FLASH_SR	(MCCI_STM32L0_REG_FLASH + 0x18)	///< Flash status register
#define MCCI_STM32L0_REG_FLASH_OPTR	(MCCI_STM32L0_REG_FLASH + 0x1C)	///< Flash option bytes register
#define MCCI_STM32L0_REG_FLASH_WPROT1	(MCCI_STM32L0_REG_FLASH + 0x20)	///< Flash write proection register 1
#define MCCI_STM32L0_REG_FLASH_WPROT2	(MCCI_STM32L0_REG_FLASH + 0x80)	///< Flash write protection register 2
///	@}

/// \name FLASH_ACR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_ACR_RSV7		UINT32_C(0xFFFFFF80)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_ACR_PRE_READ	(UINT32_C(1) << 6)	///< Enable pre-read
#define MCCI_STM32L0_REG_FLASH_ACR_DISAB_BUF	(UINT32_C(1) << 5)	///< Disable read buffer
#define MCCI_STM32L0_REG_FLASH_ACR_RUN_PD	(UINT32_C(1) << 4)	///< power-down in run mode
#define MCCI_STM32L0_REG_FLASH_ACR_SLEEP_PD	(UINT32_C(1) << 3)	///< power-down in sleep mode
#define MCCI_STM32L0_REG_FLASH_ACR_RSV2		(UINT32_C(1) << 2)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_ACR_PRFTEN	(UINT32_C(1) << 1)	///< prefetch enable
#define MCCI_STM32L0_REG_FLASH_ACR_LATENCY	(UINT32_C(1) << 0)	///< NVM latency: 1 wait state (not zero wait state)
///	@}

/// \name FLASH_PECR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_PECR_RSV24		UINT32_C(0xFF000000)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_PECR_NZDISABLE		(UINT32_C(1) << 23)	///< Disable non-zero check
#define MCCI_STM32L0_REG_FLASH_PECR_RSV19		(UINT32_C(0xF) << 19)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_PECR_OBL_LAUNCH		(UINT32_C(1) << 18)	///< Reload option bytes and reset system
#define MCCI_STM32L0_REG_FLASH_PECR_ERRIE		(UINT32_C(1) << 17)	///< Error interrupt enable
#define MCCI_STM32L0_REG_FLASH_PECR_EOPIE		(UINT32_C(1) << 16)	///< End of programming interrupt enable
#define MCCI_STM32L0_REG_FLASH_PECR_PARALLELBANK	(UINT32_C(1) << 15)	///< Parallel bank programming enable
#define MCCI_STM32L0_REG_FLASH_PECR_RSV11		(UINT32_C(0xF) << 11)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_PECR_FPRG		(UINT32_C(1) << 10)	///< Enable half-page programming mode
#define MCCI_STM32L0_REG_FLASH_PECR_ERASE		(UINT32_C(1) << 9)	///< Erase operation requested/not requested
#define MCCI_STM32L0_REG_FLASH_PECR_FIX			(UINT32_C(1) << 8)	///< Atomatically erase before programming EEPROM and options
#define MCCI_STM32L0_REG_FLASH_PECR_RSV5		(UINT32_C(7) << 5)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_PECR_DATA		(UINT32_C(1) << 4)	///< Select data memory
#define MCCI_STM32L0_REG_FLASH_PECR_PROG		(UINT32_C(1) << 3)	///< Select program memory
#define MCCI_STM32L0_REG_FLASH_PECR_OPTLOCK		(UINT32_C(1) << 2)	///< Lock option bytes
#define MCCI_STM32L0_REG_FLASH_PECR_PRGLOCK		(UINT32_C(1) << 1)	///< Lock program memory
#define MCCI_STM32L0_REG_FLASH_PECR_PELOCK		(UINT32_C(1) << 0)	///< Lock the FLASH_PECR register
///	@}

/// \name FLASH_PDKEYR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_PDKEYR_UNLOCK1	UINT32_C(0x04152637)	///< unlock word 1 for RUN_PD
#define MCCI_STM32L0_REG_FLASH_PDKEYR_UNLOCK2	UINT32_C(0xFAFBFCFD)	///< unlock word 2 for RUN_PD
///	@}

/// \name FLASH_PEKEYR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK1	UINT32_C(0x89ABCDEF)	///< unlock word 1 for PECR
#define MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK2	UINT32_C(0x02030405)	///< unlock word 2 for PECR
///	@}

/// \name FLASH_PRGKEYR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_PRGKEYR_UNLOCK1	UINT32_C(0x8C9DAEBF)	///< unlock word 1 for PRGKEYR
#define MCCI_STM32L0_REG_FLASH_PRGKEYR_UNLOCK2	UINT32_C(0x13141516)	///< unlock word 2 for PRGKEYR
///	@}

/// \name FLASH_OPTKEYR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_OPTKEYR_UNLOCK1	UINT32_C(0xFBEAD9C8)	///< unlock word 1 for option bytes
#define MCCI_STM32L0_REG_FLASH_OPTKEYR_UNLOCK2	UINT32_C(0x24252627)	///< unlock word 2 for option bytes
///	@}

/// \name FLASH_SR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_SR_RSV18		UINT32_C(0xFFFC0000)	///< Reserved, don't change.
#define MCCI_STM32L0_REG_FLASH_SR_FWWERR	(UINT32_C(1) << 17)	///< Write/erase aborted for fetch.
#define MCCI_STM32L0_REG_FLASH_SR_NOTZEROERR	(UINT32_C(1) << 16)	///< Attempt to program non-zero area
#define MCCI_STM32L0_REG_FLASH_SR_RSV14		(UINT32_C(3) << 14)	///< Reserved, don't change.
#define MCCI_STM32L0_REG_FLASH_SR_RDERR		(UINT32_C(1) << 13)	///< Read-protection error
#define MCCI_STM32L0_REG_FLASH_SR_RSV12		(UINT32_C(1) << 12)	///< Reserved, don't change.
#define MCCI_STM32L0_REG_FLASH_SR_OPTVERR	(UINT32_C(1) << 11)	///< Option valid error
#define MCCI_STM32L0_REG_FLASH_SR_SIZERR	(UINT32_C(1) << 10)	///< Size error when programming
#define MCCI_STM32L0_REG_FLASH_SR_PGAERR	(UINT32_C(1) << 9)	///< Programming alignment error
#define MCCI_STM32L0_REG_FLASH_SR_WRPERR	(UINT32_C(1) << 8)	///< write protection error.
#define MCCI_STM32L0_REG_FLASH_SR_RSV4		(UINT32_C(0xF) << 4)	///< Reserved, don't change.
#define MCCI_STM32L0_REG_FLASH_SR_READY		(UINT32_C(1) << 3)	///< NVM is ready
#define MCCI_STM32L0_REG_FLASH_SR_ENDHV		(UINT32_C(1) << 2)	///< High voltage is off (not on), not active
#define MCCI_STM32L0_REG_FLASH_SR_EOP		(UINT32_C(1) << 1)	///< End of program
#define MCCI_STM32L0_REG_FLASH_SR_BSY		(UINT32_C(1) << 0)	///< Busy doing write/erase
///	@}

/// \name FLASH_OPTR bits
///	@{
#define MCCI_STM32L0_REG_FLASH_OPTR_nBOOT1	(UINT32_C(1) << 31)	///< If boot0, boot from system rom (not RAM)
#define MCCI_STM32L0_REG_FLASH_OPTR_RSV24	(UINT32_C(0x7F) << 24)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_OPTR_BFB2	(UINT32_C(1) << 23)	///< Boot from system memory (not bank 2)
#define MCCI_STM32L0_REG_FLASH_OPTR_nRST_STDBY	(UINT32_C(1) << 22)	///< do not generate reset when entering standby
#define MCCI_STM32L0_REG_FLASH_OPTR_nRST_STOP	(UINT32_C(1) << 21)	///< do not generate reset when entering stop
#define MCCI_STM32L0_REG_FLASH_OPTR_WDG_SW	(UINT32_C(1) << 20)	///< software (not hardware) watchdog

#define MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV	(UINT32_C(0xF) << 16)	///< brown-out reset level
#define  MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV_1v8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV, 8)		///< Level 1 (1.8 V)
#define  MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV_2v0	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV, 9)		///< Level 2 (2.0 V)
#define  MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV_2v5	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV, 10)	///< Level 3 (2.5 V)
#define  MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV_2v7	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV, 11)	///< Level 4 (2.7 V)
#define  MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV_3v0	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_BOR_LEV, 12)	///< Level 5 (3.0 V)

#define MCCI_STM32L0_REG_FLASH_OPTR_RSV9	(UINT32_C(0x7F) << 9)	///< Reserved, don't change
#define MCCI_STM32L0_REG_FLASH_OPTR_WPRMOD	(UINT32_C(1) << 8)	///< PCROP enabled (use WPROT for read protection)

#define MCCI_STM32L0_REG_FLASH_OPTR_RDPROT	(UINT32_C(0xFF) << 0)	///< Read protection level
#define  MCCI_STM32L0_REG_FLASH_OPTR_RDPROT_L0	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_RDPROT, 0xAA)	//< level 0
#define  MCCI_STM32L0_REG_FLASH_OPTR_RDPROT_L2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_RDPROT, 0xCC)	//< level 2
#define  MCCI_STM32L0_REG_FLASH_OPTR_RDPROT_L1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_FLASH_OPTR_RDPROT, 0x0)	//< level 2

/// \brief given image of FLASH_OPTR, return true if set for level 0 protection
#define	MCCI_STM32L0_FLASH_OPTR_RDPROT_IS_L0(v)	\
	((v) & MCCI_STM32L0_REG_FLASH_OPTR_RDPROT) == MCCI_STM32L0_REG_FLASH_OPTR_RDPROT_L0)
/// \brief given image of FLASH_OPTR, return true if set for level 2 protection
#define	MCCI_STM32L0_FLASH_OPTR_RDPROT_IS_L2(v)	\
	((v) & MCCI_STM32L0_REG_FLASH_OPTR_RDPROT) == MCCI_STM32L0_REG_FLASH_OPTR_RDPROT_L0)
/// \brief given image of FLASH_OPTR, return true if set for level 1 protection
#define	MCCI_STM32L0_FLASH_OPTR_RDPROT_IS_L1(v)	\
	(! (MCCI_STM32L0_FLASH_OPTR_RDPROT_IS_L0(v) || MCCI_STM32L0_FLASH_OPTR_RDPROT_IS_L2(v)))
///	@}

/// \name FLASH_WPROT1, FLASH_WPROT2 bits
///	@{
#define MCCI_STM32L0_FLASH_SECTOR_SIZE		UINT32_C(4096)	///< size in bytes of a flash sector
/// \brief given a flash address, convert to sector number
#define	MCCI_STM32L0_FLASH_ADDRESS_GET_SECTOR(a)	\
	(((uint32_t)(a) - MCCI_STM32L0_MEMORY_FLASH) >> MCCI_BOOTLOADER_FIELD_SHIFT(MCCI_STM32L0_FLASH_SECTOR_SIZE))

/// \brief get reg offset for protection bit for sector \p s
#define	MCCI_STM32L0_REG_FLASH_WPROTx_FOR_SECTOR(s)	((s) < 32 ? MCCI_STM32L0_REG_FLASH_WPROT1 : MCCI_STM32L0_REG_FLASH_WPROT2)

/// \brief get mask for sector \p s.
#define	MCCI_STM32L0_FLASH_WPROT_MASK_FOR_SECTOR(s)	(UINT32_C(1) << ((s) & 0x1F)) 
///	@}

/// \name Flash programming constants
///	@{
#define MCCI_STM32L0_FLASH_HALF_PAGE_SIZE	UINT32_C(64)	///< size in bytes of a half-page
#define MCCI_STM32L0_FLASH_PAGE_SIZE		UINT32_C(128)	///< size in bytes of a page
///	@}

/****************************************************************************\
|
|	Power Control Registers
|
\****************************************************************************/

/// \name PWR registers
///	@{
#define	MCCI_STM32L0_REG_PWR_CR		(MCCI_STM32L0_REG_PWR + 0x0)
#define	MCCI_STM32L0_REG_PWR_CSR	(MCCI_STM32L0_REG_PWR + 0x4)
///	@}

/// \name PWR_CR bits
///	@{
#define	MCCI_STM32L0_REG_PWR_CR_LPRUN		(UINT32_C(1) << 14)	///< Low power run mode
#define	MCCI_STM32L0_REG_PWR_CR_DS_EE_KOFF	(UINT32_C(1) << 13)	///< deep sleep mode with nv mem off

#define	MCCI_STM32L0_REG_PWR_CR_VOS		(UINT32_C(3) << 11)	///< voltage scaling range
# define MCCI_STM32L0_REG_PWR_CR_VOS_NC		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_VOS, 0)	///< no change / not allowed
# define MCCI_STM32L0_REG_PWR_CR_VOS_1V8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_VOS, 1)	///< 1.8V
# define MCCI_STM32L0_REG_PWR_CR_VOS_1V5	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_VOS, 2)	///< 1.5V
# define MCCI_STM32L0_REG_PWR_CR_VOS_1V2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_VOS, 3)	///< 1.2V

#define	MCCI_STM32L0_REG_PWR_CR_FWU		(UINT32_C(1) << 10)	///< fast wakeup
#define	MCCI_STM32L0_REG_PWR_CR_ULP		(UINT32_C(1) << 9)	///< ultra low-power mode
#define	MCCI_STM32L0_REG_PWR_CR_DBP		(UINT32_C(1) << 8)	///< disable backup write protection

#define	MCCI_STM32L0_REG_PWR_CR_PLS		(UINT32_C(7) << 5)	///< power voltage detector level
# define MCCI_STM32L0_REG_PWR_CR_PLS_1V9	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 0)	///< 1.9 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_2V1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 1)	///< 2.1 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_2V3	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 2)	///< 2.3 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_2V5	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 3)	///< 2.5 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_2V7	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 4)	///< 2.7 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_2V9	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 5)	///< 2.9 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_3V1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 6)	///< 3.1 V
# define MCCI_STM32L0_REG_PWR_CR_PLS_EXT	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLS, 7)	///< Vrefint

#define	MCCI_STM32L0_REG_PWR_CR_PVDE		(UINT32_C(1) << 4)	///< power voltage detector enabled
#define	MCCI_STM32L0_REG_PWR_CR_CSBF		(UINT32_C(1) << 3)	///< clear the SBF standby flag
#define	MCCI_STM32L0_REG_PWR_CR_CWUF		(UINT32_C(1) << 2)	///< clear the wakeup flag
#define	MCCI_STM32L0_REG_PWR_CR_PDDS		(UINT32_C(1) << 1)	///< power-down deep sleep
#define	MCCI_STM32L0_REG_PWR_CR_LPSDSR		(UINT32_C(1) << 0)	///< low-power deep sleep/sleep/low-power run
/// @}

/// \name PWR_SCR bits
///	@{
#define MCCI_STM32L0_REG_PWR_CSR_RSV11		UINT32C(0xFFFFF800)	///< reserved, do not change
#define MCCI_STM32L0_REG_PWR_CSR_EWUP3		(UINT32_C(1) << 10)	///< Enable WKUP pin 3
#define MCCI_STM32L0_REG_PWR_CSR_EWUP2		(UINT32_C(1) << 9)	///< Enable WKUP pin 2
#define MCCI_STM32L0_REG_PWR_CSR_EWUP1		(UINT32_C(1) << 8)	///< Enable WKUP pin 1
#define MCCI_STM32L0_REG_PWR_CSR_RSV6		(UINT32_C(3) << 6)	///< Reserved, do not change
#define MCCI_STM32L0_REG_PWR_CSR_REGLPF		(UINT32_C(1) << 5)	///< Regulator low-power flag
#define MCCI_STM32L0_REG_PWR_CSR_VOSF		(UINT32_C(1) << 4)	///< Voltage scaling select flag
#define MCCI_STM32L0_REG_PWR_CSR_VREFINTRDYF	(UINT32_C(1) << 3)	///< Vrefint ready flag
#define MCCI_STM32L0_REG_PWR_CSR_PVDO	 	(UINT32_C(1) << 2)	///< PVD output
#define MCCI_STM32L0_REG_PWR_CSR_SBF	 	(UINT32_C(1) << 1)	///< Standby flag
#define MCCI_STM32L0_REG_PWR_CSR_WUF		(UINT32_C(1) << 0)	///< Wakeup flag
///	@}

/****************************************************************************\
|
|	Reset and Clock Control (RCC) Registers
|
\****************************************************************************/

/// \name RCC registers
///	@{
#define	MCCI_STM32L0_REG_RCC_CR		(MCCI_STM32L0_REG_RCC + 0x00)	///< Clock control
#define	MCCI_STM32L0_REG_RCC_ICSCR	(MCCI_STM32L0_REG_RCC + 0x04)	///< Internal clock sources calibration
#define	MCCI_STM32L0_REG_RCC_CRRCR	(MCCI_STM32L0_REG_RCC + 0x08)	///< Clock recovery RC
#define	MCCI_STM32L0_REG_RCC_CFGR	(MCCI_STM32L0_REG_RCC + 0x0C)	///< Clock configuration
#define	MCCI_STM32L0_REG_RCC_CIER	(MCCI_STM32L0_REG_RCC + 0x10)	///< Clock interrupt enable
#define	MCCI_STM32L0_REG_RCC_CIFR	(MCCI_STM32L0_REG_RCC + 0x14)	///< Clock interrupt flag
#define	MCCI_STM32L0_REG_RCC_CICR	(MCCI_STM32L0_REG_RCC + 0x18)	///< Clock interrupt clear
#define	MCCI_STM32L0_REG_RCC_IOPRSTR	(MCCI_STM32L0_REG_RCC + 0x1C)	///< GPIO reset
#define	MCCI_STM32L0_REG_RCC_AHBRSTR	(MCCI_STM32L0_REG_RCC + 0x20)	///< AHB peripheral reset
#define	MCCI_STM32L0_REG_RCC_APB2RSTR	(MCCI_STM32L0_REG_RCC + 0x24)	///< APB2 peripheral reset
#define	MCCI_STM32L0_REG_RCC_APB1RSTR	(MCCI_STM32L0_REG_RCC + 0x28)	///< APB1 peripheral reset
#define	MCCI_STM32L0_REG_RCC_IOPENR	(MCCI_STM32L0_REG_RCC + 0x2C)	///< GPIO clock enable
#define	MCCI_STM32L0_REG_RCC_AHBENR	(MCCI_STM32L0_REG_RCC + 0x30)	///< AHB peripheral clock enable
#define	MCCI_STM32L0_REG_RCC_APB2ENR	(MCCI_STM32L0_REG_RCC + 0x34)	///< APB2 peripheral clock enable
#define	MCCI_STM32L0_REG_RCC_APB1ENR	(MCCI_STM32L0_REG_RCC + 0x38)	///< APB1 peripheral clock enable
#define	MCCI_STM32L0_REG_RCC_IOPSMEN	(MCCI_STM32L0_REG_RCC + 0x3C)	///< GPIO clock enable in sleep
#define	MCCI_STM32L0_REG_RCC_AHBSMENR	(MCCI_STM32L0_REG_RCC + 0x40)	///< AHB peripheral clock enable in sleep
#define	MCCI_STM32L0_REG_RCC_APB2SMENR	(MCCI_STM32L0_REG_RCC + 0x44)	///< APB2 peripheral clock enable in sleep
#define	MCCI_STM32L0_REG_RCC_APB1SMENR	(MCCI_STM32L0_REG_RCC + 0x48)	///< APB1 peripheral clock enable in sleep
#define	MCCI_STM32L0_REG_RCC_CCIPR	(MCCI_STM32L0_REG_RCC + 0x4C)	///< Clock configuration CCIPR
#define	MCCI_STM32L0_REG_RCC_CSR	(MCCI_STM32L0_REG_RCC + 0x50)	///< Control/status
///	@}

/// \name RCC_CR bits
///	@{
#define MCCI_STM32L0_REG_RCC_CR_RSV26		UINT32_C(0xFC000000)	//< reserved, no change
#define MCCI_STM32L0_REG_RCC_CR_PLLRDY		(UINT32_C(1) << 25)	//< PLL clock is ready
#define MCCI_STM32L0_REG_RCC_CR_PLLON		(UINT32_C(1) << 24)	//< PLL enable
#define MCCI_STM32L0_REG_RCC_CR_RSV22		(UINT32_C(3) << 22)	//< reserved, no change
#define MCCI_STM32L0_REG_RCC_CR_RTCPRE		(UINT32_C(3) << 20)	//< RTC prescalers
#define MCCI_STM32L0_REG_RCC_CR_RTCPRE_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLSMCCI_STM32L0_REG_RCC_CR_RTCPRE, 0)
#define MCCI_STM32L0_REG_RCC_CR_RTCPRE_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLSMCCI_STM32L0_REG_RCC_CR_RTCPRE, 1)
#define MCCI_STM32L0_REG_RCC_CR_RTCPRE_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLSMCCI_STM32L0_REG_RCC_CR_RTCPRE, 2)
#define MCCI_STM32L0_REG_RCC_CR_RTCPRE_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_PWR_CR_PLSMCCI_STM32L0_REG_RCC_CR_RTCPRE, 3)
#define MCCI_STM32L0_REG_RCC_CR_CSSHSEON	(UINT32_C(1) << 19)	//< enable clock security HSE
#define MCCI_STM32L0_REG_RCC_CR_HSEBYP		(UINT32_C(1) << 18)	//< enable HSE clock bypass
#define MCCI_STM32L0_REG_RCC_CR_HSERDY		(UINT32_C(1) << 17)	//< HSE clock ready
#define MCCI_STM32L0_REG_RCC_CR_HSEON		(UINT32_C(1) << 16)	//< HSE enabled
#define MCCI_STM32L0_REG_RCC_CR_RSV10		UINT32_C(0x0000FC00)	//< reserved, no change
#define MCCI_STM32L0_REG_RCC_CR_MSIRDY		(UINT32_C(1) << 9)	//< MSI clock ready
#define MCCI_STM32L0_REG_RCC_CR_MSION		(UINT32_C(1) << 8)	//< MSI clock on
#define MCCI_STM32L0_REG_RCC_CR_RSV6		(UINT32_C(3) << 6)	//< reserved, no change
#define MCCI_STM32L0_REG_RCC_CR_HSI16OUTEN	(UINT32_C(1) << 5)	//< enable HSI16 output to TIM2
#define MCCI_STM32L0_REG_RCC_CR_HSI16DIVF	(UINT32_C(1) << 4)	//< HSI16 is being divided by 4 (status)
#define MCCI_STM32L0_REG_RCC_CR_HSI16DIVEN	(UINT32_C(1) << 3)	//< Divide HSI16 by 4 (control)
#define MCCI_STM32L0_REG_RCC_CR_HSI16RDYF	(UINT32_C(1) << 2)	//< HSI16 is stable
#define MCCI_STM32L0_REG_RCC_CR_HSI16KERON	(UINT32_C(1) << 1)	//< force HSI16 on during stop
#define MCCI_STM32L0_REG_RCC_CR_HSI16ON		(UINT32_C(1) << 0)	//< enable HSI16
///	@}

/// \name RCC_ICSCR bits
///	@{
#define MCCI_STM32L0_REG_RCC_ICSCR_MSITRIM	(UINT32_C(0xFF) << 24)	//< MSI clock trimming
#define MCCI_STM32L0_REG_RCC_ICSCR_MSICAL	(UINT32_C(0xFF) << 16)	//< MSI clock cal

#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE	(UINT32_C(7) << 13)	//< MSI clock ranges
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_65k		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 0)	//< 65.536 kHz
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_131k	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 1)	//< 131.072 kHz
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_262k	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 2)	//< 262.144 kHz
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_524k	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 3)	//< 524.288 kHz
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_1048k	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 4)	//< 1.048 MHz
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_2097k	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 5)	//< 2.097 MHz
#define MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE_4194k	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_ICSCR_MSIRANGE, 6)	//< 4.194 MHz

#define MCCI_STM32L0_REG_RCC_ICSCR_HSI16TRIM	(UINT32_C(0x1F) << 8)	//< HSI16 trim
#define MCCI_STM32L0_REG_RCC_ICSCR_HSI16CAL	(UINT32_C(0xFF) << 0)	//< HSI16 clock cal
///	@}

/// \name RCC_CRRCR bits
///	@{
#define MCCI_STM32L0_REG_RCC_CRRCR_RSV16	UINT32_C(0xFFFF0000)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_CRRCR_HSI48CAL	(UINT32_C(0xFF) << 8)	//< calibration for HSI48
#define MCCI_STM32L0_REG_RCC_CRRCR_RSV3		UINT32_C(0xF8)		//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_CRRCR_HSI48DIVEN	(UINT32_C(1) << 2)	//< deliver HSI48/6 to TIM3
#define MCCI_STM32L0_REG_RCC_CRRCR_HSI48RDY	(UINT32_C(1) << 1)	//< 48 MHz clock ready
#define MCCI_STM32L0_REG_RCC_CRRCR_HSI48ON	(UINT32_C(1) << 0)	//< 48 MHz clock enable
///	@}

/// \name RCC_CFGR bits
///	@{
#define MCCI_STM32L0_REG_RCC_CFGR_RSV31		(UINT32_C(1) << 31)	//< reserved, don't change

#define MCCI_STM32L0_REG_RCC_CFGR_MCOPRE	(UINT32_C(7) << 28)	//< Clock output prescaler
#define MCCI_STM32L0_REG_RCC_CFGR_MCOPRE_1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOPRE, 0)	//< prescale MCO divide by 1
#define MCCI_STM32L0_REG_RCC_CFGR_MCOPRE_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOPRE, 1)	//< prescale MCO divide by 2
#define MCCI_STM32L0_REG_RCC_CFGR_MCOPRE_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOPRE, 2)	//< prescale MCO divide by 4
#define MCCI_STM32L0_REG_RCC_CFGR_MCOPRE_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOPRE, 3)	//< prescale MCO divide by 6
#define MCCI_STM32L0_REG_RCC_CFGR_MCOPRE_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOPRE, 4)	//< prescale MCO divide by 16

#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL	(UINT32_C(0xF) << 24)	//< Clock output selection
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_OFF	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 0)	//< Clock output disabled
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_SYSCLK	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 1)	//< MCO from Sysclk
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 2)	//< MCO from HSI16
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_MSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 3)	//< MCO from MSI
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_HSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 4)	//< MCO from HSE
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_PLL	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 5)	//< MCO from PLL
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_LSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 6)	//< MCO from LSI
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_LSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 7)	//< MCO from LSE
#define MCCI_STM32L0_REG_RCC_CFGR_MCOSEL_HSI48	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_MCOSEL, 8)	//< MCO from HSI48

#define MCCI_STM32L0_REG_RCC_CFGR_PLLDIV	(UINT32_C(3) << 22)	//< PLL divisor
#define MCCI_STM32L0_REG_RCC_CFGR_PLLDIV_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLDIV, 1)	//< PLL: divide by 2
#define MCCI_STM32L0_REG_RCC_CFGR_PLLDIV_3	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLDIV, 2)	//< PLL: divide by 3
#define MCCI_STM32L0_REG_RCC_CFGR_PLLDIV_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLDIV, 3)	//< PLL: divide by 4
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL	(UINT32_C(0xF) << 18)	//< PLL multiplier
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_3	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 0)	//< PLL: multiply by 3
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 1)	//< PLL: multiply by 4
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_6	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 2)	//< PLL: multiply by 6
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 3)	//< PLL: multiply by 8
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_12	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 4)	//< PLL: multiply by 12
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 5)	//< PLL: multiply by 16
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_24	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 6)	//< PLL: multiply by 24
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_32	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 7)	//< PLL: multiply by 32
#define MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_48	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLMUL, 8)	//< PLL: multiply by 48
#define MCCI_STM32L0_REG_RCC_CFGR_RSV17		(UINT32_C(1) << 17)	//< reserved, don't change

#define MCCI_STM32L0_REG_RCC_CFGR_PLLSRC	(UINT32_C(1) << 16)	//< PLL clock source
#define  MCCI_STM32L0_REG_RCC_CFGR_PLLSRC_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLSRC, 0)	//< PLL clock source: HSI16
#define  MCCI_STM32L0_REG_RCC_CFGR_PLLMUL_HSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PLLSRC, 1)	//< PLL clock source: HSE

#define MCCI_STM32L0_REG_RCC_CFGR_STOPWUCK	(UINT32_C(1) << 15)	//< Wakeup from stop clock
#define  MCCI_STM32L0_REG_RCC_CFGR_STOPWUCK_MSI		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_STOPWUCK, 0)	//< Wakeup from stop clock: MSI
#define  MCCI_STM32L0_REG_RCC_CFGR_STOPWUCK_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_STOPWUCK, 1)	//< Wakeup from stop clock: HSI16

#define MCCI_STM32L0_REG_RCC_CFGR_RSV14		(UINT32_C(1) << 14)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE2		(UINT32_C(7) << 11)	//< APB high-speed prescaler
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE2_1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE2, 0)	//< AHB high-speed prescaler: not divided
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE2_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE2, 4)	//< AHB high-speed prescaler: divide by 2
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE2_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE2, 5)	//< AHB high-speed prescaler: divide by 4
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE2_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE2, 6)	//< AHB high-speed prescaler: divide by 8
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE2_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE2, 7)	//< AHB high-speed prescaler: divide by 16
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE1		(UINT32_C(7) << 8)	//< APB low-speed prescaler 
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE1_1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE1, 0)	//< APB low-speed prescaler: none
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE1_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE1, 4)	//< APB low-speed prescaler: divide by 2
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE1_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE1, 5)	//< APB low-speed prescaler: divide by 4
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE1_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE1, 6)	//< APB low-speed prescaler: divide by 8
#define MCCI_STM32L0_REG_RCC_CFGR_PPRE1_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_PPRE1, 7)	//< APB low-speed prescaler: divide by 16
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE		(UINT32_C(0xF) << 4)	//< AHB prescaler
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 0)	//< AHB prescaler: SYSCLK not divided
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 8)	//< AHB prescaler: SYSCLK / 2
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 9)	//< AHB prescaler: SYSCLK / 4
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 10)	//< AHB prescaler: SYSCLK / 8
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 11)	//< AHB prescaler: SYSCLK / 16
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_64	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 12)	//< AHB prescaler: SYSCLK / 64
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_128	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 13)	//< AHB prescaler: SYSCLK / 128
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_256	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 14)	//< AHB prescaler: SYSCLK / 256
#define MCCI_STM32L0_REG_RCC_CFGR_HPRE_512	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_HPRE, 15)	//< AHB prescaler: SYSCLK / 512
#define MCCI_STM32L0_REG_RCC_CFGR_SWS		(UINT32_C(3) << 2)	//< SYSCLK switch status
#define MCCI_STM32L0_REG_RCC_CFGR_SWS_MSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SWS, 0)	//< SYSCLK using MSI
#define MCCI_STM32L0_REG_RCC_CFGR_SWS_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SWS, 1)	//< SYSCLK using HSI16
#define MCCI_STM32L0_REG_RCC_CFGR_SWS_HSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SWS, 2)	//< SYSCLK using HSE
#define MCCI_STM32L0_REG_RCC_CFGR_SWS_PLL	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SWS, 3)	//< SYSCLK using PLLL
#define MCCI_STM32L0_REG_RCC_CFGR_SW		(UINT32_C(3) << 0)	//< SYSCLK source select
#define MCCI_STM32L0_REG_RCC_CFGR_SW_MSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SW, 0)	//< SYSCLK: use MSI
#define MCCI_STM32L0_REG_RCC_CFGR_SW_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SW, 1)	//< SYSCLK: use HSI16
#define MCCI_STM32L0_REG_RCC_CFGR_SW_HSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SW, 2)	//< SYSCLK: use HSE
#define MCCI_STM32L0_REG_RCC_CFGR_SW_PLL	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CFGR_SW, 3)	//< SYSCLK: use PLL
///	@}

/// \name RCC_CIER bits
///	@{
#define MCCI_STM32L0_REG_RCC_CIER_RSV8		UINT32_C(0xFFFFFF00)
#define MCCI_STM32L0_REG_RCC_CIER_CSSLSE	(UINT32_C(1) << 7)
#define MCCI_STM32L0_REG_RCC_CIER_HSI48RDYIE	(UINT32_C(1) << 6)
#define MCCI_STM32L0_REG_RCC_CIER_MSIRDYIE	(UINT32_C(1) << 5)
#define MCCI_STM32L0_REG_RCC_CIER_PLLRDYIE	(UINT32_C(1) << 4)
#define MCCI_STM32L0_REG_RCC_CIER_HSERDYIE	(UINT32_C(1) << 3)
#define MCCI_STM32L0_REG_RCC_CIER_HSI16RDYIE	(UINT32_C(1) << 2)
#define MCCI_STM32L0_REG_RCC_CIER_LSERDYIE	(UINT32_C(1) << 1)
#define MCCI_STM32L0_REG_RCC_CIER_LSIRDYIE	(UINT32_C(1) << 0)
///	@}

/// \name RCC_CIFR bits
///	@{
#define MCCI_STM32L0_REG_RCC_CIFR_RSV9		UINT32_C(0xFFFFFE00)
#define MCCI_STM32L0_REG_RCC_CIFR_CSSHSEF	(UINT32_C(1) << 8)
#define MCCI_STM32L0_REG_RCC_CIFR_CSSLSEF	(UINT32_C(1) << 7)
#define MCCI_STM32L0_REG_RCC_CIFR_HSI48RDYF	(UINT32_C(1) << 6)
#define MCCI_STM32L0_REG_RCC_CIFR_MSIRDYF	(UINT32_C(1) << 5)
#define MCCI_STM32L0_REG_RCC_CIFR_PLLRDYF	(UINT32_C(1) << 4)
#define MCCI_STM32L0_REG_RCC_CIFR_HSERDYF	(UINT32_C(1) << 3)
#define MCCI_STM32L0_REG_RCC_CIFR_HSI16RDYF	(UINT32_C(1) << 2)
#define MCCI_STM32L0_REG_RCC_CIFR_LSERDYF	(UINT32_C(1) << 1)
#define MCCI_STM32L0_REG_RCC_CIFR_LSIRDYF	(UINT32_C(1) << 0)
///	@}

/// \name RCC_CICR bits
///	@{
#define MCCI_STM32L0_REG_RCC_CICR_RSV9		UINT32_C(0xFFFFFE00)
#define MCCI_STM32L0_REG_RCC_CICR_CSSHSEC	(UINT32_C(1) << 8)
#define MCCI_STM32L0_REG_RCC_CICR_CSSLSEC	(UINT32_C(1) << 7)
#define MCCI_STM32L0_REG_RCC_CICR_HSI48RDYC	(UINT32_C(1) << 6)
#define MCCI_STM32L0_REG_RCC_CICR_MSIRDYC	(UINT32_C(1) << 5)
#define MCCI_STM32L0_REG_RCC_CICR_PLLRDYC	(UINT32_C(1) << 4)
#define MCCI_STM32L0_REG_RCC_CICR_HSERDYC	(UINT32_C(1) << 3)
#define MCCI_STM32L0_REG_RCC_CICR_HSI16RDYC	(UINT32_C(1) << 2)
#define MCCI_STM32L0_REG_RCC_CICR_LSERDYC	(UINT32_C(1) << 1)
#define MCCI_STM32L0_REG_RCC_CICR_LSIRDYC	(UINT32_C(1) << 0)
///	@}

/// \name RCC_IOPRSTR bits
///	@{
#define MCCI_STM32L0_REG_RCC_IOPRSTR_RSV8	UINT32_C(0xFFFFFF00)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_IOPRSTR_IOPHRST	(UINT32_C(1) << 7)	//< Port H reset
#define MCCI_STM32L0_REG_RCC_IOPRSTR_RSV5	(UINT32_C(3) << 5)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_IOPRSTR_IOPERST	(UINT32_C(1) << 4)	//< Port E reset
#define MCCI_STM32L0_REG_RCC_IOPRSTR_IOPDRST	(UINT32_C(1) << 3)	//< Port D reset
#define MCCI_STM32L0_REG_RCC_IOPRSTR_IOPCRST	(UINT32_C(1) << 2)	//< Port C reset
#define MCCI_STM32L0_REG_RCC_IOPRSTR_IOPBRST	(UINT32_C(1) << 1)	//< Port B reset
#define MCCI_STM32L0_REG_RCC_IOPRSTR_IOPARST	(UINT32_C(1) << 0)	//< Port A reset
///	@}

/// \name RCC_AHBRSTR bits
///	@{
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RSV25	(UINT32_C(0x7F) << 25)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBRSTR_CRYPRST	(UINT32_C(1) << 24)	//< Crypto reset
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RSV21	(UINT32_C(7) << 21)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RNGRST	(UINT32_C(1) << 20)	//< Random number generator reset
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RSV17	(UINT32_C(7) << 17)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBRSTR_TSCRST	(UINT32_C(1) << 16)	//< Touch sensor reset
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RSV13	(UINT32_C(7) << 13)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBRSTR_CRCRST	(UINT32_C(1) << 12)	//< CRC reset
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RSV9	(UINT32_C(7) << 9)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBRSTR_MIFRST	(UINT32_C(1) << 8)	//< Memory interface reset
#define MCCI_STM32L0_REG_RCC_AHBRSTR_RSV1	(UINT32_C(0x7F) << 1)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBRSTR_DMARST	(UINT32_C(1) << 0)	//< DMA reset
///	@}

/// \name RCC_APB2RSTR bits
///	@{
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV23	UINT32_C(0xFF800000)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_DBGRST	(UINT32_C(1) << 22)	///< Debug reset
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV15	(UINT32_C(0x7F) << 15)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_USART1RST	(UINT32_C(1) << 14)	///< USART1 reset
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV13	(UINT32_C(1) << 13)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_SPI1RST	(UINT32_C(1) << 12)	///< SPI1 reset
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV10	(UINT32_C(3) << 10)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_ADCRST	(UINT32_C(1) << 9)	///< ADC reset
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV6	(UINT32_C(7) << 6)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_TIM22RST	(UINT32_C(1) << 5)	///< TIM22 reset
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV3	(UINT32_C(3) << 3)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_TIM21RST	(UINT32_C(1) << 2)	///< TIM21 reset
#define MCCI_STM32L0_REG_RCC_APB2RSTR_RSV1	(UINT32_C(1) << 1)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2RSTR_SYSCFRST	(UINT32_C(1) << 0)	///< SYSCFG reset
///	@}

/// \name RCC_APB1RSTR bits
///	@{
#define MCCI_STM32L0_REG_RCC_APB1RSTR_LPTIM1RST		(UINT32_C(1) << 31)	//< LPTIM1 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_I2C3RST		(UINT32_C(1) << 30)	//< I2C3 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_DACRRST		(UINT32_C(1) << 29)	//< DACR reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_PWRRST		(UINT32_C(1) << 28)	//< PWR reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_CRSRST		(UINT32_C(1) << 27)	//< CRS reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_RSV24		(UINT32_C(7) << 24)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1RSTR_USBRST		(UINT32_C(1) << 23)	//< USB reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_I2C2RST		(UINT32_C(1) << 22)	//< I2C2 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_I2C1RST		(UINT32_C(1) << 21)	//< I2C1 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_USART5RST		(UINT32_C(1) << 20)	//< USART5 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_USART4RST		(UINT32_C(1) << 19)	//< USART4 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_LPUART1RST	(UINT32_C(1) << 18)	//< LPUART1 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_USART2RST		(UINT32_C(1) << 17)	//< USART2 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_RSV15		(UINT32_C(3) << 15)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1RSTR_SPI2RST		(UINT32_C(1) << 14)	//< SPI2 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_RSV12		(UINT32_C(3) << 12)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1RSTR_WWDGRST		(UINT32_C(1) << 11)	//< Watchdog reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_RSV6		(UINT32_C(0x1F) << 6)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1RSTR_TIM7RST		(UINT32_C(1) << 5)	//< TIM7 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_TIM6RST		(UINT32_C(1) << 4)	//< TIM6 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_RSV2		(UINT32_C(3) << 2)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1RSTR_TIM3		(UINT32_C(1) << 1)	//< TIM3 reset
#define MCCI_STM32L0_REG_RCC_APB1RSTR_TIM2		(UINT32_C(1) << 0)	//< TIM2 reset
///	@}

/// \name RCC_IOPENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_IOPENR_RSV8	UINT32_C(0xFFFFFF00)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_IOPENR_IOPHEN	(UINT32_C(1) << 7)	//< Port H enable
#define MCCI_STM32L0_REG_RCC_IOPENR_RSV5	(UINT32_C(3) << 5)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_IOPENR_IOPEEN	(UINT32_C(1) << 4)	//< Port E enable
#define MCCI_STM32L0_REG_RCC_IOPENR_IOPDEN	(UINT32_C(1) << 3)	//< Port D enable
#define MCCI_STM32L0_REG_RCC_IOPENR_IOPCEN	(UINT32_C(1) << 2)	//< Port C enable
#define MCCI_STM32L0_REG_RCC_IOPENR_IOPBEN	(UINT32_C(1) << 1)	//< Port B enable
#define MCCI_STM32L0_REG_RCC_IOPENR_IOPAEN	(UINT32_C(1) << 0)	//< Port A enable
///	@}

/// \name RCC_AHBENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_AHBENR_RSV25	(UINT32_C(0x7F) << 25)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBENR_CRYPEN	(UINT32_C(1) << 24)	//< Crypto enable
#define MCCI_STM32L0_REG_RCC_AHBENR_RSV21	(UINT32_C(7) << 21)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBENR_RNGEN	(UINT32_C(1) << 20)	//< Random number generator enable
#define MCCI_STM32L0_REG_RCC_AHBENR_RSV17	(UINT32_C(7) << 17)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBENR_TSCEN	(UINT32_C(1) << 16)	//< Touch sensor enable
#define MCCI_STM32L0_REG_RCC_AHBENR_RSV13	(UINT32_C(7) << 13)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBENR_CRCEN	(UINT32_C(1) << 12)	//< CRC enable
#define MCCI_STM32L0_REG_RCC_AHBENR_RSV9	(UINT32_C(7) << 9)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBENR_MIFEN	(UINT32_C(1) << 8)	//< Memory interface enable
#define MCCI_STM32L0_REG_RCC_AHBENR_RSV1	(UINT32_C(0x7F) << 1)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBENR_DMAEN	(UINT32_C(1) << 0)	//< DMA enable
///	@}

/// \name RCC_APB2ENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV23	UINT32_C(0xFF800000)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_DBGEN	(UINT32_C(1) << 22)	///< Debug enable
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV15	(UINT32_C(0x7F) << 15)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_USART1EN	(UINT32_C(1) << 14)	///< USART1 enable
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV13	(UINT32_C(1) << 13)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_SPI1EN	(UINT32_C(1) << 12)	///< SPI1 enable
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV10	(UINT32_C(3) << 10)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_ADCEN	(UINT32_C(1) << 9)	///< ADC enable
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV6	(UINT32_C(7) << 6)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_TIM22EN	(UINT32_C(1) << 5)	///< TIM22 enable
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV3	(UINT32_C(3) << 3)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_TIM21EN	(UINT32_C(1) << 2)	///< TIM21 enable
#define MCCI_STM32L0_REG_RCC_APB2ENR_RSV1	(UINT32_C(1) << 1)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2ENR_SYSCFEN	(UINT32_C(1) << 0)	///< SYSCFG enable
///	@}

/// \name RCC_APB1ENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_APB1ENR_LPTIM1EN		(UINT32_C(1) << 31)	//< LPTIM1 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_I2C3EN		(UINT32_C(1) << 30)	//< I2C3 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_DACREN		(UINT32_C(1) << 29)	//< DACR enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_PWREN		(UINT32_C(1) << 28)	//< PWR enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_CRSEN		(UINT32_C(1) << 27)	//< CRS enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_RSV24		(UINT32_C(7) << 24)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1ENR_USBEN		(UINT32_C(1) << 23)	//< USB enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_I2C2EN		(UINT32_C(1) << 22)	//< I2C2 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_I2C1EN		(UINT32_C(1) << 21)	//< I2C1 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_USART5EN		(UINT32_C(1) << 20)	//< USART5 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_USART4EN		(UINT32_C(1) << 19)	//< USART4 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_LPUART1EN		(UINT32_C(1) << 18)	//< LPUART1 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_USART2EN		(UINT32_C(1) << 17)	//< USART2 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_RSV15		(UINT32_C(3) << 15)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1ENR_SPI2EN		(UINT32_C(1) << 14)	//< SPI2 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_RSV12		(UINT32_C(3) << 12)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1ENR_WWDGEN		(UINT32_C(1) << 11)	//< Watchdog enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_RSV6		(UINT32_C(0x1F) << 6)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1ENR_TIM7EN		(UINT32_C(1) << 5)	//< TIM7 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_TIM6EN		(UINT32_C(1) << 4)	//< TIM6 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_RSV2		(UINT32_C(3) << 2)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1ENR_TIM3		(UINT32_C(1) << 1)	//< TIM3 enable
#define MCCI_STM32L0_REG_RCC_APB1ENR_TIM2		(UINT32_C(1) << 0)	//< TIM2 enable
///	@}

/// \name RCC_IOPSMEN bits
///	@{
#define MCCI_STM32L0_REG_RCC_IOPSMENR_RSV8	UINT32_C(0xFFFFFF00)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_IOPSMENR_IOPHSMEN	(UINT32_C(1) << 7)	//< Port H sleep-mode enable
#define MCCI_STM32L0_REG_RCC_IOPSMENR_RSV5	(UINT32_C(3) << 5)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_IOPSMENR_IOPESMEN	(UINT32_C(1) << 4)	//< Port E sleep-mode enable
#define MCCI_STM32L0_REG_RCC_IOPSMENR_IOPDSMEN	(UINT32_C(1) << 3)	//< Port D sleep-mode enable
#define MCCI_STM32L0_REG_RCC_IOPSMENR_IOPCSMEN	(UINT32_C(1) << 2)	//< Port C sleep-mode enable
#define MCCI_STM32L0_REG_RCC_IOPSMENR_IOPBSMEN	(UINT32_C(1) << 1)	//< Port B sleep-mode enable
#define MCCI_STM32L0_REG_RCC_IOPSMENR_IOPASMEN	(UINT32_C(1) << 0)	//< Port A sleep-mode enable
///	@}

/// \name RCC_AHBSMENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RSV25	(UINT32_C(0x7F) << 25)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBSMENR_CRYPSMEN	(UINT32_C(1) << 24)	//< Crypto sleep-mode enable
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RSV21	(UINT32_C(7) << 21)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RNGSMEN	(UINT32_C(1) << 20)	//< Random number generator sleep-mode enable
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RSV17	(UINT32_C(7) << 17)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBSMENR_TSCSMEN	(UINT32_C(1) << 16)	//< Touch sensor sleep-mode enable
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RSV13	(UINT32_C(7) << 13)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBSMENR_CRCSMEN	(UINT32_C(1) << 12)	//< CRC sleep-mode enable
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RSV10	(UINT32_C(3) << 10)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBSMENR_SRAMSMEN	(UINT32_C(1) << 9)	//< SRAM sleep-mode enable
#define MCCI_STM32L0_REG_RCC_AHBSMENR_MIFSMEN	(UINT32_C(1) << 8)	//< Memory interface sleep-mode enable
#define MCCI_STM32L0_REG_RCC_AHBSMENR_RSV1	(UINT32_C(0x7F) << 1)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_AHBSMENR_DMASMEN	(UINT32_C(1) << 0)	//< DMA sleep-mode enable
///	@}

/// \name RCC_APB2SMENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV23		UINT32_C(0xFF800000)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_DBGSMEN		(UINT32_C(1) << 22)	///< Debug sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV15		(UINT32_C(0x7F) << 15)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_USART1SMEN	(UINT32_C(1) << 14)	///< USART1 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV13		(UINT32_C(1) << 13)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_SPI1SMEN		(UINT32_C(1) << 12)	///< SPI1 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV10		(UINT32_C(3) << 10)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_ADCSMEN		(UINT32_C(1) << 9)	///< ADC sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV6		(UINT32_C(7) << 6)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_TIM22SMEN	(UINT32_C(1) << 5)	///< TIM22 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV3		(UINT32_C(3) << 3)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_TIM21SMEN	(UINT32_C(1) << 2)	///< TIM21 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB2SMENR_RSV1		(UINT32_C(1) << 1)	///< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB2SMENR_SYSCFSMEN	(UINT32_C(1) << 0)	///< SYSCFG sleep-mode enable
///	@}

/// \name RCC_APB1SMENR bits
///	@{
#define MCCI_STM32L0_REG_RCC_APB1SMENR_LPTIM1SMEN	(UINT32_C(1) << 31)	//< LPTIM1 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_I2C3SMEN		(UINT32_C(1) << 30)	//< I2C3 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_DACRSMEN		(UINT32_C(1) << 29)	//< DACR sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_PWRSMEN		(UINT32_C(1) << 28)	//< PWR sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_CRSSMEN		(UINT32_C(1) << 27)	//< CRS sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_RSV24		(UINT32_C(7) << 24)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1SMENR_USBSMEN		(UINT32_C(1) << 23)	//< USB sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_I2C2SMEN		(UINT32_C(1) << 22)	//< I2C2 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_I2C1SMEN		(UINT32_C(1) << 21)	//< I2C1 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_USART5SMEN	(UINT32_C(1) << 20)	//< USART5 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_USART4SMEN	(UINT32_C(1) << 19)	//< USART4 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_LPUART1SMEN	(UINT32_C(1) << 18)	//< LPUART1 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_USART2SMEN	(UINT32_C(1) << 17)	//< USART2 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_RSV15		(UINT32_C(3) << 15)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1SMENR_SPI2SMEN		(UINT32_C(1) << 14)	//< SPI2 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_RSV12		(UINT32_C(3) << 12)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1SMENR_WWDGSMEN		(UINT32_C(1) << 11)	//< Watchdog sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_RSV6		(UINT32_C(0x1F) << 6)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1SMENR_TIM7SMEN		(UINT32_C(1) << 5)	//< TIM7 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_TIM6SMEN		(UINT32_C(1) << 4)	//< TIM6 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_RSV2		(UINT32_C(3) << 2)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_APB1SMENR_TIM3		(UINT32_C(1) << 1)	//< TIM3 sleep-mode enable
#define MCCI_STM32L0_REG_RCC_APB1SMENR_TIM2		(UINT32_C(1) << 0)	//< TIM2 sleep-mode enable
///	@}

/// \name RCC_CCIPR bits
///	@{
#define MCCI_STM32L0_REG_RCC_CCIPR_RSV27	(UINT32_C(0x1F) << 27)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_CCIPR_HSI48SEL	(UINT32_C(1) << 26)	//< HSI48 from PLL USB (not RC48)
#define MCCI_STM32L0_REG_RCC_CCIPR_RSV20	(UINT32_C(0x3F) << 20)	//< reserved, don't change

#define MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL	(UINT32_C(3) << 18)	//< select LPTIM1 srt
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL_APB	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL, 0)	//< APB clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL_LSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL, 1)	//< LSI clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL, 2)	//< HSI16 clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL_LSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPTIM1SEL, 3)	//< LSE clock

#define MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL	(UINT32_C(3) << 16)	//< 
#define  MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL_APB		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL, 0)	//< APB clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL_LSI		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL, 1)	//< LSI clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_I2C3SEL, 2)	//< HSI16 clock

#define MCCI_STM32L0_REG_RCC_CCIPR_RSV14	(UINT32_C(3) << 14)	//< reserved, don't change
#define MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL	(UINT32_C(3) << 12)	//< 
#define  MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL_APB		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL, 0)	//< APB clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL_LSI		MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL, 1)	//< LSI clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_I2C1SEL, 2)	//< HSI16 clock

#define MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL	(UINT32_C(3) << 10)	//< 
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL_APB	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL, 0)	//< APB clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL_LSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL, 1)	//< LSI clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL, 2)	//< HSI16 clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL_LSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_LPUART1SEL, 3)	//< LSE clock

#define MCCI_STM32L0_REG_RCC_CCIPR_RSV4		(UINT32_C(0x3F) << 4)	//< reserved, don't change

#define MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL	(UINT32_C(3) << 2)	//< 
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL_APB	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL, 0)	//< APB clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL_LSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL, 1)	//< LSI clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL, 2)	//< HSI16 clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL_LSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART2SEL, 3)	//< LSE clock

#define MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL	(UINT32_C(3) << 0)	//< 
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL_APB	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL, 0)	//< APB clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL_LSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL, 1)	//< LSI clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL_HSI16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL, 2)	//< HSI16 clock
#define  MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL_LSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CCIPR_USART1SEL, 3)	//< LSE clock
///	@}

/// \name RCC_CSR bits
///	@{
#define  MCCI_STM32L0_REG_RCC_CSR_LPWRRSTF	(UINT32_C(1) << 31)	//< Reset due to low-power
#define  MCCI_STM32L0_REG_RCC_CSR_WWDGRSTF	(UINT32_C(1) << 30)	//< reset due to window watchdog
#define  MCCI_STM32L0_REG_RCC_CSR_IWDGRSTF	(UINT32_C(1) << 29)	//< reset due to independent watchdog
#define  MCCI_STM32L0_REG_RCC_CSR_SFTRSTF	(UINT32_C(1) << 28)	//< reset due to softwaare
#define  MCCI_STM32L0_REG_RCC_CSR_PORRSTF	(UINT32_C(1) << 27)	//< reset due to power: POR, PDR
#define  MCCI_STM32L0_REG_RCC_CSR_PINRSTF	(UINT32_C(1) << 26)	//< reset due to NRST pin
#define  MCCI_STM32L0_REG_RCC_CSR_OBLRSTF	(UINT32_C(1) << 25)	//< reset due to option byte loading
#define  MCCI_STM32L0_REG_RCC_CSR_FWRSTF	(UINT32_C(1) << 24)	//< reset due to firewall
#define  MCCI_STM32L0_REG_RCC_CSR_RMVF		(UINT32_C(1) << 23)	//< remove reset (clears flags)
#define  MCCI_STM32L0_REG_RCC_CSR_RSV20		(UINT32_C(7) << 20)	//< Reserved, don't change
#define  MCCI_STM32L0_REG_RCC_CSR_RTCRST	(UINT32_C(1) << 19)	//< reset RTC and backup
#define  MCCI_STM32L0_REG_RCC_CSR_RTCEN		(UINT32_C(1) << 18)	//< enable RTC

#define  MCCI_STM32L0_REG_RCC_CSR_RTCSEL	(UINT32_C(3) << 16)	//< RTC clock source select
#define   MCCI_STM32L0_REG_RCC_CSR_RTCSEL_NONE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_RTCSEL, 0)	//< no RTC clock
#define   MCCI_STM32L0_REG_RCC_CSR_RTCSEL_LSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_RTCSEL, 0)	//< LSE clock as RTC clock
#define   MCCI_STM32L0_REG_RCC_CSR_RTCSEL_LSI	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_RTCSEL, 0)	//< LSI clock as RTC clock
#define   MCCI_STM32L0_REG_RCC_CSR_RTCSEL_HSE	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_RTCSEL, 0)	//< HSE clock divided as RTC clock

#define  MCCI_STM32L0_REG_RCC_CSR_RSV15		(UINT32_C(1) << 15)	//< Reserved, don't change
#define  MCCI_STM32L0_REG_RCC_CSR_CSSLSED	(UINT32_C(1) << 14)	//< CSS on LSE failure
#define  MCCI_STM32L0_REG_RCC_CSR_CSSLSEON	(UINT32_C(1) << 13)	//< CSS on LSE enable

#define  MCCI_STM32L0_REG_RCC_CSR_LSEDRV	(UINT32_C(3) << 11)	//< LSE drive
#define   MCCI_STM32L0_REG_RCC_CSR_LSEDRV_LOW	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_LSEDRV, 0)	//< LSE drive: lowest
#define   MCCI_STM32L0_REG_RCC_CSR_LSEDRV_M1	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_LSEDRV, 1)	//< LSE drive: medium low
#define   MCCI_STM32L0_REG_RCC_CSR_LSEDRV_M2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_LSEDRV, 2)	//< LSE drive: medium high
#define   MCCI_STM32L0_REG_RCC_CSR_LSEDRV_HIGH	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_REG_RCC_CSR_LSEDRV, 3)	//< LSE drive: highest

#define  MCCI_STM32L0_REG_RCC_CSR_LSEBYP	(UINT32_C(1) << 10)	//< external LSE bypass
#define  MCCI_STM32L0_REG_RCC_CSR_LSERDY	(UINT32_C(1) << 9)	//< LSE ready
#define  MCCI_STM32L0_REG_RCC_CSR_LSEON		(UINT32_C(1) << 8)	//< LSE enable
#define  MCCI_STM32L0_REG_RCC_CSR_RSV2		(UINT32_C(0x3F) << 2)	//< Reserved, don't change
#define  MCCI_STM32L0_REG_RCC_CSR_LSIRDY	(UINT32_C(1) << 1)	//< LSI ready
#define  MCCI_STM32L0_REG_RCC_CSR_LSION		(UINT32_C(1) << 0)	//< LSI enable
///	@}

/****************************************************************************\
|
|	GPIO Control Registers
|
\****************************************************************************/

/// \name GPIO register offsets
///	@{
#define MCCI_STM32L0_GPIO_MODER		UINT32_C(0x00)	//< port mode register
#define MCCI_STM32L0_GPIO_OTYPER	UINT32_C(0x04)	//< port output type register
#define MCCI_STM32L0_GPIO_OSPEEDR	UINT32_C(0x08)	//< port output speed register
#define MCCI_STM32L0_GPIO_PUPDR		UINT32_C(0x0C)	//< port pull-up/pull-down register
#define MCCI_STM32L0_GPIO_IDR		UINT32_C(0x10)	//< port input data register
#define MCCI_STM32L0_GPIO_ODR		UINT32_C(0x14)	//< port output data register
#define MCCI_STM32L0_GPIO_BSRR		UINT32_C(0x18)	//< port bit set/reset register
#define MCCI_STM32L0_GPIO_LCKR		UINT32_C(0x1C)	//< port configuration lock register
#define MCCI_STM32L0_GPIO_AFRL		UINT32_C(0x20)	//< port alternate function low register
#define MCCI_STM32L0_GPIO_AFRH		UINT32_C(0x24)	//< port alternate function high register
#define MCCI_STM32L0_GPIO_BRR		UINT32_C(0x28)	//< port bit reset register
///	@}

/// \name GPIO_MODER bits -- used to select pin mode, two bits per pin
///	@{
#define MCCI_STM32L0_GPIO_MODE_MASK	UINT32_C(3)	//< mode bit masks
#define MCCI_STM32L0_GPIO_MODE_IN	UINT32_C(0)	//< digital input
#define MCCI_STM32L0_GPIO_MODE_OUT	UINT32_C(1)	//< digital output
#define MCCI_STM32L0_GPIO_MODE_AF	UINT32_C(2)	//< alternate function
#define MCCI_STM32L0_GPIO_MODE_ANALOG	UINT32_C(3)	//< analog
///	@}

/// \brief compute the mask for the mode bits for port bits 0..15
///
/// Normally we compute a mask using an expression like:
///
///	`MCCI_BOOTLOADER_FIELD_SET_VALUE(
///		MCCI_STM32L0_GPIO_MODE_P(3),
///		MCCI_STM32L0_GPIO_MODE_IN
///		)`
///
#define	MCCI_STM32L0_GPIO_MODE_P(p)	(UINT32_C(3) << (2 * (p)))

/// \name GPIO_OTYPER bits
///	@{
#define	MCCI_STM32L0_GPIO_OTYPE_OD	UINT32_C(1)	//<
///	@}

/// \name GPIO_OSPEEDR bits -- used to select pin speed, two bits per pin
///	@{
#define MCCI_STM32L0_GPIO_OSPEED_MASK	UINT32_C(3)	//< speed bit masks
#define MCCI_STM32L0_GPIO_OSPEED_LOW	UINT32_C(0)	//< low
#define MCCI_STM32L0_GPIO_OSPEED_MEDIUM	UINT32_C(1)	//< medium
#define MCCI_STM32L0_GPIO_OSPEED_HIGH	UINT32_C(2)	//< high
#define MCCI_STM32L0_GPIO_OSPEED_VHIGH	UINT32_C(3)	//< very high

/// \brief compute the mask for the mode bits for port bits 0..15
///
/// Normally we compute a mask using an expression like:
///
///	`MCCI_BOOTLOADER_FIELD_SET_VALUE(
///		MCCI_STM32L0_GPIO_OSPEED_P(3),
///		MCCI_STM32L0_GPIO_OSPEED_IN
///		)`
///
#define	MCCI_STM32L0_GPIO_OSPEED_P(p)	(UINT32_C(3) << (2 * (p)))
///	@}

/// \name GPIO_BSRR bits
///	@{
#define MCCI_STM32L0_GPIO_BSRR_BR0	(UINT32_C(1) << 16)		//< reset port bit 0
#define MCCI_STM32L0_GPIO_BSRR_BR	(UINT32_C(0xFFFF) << 16)	//< mask of port-reset bits
#define MCCI_STM32L0_GPIO_BSRR_BS0	(UINT32_C(1) << 0)		//< set port bit 0
#define MCCI_STM32L0_GPIO_BSRR_BS	(UINT32_C(0xFFFF) << 0)		//< mask of port-set bits
/// \brief compute port-bit reset mask for bit \p p.
#define MCCI_STM32L0_GPIO_BSRR_BR_P(p)	(MCCI_STM32L0_GPIO_BR0 << (p))
/// \brief compute port-bit set mask for bit \p p.
#define MCCI_STM32L0_GPIO_BSRR_BS_P(p)	(MCCI_STM32L0_GPIO_BS0 << (p))
///	@}

/// \name GPIO_LCKR bits
///	@{
#define	MCCI_STM32L0_GPIO_LCKR_RSV17	UINT32_C(0xFFFE0000)	//< reserved, don't change
#define	MCCI_STM32L0_GPIO_LCKR_LCKK	(UINT32_C(1) << 16)	//< lock key bit; if set, ports are locked.
/// \brief compute GPIO lock bit fmask for bit \p p.
#define	MCCI_STM32L0_GPIO_LCKR_LCK_P(p)	(UINT32_C(1) << (p))
#define	MCCI_STM32L0_GPIO_LCKR_LCK	(UINT32_C(0xFFFF) << 0)	//< mask of port-lock bits.
///	@}

/// \name GPIO_AFRx bits
///	@{
/// \brief get reg offset for GPIO_AFRx
#define	MCCI_STM32L0_GPIO_AFRx_P(p)	(MCCI_STM32L0_GPIO_AFRL + ((p) / UINT32_C(8)))	//< f 

/// \brief get AFRx mask for port bit \p p.
///
/// Normal use:
///	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_GPIO_AFSEL_P(bitnum), 0..7)
///
#define	MCCI_STM32L0_GPIO_AFSEL_P(p)	(UINT32_C(0xF) << ((p) & 0x7u) 
///	@}

/****************************************************************************\
|
|	SPI Control Registers
|
\****************************************************************************/

/// \name SPI offsets
///	@{
#define	MCCI_STM32L0_SPI_CR1		UINT32_C(0x00)	///< offset to SPI control register 1
#define MCCI_STM32L0_SPI_CR2		UINT32_C(0x04)	///< offset to SPI control register 2
#define MCCI_STM32L0_SPI_SR		UINT32_C(0x08)	///< offset to SPI status register
#define MCCI_STM32L0_SPI_DR		UINT32_C(0x0C)	///< offset to SPI data register
#define MCCI_STM32L0_SPI_CRCPR		UINT32_C(0x10)	///< offset to SPI CRC polynomial
#define MCCI_STM32L0_SPI_RXCRCR		UINT32_C(0x14)	///< offset to SPI receive CRC
#define MCCI_STM32L0_SPI_TXCRCR		UINT32_C(0x18)	///< offset to SPI transmit CRC
#define MCCI_STM32L0_SPI_I2SCFGR	UINT32_C(0x1C)	///< offset to SPI I2S config register
#define MCCI_STM32L0_SPI_I2SPR		UINT32_C(0x20)	///< offset to SPI I2S prescaler
///	@}

/// \name SPI_CR1 bits
///	@{
#define MCCI_STM32L0_SPI_CR1_RSV16	UINT32_C(0xFFFF0000)	///< reserved
#define MCCI_STM32L0_SPI_CR1_BIDIMODE	(UINT32_C(1) << 15)	///< Bidirectional mode
#define MCCI_STM32L0_SPI_CR1_BIDIOE	(UINT32_C(1) << 14)	///< Bidirectional output enable
#define MCCI_STM32L0_SPI_CR1_CRCEN	(UINT32_C(1) << 13)	///< CRC enabled
#define MCCI_STM32L0_SPI_CR1_CRCNEXT	(UINT32_C(1) << 12)	///< CRC is next
#define MCCI_STM32L0_SPI_CR1_DFF	(UINT32_C(1) << 11)	///< Data frame format (16 bit / not 8 bit)
#define MCCI_STM32L0_SPI_CR1_RXONLY	(UINT32_C(1) << 10)	///< Receive-only mode
#define MCCI_STM32L0_SPI_CR1_SSM	(UINT32_C(1) << 9)	///< software slave management
#define MCCI_STM32L0_SPI_CR1_SSI	(UINT32_C(1) << 8)	///< internal slave select
#define MCCI_STM32L0_SPI_CR1_LSBFIRST	(UINT32_C(1) << 7)	///< LSB first (not MSB)
#define MCCI_STM32L0_SPI_CR1_SPE	(UINT32_C(1) << 6)	///< SPI enabled

#define MCCI_STM32L0_SPI_CR1_BR		(UINT32_C(7) << 3)	///< baud rate control (PCLK divisor)
# define MCCI_STM32L0_SPI_CR1_BR_2	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 0)	///< PCLK/2
# define MCCI_STM32L0_SPI_CR1_BR_4	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 1)	///< PCLK/4
# define MCCI_STM32L0_SPI_CR1_BR_8	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 2)	///< PCLK/8
# define MCCI_STM32L0_SPI_CR1_BR_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 3)	///< PCLK/16
# define MCCI_STM32L0_SPI_CR1_BR_32	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 4)	///< PCLK/32
# define MCCI_STM32L0_SPI_CR1_BR_64	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 5)	///< PCLK/64
# define MCCI_STM32L0_SPI_CR1_BR_128	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 6)	///< PCLK/128
# define MCCI_STM32L0_SPI_CR1_BR_256	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_CR1_BR, 7)	///< PCLK/256

#define MCCI_STM32L0_SPI_CR1_MSTR	(UINT32_C(1) << 2)	///< Master (not slave) 
#define MCCI_STM32L0_SPI_CR1_CPOL	(UINT32_C(1) << 1)	///< Clk to 1 when idle (not zero)
#define MCCI_STM32L0_SPI_CR1_CPHA	(UINT32_C(1) << 0)	///< Clock phase: second clock transaction captures (not first)
///	@}

/// \name SPI_CR2 bits
///	@{
#define MCCI_STM32L0_SPI_CR2_RSV8	UINT32_C(0xFFFFFF00)	///< reserved
#define MCCI_STM32L0_SPI_CR2_TXEIE	(UINT32_C(1) << 7)	///< tx empty interrupt enable
#define MCCI_STM32L0_SPI_CR2_RXNEIE	(UINT32_C(1) << 6)	///< rx not empty interrupt enable
#define MCCI_STM32L0_SPI_CR2_ERRIE	(UINT32_C(1) << 5)	///< error interrupt enable
#define MCCI_STM32L0_SPI_CR2_FRF	(UINT32_C(1) << 4)	///< frame format TI (not Motorola)
#define MCCI_STM32L0_SPI_CR2_RSV3	(UINT32_C(1) << 3)	///< reserved, zero
#define MCCI_STM32L0_SPI_CR2_SSOE	(UINT32_C(1) << 2)	///< enable SS in master mode
#define MCCI_STM32L0_SPI_CR2_TXDMAEN	(UINT32_C(1) << 1)	///< tx DMA enable
#define MCCI_STM32L0_SPI_CR2_RXDMAEN	(UINT32_C(1) << 0)	///< rx DMA enable
///	@}

/// \name SPI_SR bits
///	@{
#define MCCI_STM32L0_SPI_SR_RSV9	UINT32_C(0xFFFFFE00)	///< reserved, zero
#define MCCI_STM32L0_SPI_SR_FRE		(UINT32_C(1) << 8)	///< frame error (read to clear)
#define MCCI_STM32L0_SPI_SR_BSY		(UINT32_C(1) << 7)	///< busy
#define MCCI_STM32L0_SPI_SR_OVR		(UINT32_C(1) << 6)	///< overrun
#define MCCI_STM32L0_SPI_SR_MODF	(UINT32_C(1) << 5)	///< mode fault
#define MCCI_STM32L0_SPI_SR_CRCERR	(UINT32_C(1) << 4)	///< CRC error (write zero to clear)
#define MCCI_STM32L0_SPI_SR_UDR		(UINT32_C(1) << 3)	///< underrun
#define MCCI_STM32L0_SPI_SR_CHSIDE	(UINT32_C(1) << 2)	///< channel right (not left)
#define MCCI_STM32L0_SPI_SR_TXE		(UINT32_C(1) << 1)	///< TX buffer empty
#define MCCI_STM32L0_SPI_SR_RXE		(UINT32_C(1) << 0)	///< RX buffer not-empty
///	@}

/// \name SPI_I2SCFGR bits
///	@{
#define MCCI_STM32L0_SPI_I2SCFGR_RSV13		UINT32_C(0xFFFFE000)	///< reserved (do not change)
#define MCCI_STM32L0_SPI_I2SCFGR_I2SMOD		(UINT32_C(1) << 11)	///< I2S mode (not SPI)
#define MCCI_STM32L0_SPI_I2SCFGR_I2SE		(UINT32_C(1) << 10)	///< I2S enable
#define MCCI_STM32L0_SPI_I2SCFGR_I2SCFG		(UINT32_C(3) << 8)	///< I2S configuration mode
#define MCCI_STM32L0_SPI_I2SCFGR_I2SCFG_STX	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SCFG, 0)	///< I2S slave transmit
#define MCCI_STM32L0_SPI_I2SCFGR_I2SCFG_SRX	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SCFG, 1)	///< I2S slave receive
#define MCCI_STM32L0_SPI_I2SCFGR_I2SCFG_MTX	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SCFG, 2)	///< I2S master transmit
#define MCCI_STM32L0_SPI_I2SCFGR_I2SCFG_MRX	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SCFG, 3)	///< I2S master receive
#define MCCI_STM32L0_SPI_I2SCFGR_PCMSYNC	(UINT32_C(1) << 7)	///< Long (not short) PCM frame synchronization
#define MCCI_STM32L0_SPI_I2SCFGR_RSV6		(UINT32_C(1) << 6)	///< reserved, zero
#define MCCI_STM32L0_SPI_I2SCFGR_I2SSTD		(UINT32_C(3) << 4)	///< I2S standard selection
#define MCCI_STM32L0_SPI_I2SCFGR_I2SSTD_PHILIPS	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SSTD, 0)	///< Philips standard.
#define MCCI_STM32L0_SPI_I2SCFGR_I2SSTD_LEFT	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SSTD, 1)	///< MSB justified
#define MCCI_STM32L0_SPI_I2SCFGR_I2SSTD_RIGHT	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SSTD, 2)	///< LSB justified
#define MCCI_STM32L0_SPI_I2SCFGR_I2SSTD_PCM	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_I2SSTD, 3)	///< PCM standard
#define MCCI_STM32L0_SPI_I2SCFGR_CKPOL		(UINT32_C(1) << 3)	///< steady state clock polarity high (not low)
#define MCCI_STM32L0_SPI_I2SCFGR_DATLEN		(UINT32_C(3) << 1)	///< data length
#define MCCI_STM32L0_SPI_I2SCFGR_DATLEN_16	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_DATLEN, 0)	///< 16-bit data
#define MCCI_STM32L0_SPI_I2SCFGR_DATLEN_24	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_DATLEN, 1)	///< 24-bit data
#define MCCI_STM32L0_SPI_I2SCFGR_DATLEN_32	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_DATLEN, 2)	///< 32-bit data
#define MCCI_STM32L0_SPI_I2SCFGR_DATLEN_XX	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32L0_SPI_I2SCFGR_DATLEN, 3)	///< invalid data length
#define MCCI_STM32L0_SPI_I2SCFGR_CHLEN		(UINT32_C(1) << 0)	///< channel 32-bits wide (not 16)
///	@}


#ifdef __cplusplus
}
#endif

#endif /* _mcci_stm32l0xx_h_ */
