/*

Module:	mcci_stm32h7xx.h

Function:
	Register definitions for STM32H7xx CPUs

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_stm32h7xx_h_
#define _mcci_stm32h7xx_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_bits_h_
# include "mcci_bootloader_bits.h"
#endif

#ifndef _mcci_arm_cm7_h_
# include "mcci_arm_cm7.h"
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

/// \name STM32H7xx top-level address breakdown
///	@{
#define	MCCI_STM32H7_MEMORY_FLASH	UINT32_C(0x08000000)	///< Flash program memory (up to 2M)
#define	MCCI_STM32H7_MEMORY_FLASH1	UINT32_C(0x08000000)	///< Flash program memory (up to 1M)
#define	MCCI_STM32H7_MEMORY_FLASH2	UINT32_C(0x08100000)	///< Flash program memory (up to 1M)
#define	MCCI_STM32H7_MEMORY_FLASH_END	UINT32_C(0x081FFFFF)	///< End of Flash program memory
#define	MCCI_STM32H7_MEMORY_SYSTEM	UINT32_C(0x1FF00000)	///< System memory (128K)
#define	MCCI_STM32H7_MEMORY_SYSTEM_END	UINT32_C(0x1FF1FFFF)	///< End of System memory
#define	MCCI_STM32H7_MEMORY_OTP		UINT32_C(0x08FFF000)	///< OTP Area (1K)
#define	MCCI_STM32H7_MEMORY_OTP_END	UINT32_C(0x08FFF3FF)	///< End of OTP Area
#define	MCCI_STM32H7_MEMORY_READ_ONLY	UINT32_C(0x08FFF800)	///< read-only area (512)
#define MCCI_STM32H7_MEMORY_ITCM_RAM	UINT32_C(0x00000000)	///< ITCM RAM (64K)
#define MCCI_STM32H7_MEMORY_DTCM_RAM	UINT32_C(0x20000000)	///< DTCM RAM (128K)
#define	MCCI_STM32H7_MEMORY_AXI_SRAM1	UINT32_C(0x24000000)	///< AXU SRAM1 (up to 256K)
#define	MCCI_STM32H7_MEMORY_AXI_SRAM2	UINT32_C(0x24040000)	///< AXU SRAM2 (up to 384K)
#define	MCCI_STM32H7_MEMORY_AXI_SRAM3	UINT32_C(0x240A0000)	///< AXU SRAM3 (up to 384K)
#define MCCI_STM32H7_MEMORY_AHB_SRAM1	UINT32_C(0x30000000)	///< AHB SRAM1 (up to 64K)
#define MCCI_STM32H7_MEMORY_AHB_SRAM2	UINT32_C(0x30010000)	///< AHB SRAM2 (up to 64K)
#define MCCI_STM32H7_MEMORY_SRD_SRAM	UINT32_C(0x38000000)	///< SRD SRAM (up to 32K)
#define MCCI_STM32H7_MEMORY_SRD_BKPSRAM	UINT32_C(0x38800000)	///< SRD Backup SRAM (up to 4K)
#define	MCCI_STM32H7_REG_TIMER2		UINT32_C(0x40000000)	///< Section 43.4: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER3		UINT32_C(0x40000400)	///< Section 43.4: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER4		UINT32_C(0x40000800)	///< Section 43.4: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER5		UINT32_C(0x40000C00)	///< Section 43.4: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER6		UINT32_C(0x40001000)	///< Section 46.4: TIM6/7 register map (1K)
#define	MCCI_STM32H7_REG_TIMER7		UINT32_C(0x40001400)	///< Section 46.4: TIM6/7 register map (1K)
#define	MCCI_STM32H7_REG_TIMER12	UINT32_C(0x40001800)	///< Section 43.4: TIM6/7 register map (1K)
#define	MCCI_STM32H7_REG_TIMER13	UINT32_C(0x40001C00)	///< Section 43.4: TIM6/7 register map (1K)
#define	MCCI_STM32H7_REG_TIMER14	UINT32_C(0x40002000)	///< Section 43.4: TIM6/7 register map (1K)
#define	MCCI_STM32H7_REG_LPTIM1		UINT32_C(0x40002400)	///< Section 47.7: LPTIM register map (1K)
#define	MCCI_STM32H7_REG_SPI2		UINT32_C(0x40003800)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_SPI3		UINT32_C(0x40003C00)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_SPDIFRX1	UINT32_C(0x40004000)	///< Section 57.5: SPDIFRX interface register map (1K)
#define	MCCI_STM32H7_REG_USART2		UINT32_C(0x40004400)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_USART3		UINT32_C(0x40004800)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_UART4		UINT32_C(0x40004C00)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_UART5		UINT32_C(0x40005000)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_I2C1		UINT32_C(0x40005400)	///< Section 52.7: I2C register map (1K)
#define	MCCI_STM32H7_REG_I2C2		UINT32_C(0x40005800)	///< Section 52.7: I2C register map (1K)
#define	MCCI_STM32H7_REG_I2C3		UINT32_C(0x40005C00)	///< Section 52.7: I2C register map (1K)
#define	MCCI_STM32H7_REG_HDMI_CEC	UINT32_C(0x40006C00)	///< Section 63.7: HDMI-CEC register map (1K)
#define	MCCI_STM32H7_REG_DAC1		UINT32_C(0x40007400)	///< Section 29.7: DAC register map (1K)
#define	MCCI_STM32H7_REG_UART7		UINT32_C(0x40007800)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_UART8		UINT32_C(0x40007C00)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_CRS		UINT32_C(0x40008400)	///< Section 9.8: CRS register map (1K)
#define	MCCI_STM32H7_REG_SWPMI		UINT32_C(0x40008800)	///< Section 58.6: SWPMI register map (1K)
#define	MCCI_STM32H7_REG_OPAMP		UINT32_C(0x40009000)	///< Section 32.6: OPAMP register map (1K)
#define	MCCI_STM32H7_REG_MDIOS		UINT32_C(0x40009400)	///< Section 59.4: MDIOS register map (1K)
#define	MCCI_STM32H7_REG_TT_FDCAN	UINT32_C(0x4000A000)	///< Section 61.5: FDCAN register map (1K)
#define	MCCI_STM32H7_REG_FDCAN		UINT32_C(0x4000A400)	///< Section 61.5: FDCAN register map (1K)
#define	MCCI_STM32H7_REG_CAN_CCU	UINT32_C(0x4000A800)	///< Section 61.5: FDCAN register map (1K)
#define	MCCI_STM32H7_REG_CAN_MSG_RAM	UINT32_C(0x4000AC00)	///< Section 61.5: FDCAN register map (1K)
#define	MCCI_STM32H7_REG_TIMER1		UINT32_C(0x40010000)	///< Section 42.4: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER8		UINT32_C(0x40010400)	///< Section 42.4: TIMx register map (1K)
#define	MCCI_STM32H7_REG_USART1		UINT32_C(0x40011000)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_USART6		UINT32_C(0x40011400)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_UART9		UINT32_C(0x40011800)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_USART10	UINT32_C(0x40011C00)	///< Section 53.7: USART register map (1K)
#define	MCCI_STM32H7_REG_SPI1		UINT32_C(0x40013000)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_I2S1		UINT32_C(0x40013000)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_SPI4		UINT32_C(0x40013400)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_TIMER15	UINT32_C(0x40014000)	///< Section 45.5: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER16	UINT32_C(0x40014400)	///< Section 45.5: TIMx register map (1K)
#define	MCCI_STM32H7_REG_TIMER17	UINT32_C(0x40014800)	///< Section 45.5: TIMx register map (1K)
#define	MCCI_STM32H7_REG_SPI5		UINT32_C(0x40015000)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_SAI1		UINT32_C(0x40015800)	///< Section 56.6: SAI register map (1K)
#define	MCCI_STM32H7_REG_SAI2		UINT32_C(0x40015C00)	///< Section 56.6: SAI register map (1K)
#define	MCCI_STM32H7_REG_DFSDM1		UINT32_C(0x40017800)	///< Section 33.7: 33.8: DFSDM register map (1K)
#define	MCCI_STM32H7_REG_DMA1		UINT32_C(0x40020000)	///< Section 15.5: DMA register map (1K)
#define	MCCI_STM32H7_REG_DMA2		UINT32_C(0x40020400)	///< Section 15.5: DMA register map (1K)
#define	MCCI_STM32H7_REG_DMAMUX1	UINT32_C(0x40020800)	///< Section 17.6: DMAMUX register map (1K)
#define	MCCI_STM32H7_REG_ADC1		UINT32_C(0x40022000)	///< Section 27.7: ADC register map (1K)
#define	MCCI_STM32H7_REG_CRC		UINT32_C(0x40023000)	///< Section 22.4: CRC register map (1K)
#define	MCCI_STM32H7_REG_OTG_HS		UINT32_C(0x40040000)	///< Section 62.14: OTG_HS register map (1K)
#define	MCCI_STM32H7_REG_DCMI		UINT32_C(0x48020000)	///< Section 34.5: DCMI register map (1K)
#define	MCCI_STM32H7_REG_PSSI		UINT32_C(0x48020400)	///< Section 35.5: PSSI register map (1K)
#define	MCCI_STM32H7_REG_HSEM		UINT32_C(0x48020800)	///< Section 10.4: HSEM register map (1K)
#define	MCCI_STM32H7_REG_CRYPTO		UINT32_C(0x48021000)	///< Section 39.7: CRYPTO register map (1K)
#define	MCCI_STM32H7_REG_HASH		UINT32_C(0x48021400)	///< Section 40.7: HASH register map (1K)
#define	MCCI_STM32H7_REG_RNG		UINT32_C(0x48021800)	///< Section 38.7: RNG register map (1K)
#define	MCCI_STM32H7_REG_SDMMC2		UINT32_C(0x48022400)	///< Section 60.10: SDMMC register map (1K)
#define	MCCI_STM32H7_REG_DLYB_SDMMC2	UINT32_C(0x48022800)	///< Section 26.4: DLYB register map (1K)
#define	MCCI_STM32H7_REG_BDMA1		UINT32_C(0x48022C00)	///< Section 16.6: BDMA register map (1K)
#define	MCCI_STM32H7_REG_LTDC		UINT32_C(0x50001000)	///< Section 36.7: LTDC register map (4K)
#define	MCCI_STM32H7_REG_WWDG		UINT32_C(0x50003000)	///< Section 48.4: WWDG register map (4K)
#define	MCCI_STM32H7_REG_GPV		UINT32_C(0x51000000)	///< Section 2.2.4: AXI interconnect register map (1M)
#define	MCCI_STM32H7_REG_MDMA		UINT32_C(0x52000000)	///< Section 14.5: MDMA register map (4K)
#define	MCCI_STM32H7_REG_DMA2D		UINT32_C(0x52001000)	///< Section 18.5: DMA2D register map (4K)
#define	MCCI_STM32H7_REG_FLASH		UINT32_C(0x52002000)	///< Section 4.9: FLASH register map (4K)
#define	MCCI_STM32H7_REG_JPEG		UINT32_C(0x52003000)	///< Section 4.9: JPEG register map (4K)
#define	MCCI_STM32H7_REG_FMC		UINT32_C(0x52004000)	///< Section 23.7.6: 23.8.7: 23.9.5: FMC register map (4K)
#define	MCCI_STM32H7_REG_OCTOSPI1	UINT32_C(0x52005000)	///< Section 24.7: OCTOSPI register map (4K)
#define	MCCI_STM32H7_REG_DLYB_OCTOSPI1	UINT32_C(0x52006000)	///< Section 26.4: DLYB register map (4K)
#define	MCCI_STM32H7_REG_SDMMC1		UINT32_C(0x52007000)	///< Section 60.10: SDMMC register map (4K)
#define	MCCI_STM32H7_REG_DLYB_SDMMC1	UINT32_C(0x52008000)	///< Section 26.4: DLYB register map (1K)
#define	MCCI_STM32H7_REG_RAMECC		UINT32_C(0x52009000)	///< Section 3.4: RAMECC register map (1K)
#define	MCCI_STM32H7_REG_OCTOSPI2	UINT32_C(0x5200A000)	///< Section 24.7: OCTOSPI register map (4K)
#define	MCCI_STM32H7_REG_DLYB_OCTOSPI2	UINT32_C(0x5200B000)	///< Section 26.4: DLYB register map (1K)
#define	MCCI_STM32H7_REG_OTCOSPIM	UINT32_C(0x5200B400)	///< Section 25.4: OTCOSPIM register map (1K)
#define	MCCI_STM32H7_REG_OTFDEC1	UINT32_C(0x5200B800)	///< Section 41.6: OTFDEC register map (1K)
#define	MCCI_STM32H7_REG_OTFDEC2	UINT32_C(0x5200BC00)	///< Section 41.6: OTFDEC register map (1K)
#define	MCCI_STM32H7_REG_GFXMMU		UINT32_C(0x5200C000)	///< Section 21.5: GFXMMU register map (8K)
#define	MCCI_STM32H7_REG_EXTI		UINT32_C(0x58000000)	///< Section 20.6: EXTI register map (1K)
#define	MCCI_STM32H7_REG_SYSCFG		UINT32_C(0x58000400)	///< Section 12.4: SYSCFG register map (1K)
#define	MCCI_STM32H7_REG_LPUART1	UINT32_C(0x58000C00)	///< Section 54.6: LPUART register map (1K)
#define	MCCI_STM32H7_REG_SPI6		UINT32_C(0x58001400)	///< Section 55.11: SPI register map (1K)
#define	MCCI_STM32H7_REG_I2S6		UINT32_C(0x58001400)	///< Section 55.11: I2S register map (1K)
#define	MCCI_STM32H7_REG_I2C4		UINT32_C(0x58001C00)	///< Section 52.7: I2C register map (1K)
#define	MCCI_STM32H7_REG_LPTIM2		UINT32_C(0x58002400)	///< Section 47.7: LPTIM register map (1K)
#define	MCCI_STM32H7_REG_LPTIM3		UINT32_C(0x58002800)	///< Section 47.7: LPTIM register map (1K)
#define	MCCI_STM32H7_REG_DAC2		UINT32_C(0x58003400)	///< Section 29.7: DAC register map (1K)
#define	MCCI_STM32H7_REG_COMP		UINT32_C(0x58003800)	///< Section 31.6: COMP register map (1K)
#define	MCCI_STM32H7_REG_VREF		UINT32_C(0x58003C00)	///< Section 30.3: VREF register map (1K)
#define	MCCI_STM32H7_REG_RTC		UINT32_C(0x58004000)	///< Section 50.6: RTC register map (1K)
#define	MCCI_STM32H7_REG_TAMP		UINT32_C(0x58004400)	///< Section 51.6: TAMP register map (1K)
#define	MCCI_STM32H7_REG_IWDG		UINT32_C(0x58004800)	///< Section 49.4: IWDG register map (1K)
#define	MCCI_STM32H7_REG_DTS		UINT32_C(0x58006800)	///< Section 28.6: DTS register map (1K)
#define	MCCI_STM32H7_REG_DFSDM2		UINT32_C(0x58006C00)	///< Section 33.7: DFSDM register map (1K)
#define	MCCI_STM32H7_REG_GPIOA		UINT32_C(0x58020000)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOB		UINT32_C(0x58020400)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOC		UINT32_C(0x58020800)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOD		UINT32_C(0x58020C00)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOE		UINT32_C(0x58021000)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOF		UINT32_C(0x58021400)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOG		UINT32_C(0x58021800)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOH		UINT32_C(0x58021C00)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOI		UINT32_C(0x58022000)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOJ		UINT32_C(0x58022400)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_GPIOK		UINT32_C(0x58022800)	///< Section 11.4: GPIO register map (1K)
#define	MCCI_STM32H7_REG_RCC		UINT32_C(0x58024400)	///< Section 8.7: RCC register map (1K)
#define	MCCI_STM32H7_REG_PWR		UINT32_C(0x58024800)	///< Section 6.8: PWR register map (1K)
#define	MCCI_STM32H7_REG_BDMA2		UINT32_C(0x58025400)	///< Section 16.6: BDMA register map (1K)
#define	MCCI_STM32H7_REG_DMAMUX2	UINT32_C(0x58025800)	///< Section 17.6: DMAMUX register map (1K)
///	@}

/****************************************************************************\
|
|	Option bytes, etc
|
\****************************************************************************/

/// \name System values in system option memory
///	@{
#define	MCCI_STM32H7_OPTIONS_U_ID_0	UINT32_C(0x08FFF800)			///< register address: unique ID bits 31:0
#define	MCCI_STM32H7_OPTIONS_U_ID_4	(MCCI_STM32H7_OPTIONS_U_ID_0 + 0x04)	///< register address: unique ID bits 63:32
#define	MCCI_STM32H7_OPTIONS_U_ID_8	(MCCI_STM32H7_OPTIONS_U_ID_0 + 0x08)	///< register address: unique ID bits 95:64

#define	MCCI_STM32H7_OPTIONS_SYSTEM_FLASH_SIZE	UINT32_C(0x08FFF80C)	///< memory size in k bytes (16 bits)

/// \brief convert flash_size_16 value to bytes
#define	MCCI_STM32H7_OPTIONS_SYSTEM_FLASH_SIZE_TO_BYTES(h)	\
	((h) & UINT32_C(0xFFFF)) == UINT32_C(0xFFFF)		\
		? UINT32_C(0x200000)				\
		: ((h) & UINT32_C(0xFFFF)) == UINT32_C(0)	\
			? UINT32_C(0x200000)			\
			: (((h) & UINT32_C(0xFFFF)) * 1024)

#define	MCCI_STM32H7_OPTIONS_PACKAGE_DATA	UINT32_C(0x08FFF80E)	///< package data (16 bits)
///	@}

/****************************************************************************\
|
|	Flash Control Registers (3.7)
|
\****************************************************************************/

/// \name FLASH registers
///	@{
#define MCCI_STM32H7_REG_FLASH_ACR		(MCCI_STM32H7_REG_FLASH + 0x000) ///< Flash access control register
#define MCCI_STM32H7_REG_FLASH_KEYR1		(MCCI_STM32H7_REG_FLASH + 0x004) ///< Flash key register for bank 1
#define MCCI_STM32H7_REG_FLASH_OPTKEYR		(MCCI_STM32H7_REG_FLASH + 0x008) ///< Flash option key register
#define MCCI_STM32H7_REG_FLASH_CR1		(MCCI_STM32H7_REG_FLASH + 0x00C) ///< Flash control register for bank 1
#define MCCI_STM32H7_REG_FLASH_SR1		(MCCI_STM32H7_REG_FLASH + 0x010) ///< Flash status register for bank 1
#define MCCI_STM32H7_REG_FLASH_CCR1		(MCCI_STM32H7_REG_FLASH + 0x014) ///< Flash clear control register for bank 1
#define MCCI_STM32H7_REG_FLASH_OPTCR		(MCCI_STM32H7_REG_FLASH + 0x018) ///< Flash option control register
#define MCCI_STM32H7_REG_FLASH_OPTSR_CUR	(MCCI_STM32H7_REG_FLASH + 0x01C) ///< Flash option status register
#define MCCI_STM32H7_REG_FLASH_OPTSR_PRG	(MCCI_STM32H7_REG_FLASH + 0x020) ///< Flash option status register
#define MCCI_STM32H7_REG_FLASH_OPTCCR		(MCCI_STM32H7_REG_FLASH + 0x024) ///< Flash option clear control register
#define MCCI_STM32H7_REG_FLASH_PRAR_CUR1	(MCCI_STM32H7_REG_FLASH + 0x028) ///< Flash protection address for bank 1
#define MCCI_STM32H7_REG_FLASH_PRAR_PRG1	(MCCI_STM32H7_REG_FLASH + 0x02C) ///< Flash protection address for bank 1
#define MCCI_STM32H7_REG_FLASH_SCAR_CUR1	(MCCI_STM32H7_REG_FLASH + 0x030) ///< Flash secure address for bank 1
#define MCCI_STM32H7_REG_FLASH_SCAR_PRG1	(MCCI_STM32H7_REG_FLASH + 0x034) ///< Flash secure address for bank 1
#define MCCI_STM32H7_REG_FLASH_WPSGN_CUR1	(MCCI_STM32H7_REG_FLASH + 0x038) ///< Flash write sector group protection for bank 1
#define MCCI_STM32H7_REG_FLASH_WPSGN_PRG1	(MCCI_STM32H7_REG_FLASH + 0x03C) ///< Flash write sector group protection for bank 1
#define MCCI_STM32H7_REG_FLASH_BOOT_CUR		(MCCI_STM32H7_REG_FLASH + 0x040) ///< Flash boot address
#define MCCI_STM32H7_REG_FLASH_BOOT_PRG		(MCCI_STM32H7_REG_FLASH + 0x044) ///< Flash boot address
#define MCCI_STM32H7_REG_FLASH_CRCCR1		(MCCI_STM32H7_REG_FLASH + 0x050) ///< Flash CRC control register for bank 1
#define MCCI_STM32H7_REG_FLASH_CRCSADD1		(MCCI_STM32H7_REG_FLASH + 0x054) ///< Flash CRC start address register for bank 1
#define MCCI_STM32H7_REG_FLASH_CRCEADD1		(MCCI_STM32H7_REG_FLASH + 0x058) ///< Flash CRC end address register for bank 1
#define MCCI_STM32H7_REG_FLASH_CRCDATA		(MCCI_STM32H7_REG_FLASH + 0x05C) ///< Flash CRC data register
#define MCCI_STM32H7_REG_FLASH_ECC_FA1		(MCCI_STM32H7_REG_FLASH + 0x060) ///< Flash ECC fail address for bank 1
#define MCCI_STM32H7_REG_FLASH_OTPBL_CUR	(MCCI_STM32H7_REG_FLASH + 0x068) ///< Flash OTP block lock
#define MCCI_STM32H7_REG_FLASH_OTPBL_PRG	(MCCI_STM32H7_REG_FLASH + 0x06C) ///< Flash OTP block lock
#define MCCI_STM32H7_REG_FLASH_KEYR2		(MCCI_STM32H7_REG_FLASH + 0x104) ///< Flash key register for bank 2
#define MCCI_STM32H7_REG_FLASH_CR2		(MCCI_STM32H7_REG_FLASH + 0x10C) ///< Flash control register for bank 2
#define MCCI_STM32H7_REG_FLASH_SR2		(MCCI_STM32H7_REG_FLASH + 0x110) ///< Flash status register  for bank 2
#define MCCI_STM32H7_REG_FLASH_CCR2		(MCCI_STM32H7_REG_FLASH + 0x114) ///< Flash clear control register for bank 2
#define MCCI_STM32H7_REG_FLASH_PRAR_CUR2	(MCCI_STM32H7_REG_FLASH + 0x128) ///< Flash protection address for bank 2
#define MCCI_STM32H7_REG_FLASH_PRAR_PRG2	(MCCI_STM32H7_REG_FLASH + 0x12C) ///< Flash protection address for bank 2
#define MCCI_STM32H7_REG_FLASH_SCAR_CUR2	(MCCI_STM32H7_REG_FLASH + 0x130) ///< Flash secure address for bank 2
#define MCCI_STM32H7_REG_FLASH_SCAR_PRG2	(MCCI_STM32H7_REG_FLASH + 0x134) ///< Flash secure address for bank 2
#define MCCI_STM32H7_REG_FLASH_WPSGN_CUR2	(MCCI_STM32H7_REG_FLASH + 0x138) ///< Flash write sector group protection for bank 2
#define MCCI_STM32H7_REG_FLASH_WPSGN_PRG2	(MCCI_STM32H7_REG_FLASH + 0x13C) ///< Flash write sector group protection for bank 2
#define MCCI_STM32H7_REG_FLASH_CRCCR2		(MCCI_STM32H7_REG_FLASH + 0x150) ///< Flash CRC control register for bank 2
#define MCCI_STM32H7_REG_FLASH_CRCSADD2		(MCCI_STM32H7_REG_FLASH + 0x154) ///< Flash CRC start address register for bank 2
#define MCCI_STM32H7_REG_FLASH_CRCEADD2		(MCCI_STM32H7_REG_FLASH + 0x158) ///< Flash CRC end address register for bank 2
#define MCCI_STM32H7_REG_FLASH_ECC_FA2		(MCCI_STM32H7_REG_FLASH + 0x160) ///< Flash ECC fail address for bank 2
///	@}

/// \name FLASH_ACR bits
///	@{
#define MCCI_STM32H7_REG_FLASH_ACR_RSV6			UINT32_C(0xFFFFFFC0)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_ACR_WRHIGHFREQ		(UINT32_C(3) << 4)	///< Flash signal delay
#define MCCI_STM32H7_REG_FLASH_ACR_WRHIGHFREQ_V(n)	(UINT32_C(n) << 4)	///< Flash signal delay
#define MCCI_STM32H7_REG_FLASH_ACR_LATENCY		(UINT32_C(0xF) << 0)	///< Read latency:
#define MCCI_STM32H7_REG_FLASH_ACR_LATENCY_V(n)		(UINT32_C(n) << 0)	///< Read latency: n wait state
///	@}

/// \name FLASH_KEYR1, FLASH_KEYR2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_KEYR_UNLOCK1	UINT32_C(0x45670123)	///< unlock word 1 for FLASH_CR1
#define MCCI_STM32H7_REG_FLASH_KEYR_UNLOCK2	UINT32_C(0xCDEF89AB)	///< unlock word 2 for FLASH_CR1
///	@}

/// \name FLASH_OPTKEYR bits
///	@{
#define MCCI_STM32H7_REG_FLASH_OPTKEYR_UNLOCK1	UINT32_C(0x08192A3B)	///< unlock word 1 for option bytes
#define MCCI_STM32H7_REG_FLASH_OPTKEYR_UNLOCK2	UINT32_C(0x4C5D6E7F)	///< unlock word 2 for option bytes
///	@}

/// \name FLASH_CR1, FLASH_CR2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_CR_RSV29		(UINT32_C(7) << 29)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CR_CRCRDERRIE	(UINT32_C(1) << 28)	///< ECC CRC read error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_CRCENDIE	(UINT32_C(1) << 27)	///< CRC end of calculation interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_DBECCERRIE	(UINT32_C(1) << 26)	///< ECC double detection error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_SNECCERRIE	(UINT32_C(1) << 25)	///< ECC single correction error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_RDSERRIE	(UINT32_C(1) << 24)	///< secure error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_RDPERRIE	(UINT32_C(1) << 23)	///< read protection error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_RSV22		(UINT32_C(1) << 22)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CR_INCERRIE	(UINT32_C(1) << 21)	///< inconsistency error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_RSV20		(UINT32_C(1) << 20)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CR_STRBERRIE	(UINT32_C(1) << 19)	///< strobe error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_PGSERRIE	(UINT32_C(1) << 18)	///< programming sequence error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_WRPERRIE	(UINT32_C(1) << 17)	///< write protection error interrupt enable
#define MCCI_STM32H7_REG_FLASH_CR_EOPIE		(UINT32_C(1) << 16)	///< End-of-program interrupt control
#define MCCI_STM32H7_REG_FLASH_CR_CRC_EN	(UINT32_C(1) << 15)	///< CRC control
#define MCCI_STM32H7_REG_FLASH_CR_RSV13		(UINT32_C(3) << 13)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CR_SSN		(UINT32_C(0x7F) << 6)	///< Sector erase selection number
#define MCCI_STM32H7_REG_FLASH_CR_SSN_N(n)	((n) << 6)		///< Sector erase selection number
#define MCCI_STM32H7_REG_FLASH_CR_START		(UINT32_C(7) << 5)	///< Erase start control
#define MCCI_STM32H7_REG_FLASH_CR_FW		(UINT32_C(1) << 4)	///< Write forcing control
#define MCCI_STM32H7_REG_FLASH_CR_BER		(UINT32_C(1) << 3)	///< Bank erase request
#define MCCI_STM32H7_REG_FLASH_CR_SER		(UINT32_C(1) << 2)	///< Sector erase request
#define MCCI_STM32H7_REG_FLASH_CR_PG		(UINT32_C(1) << 1)	///< Internal buffer control
#define MCCI_STM32H7_REG_FLASH_CR_LOCK		(UINT32_C(1) << 0)	///< Lock the FLASH_CR register
///	@}

/// \name FLASH_SR1, FLASH_SR2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_SR_RSV29		(UINT32_C(7) << 29)	///< Reserved, don't change.
#define MCCI_STM32H7_REG_FLASH_SR_CRCRDERR	(UINT32_C(1) << 28)	///< ECC CRC read error flag
#define MCCI_STM32H7_REG_FLASH_SR_CRCEND	(UINT32_C(1) << 27)	///< CRC end of calculation flag
#define MCCI_STM32H7_REG_FLASH_SR_DBECCERR	(UINT32_C(1) << 26)	///< ECC double detection error flag
#define MCCI_STM32H7_REG_FLASH_SR_SNECCERR	(UINT32_C(1) << 25)	///< ECC single correction error flag
#define MCCI_STM32H7_REG_FLASH_SR_RDSERR	(UINT32_C(1) << 24)	///< secure error flag
#define MCCI_STM32H7_REG_FLASH_SR_RDPERR	(UINT32_C(1) << 23)	///< read protection error flag
#define MCCI_STM32H7_REG_FLASH_SR_RSV22		(UINT32_C(1) << 22)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_SR_INCERR	(UINT32_C(1) << 21)	///< inconsistency error flag
#define MCCI_STM32H7_REG_FLASH_SR_RSV20		(UINT32_C(1) << 20)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_SR_STRBERR	(UINT32_C(1) << 19)	///< strobe error flag
#define MCCI_STM32H7_REG_FLASH_SR_PGSERR	(UINT32_C(1) << 18)	///< programming sequence error flag
#define MCCI_STM32H7_REG_FLASH_SR_WRPERR	(UINT32_C(1) << 17)	///< write protection error flag
#define MCCI_STM32H7_REG_FLASH_SR_EOP		(UINT32_C(1) << 16)	///< End-of-program flag
#define MCCI_STM32H7_REG_FLASH_SR_RSV4		(UINT32_C(0xFFF) << 4)	///< Reserved, don't change.
#define MCCI_STM32H7_REG_FLASH_SR_CRC_BUSY	(UINT32_C(1) << 3)	///< CRC busy flag
#define MCCI_STM32H7_REG_FLASH_SR_QW		(UINT32_C(1) << 2)	///< wait queue flag
#define MCCI_STM32H7_REG_FLASH_SR_WBNE		(UINT32_C(1) << 1)	///< write buffer not empty flag
#define MCCI_STM32H7_REG_FLASH_SR_BSY		(UINT32_C(1) << 0)	///< Busy flag
///	@}

/// \name FLASH_CCR1, FLASH_CCR2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_CCR_RSV29	(UINT32_C(7) << 29)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CCR_CRCRDERR	(UINT32_C(1) << 28)	///< CRCRDERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_CRCEND	(UINT32_C(1) << 27)	///< CRCEND flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_DBECCERR	(UINT32_C(1) << 26)	///< DBECCERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_SNECCERR	(UINT32_C(1) << 25)	///< SNECCERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_RDSERR	(UINT32_C(1) << 24)	///< RDSERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_RDPERR	(UINT32_C(1) << 23)	///< RDPERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_RSV22	(UINT32_C(1) << 22)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CCR_INCERR	(UINT32_C(1) << 21)	///< INCERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_RSV20	(UINT32_C(1) << 20)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CCR_STRBERR	(UINT32_C(1) << 19)	///< STRBERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_PGSERR	(UINT32_C(1) << 18)	///< PGSERR flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_EOP		(UINT32_C(1) << 16)	///< EOP flag clear
#define MCCI_STM32H7_REG_FLASH_CCR_RSV0		(UINT32_C(0xFFFF) << 0)	///< Reserved, don't change
///	@}

/// \name FLASH_OPTCR bits
///	@{
#define MCCI_STM32H7_REG_FLASH_OPTCR_SWAP_BANK		(UINT32_C(1) << 31)	///< Bank swapping option configuration
#define MCCI_STM32H7_REG_FLASH_OPTCR_OPTCHANGEERRIE	(UINT32_C(1) << 30)	///< Option byte change error interrupt enable
#define MCCI_STM32H7_REG_FLASH_OPTCR_RSV29		(UINT32_C(1) << 29)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_OPTCR_PG_OTP		(UINT32_C(1) << 5)	///< OTP program control
#define MCCI_STM32H7_REG_FLASH_OPTCR_MER		(UINT32_C(1) << 4)	///< mass erase request
#define MCCI_STM32H7_REG_FLASH_OPTCR_RSV22		(UINT32_C(3) << 2)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_OPTCR_OPTSTART		(UINT32_C(1) << 1)	///< Option byte start change option configuration
#define MCCI_STM32H7_REG_FLASH_OPTCR_OPTLOCK		(UINT32_C(1) << 0)	///< FLASH_OPTCR lock option configuration
///	@}

/// \name FLASH_OPTSR_CUR, FLASH_OPTSR_PRG bits
///	@{
#define	MCCI_STM32H7_REG_FLASH_OPTSR_SWAP_BANK_OPT	(UINT32_C(1) << 31)	///< Bank swapping option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_OPTCHANGEERR	(UINT32_C(1) << 30)	///< Option byte change error flag
#define	MCCI_STM32H7_REG_FLASH_OPTSR_VDDIO_HSLV		(UINT32_C(1) << 29)	///< VDD I/O high-speed at low-voltage status
#define MCCI_STM32H7_REG_FLASH_OPTSR_RSV26		(UINT32_C(7) << 26)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_OPTSR_RSV22		(UINT32_C(0xF) << 22)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_OPTSR_SECURITY		(UINT32_C(1) << 21)	///< Security enable option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_ST_RAM_SIZE	(UINT32_C(3) << 19)	///< ST RAM size option
#define	MCCI_STM32H7_REG_FLASH_OPTSR_ST_RAM_SIZE_2KB	(UINT32_C(0) << 19)	///< 2KB reserved to ST code
#define	MCCI_STM32H7_REG_FLASH_OPTSR_ST_RAM_SIZE_4KB	(UINT32_C(1) << 19)	///< 2KB reserved to ST code
#define	MCCI_STM32H7_REG_FLASH_OPTSR_ST_RAM_SIZE_8KB	(UINT32_C(2) << 19)	///< 2KB reserved to ST code
#define	MCCI_STM32H7_REG_FLASH_OPTSR_ST_RAM_SIZE_16KB	(UINT32_C(3) << 19)	///< 2KB reserved to ST code
#define	MCCI_STM32H7_REG_FLASH_OPTSR_IWDG_FZ_SDBY	(UINT32_C(1) << 18)	///< IWDG Standby mode freeze option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_IWDG_FZ_STOP	(UINT32_C(1) << 17)	///< IWDG Stop mode freeze option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_VDDMMC_HSLV	(UINT32_C(1) << 16)	///< VDDMMC I/O high-speed at low-voltage status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_RDP		(UINT32_C(0xFF) << 8)	///< Readout protection level option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_RDP_LEVEL_0	(UINT32_C(0xAA) << 8)	///< global readout protection level 0
#define	MCCI_STM32H7_REG_FLASH_OPTSR_RDP_LEVEL_2	(UINT32_C(0xCC) << 8)	///< global readout protection level 2
#define	MCCI_STM32H7_REG_FLASH_OPTSR_RDP_LEVEL_1	(UINT32_C(0xBB) << 8)	///< others values: global readout protection level 1
#define	MCCI_STM32H7_REG_FLASH_OPTSR_NRST_STDY		(UINT32_C(1) << 7)	///< Core domain Standby entry reset option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_NRST_STOP		(UINT32_C(1) << 6)	///< Core domain DStop entry reset option status
#define MCCI_STM32H7_REG_FLASH_OPTSR_RSV5		(UINT32_C(1) << 5)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_OPTSR_IWDG_SW		(UINT32_C(1) << 4)	///< IWDG control mode option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_BOR_LEV		(UINT32_C(3) << 2)	///< Brownout level option status
#define	MCCI_STM32H7_REG_FLASH_OPTSR_BOR_LEV_OFF	(UINT32_C(0) << 2)	///< BOR OFF
#define	MCCI_STM32H7_REG_FLASH_OPTSR_BOR_LEV_1		(UINT32_C(1) << 2)	///< BOR Level 1, the threshold level is low (around 2.1 V)
#define	MCCI_STM32H7_REG_FLASH_OPTSR_BOR_LEV_2		(UINT32_C(2) << 2)	///< BOR Level 2, the threshold level is medium (around 2.4 V)
#define	MCCI_STM32H7_REG_FLASH_OPTSR_BOR_LEV_3		(UINT32_C(3) << 2)	///< BOR Level 3, the threshold level is high (around 2.7 V)
#define MCCI_STM32H7_REG_FLASH_OPTSR_RSV1		(UINT32_C(1) << 1)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_OPTSR_OPT_BUSY		(UINT32_C(1) << 0)	///< Option byte change ongoing flag
///	@}

/// \name FLASH_OPTCCR bits
///	@{
#define MCCI_STM32H7_REG_FLASH_OPTCCR_RSV31		(UINT32_C(1) << 31)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_OPTCCR_OPTCHANGEERR	(UINT32_C(1) << 30)	///< OPTCHANGEERR reset
#define MCCI_STM32H7_REG_FLASH_OPTCCR_RSV0		(0x3FFFFFFF)		///< Reserved, don't change
///	@}

/// \name FLASH_PRAR_CUR1, FLASH_PRAR_PRG1, FLASH_PRAR_CUR2, FLASH_PRAR_PRG2 bits
///	@{
#define	MCCI_STM32H7_REG_FLASH_PRAR_DMEP		(UINT32_C(1) << 31)	///< PCROP protected erase enable option status
#define MCCI_STM32H7_REG_FLASH_PRAR_RSV28		(UINT32_C(7) << 28)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_PRAR_PROT_AREA_END	(UINT32_C(0xFFF) << 16)	///< PCROP area end status
#define MCCI_STM32H7_REG_FLASH_PRAR_RSV12		(UINT32_C(15) << 12)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_PRAR_PROT_AREA_START	(UINT32_C(0xFFF) << 0)	///< PCROP area start status
///	@}

/// \name FLASH_SCAR_CUR1, FLASH_SCAR_PRG1, FLASH_SCAR_CUR2, FLASH_SCAR_PRG2 bits
///	@{
#define	MCCI_STM32H7_REG_FLASH_SCAR_DMES		(UINT32_C(1) << 31)	///< secure access protected erase enable option status
#define MCCI_STM32H7_REG_FLASH_SCAR_RSV28		(UINT32_C(7) << 28)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_SCAR_SEC_AREA_END	(UINT32_C(0xFFF) << 16)	///< secure-only area end status
#define MCCI_STM32H7_REG_FLASH_SCAR_RSV12		(UINT32_C(15) << 12)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_SCAR_SEC_AREA_START	(UINT32_C(0xFFF) << 0)	///< secure-only area start status
///	@}

/// \name FLASH_WPSGN_CUR1, FLASH_WPSGN_PRG1, FLASH_WPSGN_CUR2, FLASH_WPSGN_PRG2 bits
///	@{
#define	MCCI_STM32H7_REG_FLASH_WPSGN_SECT(n)		(UINT32_C(1) << (((n) & 127) >> 2))	///< Group embedding sectors
///	@}

/// \name FLASH_BOOT_CUR, FLASH_BOOT_PRG bits
///	@{
#define	MCCI_STM32H7_REG_FLASH_BOOT_ADD1	(UINT32_C(0xFFFF) << 16)	///< boot address 1
#define	MCCI_STM32H7_REG_FLASH_BOOT_ADD0	(UINT32_C(0xFFFF) << 0)		///< boot address 0
///	@}

/// \name FLASH_CRCCR1, FLASH_CRCCR2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_CRCCR_RSV23		(UINT32_C(0x1FF) << 23)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_CRCCR_ALL_BANK		(UINT32_C(1) << 22)	///< all CRC select
#define MCCI_STM32H7_REG_FLASH_CRCCR_CRC_BURST		(UINT32_C(3) << 20)	///< CRC burst size
#define MCCI_STM32H7_REG_FLASH_CRCCR_RSV18		(UINT32_C(3) << 18)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_CRCCR_CLEAN_CRC		(UINT32_C(1) << 17)	///< CRC clear bit
#define	MCCI_STM32H7_REG_FLASH_CRCCR_START_CRC		(UINT32_C(1) << 16)	///< CRC start bit
#define MCCI_STM32H7_REG_FLASH_CRCCR_RSV11		(UINT32_C(0x1F) << 11)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_CRCCR_CLEAN_SECT		(UINT32_C(1) << 10)	///< CRC sector list clear bit
#define	MCCI_STM32H7_REG_FLASH_CRCCR_ADD_SECT		(UINT32_C(1) << 9)	///< CRC sector select bit
#define	MCCI_STM32H7_REG_FLASH_CRCCR_CRC_BY_SECT	(UINT32_C(1) << 8)	///< CRC sector mode select bit
#define MCCI_STM32H7_REG_FLASH_CRCCR_RSV7		(UINT32_C(1) << 7)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_FLASH_CRCCR_CRC_SECT		(UINT32_C(0x7F) << 0)	///< CRC sector number
///	@}

/// \name FLASH_CRCSADD1, FLASH_CRCSADD2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_CRCSADD_RSV20		(UINT32_C(0xFFF) << 20)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CRCSADD_CRC_START_ADDR	(UINT32_C(0x3FFFF) << 2) ///< CRC start address on bank 1/2
#define MCCI_STM32H7_REG_FLASH_CRCSADD_RSV0		(UINT32_C(3) << 0)	///< Reserved, don't change
///	@}

/// \name FLASH_CRCEADD1, FLASH_CRCEADD2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_CRCEADD_RSV20		(UINT32_C(0xFFF) << 20)	///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_CRCEADD_CRC_START_ADDR	(UINT32_C(0x3FFFF) << 2) ///< CRC end address on bank 1/2
#define MCCI_STM32H7_REG_FLASH_CRCEADD_RSV0		(UINT32_C(3) << 0)	///< Reserved, don't change
///	@}

/// \name FLASH_ECC_FA1, FLASH_ECC_FA2 bits
///	@{
#define MCCI_STM32H7_REG_FLASH_ECC_FA_OTP_FAIL_ECC	(UINT32_C(1) << 31)	///< OTP ECC error bit
#define MCCI_STM32H7_REG_FLASH_ECC_FA_RSV16		(UINT32_C(0x7FFF) << 16) ///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_ECC_FA_FAIL_ECC_ADDR	(UINT32_C(0xFFFF) << 0) ///< ECC error address
///	@}

/// \name FLASH_OTPBL_CUR, FLASH_OTPBL_PRG bits
///	@{
#define MCCI_STM32H7_REG_FLASH_OTPBL_RSV16		(UINT32_C(0xFFFF) << 16) ///< Reserved, don't change
#define MCCI_STM32H7_REG_FLASH_OTPBL_LOCKBL		(UINT32_C(0xFFFF) << 0) ///< OTP Block Lock
///	@}

/// \name Flash programming constants
///	@{
#define MCCI_STM32H7_FLASH_SECTOR_SIZE		UINT32_C(8192)	///< size in bytes of a sector
#define MCCI_STM32H7_FLASH_PROGRAM_FLASH_SIZE	UINT32_C(16)	///< size in bytes of a FLASH program
#define MCCI_STM32H7_FLASH_PROGRAM_OTP_SIZE	UINT32_C(2)	///< size in bytes of a FLASH program

#define	MCCI_STM32H7_FLASH_IS_VALID(f)		((f) >= MCCI_STM32H7_MEMORY_FLASH && (f) <= MCCI_STM32H7_MEMORY_FLASH_END)
#define	MCCI_STM32H7_FLASH_IS_BANK2(f)		((f) & UINT32_C(0x100000))
#define	MCCI_STM32H7_FLASH_GET_BANK(f)		(((f) >> 20) & 1)
#define	MCCI_STM32H7_FLASH_GET_SECTOR(f)	(((f) >> 13) & 0x7F)
///	@}

/****************************************************************************\
|
|	Power Control Registers
|
\****************************************************************************/

/// \name PWR registers
///	@{
#define	MCCI_STM32H7_REG_PWR_CR1	(MCCI_STM32H7_REG_PWR + 0x00)	///< control
#define	MCCI_STM32H7_REG_PWR_CSR1	(MCCI_STM32H7_REG_PWR + 0x04)	///< control status
#define	MCCI_STM32H7_REG_PWR_CR2	(MCCI_STM32H7_REG_PWR + 0x08)	///< control 2
#define	MCCI_STM32H7_REG_PWR_CR3	(MCCI_STM32H7_REG_PWR + 0x0C)	///< control 3
#define	MCCI_STM32H7_REG_PWR_CPUCR	(MCCI_STM32H7_REG_PWR + 0x10)	///< CPU control
#define	MCCI_STM32H7_REG_PWR_SRDCR	(MCCI_STM32H7_REG_PWR + 0x18)	///< SmartRun domain control
#define	MCCI_STM32H7_REG_PWR_WKUPCR	(MCCI_STM32H7_REG_PWR + 0x20)	///< wakeup clear
#define	MCCI_STM32H7_REG_PWR_WKUPFR	(MCCI_STM32H7_REG_PWR + 0x24)	///< wakeup flag
#define	MCCI_STM32H7_REG_PWR_WKUPEPR	(MCCI_STM32H7_REG_PWR + 0x28)	///< wakeup enable and polarity
///	@}

/// \name PWR_CR1 bits
///	@{
#define	MCCI_STM32H7_REG_PWR_CR1_RSV28		(UINT32_C(15) << 28)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR1_SRDRAMSO	(UINT32_C(1) << 27)	///< SmartRun domain AHB memory shut-off in DStop/DStop2 low-power mode
#define	MCCI_STM32H7_REG_PWR_CR1_HSITFSO	(UINT32_C(1) << 26)	///< high-speed interfaces USB and FDCAN memory shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_GFXSO		(UINT32_C(1) << 25)	///< GFXMMU and JPEG memory shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_ITCMSO		(UINT32_C(1) << 24)	///< instruction TCM and ETM memory shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_AHBRAM2SO	(UINT32_C(1) << 23)	///< AHB SRAM2 shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_AHBRAM1SO	(UINT32_C(1) << 22)	///< AHB SRAM1 shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_AXIRAM3SO	(UINT32_C(1) << 21)	///< AXI SRAM3 shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_AXIRAM2SO	(UINT32_C(1) << 20)	///< AXI SRAM2 shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_AXIRAM1SO	(UINT32_C(1) << 19)	///< AXI SRAM1 shut-off in DStop/DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_ALS		(UINT32_C(3) << 17)	///< analog voltage detector level selection
#define	MCCI_STM32H7_REG_PWR_CR1_ALS_1_7V	(UINT32_C(0) << 17)	///< 1.7V
#define	MCCI_STM32H7_REG_PWR_CR1_ALS_2_1V	(UINT32_C(1) << 17)	///< 2.1V
#define	MCCI_STM32H7_REG_PWR_CR1_ALS_2_5V	(UINT32_C(2) << 17)	///< 2.5V
#define	MCCI_STM32H7_REG_PWR_CR1_ALS_2_8V	(UINT32_C(3) << 17)	///< 2.8V
#define	MCCI_STM32H7_REG_PWR_CR1_AVDEN		(UINT32_C(1) << 16)	///< peripheral voltage monitor on VDDA enable
#define	MCCI_STM32H7_REG_PWR_CR1_SVOS		(UINT32_C(3) << 14)	///< system stop mode voltage scaling selection
#define	MCCI_STM32H7_REG_PWR_CR1_SVOS_5		(UINT32_C(1) << 14)	///< SVOS5 scale 5
#define	MCCI_STM32H7_REG_PWR_CR1_SVOS_4		(UINT32_C(2) << 14)	///< SVOS5 scale 4
#define	MCCI_STM32H7_REG_PWR_CR1_SVOS_3		(UINT32_C(3) << 14)	///< SVOS5 scale 3
#define	MCCI_STM32H7_REG_PWR_CR1_AVD_READY	(UINT32_C(1) << 13)	///< analog voltage ready
#define	MCCI_STM32H7_REG_PWR_CR1_BOOSTE		(UINT32_C(1) << 12)	///< analog switch VBoost control
#define	MCCI_STM32H7_REG_PWR_CR1_RSV10		(UINT32_C(3) << 10)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR1_FLPS		(UINT32_C(1) << 9)	///< Flash memory low-power mode in DStop or DStop2 mode
#define	MCCI_STM32H7_REG_PWR_CR1_DBP		(UINT32_C(1) << 8)	///< disable Backup domain write protection
#define	MCCI_STM32H7_REG_PWR_CR1_PLS		(UINT32_C(7) << 5)	///< programmable voltage detector level selection
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_1_95V	(UINT32_C(0) << 5)	///< 1.95V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_2_1V	(UINT32_C(1) << 5)	///< 2.1V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_2_25V	(UINT32_C(2) << 5)	///< 2.25V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_2_4V	(UINT32_C(3) << 5)	///< 2.4V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_2_55V	(UINT32_C(4) << 5)	///< 2.55V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_2_7V	(UINT32_C(5) << 5)	///< 2.7V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_2_85V	(UINT32_C(6) << 5)	///< 2.85V
#define	MCCI_STM32H7_REG_PWR_CR1_PLS_PVD_IN	(UINT32_C(7) << 5)	///< PVD_IN pin
#define	MCCI_STM32H7_REG_PWR_CR1_PVDE		(UINT32_C(1) << 4)	///< programmable voltage detector enable
#define	MCCI_STM32H7_REG_PWR_CR1_RSV1		(UINT32_C(7) << 1)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR1_LPDS		(UINT32_C(1) << 0)	///< low-power Deepsleep with SVOS3
/// @}

/// \name PWR_CSR1 bits
///	@{
#define MCCI_STM32H7_REG_PWR_CSR1_RSV18		UINT32C(0xFFFC0000)	///< reserved, do not change
#define MCCI_STM32H7_REG_PWR_CSR1_MMCVDO	(UINT32_C(1) << 17)	///< voltage detector output on VDDMMC
#define MCCI_STM32H7_REG_PWR_CSR1_AVDO		(UINT32_C(1) << 16)	///< analog voltage detector output on VDDA
#define MCCI_STM32H7_REG_PWR_CSR1_ACTVOS	(UINT32_C(3) << 14)	///< VOS currently applied for VCORE voltage scaling selection
#define MCCI_STM32H7_REG_PWR_CSR1_ACTVOSRDY	(UINT32_C(1) << 13)	///< Regulator low-power flag
#define MCCI_STM32H7_REG_PWR_CSR1_RSV5		(UINT32_C(0xFF) << 5)	///< Reserved, do not change
#define MCCI_STM32H7_REG_PWR_CSR1_PVDO		(UINT32_C(1) << 4)	///< programmable voltage detect output
#define MCCI_STM32H7_REG_PWR_CSR1_RSV0		(UINT32_C(0xF) << 0)	///< Reserved, do not change
///	@}

/// \name PWR_CR2 bits
///	@{
#define	MCCI_STM32H7_REG_PWR_CR2_RSV24		(UINT32_C(0xFF) << 24)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR2_TEMPH		(UINT32_C(1) << 23)	///< temperature level monitoring versus high threshold
#define	MCCI_STM32H7_REG_PWR_CR2_TEMPL		(UINT32_C(1) << 22)	///< temperature level monitoring versus low threshold
#define	MCCI_STM32H7_REG_PWR_CR2_RSV17		(UINT32_C(0x1F) << 17)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR2_BRRDY		(UINT32_C(1) << 16)	///< backup regulator ready
#define	MCCI_STM32H7_REG_PWR_CR2_RSV5		(UINT32_C(0x7FF) << 5)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR2_MONEN		(UINT32_C(1) << 4)	///< VBAT and temperature monitoring enable
#define	MCCI_STM32H7_REG_PWR_CR2_RSV1		(UINT32_C(7) << 1)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR2_BREN		(UINT32_C(1) << 0)	///< backup regulator enable
///	@}

/// \name PWR_CR3 bits
///	@{
#define	MCCI_STM32H7_REG_PWR_CR3_RSV27		(UINT32_C(0x1F) << 27)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR3_USB33RDY	(UINT32_C(1) << 26)	///< USB supply ready
#define	MCCI_STM32H7_REG_PWR_CR3_USBREGEN	(UINT32_C(1) << 25)	///< USB regulator enable
#define	MCCI_STM32H7_REG_PWR_CR3_USB33DEN	(UINT32_C(1) << 24)	///< VDD33USB voltage level detector enable
#define	MCCI_STM32H7_REG_PWR_CR3_RSV17		(UINT32_C(0x7F) << 17)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSEXTRDY	(UINT32_C(1) << 16)	///< SMPS step-down converter external supply ready
#define	MCCI_STM32H7_REG_PWR_CR3_RSV10		(UINT32_C(0x3F) << 10)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR3_VBRS		(UINT32_C(1) << 9)	///< VBAT charging resistor selection
#define	MCCI_STM32H7_REG_PWR_CR3_VBE		(UINT32_C(1) << 8)	///< VBAT charging enable
#define	MCCI_STM32H7_REG_PWR_CR3_RSV6		(UINT32_C(3) << 6)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL	(UINT32_C(3) << 4)	///< SMPS step-down converter voltage output level selection
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_1_8V	(UINT32_C(1) << 4)	///< 1.8V
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_2_5V	(UINT32_C(2) << 4)	///< 2.5V
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSLEVEL_2V5	(UINT32_C(3) << 4)	///< 2.5V
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSEXTHP	(UINT32_C(1) << 3)	///< SMPS step-down converter external power delivery selection
#define	MCCI_STM32H7_REG_PWR_CR3_SMPSEN		(UINT32_C(1) << 2)	///< SMPS step-down converter enable
#define	MCCI_STM32H7_REG_PWR_CR3_LDOEN		(UINT32_C(1) << 1)	///< low drop-out regulator enable
#define	MCCI_STM32H7_REG_PWR_CR3_BYPASS		(UINT32_C(1) << 0)	///< power management unit bypass
///	@}

/// \name PWR_CPUCR bits
///	@{
#define	MCCI_STM32H7_REG_PWR_CPUCR_RSV12	UINT32_C(0xFFFFF000)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CPUCR_RUN_SRD	(UINT32_C(1) << 11)	///< temperature level monitoring versus high threshold
#define	MCCI_STM32H7_REG_PWR_CPUCR_RSV10	(UINT32_C(1) << 10)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CPUCR_CSSF		(UINT32_C(1) << 9)	///< clear Standby and Stop flags (always read as 0)
#define	MCCI_STM32H7_REG_PWR_CPUCR_RSV7		(UINT32_C(3) << 7)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CPUCR_SBF		(UINT32_C(1) << 6)	///< system Standby flag
#define	MCCI_STM32H7_REG_PWR_CPUCR_STOPF	(UINT32_C(1) << 5)	///< STOP flag
#define	MCCI_STM32H7_REG_PWR_CPUCR_RSV3		(UINT32_C(3) << 3)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CPUCR_PDDS_SRD	(UINT32_C(1) << 2)	///< system SmartRun domain power down Deepsleep
#define	MCCI_STM32H7_REG_PWR_CPUCR_RSV1		(UINT32_C(1) << 1)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_CPUCR_RETDS_CD	(UINT32_C(1) << 0)	///< CPU domain power down Deepsleep selection
///	@}

/// \name PWR_SRDCR bits
///	@{
#define	MCCI_STM32H7_REG_PWR_SRDCR_RSV16	UINT32_C(0xFFFF0000)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_SRDCR_VOS		(UINT32_C(3) << 14)	///< voltage scaling selection according to performance
#define	MCCI_STM32H7_REG_PWR_SRDCR_VOS_SCALE3	(UINT32_C(0) << 14)	///< scale 3
#define	MCCI_STM32H7_REG_PWR_SRDCR_VOS_SCALE2	(UINT32_C(1) << 14)	///< scale 2
#define	MCCI_STM32H7_REG_PWR_SRDCR_VOS_SCALE1	(UINT32_C(2) << 14)	///< scale 1
#define	MCCI_STM32H7_REG_PWR_SRDCR_VOS_SCALE0	(UINT32_C(3) << 14)	///< scale 0
#define	MCCI_STM32H7_REG_PWR_SRDCR_VOSRDY	(UINT32_C(1) << 13)	///< VOS ready bit for VCORE voltage scaling output selection
#define	MCCI_STM32H7_REG_PWR_SRDCR_RSV0		UINT32_C(0x00001FFF)	///< Reserved, don't change
///	@}

/// \name PWR_WKUPCR bits
///	@{
#define	MCCI_STM32H7_REG_PWR_WKUPCR_RSV6	UINT32_C(0xFFFFFC00)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC6	(UINT32_C(1) << 5)	///< clear wakeup pin flag for WKUP6
#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC5	(UINT32_C(1) << 4)	///< clear wakeup pin flag for WKUP5
#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC4	(UINT32_C(1) << 3)	///< clear wakeup pin flag for WKUP4
#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC3	(UINT32_C(1) << 2)	///< clear wakeup pin flag for WKUP3
#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC2	(UINT32_C(1) << 1)	///< clear wakeup pin flag for WKUP2
#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC1	(UINT32_C(1) << 0)	///< clear wakeup pin flag for WKUP1

#define	MCCI_STM32H7_REG_PWR_WKUPCR_WKUPC(n)	(UINT32_C(1) << ((n)-1))
///	@}

/// \name PWR_WKUPFR bits
///	@{
#define	MCCI_STM32H7_REG_PWR_WKUPFR_RSV6	UINT32_C(0xFFFFFC00)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF6	(UINT32_C(1) << 5)	///< wakeup pin flag for WKUP6
#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF5	(UINT32_C(1) << 4)	///< wakeup pin flag for WKUP5
#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF4	(UINT32_C(1) << 3)	///< wakeup pin flag for WKUP4
#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF3	(UINT32_C(1) << 2)	///< wakeup pin flag for WKUP3
#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF2	(UINT32_C(1) << 1)	///< wakeup pin flag for WKUP2
#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF1	(UINT32_C(1) << 0)	///< wakeup pin flag for WKUP1

#define	MCCI_STM32H7_REG_PWR_WKUPFR_WKUPF(n)	(UINT32_C(1) << ((n)-1))
///	@}

/// \name PWR_WKUPEPR bits
///	@{
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_RSV28	UINT32_C(0xF0000000)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PUPD6	(UINT32_C(3) << 26)	///< wakeup pin pull configuration for WKUP6
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PUPD5	(UINT32_C(3) << 24)	///< wakeup pin pull configuration for WKUP5
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PUPD4	(UINT32_C(3) << 22)	///< wakeup pin pull configuration for WKUP4
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PUPD3	(UINT32_C(3) << 20)	///< wakeup pin pull configuration for WKUP3
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PUPD2	(UINT32_C(3) << 18)	///< wakeup pin pull configuration for WKUP2
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PUPD1	(UINT32_C(3) << 16)	///< wakeup pin pull configuration for WKUP1

#define	MCCI_STM32H7_REG_PWR_WKUPEPR_NOPU(n)	(UINT32_C(0) << ((((n)-1)*2)+16))	///< no pull-up WKUPn
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PU(n)	(UINT32_C(1) << ((((n)-1)*2)+16))	///< pull-up WKUPn
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_PD(n)	(UINT32_C(2) << ((((n)-1)*2)+16))	///< pull-down WKUPn

#define	MCCI_STM32H7_REG_PWR_WKUPEPR_RSV14	(UINT32_C(3) << 14)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPP6	(UINT32_C(1) << 13)	///< wakeup pin polarity for WKUP6
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPP5	(UINT32_C(1) << 12)	///< wakeup pin polarity for WKUP5
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPP4	(UINT32_C(1) << 11)	///< wakeup pin polarity for WKUP4
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPP3	(UINT32_C(1) << 10)	///< wakeup pin polarity for WKUP3
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPP2	(UINT32_C(1) << 9)	///< wakeup pin polarity for WKUP2
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPP1	(UINT32_C(1) << 8)	///< wakeup pin polarity for WKUP1
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_RSV6	(UINT32_C(3) << 6)	///< Reserved, don't change
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPEN6	(UINT32_C(1) << 5)	///< enable wakeup pin for WKUP6
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPEN5	(UINT32_C(1) << 4)	///< enable wakeup pin for WKUP5
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPEN4	(UINT32_C(1) << 3)	///< enable wakeup pin for WKUP4
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPEN3	(UINT32_C(1) << 2)	///< enable wakeup pin for WKUP3
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPEN2	(UINT32_C(1) << 1)	///< enable wakeup pin for WKUP2
#define	MCCI_STM32H7_REG_PWR_WKUPEPR_WKUPEN1	(UINT32_C(1) << 0)	///< enable wakeup pin for WKUP1
///	@}

/****************************************************************************\
|
|	Reset and Clock Control (RCC) Registers
|
\****************************************************************************/

/// \name RCC registers
///	@{
#define	MCCI_STM32H7_REG_RCC_CR		(MCCI_STM32H7_REG_RCC + 0x00)	///< source control
#define	MCCI_STM32H7_REG_RCC_HSICFGR	(MCCI_STM32H7_REG_RCC + 0x04)	///< HSI calibration
#define	MCCI_STM32H7_REG_RCC_CRRCR	(MCCI_STM32H7_REG_RCC + 0x08)	///< Clock recovery RC
#define	MCCI_STM32H7_REG_RCC_CSICFGR	(MCCI_STM32H7_REG_RCC + 0x0C)	///< CSI calibration
#define	MCCI_STM32H7_REG_RCC_CFGR	(MCCI_STM32H7_REG_RCC + 0x10)	///< Clock configuration
#define	MCCI_STM32H7_REG_RCC_CDCFGR1	(MCCI_STM32H7_REG_RCC + 0x14)	///< CPU domain clock configuration
#define	MCCI_STM32H7_REG_RCC_CDCFGR2	(MCCI_STM32H7_REG_RCC + 0x18)	///< CPU domain clock configuration
#define	MCCI_STM32H7_REG_RCC_SRDCFGR	(MCCI_STM32H7_REG_RCC + 0x20)	///< SmartRun domain clock configuration
#define	MCCI_STM32H7_REG_RCC_PLLCKSELR	(MCCI_STM32H7_REG_RCC + 0x28)	///< PLLs clock source selection
#define	MCCI_STM32H7_REG_RCC_PLLCFGR	(MCCI_STM32H7_REG_RCC + 0x2C)	///< PLLs configuration
#define	MCCI_STM32H7_REG_RCC_PLL1DIVR	(MCCI_STM32H7_REG_RCC + 0x30)	///< PLL1 dividers configuration
#define	MCCI_STM32H7_REG_RCC_PLL1FRACR	(MCCI_STM32H7_REG_RCC + 0x34)	///< PLL1 fractional divider
#define	MCCI_STM32H7_REG_RCC_PLL2DIVR	(MCCI_STM32H7_REG_RCC + 0x38)	///< PLL2 dividers configuration
#define	MCCI_STM32H7_REG_RCC_PLL2FRACR	(MCCI_STM32H7_REG_RCC + 0x3C)	///< PLL2 fractional divider
#define	MCCI_STM32H7_REG_RCC_PLL3DIVR	(MCCI_STM32H7_REG_RCC + 0x40)	///< PLL3 dividers configuration
#define	MCCI_STM32H7_REG_RCC_PLL3FRACR	(MCCI_STM32H7_REG_RCC + 0x44)	///< PLL4 fractional divider
#define	MCCI_STM32H7_REG_RCC_CDCCIPR	(MCCI_STM32H7_REG_RCC + 0x4C)	///< CPU domain kernel clock configuration
#define	MCCI_STM32H7_REG_RCC_CDCCIP1R	(MCCI_STM32H7_REG_RCC + 0x50)	///< CPU domain kernel clock configuration
#define	MCCI_STM32H7_REG_RCC_CDCCIP2R	(MCCI_STM32H7_REG_RCC + 0x54)	///< CPU domain kernel clock configuration
#define	MCCI_STM32H7_REG_RCC_SRDCCIPR	(MCCI_STM32H7_REG_RCC + 0x58)	///< SmartRun domain kernel clock configuration
#define	MCCI_STM32H7_REG_RCC_CIER	(MCCI_STM32H7_REG_RCC + 0x60)	///< clock source interrupt enable
#define	MCCI_STM32H7_REG_RCC_CIFR	(MCCI_STM32H7_REG_RCC + 0x64)	///< clock source interrupt flag
#define	MCCI_STM32H7_REG_RCC_CICR	(MCCI_STM32H7_REG_RCC + 0x68)	///< clock source interrupt clear
#define	MCCI_STM32H7_REG_RCC_BDCR	(MCCI_STM32H7_REG_RCC + 0x70)	///< Backup domain control
#define	MCCI_STM32H7_REG_RCC_CSR	(MCCI_STM32H7_REG_RCC + 0x74)	///< clock control and status
#define	MCCI_STM32H7_REG_RCC_AHB3RSTR	(MCCI_STM32H7_REG_RCC + 0x7C)	///< AHB3 reset
#define	MCCI_STM32H7_REG_RCC_AHB1RSTR	(MCCI_STM32H7_REG_RCC + 0x80)	///< AHB1 peripheral reset
#define	MCCI_STM32H7_REG_RCC_AHB2RSTR	(MCCI_STM32H7_REG_RCC + 0x84)	///< AHB2 peripheral reset
#define	MCCI_STM32H7_REG_RCC_AHB4RSTR	(MCCI_STM32H7_REG_RCC + 0x88)	///< AHB4 peripheral reset
#define	MCCI_STM32H7_REG_RCC_APB3RSTR	(MCCI_STM32H7_REG_RCC + 0x8C)	///< APB3 peripheral reset
#define	MCCI_STM32H7_REG_RCC_APB1LRSTR	(MCCI_STM32H7_REG_RCC + 0x90)	///< APB1 peripheral reset
#define	MCCI_STM32H7_REG_RCC_APB1HRSTR	(MCCI_STM32H7_REG_RCC + 0x94)	///< APB1 peripheral reset
#define	MCCI_STM32H7_REG_RCC_APB2RSTR	(MCCI_STM32H7_REG_RCC + 0x98)	///< APB2 peripheral reset
#define	MCCI_STM32H7_REG_RCC_APB4RSTR	(MCCI_STM32H7_REG_RCC + 0x9C)	///< APB4 peripheral reset
#define	MCCI_STM32H7_REG_RCC_SRDAMR	(MCCI_STM32H7_REG_RCC + 0xA8)	///< SmartRun domain Autonomous mode
#define	MCCI_STM32H7_REG_RCC_CKGAENR	(MCCI_STM32H7_REG_RCC + 0xB0)	///< AXI clocks gating enable
#define	MCCI_STM32H7_REG_RCC_RSR	(MCCI_STM32H7_REG_RCC + 0x130)	///< reset status
#define	MCCI_STM32H7_REG_RCC_AHB3ENR	(MCCI_STM32H7_REG_RCC + 0x134)	///< AHB3 clock
#define	MCCI_STM32H7_REG_RCC_AHB1ENR	(MCCI_STM32H7_REG_RCC + 0x138)	///< AHB1 clock
#define	MCCI_STM32H7_REG_RCC_AHB2ENR	(MCCI_STM32H7_REG_RCC + 0x13C)	///< AHB2 clock
#define	MCCI_STM32H7_REG_RCC_AHB4ENR	(MCCI_STM32H7_REG_RCC + 0x140)	///< AHB4 clock
#define	MCCI_STM32H7_REG_RCC_APB3ENR	(MCCI_STM32H7_REG_RCC + 0x144)	///< APB3 clock
#define	MCCI_STM32H7_REG_RCC_APB1LENR	(MCCI_STM32H7_REG_RCC + 0x148)	///< APB1 clock
#define	MCCI_STM32H7_REG_RCC_APB1HENR	(MCCI_STM32H7_REG_RCC + 0x14C)	///< APB1 clock
#define	MCCI_STM32H7_REG_RCC_APB2ENR	(MCCI_STM32H7_REG_RCC + 0x150)	///< APB2 clock
#define	MCCI_STM32H7_REG_RCC_APB4ENR	(MCCI_STM32H7_REG_RCC + 0x154)	///< APB4 clock
#define	MCCI_STM32H7_REG_RCC_AHB3LPENR	(MCCI_STM32H7_REG_RCC + 0x15C)	///< AHB3 sleep clock
#define	MCCI_STM32H7_REG_RCC_AHB1LPENR	(MCCI_STM32H7_REG_RCC + 0x160)	///< AHB1 sleep clock
#define	MCCI_STM32H7_REG_RCC_AHB2LPENR	(MCCI_STM32H7_REG_RCC + 0x164)	///< AHB2 sleep clock
#define	MCCI_STM32H7_REG_RCC_AHB4LPENR	(MCCI_STM32H7_REG_RCC + 0x168)	///< AHB4 sleep clock
#define	MCCI_STM32H7_REG_RCC_APB3LPENR	(MCCI_STM32H7_REG_RCC + 0x16C)	///< APB3 sleep clock
#define	MCCI_STM32H7_REG_RCC_APB1LLPENR	(MCCI_STM32H7_REG_RCC + 0x170)	///< APB1 low-sleep clock
#define	MCCI_STM32H7_REG_RCC_APB1HLPENR	(MCCI_STM32H7_REG_RCC + 0x174)	///< APB1 high-sleep clock
#define	MCCI_STM32H7_REG_RCC_APB2LPENR	(MCCI_STM32H7_REG_RCC + 0x178)	///< APB2 sleep clock
#define	MCCI_STM32H7_REG_RCC_APB4LPENR	(MCCI_STM32H7_REG_RCC + 0x17C)	///< APB4 sleep clock
///	@}

/// \name RCC_CR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CR_RSV30		(UINT32_C(3) << 30)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CR_PLL3RDY		(UINT32_C(1) << 29)	//< PLL3 clock ready flag
#define MCCI_STM32H7_REG_RCC_CR_PLL3ON		(UINT32_C(1) << 28)	//< PLL3 enable
#define MCCI_STM32H7_REG_RCC_CR_PLL2RDY		(UINT32_C(1) << 27)	//< PLL2 clock ready flag
#define MCCI_STM32H7_REG_RCC_CR_PLL2ON		(UINT32_C(1) << 26)	//< PLL2 enable
#define MCCI_STM32H7_REG_RCC_CR_PLL1RDY		(UINT32_C(1) << 25)	//< PLL1 clock ready flag
#define MCCI_STM32H7_REG_RCC_CR_PLL1ON		(UINT32_C(1) << 24)	//< PLL1 enable
#define MCCI_STM32H7_REG_RCC_CR_RSV21		(UINT32_C(7) << 21)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CR_HSEEXT		(UINT32_C(1) << 20)	//< external high speed clock type in Bypass mode
#define MCCI_STM32H7_REG_RCC_CR_HSECSSON	(UINT32_C(1) << 19)	//< HSE clock security system enable
#define MCCI_STM32H7_REG_RCC_CR_HSEBYP		(UINT32_C(1) << 18)	//< enable HSE clock bypass
#define MCCI_STM32H7_REG_RCC_CR_HSERDY		(UINT32_C(1) << 17)	//< HSE clock ready
#define MCCI_STM32H7_REG_RCC_CR_HSEON		(UINT32_C(1) << 16)	//< HSE clock enabled
#define MCCI_STM32H7_REG_RCC_CR_CDCKRDY		(UINT32_C(1) << 15)	//< CPU domain clocks ready flag
#define MCCI_STM32H7_REG_RCC_CR_CPUCKRDY	(UINT32_C(1) << 14)	//< CPU related clocks ready flag
#define MCCI_STM32H7_REG_RCC_CR_HSI48RDY	(UINT32_C(1) << 13)	//< HSI48 clock ready flag
#define MCCI_STM32H7_REG_RCC_CR_HSI48ON		(UINT32_C(1) << 12)	//< HSI48 clock enable
#define MCCI_STM32H7_REG_RCC_CR_RSV10		(UINT32_C(3) << 10)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CR_CSIKERON	(UINT32_C(1) << 9)	//< CSI clock enable in Stop mode
#define MCCI_STM32H7_REG_RCC_CR_CSIRDY		(UINT32_C(1) << 8)	//< CSI clock ready
#define MCCI_STM32H7_REG_RCC_CR_CSION		(UINT32_C(1) << 7)	//< CSI clock enable
#define MCCI_STM32H7_REG_RCC_CR_RSV6		(UINT32_C(1) << 6)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CR_HSIDIVF		(UINT32_C(1) << 5)	//< HSI divider flag
#define MCCI_STM32H7_REG_RCC_CR_HSIDIV		(UINT32_C(3) << 3)	//< HSI clock divider
#define MCCI_STM32H7_REG_RCC_CR_HSIDIV_1	(UINT32_C(0) << 3)	//< division by 1, hsi_ck=64MHz
#define MCCI_STM32H7_REG_RCC_CR_HSIDIV_2	(UINT32_C(1) << 3)	//< division by 2, hsi_ck=32MHz
#define MCCI_STM32H7_REG_RCC_CR_HSIDIV_3	(UINT32_C(2) << 3)	//< division by 4, hsi_ck=16MHz
#define MCCI_STM32H7_REG_RCC_CR_HSIDIV_8	(UINT32_C(3) << 3)	//< division by 8, hsi_ck=8MHz
#define MCCI_STM32H7_REG_RCC_CR_HSIRDY		(UINT32_C(1) << 2)	//< HSI clock ready flag
#define MCCI_STM32H7_REG_RCC_CR_HSIKERON	(UINT32_C(1) << 1)	//< HSI clock enable in Stop mode
#define MCCI_STM32H7_REG_RCC_CR_HSION		(UINT32_C(1) << 0)	//< HSI clock enable
///	@}

/// \name RCC_HSICFGR bits
///	@{
#define MCCI_STM32H7_REG_RCC_HSICFGR_RSV31	(UINT32_C(1) << 31)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_HSICFGR_HSITRIM	(UINT32_C(0x7F) << 24)	//< HSI clock trimming
#define MCCI_STM32H7_REG_RCC_HSICFGR_RSV12	(UINT32_C(0xFFF) << 12)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_HSICFGR_HSICAL	(UINT32_C(0xFFF) << 0)	//< HSI clock cal
///	@}

/// \name RCC_CRRCR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CRRCR_RSV10	UINT32_C(0xFFFFFC00)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_CRRCR_HSI48CAL	(UINT32_C(0x3FF) << 0)	//< calibration for HSI48
///	@}

/// \name RCC_CSICFGR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CSICFGR_RSV30	(UINT32_C(3) << 30)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CSICFGR_CSITRIM	(UINT32_C(0x3F) << 24)	//< CSI clock trimming
#define MCCI_STM32H7_REG_RCC_CSICFGR_RSV8	(UINT32_C(0xFFFF) << 8)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CSICFGR_CSICAL	(UINT32_C(0xFF) << 0)	//< CSI clock calibration
///	@}

/// \name RCC_CFGR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL	(UINT32_C(7) << 29)	//< microcontroller clock output 2
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL_SYS	(UINT32_C(0) << 29)	//< System clock
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL_PLL2	(UINT32_C(1) << 29)	//< PLL2
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL_HSE	(UINT32_C(2) << 29)	//< HSE
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL_PLL1	(UINT32_C(3) << 29)	//< PLL1
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL_CSI	(UINT32_C(4) << 29)	//< CSI
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2SEL_LSI	(UINT32_C(5) << 29)	//< LSI
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2PRE	(UINT32_C(0xF) << 25)	//< MCO2 prescaler
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2PRE_DIS	(UINT32_C(0) << 25)	//< prescaler disabled (default after reset)
#define MCCI_STM32H7_REG_RCC_CFGR_MCO2PRE_N(n)	((n) << 25)		//< division by n
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1SEL	(UINT32_C(7) << 22)	//< microcontroller clock output 1
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1SEL_HSI	(UINT32_C(0) << 22)	//< HSI
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1SEL_LSE	(UINT32_C(1) << 22)	//< LSE
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1SEL_HSE	(UINT32_C(2) << 22)	//< HSE
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1SEL_PLL1	(UINT32_C(3) << 22)	//< PLL1
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1SEL_HSI48	(UINT32_C(4) << 22)	//< HSI48
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1PRE	(UINT32_C(0xF) << 18)	//< MCO1 prescaler
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1PRE_DIS	(UINT32_C(0) << 18)	//< prescaler disabled (default after reset)
#define MCCI_STM32H7_REG_RCC_CFGR_MCO1PRE_N(n)	((n) << 18)		//< division by n
#define MCCI_STM32H7_REG_RCC_CFGR_RSV16		(UINT32_C(3) << 16)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_CFGR_TIMPRE	(UINT32_C(1) << 15)	//< timers clocks prescaler selection
#define MCCI_STM32H7_REG_RCC_CFGR_RSV14		(UINT32_C(1) << 14)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_CFGR_RTCPRE	(UINT32_C(0x3F) << 8)	//< HSE division factor for RTC clock
#define MCCI_STM32H7_REG_RCC_CFGR_RTCPRE_DIS	(UINT32_C(0) << 8)	//< no clock (default after reset)
#define MCCI_STM32H7_REG_RCC_CFGR_RTCPRE_N(n)	((n) << 8)		//< HSE/n
#define MCCI_STM32H7_REG_RCC_CFGR_STOPKERWUCK	(UINT32_C(1) << 7)	//< kernel clock selection after a wake up from system Stop
#define MCCI_STM32H7_REG_RCC_CFGR_STOPWUCK	(UINT32_C(1) << 6)	//< system clock selection after a wake up from system Stop
#define MCCI_STM32H7_REG_RCC_CFGR_SWS		(UINT32_C(7) << 3)	//< system clock switch status
#define MCCI_STM32H7_REG_RCC_CFGR_SWS_HSI	(UINT32_C(0) << 3)	//< HSI used as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SWS_CSI	(UINT32_C(1) << 3)	//< CSI used as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SWS_HSE	(UINT32_C(2) << 3)	//< HSE used as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SWS_PLL1	(UINT32_C(3) << 3)	//< PLL1 used as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SW		(UINT32_C(3) << 0)	//< system clock and trace clock switch
#define MCCI_STM32H7_REG_RCC_CFGR_SW_HSI	(UINT32_C(0) << 0)	//< HSI selected as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SW_CSI	(UINT32_C(1) << 0)	//< CSI selected as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SW_HSE	(UINT32_C(2) << 0)	//< HSE selected as system clock
#define MCCI_STM32H7_REG_RCC_CFGR_SW_PLL1	(UINT32_C(3) << 0)	//< PLL1 selected as system clock
///	@}

/// \name RCC_CDCFGR1 bits
///	@{
#define MCCI_STM32H7_REG_RCC_CDCFGR1_RSV12	UINT32_C(0xFFFFF000)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE	(UINT32_C(0xF) << 8)	//< CPU domain core prescaler
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_1	(UINT32_C(0) << 8)	//< sys_ck not divided
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_2	(UINT32_C(0x8) << 8)	//< sys_ck divided by 2
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_4	(UINT32_C(0x9) << 8)	//< sys_ck divided by 4
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_5	(UINT32_C(0xA) << 8)	//< sys_ck divided by 8
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_16	(UINT32_C(0xB) << 8)	//< sys_ck divided by 16
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_64	(UINT32_C(0xC) << 8)	//< sys_ck divided by 64
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_128	(UINT32_C(0xD) << 8)	//< sys_ck divided by 128
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_256	(UINT32_C(0xE) << 8)	//< sys_ck divided by 256
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDCPRE_512	(UINT32_C(0xF) << 8)	//< sys_ck divided by 512
#define MCCI_STM32H7_REG_RCC_CDCFGR1_RSV7	(UINT32_C(1) << 7)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDPPRE	(UINT32_C(7) << 4)	//< CPU domain APB3 prescaler
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDPPRE_1	(UINT32_C(0) << 4)	//< rcc_pclk3 = rcc_hclk3
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDPPRE_2	(UINT32_C(4) << 4)	//< rcc_pclk3 = rcc_hclk3 / 2
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDPPRE_3	(UINT32_C(5) << 4)	//< rcc_pclk3 = rcc_hclk3 / 4
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDPPRE_8	(UINT32_C(6) << 4)	//< rcc_pclk3 = rcc_hclk3 / 8
#define MCCI_STM32H7_REG_RCC_CDCFGR1_CDPPRE_16	(UINT32_C(7) << 4)	//< rcc_pclk3 = rcc_hclk3 / 16
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE	(UINT32_C(0xF) << 0)	//< CPU domain AHB prescaler
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_1	(UINT32_C(0) << 0)	//< rcc_hclk3 = sys_cdcpre_ck
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_2	(UINT32_C(0x8) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 2
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_4	(UINT32_C(0x9) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 4
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_8	(UINT32_C(0xA) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 8
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_16	(UINT32_C(0xB) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 16
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_64	(UINT32_C(0xC) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 64
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_128	(UINT32_C(0xD) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 128
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_256	(UINT32_C(0xE) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 256
#define MCCI_STM32H7_REG_RCC_CDCFGR1_HPRE_512	(UINT32_C(0xF) << 0)	//< rcc_hclk3 = sys_cdcpre_ck / 512
///	@}

/// \name RCC_CDCFGR2 bits
///	@{
#define MCCI_STM32H7_REG_RCC_CDCFGR2_RSV11	UINT32_C(0xFFFFF800)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE2	(UINT32_C(7) << 8)	//< CPU domain APB2 prescaler
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE2_1	(UINT32_C(0) << 8)	//< rcc_pclk2 = rcc_hclk1
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE2_2	(UINT32_C(4) << 8)	//< rcc_pclk2 = rcc_hclk1 / 2
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE2_3	(UINT32_C(5) << 8)	//< rcc_pclk2 = rcc_hclk1 / 4
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE2_8	(UINT32_C(6) << 8)	//< rcc_pclk2 = rcc_hclk1 / 8
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE2_16	(UINT32_C(7) << 8)	//< rcc_pclk2 = rcc_hclk1 / 16
#define MCCI_STM32H7_REG_RCC_CDCFGR2_RSV7	(UINT32_C(1) << 7)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE1	(UINT32_C(7) << 4)	//< CPU domain APB1 prescaler
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE1_1	(UINT32_C(0) << 4)	//< rcc_pclk1 = rcc_hclk1
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE1_2	(UINT32_C(4) << 4)	//< rcc_pclk1 = rcc_hclk1 / 2
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE1_3	(UINT32_C(5) << 4)	//< rcc_pclk1 = rcc_hclk1 / 4
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE1_8	(UINT32_C(6) << 4)	//< rcc_pclk1 = rcc_hclk1 / 8
#define MCCI_STM32H7_REG_RCC_CDCFGR2_CDPPRE1_16	(UINT32_C(7) << 4)	//< rcc_pclk1 = rcc_hclk1 / 16
#define MCCI_STM32H7_REG_RCC_CDCFGR2_RSV0	(UINT32_C(0xF) << 0)	//< reserved, no change
///	@}

/// \name RCC_SRDCFGR bits
///	@{
#define MCCI_STM32H7_REG_RCC_SRDCFGR_RSV7	UINT32_C(0xFFFFFF80)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_SRDCFGR_SRDPPRE	(UINT32_C(7) << 4)	//< SmartRun domain APB4 prescaler
#define MCCI_STM32H7_REG_RCC_SRDCFGR_SRDPPRE_1	(UINT32_C(0) << 4)	//< rcc_pclk4 = rcc_hclk4
#define MCCI_STM32H7_REG_RCC_SRDCFGR_SRDPPRE_2	(UINT32_C(4) << 4)	//< rcc_pclk4 = rcc_hclk4 / 2
#define MCCI_STM32H7_REG_RCC_SRDCFGR_SRDPPRE_3	(UINT32_C(5) << 4)	//< rcc_pclk4 = rcc_hclk4 / 4
#define MCCI_STM32H7_REG_RCC_SRDCFGR_SRDPPRE_8	(UINT32_C(6) << 4)	//< rcc_pclk4 = rcc_hclk4 / 8
#define MCCI_STM32H7_REG_RCC_SRDCFGR_SRDPPRE_16	(UINT32_C(7) << 4)	//< rcc_pclk4 = rcc_hclk4 / 16
#define MCCI_STM32H7_REG_RCC_SRDCFGR_RSV0	(UINT32_C(0xF) << 0)	//< reserved, no change
///	@}

/// \name RCC_PLLCKSELR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_RSV26	  (UINT32_C(0x3F) << 26) //< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM3	  (UINT32_C(0x3F) << 20) //< prescaler for PLL3
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM3_DIS  (UINT32_C(0x3F) << 20) //< prescaler disabled
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM3_N(n) ((n) << 20)		 //< division by n
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_RSV18	  (UINT32_C(3) << 18)	 //< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM2	  (UINT32_C(0x3F) << 12) //< prescaler for PLL2
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM2_DIS  (UINT32_C(0x3F) << 12) //< prescaler disabled
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM2_N(n) ((n) << 12)	 	//< division by n
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_RSV10	  (UINT32_C(3) << 10)	 //< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM1	  (UINT32_C(0x3F) << 14) //< prescaler for PLL1
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM1_DIS  (UINT32_C(0x3F) << 14) //< prescaler disabled
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_DIVM1_N(n) ((n) << 14)		 //< division by n
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_RSV2	  (UINT32_C(3) << 2)	 //< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_PLLSRC	  (UINT32_C(3) << 0)	 //< DIVMx and PLLs clock source selection
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_PLLSRC_HSI (UINT32_C(0) << 0)	 //< HSI
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_PLLSRC_CSI (UINT32_C(1) << 0)	 //< CSI
#define MCCI_STM32H7_REG_RCC_PLLCKSELR_PLLSRC_HSE (UINT32_C(2) << 0)	 //< HSE
///	@}

/// \name RCC_PLLCFGR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLLCFGR_RSV25	(UINT32_C(0x7F) << 25)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVR3EN	(UINT32_C(1) << 24)	//< PLL3 DIVR divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVQ3EN	(UINT32_C(1) << 23)	//< PLL3 DIVQ divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVP3EN	(UINT32_C(1) << 22)	//< PLL3 DIVP divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVR2EN	(UINT32_C(1) << 21)	//< PLL2 DIVR divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVQ2EN	(UINT32_C(1) << 20)	//< PLL2 DIVQ divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVP2EN	(UINT32_C(1) << 19)	//< PLL2 DIVP divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVR1EN	(UINT32_C(1) << 18)	//< PLL1 DIVR divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVQ1EN	(UINT32_C(1) << 17)	//< PLL1 DIVQ divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_DIVP1EN	(UINT32_C(1) << 16)	//< PLL1 DIVP divider output enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_RSV12	(UINT32_C(0xF) << 12)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL3RGE	(UINT32_C(3) << 10)	//< PLL3 input frequency range
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL3RGE_N(n) ((n) << 10)		//< PLL3 input frequency range
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL3VCOSEL	(UINT32_C(1) << 9)	//< PLL3 VCO selection
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL3FRACEN	(UINT32_C(1) << 8)	//< PLL3 fractional latch enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL2RGE	(UINT32_C(3) << 6)	//< PLL2 input frequency range
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL2RGE_N(n) ((n) << 6)		//< PLL2 input frequency range
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL2VCOSEL	(UINT32_C(1) << 5)	//< PLL2 VCO selection
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL2FRACEN	(UINT32_C(1) << 4)	//< PLL2 fractional latch enable
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL1RGE	(UINT32_C(3) << 2)	//< PLL1 input frequency range
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL1RGE_N(n) ((n) << 2)		//< PLL1 input frequency range
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL1VCOSEL	(UINT32_C(1) << 1)	//< PLL1 VCO selection
#define MCCI_STM32H7_REG_RCC_PLLCFGR_PLL1FRACEN	(UINT32_C(1) << 0)	//< PLL1 fractional latch enable
///	@}

/// \name RCC_PLL1DIVR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_RSV31	(UINT32_C(1) << 31)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVR	(UINT32_C(0x7F) << 24)	//< PLL1 DIVR division factor
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVR_N(n)	((n) << 24)		//< pll1_r_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_RSV23	(UINT32_C(1) << 23)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVQ	(UINT32_C(0x7F) << 16)	//< PLL1 DIVQ division factor
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVQ_N(n)	((n) << 16)		//< pll1_q_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVP	(UINT32_C(0x7F) << 9)	//< PLL1 DIVP division factor
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVP_N(n)	((n) << 9)		//< pll1_p_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVN	(UINT32_C(0x1FF) << 0)	//< multiplication factor for PLL1 VCO
#define MCCI_STM32H7_REG_RCC_PLL1DIVR_DIVN_N(n)	((n) << 0)		//< DIVN = n+1
///	@}

/// \name RCC_PLL1FRACR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLL1FRACR_RSV16	UINT32_C(0xFFFF0000)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL1FRACR_FRACN	(UINT32_C(0x1FFF) << 3)	//< fractional part of the multiplication factor for PLL1 VCO
#define MCCI_STM32H7_REG_RCC_PLL1FRACR_FRACN_N(n) ((n) << 3)		//< fractional part of the multiplication factor for PLL1 VCO
#define MCCI_STM32H7_REG_RCC_PLL1FRACR_RSV0	(UINT32_C(7) << 0)	//< reserved, no change
///	@}

/// \name RCC_PLL2DIVR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_RSV31	(UINT32_C(1) << 31)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVR	(UINT32_C(0x7F) << 24)	//< PLL2 DIVR division factor
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVR_N(n)	((n) << 24)		//< pll2_r_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_RSV23	(UINT32_C(1) << 23)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVQ	(UINT32_C(0x7F) << 16)	//< PLL2 DIVQ division factor
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVQ_N(n)	((n) << 16)		//< pll2_q_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVP	(UINT32_C(0x7F) << 9)	//< PLL2 DIVP division factor
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVP_N(n)	((n) << 9)		//< pll2_p_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVN	(UINT32_C(0x1FF) << 0)	//< multiplication factor for PLL2 VCO
#define MCCI_STM32H7_REG_RCC_PLL2DIVR_DIVN_N(n)	((n) << 0)		//< DIVN = n+1
///	@}

/// \name RCC_PLL2FRACR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLL2FRACR_RSV16	UINT32_C(0xFFFF0000)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL2FRACR_FRACN	(UINT32_C(0x1FFF) << 3)	//< fractional part of the multiplication factor for PLL2 VCO
#define MCCI_STM32H7_REG_RCC_PLL2FRACR_FRACN_N(n) ((n) << 3)		//< fractional part of the multiplication factor for PLL2 VCO
#define MCCI_STM32H7_REG_RCC_PLL2FRACR_RSV0	(UINT32_C(7) << 0)	//< reserved, no change
///	@}

/// \name RCC_PLL3DIVR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_RSV31	(UINT32_C(1) << 31)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVR	(UINT32_C(0x7F) << 24)	//< PLL3 DIVR division factor
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVR_N(n)	((n) << 24)		//< pll3_r_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_RSV23	(UINT32_C(1) << 23)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVQ	(UINT32_C(0x7F) << 16)	//< PLL3 DIVQ division factor
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVQ_N(n)	((n) << 16)		//< pll3_q_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVP	(UINT32_C(0x7F) << 9)	//< PLL3 DIVP division factor
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVP_N(n)	((n) << 9)		//< pll3_p_ck = vco1_ck / (n+1)
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVN	(UINT32_C(0x1FF) << 0)	//< multiplication factor for PLL3 VCO
#define MCCI_STM32H7_REG_RCC_PLL3DIVR_DIVN_N(n)	((n) << 0)		//< DIVN = n+1
///	@}

/// \name RCC_PLL3FRACR bits
///	@{
#define MCCI_STM32H7_REG_RCC_PLL3FRACR_RSV16	UINT32_C(0xFFFF0000)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_PLL3FRACR_FRACN	(UINT32_C(0x1FFF) << 3)	//< fractional part of the multiplication factor for PLL3 VCO
#define MCCI_STM32H7_REG_RCC_PLL3FRACR_FRACN_N(n) ((n) << 3)		//< fractional part of the multiplication factor for PLL3 VCO
#define MCCI_STM32H7_REG_RCC_PLL3FRACR_RSV0	(UINT32_C(7) << 0)	//< reserved, no change
///	@}

/// \name RCC_CDCCIPR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CDCCIPR_RSV30		(UINT32_C(3) << 30)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIPR_CKPERSEL		(UINT32_C(3) << 28)	//< per_ck clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIPR_CKPERSEL_HSI	(UINT32_C(0) << 28)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_CKPERSEL_CSI	(UINT32_C(1) << 28)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_CKPERSEL_HSE	(UINT32_C(2) << 28)	//< hse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_RSV17		UINT32_C(0x0FFE0000)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIPR_SDMMCSEL		(UINT32_C(1) << 16)	//< SDMMC kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIPR_RSV6		(UINT32_C(0x3F) << 6)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIPR_OCTOSPISEL		(UINT32_C(3) << 4)	//< OCTOSPI kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIPR_OCTOSPISEL_HCLK3 	(UINT32_C(0) << 4)	//< rcc_hclk3
#define MCCI_STM32H7_REG_RCC_CDCCIPR_OCTOSPISEL_PLL1	(UINT32_C(1) << 4)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_OCTOSPISEL_PLL2	(UINT32_C(2) << 4)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_OCTOSPISEL_PER	(UINT32_C(3) << 4)	//< per_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_RSV0		(UINT32_C(3) << 2)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIPR_FMCSEL		(UINT32_C(3) << 0)	//< FMC kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIPR_FMCSEL_HCLK3	(UINT32_C(0) << 0)	//< rcc_hclk3
#define MCCI_STM32H7_REG_RCC_CDCCIPR_FMCSEL_PLL1	(UINT32_C(1) << 0)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_FMCSEL_PLL2	(UINT32_C(2) << 0)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIPR_FMCSEL_PER		(UINT32_C(3) << 0)	//< per_ck
///	@}

/// \name RCC_CDCCIP1R bits
///	@{
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SWPMISEL		(UINT32_C(1) << 31)	//< SWPMI kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_RSV30		(UINT32_C(1) << 30)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_FDCANSEL		(UINT32_C(3) << 28)	//< FDCAN kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_FDCANSEL_HSE	(UINT32_C(0) << 28)	//< hse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_FDCANSEL_PLL1	(UINT32_C(1) << 28)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_FDCANSEL_PLL2	(UINT32_C(2) << 28)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_RSV25		(UINT32_C(7) << 25)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_DFSDM1SEL		(UINT32_C(1) << 24)	//< DFSDM1 kernel clock Clk source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_RSV22		(UINT32_C(3) << 22)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPDIFRXSEL	(UINT32_C(3) << 20)	//< SPDIFRX kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPDIFRXSEL_PLL1	(UINT32_C(0) << 20)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPDIFRXSEL_PLL2	(UINT32_C(1) << 20)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPDIFRXSEL_PLL3	(UINT32_C(2) << 20)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPDIFRXSEL_HSI	(UINT32_C(3) << 20)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_RSV19		(UINT32_C(1) << 19)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL		(UINT32_C(7) << 16)	//< SPI4 and 5 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL_PCLK2	(UINT32_C(0) << 16)	//< rcc_pclk2
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL_PLL2	(UINT32_C(1) << 16)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL_PLL3	(UINT32_C(2) << 16)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL_HSI	(UINT32_C(3) << 16)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL_CSI	(UINT32_C(4) << 16)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI45SEL_HSE	(UINT32_C(5) << 16)	//< hse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_RSV15		(UINT32_C(1) << 15)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI123SEL		(UINT32_C(7) << 12)	//< SPI/I2S1,2 and 3 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI123SEL_PLL1	(UINT32_C(0) << 12)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI123SEL_PLL2	(UINT32_C(1) << 12)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI123SEL_PLL3	(UINT32_C(2) << 12)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI123SEL_I2S	(UINT32_C(3) << 12)	//< I2S_CKIN
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SPI123SEL_PER	(UINT32_C(4) << 12)	//< per_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL		(UINT32_C(7) << 9)	//< SAI2 kernel clock B source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL_PLL1	(UINT32_C(0) << 9)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL_PLL2	(UINT32_C(1) << 9)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL_PLL3	(UINT32_C(2) << 9)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL_I2S	(UINT32_C(3) << 9)	//< I2S_CKIN
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL_PER	(UINT32_C(4) << 9)	//< per_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2BSEL_SPDIFRX	(UINT32_C(5) << 9)	//< spdifrx_symb_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL		(UINT32_C(7) << 6)	//< SAI2 kernel clock source A selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL_PLL1	(UINT32_C(0) << 6)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL_PLL2	(UINT32_C(1) << 6)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL_PLL3	(UINT32_C(2) << 6)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL_I2S	(UINT32_C(3) << 6)	//< I2S_CKIN
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL_PER	(UINT32_C(4) << 6)	//< per_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI2ASEL_SPDIFRX	(UINT32_C(5) << 6)	//< spdifrx_symb_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_RSV3		(UINT32_C(7) << 3)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI1SEL		(UINT32_C(7) << 0)	//< SAI1 and DFSDM1 kernel Aclk clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI1SEL_PLL1	(UINT32_C(0) << 0)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI1SEL_PLL2	(UINT32_C(1) << 0)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI1SEL_PLL3	(UINT32_C(2) << 0)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI1SEL_I2S	(UINT32_C(3) << 0)	//< I2S_CKIN
#define MCCI_STM32H7_REG_RCC_CDCCIP1R_SAI1SEL_PER	(UINT32_C(4) << 0)	//< per_ck
///	@}

/// \name RCC_CDCCIP2R bits
///	@{
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RSV31		(UINT32_C(1) << 31)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL		(UINT32_C(7) << 28)	//< LPTIM1 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL_PCLK1	(UINT32_C(0) << 28)	//< rcc_pclk1
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL_PLL2	(UINT32_C(1) << 28)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL_PLL3	(UINT32_C(2) << 28)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL_LSE	(UINT32_C(3) << 28)	//< lse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL_LSI	(UINT32_C(4) << 28)	//< lsi_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_LPTIM1SEL_PER	(UINT32_C(5) << 28)	//< per_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RSV24		(UINT32_C(0xF) << 24)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_CECSEL		(UINT32_C(3) << 22)	//< HDMI-CEC kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_CECSEL_LSE	(UINT32_C(0) << 22)	//< lse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_CECSEL_LSI	(UINT32_C(1) << 22)	//< lsi_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_CECSEL_CSI	(UINT32_C(2) << 22)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USBSEL		(UINT32_C(3) << 20)	//< USBOTG 1 and 2 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USBSEL_DIS	(UINT32_C(0) << 20)	//< disable
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USBSEL_PLL1	(UINT32_C(1) << 20)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USBSEL_PLL3	(UINT32_C(2) << 20)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USBSEL_HSI48	(UINT32_C(3) << 20)	//< hsi48_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RSV14		(UINT32_C(0x3F) << 14)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_I2C123SEL		(UINT32_C(7) << 12)	//< I2C1,2,3 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_I2C123SEL_PCLK1	(UINT32_C(0) << 12)	//< rcc_pclk1
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_I2C123SEL_PLL3	(UINT32_C(1) << 12)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_I2C123SEL_HSI	(UINT32_C(2) << 12)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_I2C123SEL_CSI	(UINT32_C(3) << 12)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RSV10		(UINT32_C(3) << 10)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RNGSEL		(UINT32_C(3) << 8)	//< RNG kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RNGSEL_HSI48	(UINT32_C(0) << 8)	//< hsi48_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RNGSEL_PLL1	(UINT32_C(1) << 8)	//< pll1_q_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RNGSEL_LSE	(UINT32_C(2) << 8)	//< lse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RNGSEL_LSI	(UINT32_C(3) << 8)	//< lsi_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_RSV6		(UINT32_C(3) << 6)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL		(UINT32_C(7) << 3)	//< USART1, 6, 9 and 10 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL_PCLK2	(UINT32_C(0) << 3)	//< rcc_pclk2
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL_PLL2	(UINT32_C(1) << 3)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL_PLL3	(UINT32_C(2) << 3)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL_HSI		(UINT32_C(3) << 3)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL_CSI		(UINT32_C(4) << 3)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART16910SEL_LSE		(UINT32_C(5) << 3)	//< lse_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL		(UINT32_C(7) << 0)	//< USART2/3, UART4,5, 7 and 8 (APB1) kernel clock source selection
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL_PCLK1	(UINT32_C(0) << 0)	//< rcc_pclk1
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL_PLL2	(UINT32_C(1) << 0)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL_PLL3	(UINT32_C(2) << 0)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL_HSI	(UINT32_C(3) << 0)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL_CSI	(UINT32_C(4) << 0)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_CDCCIP2R_USART234578SEL_LSE	(UINT32_C(5) << 0)	//< lse_ck
///	@}

/// \name RCC_SRDCCIPR bits
///	@{
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_RSV31		(UINT32_C(1) << 31)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL		(UINT32_C(7) << 28)	//< SPI6 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_PCLK4	(UINT32_C(0) << 28)	//< rcc_pclk4
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_PLL2	(UINT32_C(1) << 28)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_PLL3	(UINT32_C(2) << 28)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_HSI	(UINT32_C(3) << 28)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_CSI	(UINT32_C(4) << 28)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_HSE	(UINT32_C(5) << 28)	//< hse_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_SPI6SEL_I2S	(UINT32_C(6) << 28)	//< I2S_CKIN
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_DFSDM2SEL		(UINT32_C(1) << 27)	//< DFSDM2 kernel Clk clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_RSV18		(UINT32_C(0x1FF) << 18)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_ADCSEL		(UINT32_C(3) << 16)	//< SAR ADC kernel clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_ADCSEL_PLL2	(UINT32_C(0) << 16)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_ADCSEL_PLL3	(UINT32_C(1) << 16)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_ADCSEL_PER	(UINT32_C(2) << 16)	//< per_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL		(UINT32_C(7) << 13)	//< LPTIM3 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL_PCLK4	(UINT32_C(0) << 13)	//< rcc_pclk4
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL_PLL2	(UINT32_C(1) << 13)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL_PLL3	(UINT32_C(2) << 13)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL_LSE	(UINT32_C(3) << 13)	//< lse_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL_LSI	(UINT32_C(4) << 13)	//< lsi_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM3SEL_PER	(UINT32_C(5) << 13)	//< per_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL		(UINT32_C(7) << 10)	//< LPTIM2 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL_PCLK4	(UINT32_C(0) << 10)	//< rcc_pclk4
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL_PLL2	(UINT32_C(1) << 10)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL_PLL3	(UINT32_C(2) << 10)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL_LSE	(UINT32_C(3) << 10)	//< lse_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL_LSI	(UINT32_C(4) << 10)	//< lsi_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPTIM2SEL_PER	(UINT32_C(5) << 10)	//< per_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_I2C4SEL		(UINT32_C(3) << 8)	//< I2C4 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_I2C4SEL_PCLK4	(UINT32_C(0) << 8)	//< rcc_pclk4
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_I2C4SEL_PLL3	(UINT32_C(1) << 8)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_I2C4SEL_HSI	(UINT32_C(2) << 8)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_I2C4SEL_CSI	(UINT32_C(3) << 8)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_RSV3		(UINT32_C(0x1F) << 3)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL	(UINT32_C(7) << 0)	//< LPUART1 kernel clock source selection
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL_PCLK4	(UINT32_C(0) << 0)	//< rcc_pclk4
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL_PLL2	(UINT32_C(1) << 0)	//< pll2_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL_PLL3	(UINT32_C(2) << 0)	//< pll3_r_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL_HSI	(UINT32_C(3) << 0)	//< hsi_ker_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL_CSI	(UINT32_C(4) << 0)	//< csi_ker_ck
#define MCCI_STM32H7_REG_RCC_SRDCCIPR_LPUART1SEL_LSE	(UINT32_C(5) << 0)	//< lse_ck
///	@}

/// \name RCC_CIER bits
///	@{
#define MCCI_STM32H7_REG_RCC_CIER_RSV10		UINT32_C(0xFFFFFC00)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CIER_LSECSSIE	(UINT32_C(1) << 9)	//< LSE clock security system interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_PLL3RDYIE	(UINT32_C(1) << 8)	//< PLL3 ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_PLL2RDYIE	(UINT32_C(1) << 7)	//< PLL2 ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_PLL1RDYIE	(UINT32_C(1) << 6)	//< PLL1 ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_HSI48RDYIE	(UINT32_C(1) << 5)	//< HSI48 ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_CSIRDYIE	(UINT32_C(1) << 4)	//< CSI ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_HSERDYIE	(UINT32_C(1) << 3)	//< HSE ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_HSIRDYIE	(UINT32_C(1) << 2)	//< HSI ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_LSERDYIE	(UINT32_C(1) << 1)	//< LSE ready interrupt enable
#define MCCI_STM32H7_REG_RCC_CIER_LSIRDYIE	(UINT32_C(1) << 0)	//< LSI ready interrupt enable
///	@}

/// \name RCC_CIFR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CIFR_RSV11		UINT32_C(0xFFFFF800)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CIFR_HSECSSF	(UINT32_C(1) << 10)	//< LSE clock security system interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_LSECSSF	(UINT32_C(1) << 9)	//< LSE clock security system interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_PLL3RDYF	(UINT32_C(1) << 8)	//< PLL3 ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_PLL2RDYF	(UINT32_C(1) << 7)	//< PLL2 ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_PLL1RDYF	(UINT32_C(1) << 6)	//< PLL1 ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_HSI48RDYF	(UINT32_C(1) << 5)	//< HSI48 ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_CSIRDYF	(UINT32_C(1) << 4)	//< CSI ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_HSERDYF	(UINT32_C(1) << 3)	//< HSE ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_HSIRDYF	(UINT32_C(1) << 2)	//< HSI ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_LSERDYF	(UINT32_C(1) << 1)	//< LSE ready interrupt flag
#define MCCI_STM32H7_REG_RCC_CIFR_LSIRDYF	(UINT32_C(1) << 0)	//< LSI ready interrupt flag
///	@}

/// \name RCC_CICR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CICR_RSV11		UINT32_C(0xFFFFF800)	//< reserved, no change
#define MCCI_STM32H7_REG_RCC_CICR_HSECSSC	(UINT32_C(1) << 10)	//< LSE clock security system interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_LSECSSC	(UINT32_C(1) << 9)	//< LSE clock security system interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_PLL3RDYC	(UINT32_C(1) << 8)	//< PLL3 ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_PLL2RDYC	(UINT32_C(1) << 7)	//< PLL2 ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_PLL1RDYC	(UINT32_C(1) << 6)	//< PLL1 ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_HSI48RDYC	(UINT32_C(1) << 5)	//< HSI48 ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_CSIRDYC	(UINT32_C(1) << 4)	//< CSI ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_HSERDYC	(UINT32_C(1) << 3)	//< HSE ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_HSIRDYC	(UINT32_C(1) << 2)	//< HSI ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_LSERDYC	(UINT32_C(1) << 1)	//< LSE ready interrupt clear
#define MCCI_STM32H7_REG_RCC_CICR_LSIRDYC	(UINT32_C(1) << 0)	//< LSI ready interrupt clear
///	@}

/// \name RCC_BDCR bits
///	@{
#define MCCI_STM32H7_REG_RCC_BDCR_RSV17		UINT32_C(0xFFFE0000)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_BDCR_VSWRST	(UINT32_C(1) << 16)	//< VSwitch domain software reset
#define MCCI_STM32H7_REG_RCC_BDCR_RTCEN		(UINT32_C(1) << 15)	//< RTC clock enable
#define MCCI_STM32H7_REG_RCC_BDCR_RSV10		(UINT32_C(0x1F) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_BDCR_RTCSEL	(UINT32_C(3) << 8)	//< RTC clock source selection
#define MCCI_STM32H7_REG_RCC_BDCR_RTCSEL_NO	(UINT32_C(0) << 8)	//< no clock (default after Backup domain reset)
#define MCCI_STM32H7_REG_RCC_BDCR_RTCSEL_LSE	(UINT32_C(1) << 8)	//< LSE
#define MCCI_STM32H7_REG_RCC_BDCR_RTCSEL_LSI	(UINT32_C(2) << 8)	//< LSI
#define MCCI_STM32H7_REG_RCC_BDCR_RTCSEL_HSE	(UINT32_C(3) << 8)	//< HSE
#define MCCI_STM32H7_REG_RCC_BDCR_LSEEXT	(UINT32_C(1) << 7)	//< low-speed external clock type in Bypass mode
#define MCCI_STM32H7_REG_RCC_BDCR_LSECSSD	(UINT32_C(1) << 6)	//< LSE clock security system failure detection
#define MCCI_STM32H7_REG_RCC_BDCR_LSECSSON	(UINT32_C(1) << 5)	//< LSE clock security system enable
#define MCCI_STM32H7_REG_RCC_BDCR_LSEDRV	(UINT32_C(3) << 3)	//< LSE oscillator driving capability
#define MCCI_STM32H7_REG_RCC_BDCR_LSEDRV_LOWEST	(UINT32_C(0) << 3)	//< lowest drive (default after Backup domain reset)
#define MCCI_STM32H7_REG_RCC_BDCR_LSEDRV_MEDLOW	(UINT32_C(1) << 3)	//< medium-low drive
#define MCCI_STM32H7_REG_RCC_BDCR_LSEDRV_MEDHI	(UINT32_C(2) << 3)	//< medium-high drive
#define MCCI_STM32H7_REG_RCC_BDCR_LSEDRV_HIEST	(UINT32_C(3) << 3)	//< highest drive
#define MCCI_STM32H7_REG_RCC_BDCR_LSEBYP	(UINT32_C(1) << 2)	//< LSE oscillator bypass
#define MCCI_STM32H7_REG_RCC_BDCR_LSERDY	(UINT32_C(1) << 1)	//< LSE oscillator ready
#define MCCI_STM32H7_REG_RCC_BDCR_LSEON		(UINT32_C(1) << 0)	//< LSE oscillator enabled
///	@}

/// \name RCC_CSR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CSR_RSV2		UINT32_C(0xFFFFFFFC)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_CSR_LSIRDY		(UINT32_C(1) << 1)	//< LSI oscillator ready
#define MCCI_STM32H7_REG_RCC_CSR_LSION		(UINT32_C(1) << 0)	//< LSI oscillator enable
///	@}

/// \name RCC_AHB3RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV25	(UINT32_C(0x7F) << 25)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_GFXMMURST	(UINT32_C(1) << 24)	//< GFXMMU reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_OTFD2RST	(UINT32_C(1) << 23)	//< OTFD2 reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_OTFD1RST	(UINT32_C(1) << 22)	//< OTFD1 reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_OCTOSPIMRST (UINT32_C(1) << 21)	//< OCTOSPIM reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV20	(UINT32_C(1) << 20)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_OCTOSPI2RST (UINT32_C(1) << 19)	//< OCTOSPI2 and OCTOSPI2 delay block reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV17	(UINT32_C(3) << 17)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_SDMMC1RST	(UINT32_C(1) << 16)	//< SDMMC1 and SDMMC1 delay blocks reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV15	(UINT32_C(1) << 15)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_OCTOSPI1RST (UINT32_C(1) << 14)	//< OCTOSPI1 and OCTOSPI1 delay blocks reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV13	(UINT32_C(1) << 13)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_FMCRST	(UINT32_C(1) << 12)	//< FMC block reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV6	(UINT32_C(0x3F) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_JPGDECRST	(UINT32_C(1) << 5)	//< JPGDEC block reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_DMA2DRST	(UINT32_C(1) << 4)	//< DMA2D block reset
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_RSV1	(UINT32_C(7) << 1)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3RSTR_MDMARST	(UINT32_C(1) << 0)	//< MDMA block reset
///	@}

/// \name RCC_AHB1RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_RSV26	(UINT32_C(0x3F) << 26)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_USB1OTGRST (UINT32_C(1) << 25)	//< USB1OTG block reset
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_RSV10	(UINT32_C(0x7FFF) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_CRCRST	(UINT32_C(1) << 9)	//< CRC block reset
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_RSV6	(UINT32_C(7) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_ADC12RST	(UINT32_C(1) << 5)	//< ADC1 and 2 blocks reset
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_RSV2	(UINT32_C(7) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_DMA2RST	(UINT32_C(1) << 1)	//< DMA2 and DMAMUX2 blocks reset
#define MCCI_STM32H7_REG_RCC_AHB1RSTR_DMA1RST	(UINT32_C(1) << 0)	//< DMA1 and DMAMUX1 blocks reset
///	@}

/// \name RCC_AHB2RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_RSV12	UINT32_C(0xFFFFF000)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_BDMA1RST	(UINT32_C(1) << 11)	//< BDMA1 reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_RSV10	(UINT32_C(1) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_SDMMC2RST	(UINT32_C(1) << 9)	//< SDMMC2 and SDMMC2 delay blocks reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_RSV7	(UINT32_C(3) << 7)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_RNGRST	(UINT32_C(1) << 6)	//< random number generator block reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_HASHRST	(UINT32_C(1) << 5)	//< hash block reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_CRYPTRST	(UINT32_C(1) << 4)	//< cryptography block reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_RSV3	(UINT32_C(1) << 3)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_HSEMRST	(UINT32_C(1) << 2)	//< HSEM block reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_RSV1	(UINT32_C(1) << 1)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_DCMIRST	(UINT32_C(1) << 0)	//< digital camera interface block reset
#define MCCI_STM32H7_REG_RCC_AHB2RSTR_PSSIRST	(UINT32_C(1) << 0)	//< PSSI block reset
///	@}

/// \name RCC_AHB4RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_RSV22	UINT32_C(0xFFC00000)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_BDMA2RST	(UINT32_C(1) << 21)	//< SmartRun domain DMA and DMAMUX blocks reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_RSV11	(UINT32_C(0x3FF) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOKRST	(UINT32_C(1) << 10)	//< GPIOK block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOJRST	(UINT32_C(1) << 9)	//< GPIOJ block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOIRST	(UINT32_C(1) << 8)	//< GPIOI block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOHRST	(UINT32_C(1) << 7)	//< GPIOH block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOGRST	(UINT32_C(1) << 6)	//< GPIOG block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOFRST	(UINT32_C(1) << 5)	//< GPIOF block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOERST	(UINT32_C(1) << 4)	//< GPIOE block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIODRST	(UINT32_C(1) << 3)	//< GPIOD block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOCRST	(UINT32_C(1) << 2)	//< GPIOC block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOBRST	(UINT32_C(1) << 1)	//< GPIOB block reset
#define MCCI_STM32H7_REG_RCC_AHB4RSTR_GPIOARST	(UINT32_C(1) << 0)	//< GPIOA block reset
///	@}

/// \name RCC_APB3RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB3RSTR_RSV4	UINT32_C(0xFFFFFFF0)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB3RSTR_LTDCRST	(UINT32_C(1) << 3)	///< LTDCRST block reset
#define MCCI_STM32H7_REG_RCC_APB3RSTR_RSV0	(UINT32_C(7) << 0)	///< reserved, don't change
///	@}

/// \name RCC_APB1LRSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_UART8RST		(UINT32_C(1) << 31)	//< UART8 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_UART7RST		(UINT32_C(1) << 30)	//< UART7 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_DAC1RST		(UINT32_C(1) << 29)	//< DAC1 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_RSV28		(UINT32_C(1) << 28)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_CECRST		(UINT32_C(1) << 27)	//< CEC reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_RSV24		(UINT32_C(7) << 24)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_I2C3RST		(UINT32_C(1) << 23)	//< I2C3 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_I2C2RST		(UINT32_C(1) << 22)	//< I2C2 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_I2C1RST		(UINT32_C(1) << 21)	//< I2C1 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_USART5RST	(UINT32_C(1) << 20)	//< USART5 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_USART4RST	(UINT32_C(1) << 19)	//< USART4 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_USART3RST	(UINT32_C(1) << 18)	//< USART3 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_USART2RST	(UINT32_C(1) << 17)	//< USART2 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_SPDIFRXRST	(UINT32_C(1) << 16)	//< SPDIFRX reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_SPI3RST		(UINT32_C(1) << 15)	//< SPI3 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_SPI2RST		(UINT32_C(1) << 14)	//< SPI2 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_RSV10		(UINT32_C(0xF) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_LPTIM1RST	(UINT32_C(1) << 9)	//< LPTIM1 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM14RST		(UINT32_C(1) << 8)	//< TIM14 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM13RST		(UINT32_C(1) << 7)	//< TIM13 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM12RST		(UINT32_C(1) << 6)	//< TIM12 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM7RST		(UINT32_C(1) << 5)	//< TIM7 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM6RST		(UINT32_C(1) << 4)	//< TIM6 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM5RST		(UINT32_C(1) << 3)	//< TIM5 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM4RST		(UINT32_C(1) << 2)	//< TIM4 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM3RST		(UINT32_C(1) << 1)	//< TIM3 reset
#define MCCI_STM32H7_REG_RCC_APB1LRSTR_TIM2RST		(UINT32_C(1) << 0)	//< TIM2 reset
///	@}

/// \name RCC_APB1HRSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_RSV9		UINT32_C(0xFFFFFE00)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_FDCANRST		(UINT32_C(1) << 8)	//< FDCAN reset
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_RSV6		(UINT32_C(3) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_MDIOSRST		(UINT32_C(1) << 5)	//< MDIOS reset
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_OPAMPRST		(UINT32_C(1) << 4)	//< OPAMP reset
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_RSV3		(UINT32_C(1) << 3)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_SWPMIRST		(UINT32_C(1) << 2)	//< SWPMI reset
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_CRSRST		(UINT32_C(1) << 1)	//< CRS reset
#define MCCI_STM32H7_REG_RCC_APB1HRSTR_RSV0		(UINT32_C(1) << 0)	//< reserved, don't change
///	@}

/// \name RCC_APB2RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV31		(UINT32_C(1) << 31)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_DFSDM1RST		(UINT32_C(1) << 30)	///< DFSDM1 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV24		(UINT32_C(0x3F) << 24)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_SAI2RST		(UINT32_C(1) << 23)	///< SAI2 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_SAI1RST		(UINT32_C(1) << 22)	///< SAI1 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV21		(UINT32_C(1) << 21)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_SPI5RST		(UINT32_C(1) << 20)	///< SPI5 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV19		(UINT32_C(1) << 19)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_TIM17RST		(UINT32_C(1) << 18)	///< TIM17 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_TIM16RST		(UINT32_C(1) << 17)	///< TIM16 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_TIM15RST		(UINT32_C(1) << 16)	///< TIM15 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV14		(UINT32_C(3) << 14)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_SPI4RST		(UINT32_C(1) << 13)	///< SPI4 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_SPI1RST		(UINT32_C(1) << 12)	///< SPI1 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV8		(UINT32_C(0xF) << 8)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_USART10RST	(UINT32_C(1) << 7)	///< USART10 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_UART9RST		(UINT32_C(1) << 6)	///< UART9 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_USART6RST		(UINT32_C(1) << 5)	///< USART6 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_USART1RST		(UINT32_C(1) << 4)	///< USART1 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_RSV2		(UINT32_C(3) << 2)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2RSTR_TIM8RST		(UINT32_C(1) << 1)	///< TIM8 reset
#define MCCI_STM32H7_REG_RCC_APB2RSTR_TIM1RST		(UINT32_C(1) << 0)	///< TIM1 reset
///	@}

/// \name RCC_APB4RSTR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV28		(UINT32_C(0xF) << 28)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_DFSDM2RST		(UINT32_C(1) << 27)	//< DFSDM2 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_DTSRST		(UINT32_C(1) << 26)	//< DTS reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV16		(UINT32_C(0x3FF) << 16)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_VREFRST		(UINT32_C(1) << 15)	//< VREF reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_COMP12RST		(UINT32_C(1) << 14)	//< COMP12 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_DAC2RST		(UINT32_C(1) << 13)	//< DAC2 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV11		(UINT32_C(3) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_LPTIM3RST		(UINT32_C(1) << 10)	//< LPTIM3 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_LPTIM2RST		(UINT32_C(1) << 9)	//< LPTIM2 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV8		(UINT32_C(1) << 8)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_I2C4RST		(UINT32_C(1) << 7)	//< I2C4 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV6		(UINT32_C(1) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_SPI6RST		(UINT32_C(1) << 5)	//< SPI6 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV4		(UINT32_C(1) << 4)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_LPUART1RST	(UINT32_C(1) << 3)	//< LPUART1 reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV2		(UINT32_C(1) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4RSTR_SYSCFGRST		(UINT32_C(1) << 1)	//< SYSCFG reset
#define MCCI_STM32H7_REG_RCC_APB4RSTR_RSV0		(UINT32_C(1) << 0)	//< reserved, don't change
///	@}

/// \name RCC_SRDAMR bits
///	@{
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV25	(UINT32_C(3) << 30)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_SRDSRAMAMEN	(UINT32_C(1) << 29)	//< SmartRun domain SRAM Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_BKPRAMAMEN	(UINT32_C(1) << 28)	//< Backup RAM Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_DFSDM2AMEN	(UINT32_C(1) << 27)	//< DFSDM2 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_DTSAMEN	(UINT32_C(1) << 26)	//< Digital temperature sensor Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV17	(UINT32_C(0x1FF) << 17)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_RTCAMEN	(UINT32_C(1) << 16)	//< RTC Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_VREFAMEN	(UINT32_C(1) << 15)	//< VREF Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_COMP12AMEN	(UINT32_C(1) << 14)	//< COMP1 and 2 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_DAC2AMEN	(UINT32_C(1) << 13)	//< DAC2 (containing one converter) Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV11	(UINT32_C(3) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_LPTIM3AMEN	(UINT32_C(1) << 10)	//< LPTIM3 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_LPTIM2AMEN	(UINT32_C(1) << 9)	//< LPTIM2 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV8	(UINT32_C(7) << 8)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_I2C4AMEN	(UINT32_C(1) << 7)	//< I2C4 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV6	(UINT32_C(1) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_SPI6AMEN	(UINT32_C(1) << 5)	//< SPI6 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV4	(UINT32_C(1) << 4)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_LPUART1AMEN	(UINT32_C(1) << 3)	//< LPUART1 Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_RSV2	(UINT32_C(1) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_SRDAMR_GPIOAMEN	(UINT32_C(1) << 1)	//< GPIO Autonomous mode enable
#define MCCI_STM32H7_REG_RCC_SRDAMR_BDMA2AMEN	(UINT32_C(1) << 0)	//< SmartRun domain DMA and DMAMUX Autonomous mode enable
///	@}

/// \name RCC_CKGAENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_CKGAENR_JTAGCKG	(UINT32_C(1) << 31)	//< JTAG automatic clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_EXTICKG	(UINT32_C(1) << 30)	//< EXTI clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_ECCRAMCKG	(UINT32_C(1) << 29)	//< RAM error code correction (ECC) clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_RSV18	UINT32_C(0x1FFC0000)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_CKGAENR_GFXMMUSCKG	(UINT32_C(1) << 17)	//< AXI matrix slave GFXMMU clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AXIRAM3CKG	(UINT32_C(1) << 16)	//< AXI matrix slave SRAM3 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AXIRAM2CKG	(UINT32_C(1) << 15)	//< AXI matrix slave SRAM2 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AXIRAM1CKG	(UINT32_C(1) << 14)	//< AXI slave SRAM1 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_OCTOSPI1CKG (UINT32_C(1) << 13)	//< AXI slave OCTOSPI1 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_FMCCKG	(UINT32_C(1) << 12)	//< AXI slave FMC clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_OCTOSPI2CKG (UINT32_C(1) << 11)	//< AXI slave OCTOSPI2 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_FLIFTCKG	(UINT32_C(1) << 10)	//< AXI slave Flash interface (FLIFT) clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AHB34CKG	(UINT32_C(1) << 9)	//< AXI slave AHB34 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AHB12CKG	(UINT32_C(1) << 8)	//< AXI slave AHB12 clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_GFXMMUMCKG	(UINT32_C(1) << 7)	//< AXI master GFXMMU clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_LTDCCKG	(UINT32_C(1) << 6)	//< AXI master LTDC clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_DMA2DCKG	(UINT32_C(1) << 5)	//< AXI master DMA2D clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_MDMACKG	(UINT32_C(1) << 4)	//< AXI master MDMA clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_SDMMCCKG	(UINT32_C(1) << 3)	//< AXI master SDMMC clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_CPUCKG	(UINT32_C(1) << 2)	//< AXI master CPU clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AHBCKG	(UINT32_C(1) << 1)	//< AXI master AHB clock gating
#define MCCI_STM32H7_REG_RCC_CKGAENR_AXICKG	(UINT32_C(1) << 0)	//< AXI interconnect matrix clock gating
///	@}

/// \name RCC_RSR bits
///	@{
#define MCCI_STM32H7_REG_RCC_RSR_RSV31		(UINT32_C(1) << 31)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_RSR_LPWRRSTF	(UINT32_C(1) << 30)	//< reset due to illegal CD DStop or CD DStop2 or CPU CStop flag
#define MCCI_STM32H7_REG_RCC_RSR_RSV29		(UINT32_C(1) << 29)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_RSR_WWDGRSTF	(UINT32_C(1) << 28)	//< window watchdog reset flag
#define MCCI_STM32H7_REG_RCC_RSR_RSV27		(UINT32_C(1) << 27)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_RSR_IWDGRSTF	(UINT32_C(1) << 26)	//< independent watchdog reset flag
#define MCCI_STM32H7_REG_RCC_RSR_RSV25		(UINT32_C(1) << 25)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_RSR_SFTRSTF	(UINT32_C(1) << 24)	//< system reset from CPU reset flag
#define MCCI_STM32H7_REG_RCC_RSR_PORRSTF	(UINT32_C(1) << 23)	//< POR/PDR reset flag
#define MCCI_STM32H7_REG_RCC_RSR_PINRSTF	(UINT32_C(1) << 22)	//< pin reset flag (NRST)
#define MCCI_STM32H7_REG_RCC_RSR_BORRSTF	(UINT32_C(1) << 21)	//< BOR reset flag
#define MCCI_STM32H7_REG_RCC_RSR_RSV20		(UINT32_C(1) << 20)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_RSR_CDRSTF		(UINT32_C(1) << 19)	//< CPU domain power-switch reset flag
#define MCCI_STM32H7_REG_RCC_RSR_RSV18		(UINT32_C(3) << 18)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_RSR_RMVF		(UINT32_C(1) << 16)	//< remove reset flag
#define MCCI_STM32H7_REG_RCC_RSR_RSV0		UINT32_C(0x0000FFFF)	//< reserved, don't change
///	@}

/// \name RCC_AHB3ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV25	(UINT32_C(0x7F) << 25)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_GFXMMUEN	(UINT32_C(1) << 24)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_OTFD2EN	(UINT32_C(1) << 23)	//< OTFD2 clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_OTFD1EN	(UINT32_C(1) << 22)	//< OTFD1 clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_OCTOSPIMEN	(UINT32_C(1) << 21)	//< OCTOSPIM clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV20	(UINT32_C(1) << 20)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_OCTOSPI2EN	(UINT32_C(1) << 19)	//< OCTOSPI2 clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV17	(UINT32_C(3) << 17)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_SDMMC1EN	(UINT32_C(1) << 16)	//< SDMMC1 and SDMMC1 delay clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV15	(UINT32_C(1) << 15)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_OCTOSPI1EN	(UINT32_C(1) << 14)	//< OCTOSPI1 and OCTOSPI1 delay clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV13	(UINT32_C(1) << 13)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_FMCEN	(UINT32_C(1) << 12)	//< FMC peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV6	(UINT32_C(0x3F) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_JPGDECEN	(UINT32_C(1) << 5)	//< JPGDEC peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_DMA2DEN	(UINT32_C(1) << 4)	//< DMA2D peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB3ENR_RSV1	(UINT32_C(7) << 1)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3ENR_MDMAEN	(UINT32_C(1) << 0)	//< MDMA peripheral clock enable
///	@}

/// \name RCC_AHB1ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB1ENR_RSV27	(UINT32_C(0x1F) << 27)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1ENR_USB1ULPIEN	(UINT32_C(1) << 26)	//< USB_PHY1 clocks enable
#define MCCI_STM32H7_REG_RCC_AHB1ENR_USB1OTGEN	(UINT32_C(1) << 25)	//< USB1OTG peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB1ENR_RSV10	(UINT32_C(0x7FFF) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1ENR_CRCEN	(UINT32_C(1) << 9)	//< CRC peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB1ENR_RSV6	(UINT32_C(7) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1ENR_ADC12EN	(UINT32_C(1) << 5)	//< ADC1 and 2 peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB1ENR_RSV2	(UINT32_C(7) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1ENR_DMA2EN	(UINT32_C(1) << 1)	//< DMA2 clock enable
#define MCCI_STM32H7_REG_RCC_AHB1ENR_DMA1EN	(UINT32_C(1) << 0)	//< DMA1 clock enable
///	@}

/// \name RCC_AHB2ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RSV31	(UINT32_C(1) << 31)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2ENR_AHBSRAM2EN	(UINT32_C(1) << 30)	//< AHBSRAM2 block enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_AHBSRAM1EN	(UINT32_C(1) << 29)	//< AHBSRAM1 block enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RSV12	(UINT32_C(0x1FFFF) << 12) //< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2ENR_BDMA1EN	(UINT32_C(1) << 11)	//< DMA clock enable (DFSDM dedicated DMA)
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RSV10	(UINT32_C(1) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2ENR_SDMMC2EN	(UINT32_C(1) << 9)	//< SDMMC2 and SDMMC2 delay clock enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RSV7	(UINT32_C(3) << 7)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RNGEN	(UINT32_C(1) << 6)	//< RNG peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_HASHEN	(UINT32_C(1) << 5)	//< HASH peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_CRYPTEN	(UINT32_C(1) << 4)	//< CRYPT peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RSV3	(UINT32_C(1) << 3)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2ENR_HSEMEN	(UINT32_C(1) << 2)	//< HSEM peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_RSV1	(UINT32_C(1) << 1)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2ENR_DCMIEN	(UINT32_C(1) << 0)	//< digital camera interface peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2ENR_PSSIEN	(UINT32_C(1) << 0)	//< PSSI peripheral clock enable
///	@}

/// \name RCC_AHB4ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB4ENR_RSV30	(UINT32_C(3) << 30)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4ENR_SRDSRAMEN	(UINT32_C(1) << 29)	//< SRDSRAM enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_BKPRAMEN	(UINT32_C(1) << 28)	//< BKPRAM enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_RSV22	(UINT32_C(0x3F) << 22)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4ENR_BDMA2EN	(UINT32_C(1) << 21)	//< BDMA2 enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_RSV11	(UINT32_C(0x3FF) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOKEN	(UINT32_C(1) << 10)	//< GPIOK enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOJEN	(UINT32_C(1) << 9)	//< GPIOJ enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOIEN	(UINT32_C(1) << 8)	//< GPIOI enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOHEN	(UINT32_C(1) << 7)	//< GPIOH enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOGEN	(UINT32_C(1) << 6)	//< GPIOG enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOFEN	(UINT32_C(1) << 5)	//< GPIOF enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOEEN	(UINT32_C(1) << 4)	//< GPIOE enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIODEN	(UINT32_C(1) << 3)	//< GPIOD enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOCEN	(UINT32_C(1) << 2)	//< GPIOC enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOBEN	(UINT32_C(1) << 1)	//< GPIOB enable
#define MCCI_STM32H7_REG_RCC_AHB4ENR_GPIOAEN	(UINT32_C(1) << 0)	//< GPIOA enable
///	@}

/// \name RCC_APB3ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB3ENR_RSV7	UINT32_C(0xFFFFFF80)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB3ENR_WWDGEN	(UINT32_C(1) << 26)	//< WWDG enable
#define MCCI_STM32H7_REG_RCC_APB3ENR_RSV4	(UINT32_C(3) << 4)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB3ENR_LTDCEN	(UINT32_C(1) << 25)	//< LTDC enable
#define MCCI_STM32H7_REG_RCC_APB3ENR_RSV0	(UINT32_C(7) << 0)	//< reserved, don't change
///	@}

/// \name RCC_APB1LENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB1LENR_UART8EN	(UINT32_C(1) << 31)	//< UART8 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_UART7EN	(UINT32_C(1) << 30)	//< UART7 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_DAC1EN	(UINT32_C(1) << 29)	//< DAC1 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_RSV28	(UINT32_C(1) << 28)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LENR_CECEN	(UINT32_C(1) << 27)	//< CEC clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_RSV24	(UINT32_C(7) << 24)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LENR_I2C3EN	(UINT32_C(1) << 23)	//< I2C3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_I2C2EN	(UINT32_C(1) << 22)	//< I2C2 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_I2C1EN	(UINT32_C(1) << 21)	//< I2C1 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_USART5EN	(UINT32_C(1) << 20)	//< USART5 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_USART4EN	(UINT32_C(1) << 19)	//< USART4 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_USART3EN	(UINT32_C(1) << 18)	//< USART3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_USART2EN	(UINT32_C(1) << 17)	//< USART2 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_SPDIFRXEN	(UINT32_C(1) << 16)	//< SPDIFRX clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_SPI3EN	(UINT32_C(1) << 15)	//< SPI3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_SPI2EN	(UINT32_C(1) << 14)	//< SPI2 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_RSV10	(UINT32_C(0xF) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LENR_LPTIM1EN	(UINT32_C(1) << 9)	//< LPTIM1 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM14EN	(UINT32_C(1) << 8)	//< TIM14 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM13EN	(UINT32_C(1) << 7)	//< TIM13 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM12EN	(UINT32_C(1) << 6)	//< TIM12 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM7EN	(UINT32_C(1) << 5)	//< TIM7 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM6EN	(UINT32_C(1) << 4)	//< TIM6 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM5EN	(UINT32_C(1) << 3)	//< TIM5 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM4EN	(UINT32_C(1) << 2)	//< TIM4 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM3EN	(UINT32_C(1) << 1)	//< TIM3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LENR_TIM2EN	(UINT32_C(1) << 0)	//< TIM2 clock enable
///	@}

/// \name RCC_APB1HENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB1HENR_RSV9	UINT32_C(0xFFFFFE00)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HENR_FDCANEN	(UINT32_C(1) << 8)	//< FDCAN clock enable
#define MCCI_STM32H7_REG_RCC_APB1HENR_RSV6	(UINT32_C(3) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HENR_MDIOSEN	(UINT32_C(1) << 5)	//< MDIOS clock enable
#define MCCI_STM32H7_REG_RCC_APB1HENR_OPAMPEN	(UINT32_C(1) << 4)	//< OPAMP clock enable
#define MCCI_STM32H7_REG_RCC_APB1HENR_RSV3	(UINT32_C(1) << 3)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HENR_SWPMIEN	(UINT32_C(1) << 2)	//< SWPMI clock enable
#define MCCI_STM32H7_REG_RCC_APB1HENR_CRSEN	(UINT32_C(1) << 1)	//< CRS clock enable
#define MCCI_STM32H7_REG_RCC_APB1HENR_RSV0	(UINT32_C(1) << 0)	//< reserved, don't change
///	@}

/// \name RCC_APB2ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV31	(UINT32_C(1) << 31)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_DFSDM1EN	(UINT32_C(1) << 30)	///< DFSDM1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV24	(UINT32_C(0x3F) << 24)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_SAI2EN	(UINT32_C(1) << 23)	///< SAI2 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_SAI1EN	(UINT32_C(1) << 22)	///< SAI1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV21	(UINT32_C(1) << 21)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_SPI5EN	(UINT32_C(1) << 20)	///< SPI5 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV19	(UINT32_C(1) << 19)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_TIM17EN	(UINT32_C(1) << 18)	///< TIM17 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_TIM16EN	(UINT32_C(1) << 17)	///< TIM16 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_TIM15EN	(UINT32_C(1) << 16)	///< TIM15 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV14	(UINT32_C(3) << 14)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_SPI4EN	(UINT32_C(1) << 13)	///< SPI4 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_SPI1EN	(UINT32_C(1) << 12)	///< SPI1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV8	(UINT32_C(0xF) << 8)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_USART10EN	(UINT32_C(1) << 7)	///< USART10 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_UART9EN	(UINT32_C(1) << 6)	///< UART9 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_USART6EN	(UINT32_C(1) << 5)	///< USART6 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_USART1EN	(UINT32_C(1) << 4)	///< USART1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_RSV2	(UINT32_C(3) << 2)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2ENR_TIM8EN	(UINT32_C(1) << 1)	///< TIM8 clock enable
#define MCCI_STM32H7_REG_RCC_APB2ENR_TIM1EN	(UINT32_C(1) << 0)	///< TIM1 clock enable
///	@}

/// \name RCC_APB4ENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV28	(UINT32_C(0xF) << 28)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_DFSDM2EN	(UINT32_C(1) << 27)	//< DFSDM2 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_DTSEN	(UINT32_C(1) << 26)	//< DTS clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV17	(UINT32_C(0x1FF) << 17)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_RTCAPBEN	(UINT32_C(1) << 16)	//< RTCAPB clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_VREFEN	(UINT32_C(1) << 15)	//< VREF clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_COMP12EN	(UINT32_C(1) << 14)	//< COMP12 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_DAC2EN	(UINT32_C(1) << 13)	//< DAC2 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV11	(UINT32_C(3) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_LPTIM3EN	(UINT32_C(1) << 10)	//< LPTIM3 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_LPTIM2EN	(UINT32_C(1) << 9)	//< LPTIM2 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV8	(UINT32_C(1) << 8)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_I2C4EN	(UINT32_C(1) << 7)	//< I2C4 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV6	(UINT32_C(1) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_SPI6EN	(UINT32_C(1) << 5)	//< SPI6 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV4	(UINT32_C(1) << 4)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_LPUART1EN	(UINT32_C(1) << 3)	//< LPUART1 clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV2	(UINT32_C(1) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4ENR_SYSCFGEN	(UINT32_C(1) << 1)	//< SYSCFG clock enable
#define MCCI_STM32H7_REG_RCC_APB4ENR_RSV0	(UINT32_C(1) << 0)	//< reserved, don't change
///	@}

/// \name RCC_AHB3LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_AXISRAM1LPEN	(UINT32_C(1) << 31)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_ITCMLPEN		(UINT32_C(1) << 30)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_DTCM2LPEN	(UINT32_C(1) << 29)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_DTCM1LPEN	(UINT32_C(1) << 28)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_AXISRAM3LPEN	(UINT32_C(1) << 27)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_AXISRAM2LPEN	(UINT32_C(1) << 26)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV25		(UINT32_C(1) << 25)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_GFXMMULPEN	(UINT32_C(1) << 24)	//< GFXMMU clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_OTFD2LPEN	(UINT32_C(1) << 23)	//< OTFD2 clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_OTFD1LPEN	(UINT32_C(1) << 22)	//< OTFD1 clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_OCTOSPIMLPEN	(UINT32_C(1) << 21)	//< OCTOSPIM clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV20		(UINT32_C(1) << 20)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_OCTOSPI2LPEN	(UINT32_C(1) << 19)	//< OCTOSPI2 clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV17		(UINT32_C(3) << 17)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_SDMMC1LPEN	(UINT32_C(1) << 16)	//< SDMMC1 and SDMMC1 delay clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV15		(UINT32_C(1) << 15)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_OCTOSPI1LPEN	(UINT32_C(1) << 14)	//< OCTOSPI1 and OCTOSPI1 delay clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV13		(UINT32_C(1) << 13)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_FMCLPEN		(UINT32_C(1) << 12)	//< FMC peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV9		(UINT32_C(7) << 9)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_FLITFLPEN	(UINT32_C(1) << 8)	//< FLITF peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV6		(UINT32_C(3) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_JPGDECLPEN	(UINT32_C(1) << 5)	//< JPGDEC peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_DMA2DLPEN	(UINT32_C(1) << 4)	//< DMA2D peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_RSV1		(UINT32_C(7) << 1)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB3LPENR_MDMALPEN		(UINT32_C(1) << 0)	//< MDMA peripheral clock enable
///	@}

/// \name RCC_AHB1LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_RSV27		(UINT32_C(0x1F) << 27)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_USB1ULPILPEN	(UINT32_C(1) << 26)	//< USB_PHY1 clocks enable
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_USB1OTGLPEN	(UINT32_C(1) << 25)	//< USB1OTG peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_RSV10		(UINT32_C(0x7FFF) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_CRCLPEN		(UINT32_C(1) << 9)	//< CRC peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_RSV6		(UINT32_C(7) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_ADC12LPEN	(UINT32_C(1) << 5)	//< ADC1 and 2 peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_RSV2		(UINT32_C(7) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_DMA2LPEN		(UINT32_C(1) << 1)	//< DMA2 clock enable
#define MCCI_STM32H7_REG_RCC_AHB1LPENR_DMA1LPEN		(UINT32_C(1) << 0)	//< DMA1 clock enable
///	@}

/// \name RCC_AHB2LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_RSV31		(UINT32_C(1) << 31)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_AHBSRAM2LPEN	(UINT32_C(1) << 30)	//< AHBSRAM2 block enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_AHBSRAM1LPEN	(UINT32_C(1) << 29)	//< AHBSRAM1 block enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_RSV12		(UINT32_C(0x1FFFF) << 12) //< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_DFSDMDMALPEN	(UINT32_C(1) << 11)	//< DMA clock enable (DFSDM dedicated DMA)
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_RSV10		(UINT32_C(1) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_SDMMC2LPEN	(UINT32_C(1) << 9)	//< SDMMC2 and SDMMC2 delay clock enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_RSV7		(UINT32_C(3) << 7)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_RNGLPEN		(UINT32_C(1) << 6)	//< RNG peripheral clocks enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_HASHLPEN		(UINT32_C(1) << 5)	//< HASH peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_CRYPTLPEN	(UINT32_C(1) << 4)	//< CRYPT peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_RSV1		(UINT32_C(7) << 1)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_DCMILPEN		(UINT32_C(1) << 0)	//< digital camera interface peripheral clock enable
#define MCCI_STM32H7_REG_RCC_AHB2LPENR_PSSILPEN		(UINT32_C(1) << 0)	//< PSSI peripheral clock enable
///	@}

/// \name RCC_AHB4LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_RSV30		(UINT32_C(3) << 30)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_SRDSRAMLPEN	(UINT32_C(1) << 29)	//< SRDSRAM enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_BKPRAMLPEN	(UINT32_C(1) << 28)	//< BKPRAM enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_RSV22		(UINT32_C(0x3F) << 22)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_BDMA2LPEN	(UINT32_C(1) << 21)	//< BDMA2 enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_RSV11		(UINT32_C(0x3FF) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOKLPEN	(UINT32_C(1) << 10)	//< GPIOK enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOJLPEN	(UINT32_C(1) << 9)	//< GPIOJ enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOILPEN	(UINT32_C(1) << 8)	//< GPIOI enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOHLPEN	(UINT32_C(1) << 7)	//< GPIOH enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOGLPEN	(UINT32_C(1) << 6)	//< GPIOG enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOFLPEN	(UINT32_C(1) << 5)	//< GPIOF enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOELPEN	(UINT32_C(1) << 4)	//< GPIOE enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIODLPEN	(UINT32_C(1) << 3)	//< GPIOD enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOCLPEN	(UINT32_C(1) << 2)	//< GPIOC enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOBLPEN	(UINT32_C(1) << 1)	//< GPIOB enable
#define MCCI_STM32H7_REG_RCC_AHB4LPENR_GPIOALPEN	(UINT32_C(1) << 0)	//< GPIOA enable
///	@}

/// \name RCC_APB3LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB3LPENR_RSV7	UINT32_C(0xFFFFFF80)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB3LPENR_WWDGLPEN	(UINT32_C(1) << 26)	//< WWDG enable
#define MCCI_STM32H7_REG_RCC_APB3LPENR_RSV4	(UINT32_C(3) << 4)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB3LPENR_LTDCLPEN	(UINT32_C(1) << 25)	//< LTDC enable
#define MCCI_STM32H7_REG_RCC_APB3LPENR_RSV0	(UINT32_C(7) << 0)	//< reserved, don't change
///	@}

/// \name RCC_APB1LLPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_UART8LPEN	(UINT32_C(1) << 31)	//< UART8 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_UART7LPEN	(UINT32_C(1) << 30)	//< UART7 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_DAC1LPEN	(UINT32_C(1) << 29)	//< DAC1 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_RSV28		(UINT32_C(1) << 28)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_CECLPEN		(UINT32_C(1) << 27)	//< CEC clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_RSV24		(UINT32_C(7) << 24)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_I2C3LPEN	(UINT32_C(1) << 23)	//< I2C3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_I2C2LPEN	(UINT32_C(1) << 22)	//< I2C2 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_I2C1LPEN	(UINT32_C(1) << 21)	//< I2C1 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_USART5LPEN	(UINT32_C(1) << 20)	//< USART5 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_USART4LPEN	(UINT32_C(1) << 19)	//< USART4 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_USART3LPEN	(UINT32_C(1) << 18)	//< USART3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_USART2LPEN	(UINT32_C(1) << 17)	//< USART2 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_SPDIFRXLPEN	(UINT32_C(1) << 16)	//< SPDIFRX clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_SPI3LPEN	(UINT32_C(1) << 15)	//< SPI3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_SPI2LPEN	(UINT32_C(1) << 14)	//< SPI2 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_RSV10		(UINT32_C(0xF) << 10)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_LPTIM1LPEN	(UINT32_C(1) << 9)	//< LPTIM1 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM14LPEN	(UINT32_C(1) << 8)	//< TIM14 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM13LPEN	(UINT32_C(1) << 7)	//< TIM13 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM12LPEN	(UINT32_C(1) << 6)	//< TIM12 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM7LPEN	(UINT32_C(1) << 5)	//< TIM7 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM6LPEN	(UINT32_C(1) << 4)	//< TIM6 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM5LPEN	(UINT32_C(1) << 3)	//< TIM5 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM4LPEN	(UINT32_C(1) << 2)	//< TIM4 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM3LPEN	(UINT32_C(1) << 1)	//< TIM3 clock enable
#define MCCI_STM32H7_REG_RCC_APB1LLPENR_TIM2LPEN	(UINT32_C(1) << 0)	//< TIM2 clock enable
///	@}

/// \name RCC_APB1HLPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_RSV9		UINT32_C(0xFFFFFE00)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_FDCANLPEN	(UINT32_C(1) << 8)	//< FDCAN clock enable
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_RSV6		(UINT32_C(3) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_MDIOSLPEN	(UINT32_C(1) << 5)	//< MDIOS clock enable
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_OPAMPLPEN	(UINT32_C(1) << 4)	//< OPAMP clock enable
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_RSV3		(UINT32_C(1) << 3)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_SWPMILPEN	(UINT32_C(1) << 2)	//< SWPMI clock enable
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_CRSLPEN		(UINT32_C(1) << 1)	//< CRS clock enable
#define MCCI_STM32H7_REG_RCC_APB1HLPENR_RSV0		(UINT32_C(1) << 0)	//< reserved, don't change
///	@}

/// \name RCC_APB2LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV31		(UINT32_C(1) << 31)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_DFSDM1LPEN	(UINT32_C(1) << 30)	///< DFSDM1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV24		(UINT32_C(0x3F) << 24)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_SAI2LPEN		(UINT32_C(1) << 23)	///< SAI2 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_SAI1LPEN		(UINT32_C(1) << 22)	///< SAI1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV21		(UINT32_C(1) << 21)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_SPI5LPEN		(UINT32_C(1) << 20)	///< SPI5 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV19		(UINT32_C(1) << 19)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_TIM17LPEN	(UINT32_C(1) << 18)	///< TIM17 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_TIM16LPEN	(UINT32_C(1) << 17)	///< TIM16 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_TIM15LPEN	(UINT32_C(1) << 16)	///< TIM15 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV14		(UINT32_C(3) << 14)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_SPI4LPEN		(UINT32_C(1) << 13)	///< SPI4 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_SPI1LPEN		(UINT32_C(1) << 12)	///< SPI1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV8		(UINT32_C(0xF) << 8)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_USART10LPEN	(UINT32_C(1) << 7)	///< USART10 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_UART9LPEN	(UINT32_C(1) << 6)	///< UART9 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_USART6LPEN	(UINT32_C(1) << 5)	///< USART6 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_USART1LPEN	(UINT32_C(1) << 4)	///< USART1 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_RSV2		(UINT32_C(3) << 2)	///< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB2LPENR_TIM8LPEN		(UINT32_C(1) << 1)	///< TIM8 clock enable
#define MCCI_STM32H7_REG_RCC_APB2LPENR_TIM1LPEN		(UINT32_C(1) << 0)	///< TIM1 clock enable
///	@}

/// \name RCC_APB4LPENR bits
///	@{
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV28		(UINT32_C(0xF) << 28)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_DFSDM2LPEN	(UINT32_C(1) << 27)	//< DFSDM2 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_DTSLPEN		(UINT32_C(1) << 26)	//< DTS clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV17		(UINT32_C(0x1FF) << 17)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RTCAPBLPEN	(UINT32_C(1) << 16)	//< RTCAPB clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_VREFLPEN		(UINT32_C(1) << 15)	//< VREF clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_COMP12LPEN	(UINT32_C(1) << 14)	//< COMP12 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_DAC2LPEN		(UINT32_C(1) << 13)	//< DAC2 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV11		(UINT32_C(3) << 11)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_LPTIM3LPEN	(UINT32_C(1) << 10)	//< LPTIM3 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_LPTIM2LPEN	(UINT32_C(1) << 9)	//< LPTIM2 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV8		(UINT32_C(1) << 8)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_I2C4LPEN		(UINT32_C(1) << 7)	//< I2C4 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV6		(UINT32_C(1) << 6)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_SPI6LPEN		(UINT32_C(1) << 5)	//< SPI6 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV4		(UINT32_C(1) << 4)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_LPUART1LPEN	(UINT32_C(1) << 3)	//< LPUART1 clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV2		(UINT32_C(1) << 2)	//< reserved, don't change
#define MCCI_STM32H7_REG_RCC_APB4LPENR_SYSCFGLPEN	(UINT32_C(1) << 1)	//< SYSCFG clock enable
#define MCCI_STM32H7_REG_RCC_APB4LPENR_RSV0		(UINT32_C(1) << 0)	//< reserved, don't change
///	@}

/****************************************************************************\
|
|	GPIO Control Registers
|
\****************************************************************************/

/// \name GPIO register offsets
///	@{
#define MCCI_STM32H7_GPIO_MODER		UINT32_C(0x00)	//< port mode register
#define MCCI_STM32H7_GPIO_OTYPER	UINT32_C(0x04)	//< port output type register
#define MCCI_STM32H7_GPIO_OSPEEDR	UINT32_C(0x08)	//< port output speed register
#define MCCI_STM32H7_GPIO_PUPDR		UINT32_C(0x0C)	//< port pull-up/pull-down register
#define MCCI_STM32H7_GPIO_IDR		UINT32_C(0x10)	//< port input data register
#define MCCI_STM32H7_GPIO_ODR		UINT32_C(0x14)	//< port output data register
#define MCCI_STM32H7_GPIO_BSRR		UINT32_C(0x18)	//< port bit set/reset register
#define MCCI_STM32H7_GPIO_LCKR		UINT32_C(0x1C)	//< port configuration lock register
#define MCCI_STM32H7_GPIO_AFRL		UINT32_C(0x20)	//< port alternate function low register
#define MCCI_STM32H7_GPIO_AFRH		UINT32_C(0x24)	//< port alternate function high register
///	@}

/// \name GPIO_MODER bits -- used to select pin mode, two bits per pin
///	@{
#define MCCI_STM32H7_GPIO_MODE_MASK	UINT32_C(3)	//< mode bit masks
#define MCCI_STM32H7_GPIO_MODE_IN	UINT32_C(0)	//< digital input
#define MCCI_STM32H7_GPIO_MODE_OUT	UINT32_C(1)	//< digital output
#define MCCI_STM32H7_GPIO_MODE_AF	UINT32_C(2)	//< alternate function
#define MCCI_STM32H7_GPIO_MODE_ANALOG	UINT32_C(3)	//< analog
///	@}

/// \brief compute the mask for the mode bits for port bits 0..31
///
/// Normally we compute a mask using an expression like:
///
///	`MCCI_BOOTLOADER_FIELD_SET_VALUE(
///		MCCI_STM32H7_GPIO_MODE_P(3),
///		MCCI_STM32H7_GPIO_MODE_IN
///		)`
///
#define	MCCI_STM32H7_GPIO_MODE_P(p)	(UINT32_C(3) << (2 * (p)))

/// \name GPIO_OTYPER bits
///	@{
#define	MCCI_STM32H7_GPIO_OTYPE_PP	UINT32_C(0)	//< Output push-pull
#define	MCCI_STM32H7_GPIO_OTYPE_OD	UINT32_C(1)	//< Output open-drain
///	@}


/// \brief compute the mask for the mode bits for port bits 0..15
///
/// Normally we compute a mask using an expression like:
///
///	`MCCI_BOOTLOADER_FIELD_SET_VALUE(
///		MCCI_STM32H7_GPIO_OTYPE_P(3),
///		MCCI_STM32H7_GPIO_OTYPE_PP
///		)`
///
#define	MCCI_STM32H7_GPIO_OTYPE_P(p)	(UINT32_C(1) << (p))

/// \name GPIO_OSPEEDR bits -- used to select pin speed, two bits per pin
///	@{
#define MCCI_STM32H7_GPIO_OSPEED_MASK	UINT32_C(3)	//< speed bit masks
#define MCCI_STM32H7_GPIO_OSPEED_LOW	UINT32_C(0)	//< low
#define MCCI_STM32H7_GPIO_OSPEED_MEDIUM	UINT32_C(1)	//< medium
#define MCCI_STM32H7_GPIO_OSPEED_HIGH	UINT32_C(2)	//< high
#define MCCI_STM32H7_GPIO_OSPEED_VHIGH	UINT32_C(3)	//< very high

/// \brief compute the mask for the mode bits for port bits 0..31
///
/// Normally we compute a mask using an expression like:
///
///	`MCCI_BOOTLOADER_FIELD_SET_VALUE(
///		MCCI_STM32H7_GPIO_OSPEED_P(3),
///		MCCI_STM32H7_GPIO_OSPEED_IN
///		)`
///
#define	MCCI_STM32H7_GPIO_OSPEED_P(p)	(UINT32_C(3) << (2 * (p)))
///	@}

/// \name GPIO_PUPDR bits -- used to select pin speed, two bits per pin
///	@{
#define MCCI_STM32H7_GPIO_PUPD_MASK	UINT32_C(3)	//< speed bit masks
#define MCCI_STM32H7_GPIO_PUPD_NONE	UINT32_C(0)	//< no pullup/pulldown
#define MCCI_STM32H7_GPIO_PUPD_PULLUP	UINT32_C(1)	//< pullup
#define MCCI_STM32H7_GPIO_PUPD_PULLDOWN	UINT32_C(2)	//< pulldown

/// \brief compute the mask for the mode bits for port bits 0..31
///
/// Normally we compute a mask using an expression like:
///
///	`MCCI_BOOTLOADER_FIELD_SET_VALUE(
///		MCCI_STM32H7_GPIO_PUPD_P(3),
///		MCCI_STM32H7_GPIO_PUPD_PULLDOWN
///		)`
///
#define	MCCI_STM32H7_GPIO_PUPD_P(p)	(UINT32_C(3) << (2 * (p)))
///	@}

/// \name GPIO_BSRR bits
///	@{
#define MCCI_STM32H7_GPIO_BSRR_BR0	(UINT32_C(1) << 16)		//< reset port bit 0
#define MCCI_STM32H7_GPIO_BSRR_BR	(UINT32_C(0xFFFF) << 16)	//< mask of port-reset bits
#define MCCI_STM32H7_GPIO_BSRR_BS0	(UINT32_C(1) << 0)		//< set port bit 0
#define MCCI_STM32H7_GPIO_BSRR_BS	(UINT32_C(0xFFFF) << 0)		//< mask of port-set bits
/// \brief compute port-bit reset mask for bit \p p.
#define MCCI_STM32H7_GPIO_BSRR_BR_P(p)	(MCCI_STM32H7_GPIO_BSRR_BR0 << (p))
/// \brief compute port-bit set mask for bit \p p.
#define MCCI_STM32H7_GPIO_BSRR_BS_P(p)	(MCCI_STM32H7_GPIO_BSRR_BS0 << (p))
///	@}

/// \name GPIO_LCKR bits
///	@{
#define	MCCI_STM32H7_GPIO_LCKR_RSV17	UINT32_C(0xFFFE0000)	//< reserved, don't change
#define	MCCI_STM32H7_GPIO_LCKR_LCKK	(UINT32_C(1) << 16)	//< lock key bit; if set, ports are locked.
/// \brief compute GPIO lock bit fmask for bit \p p.
#define	MCCI_STM32H7_GPIO_LCKR_LCK_P(p)	(UINT32_C(1) << (p))
#define	MCCI_STM32H7_GPIO_LCKR_LCK	(UINT32_C(0xFFFF) << 0)	//< mask of port-lock bits.
///	@}

/// \name GPIO_AFRx bits
///	@{
/// \brief get reg offset for GPIO_AFRx
#define	MCCI_STM32H7_GPIO_AFRx_P(p)	(MCCI_STM32H7_GPIO_AFRL + ((p) / UINT32_C(8)))	//< f

/// \brief get AFRx mask for port bit \p p.
///
/// Normal use:
///	MCCI_BOOTLOADER_FIELD_SET_VALUE(MCCI_STM32H7_GPIO_AFSEL_P(bitnum), 0..7)
///
#define	MCCI_STM32H7_GPIO_AFSEL_P(p)	(UINT32_C(0xF) << ((p) & 0x7u)
///	@}

/****************************************************************************\
|
|	SPI Control Registers
|
\****************************************************************************/

/// \name SPI offsets
///	@{
#define	MCCI_STM32H7_SPI_CR1		UINT32_C(0x00)	///< offset to SPI control register 1
#define MCCI_STM32H7_SPI_CR2		UINT32_C(0x04)	///< offset to SPI control register 2
#define	MCCI_STM32H7_SPI_CFG1		UINT32_C(0x08)	///< offset to SPI configuration register 1
#define MCCI_STM32H7_SPI_CFG2		UINT32_C(0x0C)	///< offset to SPI configuration register 2
#define MCCI_STM32H7_SPI_IER		UINT32_C(0x10)	///< offset to SPI interrupt enable register
#define MCCI_STM32H7_SPI_SR		UINT32_C(0x14)	///< offset to SPI status register
#define MCCI_STM32H7_SPI_IFCR		UINT32_C(0x18)	///< offset to SPI interrupt/status flags clearregister
#define MCCI_STM32H7_SPI_TXDR		UINT32_C(0x20)	///< offset to SPI transmit data register
#define MCCI_STM32H7_SPI_RXDR		UINT32_C(0x30)	///< offset to SPI receive data register
#define MCCI_STM32H7_SPI_CRCPOLY	UINT32_C(0x40)	///< offset to SPI CRC polynomial
#define MCCI_STM32H7_SPI_TXCRC		UINT32_C(0x44)	///< offset to SPI transmit CRC
#define MCCI_STM32H7_SPI_RXCRC		UINT32_C(0x48)	///< offset to SPI receive CRC
#define MCCI_STM32H7_SPI_UDRDR		UINT32_C(0x4C)	///< offset to SPI underrun data CRC
#define MCCI_STM32H7_SPI_I2SCFGR	UINT32_C(0x50)	///< offset to SPI I2S config register
///	@}

/// \name SPI_CR1 bits
///	@{
#define MCCI_STM32H7_SPI_CR1_RSV17	UINT32_C(0xFFFE0000)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CR1_IOLOCK	(UINT32_C(1) << 16)	///< locking the AF configuration of associated IOs
#define MCCI_STM32H7_SPI_CR1_TCRCINI	(UINT32_C(1) << 15)	///< CRC calculation initialization pattern control for transmitter
#define MCCI_STM32H7_SPI_CR1_RCRCINI	(UINT32_C(1) << 14)	///< CRC calculation initialization pattern control for receiver
#define MCCI_STM32H7_SPI_CR1_CRC33_17	(UINT32_C(1) << 13)	///< 32-bit CRC polynomial configuration
#define MCCI_STM32H7_SPI_CR1_SSI	(UINT32_C(1) << 12)	///< internal SS signal input level
#define MCCI_STM32H7_SPI_CR1_HDDIR	(UINT32_C(1) << 11)	///< Rx/Tx direction at Half-duplex mode
#define MCCI_STM32H7_SPI_CR1_CSUSP	(UINT32_C(1) << 10)	///< master suspend request
#define MCCI_STM32H7_SPI_CR1_CSTART	(UINT32_C(1) << 9)	///< master transfer start
#define MCCI_STM32H7_SPI_CR1_MASRX	(UINT32_C(1) << 8)	///< master automatic SUSP in Receive mode
#define MCCI_STM32H7_SPI_CR1_RSV1	(UINT32_C(0x7F) << 1)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CR1_SPE	(UINT32_C(1) << 0)	///< serial peripheral enable
///	@}

/// \name SPI_CR2 bits
///	@{
#define MCCI_STM32H7_SPI_CR2_TSER	UINT32_C(0xFFFF0000)	///< number of data transfer extension to be reload into TSIZE
#define MCCI_STM32H7_SPI_CR2_TSIZE	UINT32_C(0x0000FFFF)	///< number of data at current transfer
///	@}

/// \name SPI_CFG1 bits
///	@{
#define MCCI_STM32H7_SPI_CFG1_RSV31		(UINT32_C(1) << 31)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG1_MBR		(UINT32_C(7) << 28)	///< master baud rate
#define MCCI_STM32H7_SPI_CFG1_MBR_2		(UINT32_C(0) << 28)	///< SPI master clock/2
#define MCCI_STM32H7_SPI_CFG1_MBR_4		(UINT32_C(1) << 28)	///< SPI master clock/4
#define MCCI_STM32H7_SPI_CFG1_MBR_8		(UINT32_C(2) << 28)	///< SPI master clock/8
#define MCCI_STM32H7_SPI_CFG1_MBR_16		(UINT32_C(3) << 28)	///< SPI master clock/16
#define MCCI_STM32H7_SPI_CFG1_MBR_32		(UINT32_C(4) << 28)	///< SPI master clock/32
#define MCCI_STM32H7_SPI_CFG1_MBR_64		(UINT32_C(5) << 28)	///< SPI master clock/64
#define MCCI_STM32H7_SPI_CFG1_MBR_128		(UINT32_C(6) << 28)	///< SPI master clock/128
#define MCCI_STM32H7_SPI_CFG1_MBR_256		(UINT32_C(7) << 28)	///< SPI master clock/256
#define MCCI_STM32H7_SPI_CFG1_RSV23		(UINT32_C(0x1F) << 23)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG1_CRCEN		(UINT32_C(1) << 22)	///< hardware CRC computation enable
#define MCCI_STM32H7_SPI_CFG1_RSV21		(UINT32_C(1) << 21)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG1_CRCSIZE		(UINT32_C(0x1F) << 16)	///< length of CRC frame to be transacted and compared
#define MCCI_STM32H7_SPI_CFG1_CRCSIZE_N(n)	((n) << 16)		///< n+1 bits
#define MCCI_STM32H7_SPI_CFG1_TXDMAEN		(UINT32_C(1) << 15)	///< Tx DMA stream enable
#define MCCI_STM32H7_SPI_CFG1_RXDMAEN		(UINT32_C(1) << 14)	///< Rx DMA stream enable
#define MCCI_STM32H7_SPI_CFG1_RSV13		(UINT32_C(1) << 13)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG1_UDRDET		(UINT32_C(3) << 11)	///< detection of underrun condition at slave transmitter
#define MCCI_STM32H7_SPI_CFG1_UDRDET_BEGIN	(UINT32_C(0) << 11)	///< underrun is detected at begin of data frame
#define MCCI_STM32H7_SPI_CFG1_UDRDET_END	(UINT32_C(1) << 11)	///< underrun is detected at end of data frame
#define MCCI_STM32H7_SPI_CFG1_UDRDET_BEGIN_SS	(UINT32_C(2) << 11)	///< underrun is detected at begin of active SS signal
#define MCCI_STM32H7_SPI_CFG1_UDRCFG		(UINT32_C(3) << 9)	///< behavior of slave transmitter at underrun condition
#define MCCI_STM32H7_SPI_CFG1_UDRCFG_CONST	(UINT32_C(0) << 9)	///< slave sends a constant pattern defined by the user at SPI_UDRDR register
#define MCCI_STM32H7_SPI_CFG1_UDRCFG_RX		(UINT32_C(1) << 9)	///< slave repeats lastly received data frame from master
#define MCCI_STM32H7_SPI_CFG1_UDRCFG_TX		(UINT32_C(2) << 9)	///< slave repeats its lastly transmitted data frame
#define MCCI_STM32H7_SPI_CFG1_FTHLV		(UINT32_C(0xF) << 5)	///< FIFO threshold level
#define MCCI_STM32H7_SPI_CFG1_FTHLV_N(n)	((n) << 5)		///< n+1 data
#define MCCI_STM32H7_SPI_CFG1_DSIZE		(UINT32_C(0x1F) << 0)	///< number of bits in at single SPI data frame
#define MCCI_STM32H7_SPI_CFG1_DSIZE_N(n)	((n) << 0)		///< n+1 bits
///	@}

/// \name SPI_CFG2 bits
///	@{
#define MCCI_STM32H7_SPI_CFG2_AFCNTR		(UINT32_C(1) << 31)	///< alternate function GPIOs control
#define MCCI_STM32H7_SPI_CFG2_SSOM		(UINT32_C(1) << 30)	///< SS output management in master mode
#define MCCI_STM32H7_SPI_CFG2_SSOE		(UINT32_C(1) << 29)	///< SS output enable
#define MCCI_STM32H7_SPI_CFG2_SSIOP		(UINT32_C(1) << 28)	///< SS input/output polarity
#define MCCI_STM32H7_SPI_CFG2_RSV27		(UINT32_C(1) << 27)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG2_SSM		(UINT32_C(1) << 26)	///< software management of SS signal input
#define MCCI_STM32H7_SPI_CFG2_CPOL		(UINT32_C(1) << 25)	///< clock polarity
#define MCCI_STM32H7_SPI_CFG2_CPHA		(UINT32_C(1) << 24)	///< clock phase
#define MCCI_STM32H7_SPI_CFG2_LSBFRST		(UINT32_C(1) << 23)	///< data frame format
#define MCCI_STM32H7_SPI_CFG2_MASTER		(UINT32_C(1) << 22)	///< SPI master
#define MCCI_STM32H7_SPI_CFG2_SP		(UINT32_C(7) << 19)	///< Serial protocol
#define MCCI_STM32H7_SPI_CFG2_COMM		(UINT32_C(3) << 17)	///< SPI communication mode
#define MCCI_STM32H7_SPI_CFG2_COMM_FULL_DUPLEX	(UINT32_C(0) << 17)	///< full-duplex
#define MCCI_STM32H7_SPI_CFG2_COMM_SIMPLEX_TX	(UINT32_C(1) << 17)	///< simplex transmitter
#define MCCI_STM32H7_SPI_CFG2_COMM_SIMPLEX_RX	(UINT32_C(2) << 17)	///< simplex receiver
#define MCCI_STM32H7_SPI_CFG2_COMM_HALF_DUPLEX	(UINT32_C(3) << 17)	///< half-duplex
#define MCCI_STM32H7_SPI_CFG2_RSV16		(UINT32_C(1) << 16)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG2_IOSWP		(UINT32_C(1) << 15)	///< swap functionality of MISO and MOSI pins
#define MCCI_STM32H7_SPI_CFG2_RSV8		(UINT32_C(0x7F) << 8)	///< reserved, don't change
#define MCCI_STM32H7_SPI_CFG2_MIDI		(UINT32_C(15) << 4)	///< master Inter-Data Idleness
#define MCCI_STM32H7_SPI_CFG2_MIDI_N(n)		((n) << 4)		///< n clock cycle period delay
#define MCCI_STM32H7_SPI_CFG2_MSSI		(UINT32_C(15) << 0)	///< master SS idleness
#define MCCI_STM32H7_SPI_CFG2_MSSI_N(n)		((n) << 0)		///< n clock cycle period delay added
///	@}

/// \name SPI_IER bits
///	@{
#define MCCI_STM32H7_SPI_IER_RSV11		UINT32_C(0xFFFFFF80)	///< reserved, don't change
#define MCCI_STM32H7_SPI_IER_TSERFIE		(UINT32_C(1) << 10)	///< additional number of transactions reload interrupt enable
#define MCCI_STM32H7_SPI_IER_MODFIE		(UINT32_C(1) << 9)	///< mode fault interrupt enable
#define MCCI_STM32H7_SPI_IER_TIFREIE		(UINT32_C(1) << 8)	///< TIFRE interrupt enable
#define MCCI_STM32H7_SPI_IER_CRCEIE		(UINT32_C(1) << 7)	///< CRC error interrupt enable
#define MCCI_STM32H7_SPI_IER_OVRIE		(UINT32_C(1) << 6)	///< OVR interrupt enable
#define MCCI_STM32H7_SPI_IER_UDRIE		(UINT32_C(1) << 5)	///< UDR interrupt enable
#define MCCI_STM32H7_SPI_IER_TXTFIE		(UINT32_C(1) << 4)	///< TXTFIE interrupt enable
#define MCCI_STM32H7_SPI_IER_EOTIE		(UINT32_C(1) << 3)	///< EOT, SUSP and TXC interrupt enable
#define MCCI_STM32H7_SPI_IER_DXPIE		(UINT32_C(1) << 2)	///< DXP interrupt enabled
#define MCCI_STM32H7_SPI_IER_TXPIE		(UINT32_C(1) << 1)	///< TXP interrupt enable
#define MCCI_STM32H7_SPI_IER_RXPIE		(UINT32_C(1) << 0)	///< RXP Interrupt Enable
///	@}

/// \name SPI_SR bits
///	@{
#define MCCI_STM32H7_SPI_SR_CTSIZE	UINT32_C(0xFFFF0000)	///< number of data frames remaining in current TSIZE session
#define MCCI_STM32H7_SPI_SR_RXWNE	(UINT32_C(1) << 15)	///< RxFIFO word not empty
#define MCCI_STM32H7_SPI_SR_RXPLVL	(UINT32_C(3) << 13)	///< RxFIFO packing leveL
#define MCCI_STM32H7_SPI_SR_RXPLVL_N(n)	((n) << 13)		///< n frame is available
#define MCCI_STM32H7_SPI_SR_TXC		(UINT32_C(1) << 12)	///< TxFIFO transmission complete
#define MCCI_STM32H7_SPI_SR_SUSP	(UINT32_C(1) << 11)	///< suspension status
#define MCCI_STM32H7_SPI_SR_TSERF	(UINT32_C(1) << 10)	///< additional number of SPI data to be transacted was reload
#define MCCI_STM32H7_SPI_SR_MODF	(UINT32_C(1) << 9)	///< mode fault
#define MCCI_STM32H7_SPI_SR_TIFRE	(UINT32_C(1) << 8)	///< TI frame format error
#define MCCI_STM32H7_SPI_SR_CRCE	(UINT32_C(1) << 7)	///< CRC error
#define MCCI_STM32H7_SPI_SR_OVR		(UINT32_C(1) << 6)	///< overrun
#define MCCI_STM32H7_SPI_SR_UDR		(UINT32_C(1) << 5)	///< underrun at slave transmission mode
#define MCCI_STM32H7_SPI_SR_TXTF	(UINT32_C(1) << 4)	///< transmission transfer filled
#define MCCI_STM32H7_SPI_SR_EOT		(UINT32_C(1) << 3)	///< end of transfer
#define MCCI_STM32H7_SPI_SR_DXP		(UINT32_C(1) << 2)	///< duplex packet
#define MCCI_STM32H7_SPI_SR_TXP		(UINT32_C(1) << 1)	///< Tx-packet space available
#define MCCI_STM32H7_SPI_SR_RXP		(UINT32_C(1) << 0)	///< Rx-packet available
///	@}

/// \name SPI_IFCR bits
///	@{
#define MCCI_STM32H7_SPI_IFCR_RSV12		UINT32_C(0xFFFFFF00)	///< reserved, don't change
#define MCCI_STM32H7_SPI_IFCR_SUSPC		(UINT32_C(1) << 11)	///< SUSPend flag clear
#define MCCI_STM32H7_SPI_IFCR_TSERFC		(UINT32_C(1) << 10)	///< additional number of transactions reload flag clear
#define MCCI_STM32H7_SPI_IFCR_MODFC		(UINT32_C(1) << 9)	///< mode fault flag clear
#define MCCI_STM32H7_SPI_IFCR_TIFREC		(UINT32_C(1) << 8)	///< TIFRE flag clear
#define MCCI_STM32H7_SPI_IFCR_CRCEC		(UINT32_C(1) << 7)	///< CRC error flag clear
#define MCCI_STM32H7_SPI_IFCR_OVRC		(UINT32_C(1) << 6)	///< OVR flag clear
#define MCCI_STM32H7_SPI_IFCR_UDRC		(UINT32_C(1) << 5)	///< UDR flag clear
#define MCCI_STM32H7_SPI_IFCR_TXTFC		(UINT32_C(1) << 4)	///< TXTFC flag clear
#define MCCI_STM32H7_SPI_IFCR_EOTC		(UINT32_C(1) << 3)	///< EOT, SUSP and TXC flag clear
#define MCCI_STM32H7_SPI_IFCR_RSV0		(UINT32_C(7) << 0)	///< reserved, don't change
///	@}

/// \name SPI_I2SCFGR bits
///	@{
#define MCCI_STM32H7_SPI_I2SCFGR_RSV26		(UINT32_C(0x3F) << 26)	///< reserved (do not change)
#define MCCI_STM32H7_SPI_I2SCFGR_MCKOE		(UINT32_C(1) << 25)	///< master clock output enable
#define MCCI_STM32H7_SPI_I2SCFGR_ODD		(UINT32_C(1) << 24)	///< odd factor for the prescaler
#define MCCI_STM32H7_SPI_I2SCFGR_I2SDIV		(UINT32_C(0xFF) << 16)	///< I2S linear prescaler
#define MCCI_STM32H7_SPI_I2SCFGR_I2SDIV_N(n)	((n) << 16)		///<
#define MCCI_STM32H7_SPI_I2SCFGR_RSV15		(UINT32_C(1) << 15)	///< reserved (do not change)
#define MCCI_STM32H7_SPI_I2SCFGR_DATFMT		(UINT32_C(1) << 14)	///< data format
#define MCCI_STM32H7_SPI_I2SCFGR_WSINV		(UINT32_C(1) << 13)	///< Word select inversion
#define MCCI_STM32H7_SPI_I2SCFGR_FIXCH		(UINT32_C(1) << 12)	///< fixed channel length in slave
#define MCCI_STM32H7_SPI_I2SCFGR_CKPOL		(UINT32_C(1) << 11)	///< serial audio clock polarity
#define MCCI_STM32H7_SPI_I2SCFGR_CHLEN		(UINT32_C(1) << 10)	///< channel length
#define MCCI_STM32H7_SPI_I2SCFGR_DATLEN		(UINT32_C(3) << 8)	///< data length to be transferred
#define MCCI_STM32H7_SPI_I2SCFGR_DATLEN_16	(UINT32_C(0) << 8)	///< 16 bit
#define MCCI_STM32H7_SPI_I2SCFGR_DATLEN_24	(UINT32_C(1) << 8)	///< 24 bit
#define MCCI_STM32H7_SPI_I2SCFGR_DATLEN_32	(UINT32_C(2) << 8)	///< 32 bit
#define MCCI_STM32H7_SPI_I2SCFGR_PCMSYNC	(UINT32_C(1) << 7)	///< PCM frame synchronization
#define MCCI_STM32H7_SPI_I2SCFGR_RSV6		(UINT32_C(1) << 6)	///< reserved (do not change)
#define MCCI_STM32H7_SPI_I2SCFGR_I2SSTD		(UINT32_C(3) << 4)	///< I2S standard selection
#define MCCI_STM32H7_SPI_I2SCFGR_I2SSTD_PHILIPS	(UINT32_C(0) << 4)	///< I2S Philips standard
#define MCCI_STM32H7_SPI_I2SCFGR_I2SSTD_MSB	(UINT32_C(1) << 4)	///< MSB justified standard
#define MCCI_STM32H7_SPI_I2SCFGR_I2SSTD_LSB	(UINT32_C(2) << 4)	///< LSB justified standard
#define MCCI_STM32H7_SPI_I2SCFGR_I2SSTD_PCM	(UINT32_C(3) << 4)	///< PCM standard
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG		(UINT32_C(7) << 1)	///< I2S configuration mode
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG_STX	(UINT32_C(0) << 1)	///< slave - transmit
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG_SRX	(UINT32_C(1) << 1)	///< slave - receive
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG_MTX	(UINT32_C(2) << 1)	///< master - transmit
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG_MRX	(UINT32_C(3) << 1)	///< master - receive
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG_SFD	(UINT32_C(4) << 1)	///< slave - full duplex
#define MCCI_STM32H7_SPI_I2SCFGR_I2SCFG_MFD	(UINT32_C(5) << 1)	///< master - full duplex
#define MCCI_STM32H7_SPI_I2SCFGR_I2SMOD		(UINT32_C(1) << 0)	///< I2S mode selection
///	@}


/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_stm32h7xx_h_ */
