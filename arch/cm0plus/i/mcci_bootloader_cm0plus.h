/*

Module:	mcci_bootloader_cm0plus.h

Function:
	ARM cm0plus definitions so we don't need Apache license for CMSIS.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_cm0plus_h_
#define _mcci_bootloader_cm0plus_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_bits_h_
# include "mcci_bootloader_bits.h"
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

#define	MCCI_CM0PLUS_SCS_BASE		UINT32_C(0xE000E000)

/// \name SysTick registers
///	@{
#define	MCCI_CM0PLUS_SysTick		UINT32_C(0xE000E010)
#define	MCCI_CM0PLUS_SysTick_CTRL	(MCCI_CM0PLUS_SysTick + 0x0)
#define	MCCI_CM0PLUS_SysTick_LOAD	(MCCI_CM0PLUS_SysTick + 0x4)
#define	MCCI_CM0PLUS_SysTick_VAL	(MCCI_CM0PLUS_SysTick + 0x8)
#define	MCCI_CM0PLUS_SysTick_CALIB	(MCCI_CM0PLUS_SysTick + 0xC)
///	@}

/// \name NVIC registers
///	@{
#define	MCCI_CM0PLUS_NVIC		UINT32_C(0xE000E100)
#define	MCCI_CM0PLUS_NVIC_ISER		(MCCI_CM0PLUS_NVIC + 0x000)
#define	MCCI_CM0PLUS_NVIC_ICER		(MCCI_CM0PLUS_NVIC + 0x080)
#define	MCCI_CM0PLUS_NVIC_ISPR		(MCCI_CM0PLUS_NVIC + 0x100)
#define	MCCI_CM0PLUS_NVIC_ICPR		(MCCI_CM0PLUS_NVIC + 0x180)
#define	MCCI_CM0PLUS_NVIC_IP0		(MCCI_CM0PLUS_NVIC + 0x300)
#define	MCCI_CM0PLUS_NVIC_IP1		(MCCI_CM0PLUS_NVIC + 0x304)
#define	MCCI_CM0PLUS_NVIC_IP2		(MCCI_CM0PLUS_NVIC + 0x308)
#define	MCCI_CM0PLUS_NVIC_IP3		(MCCI_CM0PLUS_NVIC + 0x30C)
#define	MCCI_CM0PLUS_NVIC_IP4		(MCCI_CM0PLUS_NVIC + 0x310)
#define	MCCI_CM0PLUS_NVIC_IP5		(MCCI_CM0PLUS_NVIC + 0x314)
#define	MCCI_CM0PLUS_NVIC_IP6		(MCCI_CM0PLUS_NVIC + 0x318)
#define	MCCI_CM0PLUS_NVIC_IP7		(MCCI_CM0PLUS_NVIC + 0x31C)
///	@}

/// \name SCB registers
///	@{
#define	MCCI_CM0PLUS_SCB		UINT32_C(0xE000ED00)
#define	MCCI_CM0PLUS_SCB_CPUID		(MCCI_CM0PLUS_SCB + 0x00)
#define	MCCI_CM0PLUS_SCB_ICSR		(MCCI_CM0PLUS_SCB + 0x04)
#define	MCCI_CM0PLUS_SCB_VTOR		(MCCI_CM0PLUS_SCB + 0x08)
#define	MCCI_CM0PLUS_SCB_AIRCR		(MCCI_CM0PLUS_SCB + 0x0C)
#define	MCCI_CM0PLUS_SCB_SCR		(MCCI_CM0PLUS_SCB + 0x10)
#define	MCCI_CM0PLUS_SCB_CCR		(MCCI_CM0PLUS_SCB + 0x14)
#define	MCCI_CM0PLUS_SCB_RSV18		(MCCI_CM0PLUS_SCB + 0x18)
#define	MCCI_CM0PLUS_SCB_SHP0		(MCCI_CM0PLUS_SCB + 0x1C)
#define	MCCI_CM0PLUS_SCB_SHP1		(MCCI_CM0PLUS_SCB + 0x20)
#define	MCCI_CM0PLUS_SCB_SHCSR		(MCCI_CM0PLUS_SCB + 0x24)
///	@}

/// \name SysTick registers
///	@{
#define	MCCI_CM0PLUS_MPU		UINT32_C(0xE000ED90)
#define	MCCI_CM0PLUS_MPU_TYPE		(MCCI_CM0PLUS_MPU + 0x00)	//<
#define	MCCI_CM0PLUS_MPU_CTRL		(MCCI_CM0PLUS_MPU + 0x04)	//<
#define	MCCI_CM0PLUS_MPU_RNR		(MCCI_CM0PLUS_MPU + 0x08)	//<
#define	MCCI_CM0PLUS_MPU_RBAR		(MCCI_CM0PLUS_MPU + 0x0C)	//<
#define	MCCI_CM0PLUS_MPU_RASR		(MCCI_CM0PLUS_MPU + 0x10)	//<
///	@}

/****************************************************************************\
|
|	Register bits
|
\****************************************************************************/

/// \name SCB CPUID fields
/// 	@{
#define	MCCI_CM0PLUS_SCB_CPUID_IMPLEMENTER	(UINT32_C(0xFF) << 24)	///< Implementer code
#define	MCCI_CM0PLUS_SCB_CPUID_VARIANT		(UINT32_C(0xF) << 20)	///< Variant code
#define	MCCI_CM0PLUS_SCB_CPUID_ARCHITECTURE	(UINT32_C(0xF) << 16)	///< Architecture code
#define	MCCI_CM0PLUS_SCB_CPUID_PARTNO		(UINT32_C(0xFFF) << 4)	///< Part number
#define	MCCI_CM0PLUS_SCB_CPUID_REVISION		(UINT32_C(0xF) << 0)	///< Revision
///	@}

/// \name SCB ICSR fields
///	@{
#define	MCCI_CM0PLUS_SCB_ICSR_NMIPENDSET	(UINT32_C(1) << 31)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_RSV29		(UINT32_C(3) << 29)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_PENDSVSET		(UINT32_C(1) << 28)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_PENDSVCLR		(UINT32_C(1) << 27)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_PENDSTSET		(UINT32_C(1) << 26)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_PENDSTCLR		(UINT32_C(1) << 26)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_RSV24		(UINT32_C(1) << 24)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_ISRPREEMPT	(UINT32_C(1) << 23)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_ISRPENDING	(UINT32_C(1) << 22)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_VECTPENDING	(UINT32_C(0x1FF) << 12)	///< 
#define	MCCI_CM0PLUS_SCB_ICSR_VECTACTIVE	(UINT32_C(0x1FF) << 0)	///< 
///	@}

/// \name SCB VTOR fields
///	@{
#define	MCCI_CM0PLUS_SCB_VTOR_TBLOFF		UINT32_C(0xFFFFFF00)	///<
///	@}

/// \name SCB AIRCR fields (Appplication Interrupt and Reset Control)
///	@{
#define	MCCI_CM0PLUS_SCB_AIRCR_VECTKEY		(UINT32_C(0xFFFF) << 16)	///< Vector key
#define	MCCI_CM0PLUS_SCB_AIRCR_VECTKEYSTAT	(UINT32_C(0xFFFF) << 16)	///< Vector key status
#define	MCCI_CM0PLUS_SCB_AIRCR_ENDIANNESS	(UINT32_C(1) << 15)		///<
#define	MCCI_CM0PLUS_SCB_AIRCR_SYSRESETREQ	(UINT32_C(1) << 2)		///<
#define	MCCI_CM0PLUS_SCB_AIRCR_VECTCLRACTIVE	(UINT32_C(1) << 1)		///<
///	@}

/// \name SCB SCR fields
///	@{
#define	MCCI_CM0PLUS_SCB_SCR_SEVONPEND		(UINT32_C(1) << 4)	///<
#define	MCCI_CM0PLUS_SCB_SCR_SLEEPDEEP		(UINT32_C(1) << 2)	///<
#define	MCCI_CM0PLUS_SCB_SCR_SLEEPONEXIT	(UINT32_C(1) << 1)	///<
///	@}

/// \name SCB Configuration Control Register bits
///	@{
#define	MCCI_CM0PLUS_SCB_CCR_STKALIGN		(UINT32_C(1) << 9)	///<
#define	MCCI_CM0PLUS_SCB_CCR_UNALIGNED		(UINT32_C(1) << 3)	///<
///	@}

/// \name SCB System Handler Control and State Register bits
///	@{
#define	MCCI_CM0PLUS_SCB_SHCSR_SVCALLPENDED	(UINT32_C(1) << 15)	///<
///	@}

/// \brief write a 32-bit value to a cm0plus register
static inline void
McciBootloaderArm_putReg(uint32_t reg, uint32_t val)
	{
	*(volatile uint32_t *)reg = val;
	}

/// \brief read a 32-bit value from a cm0plus register
static inline uint32_t
McciBootloaderArm_getReg(uint32_t reg)
	{
	return *(volatile uint32_t *)reg;
	}

/****************************************************************************\
|
|	ARM intrinsics (some of then)
|
\****************************************************************************/

#if defined(__GNUC__)		// GCC or clang, likely 

///
/// \brief set main stack pointer
///
/// \param[in] stack new stack pointer value.
///
/// \note This always must be inline because once stack pointer changes,
///	maybe hard to return!
///
__attribute__((__always_inline__)) static inline
void
McciBootloaderArm_setMSP(
	uint32_t stack
	)
	{
	__asm volatile ("MSR msp,%0" :: "r"(stack):);
	}
#else
# error "Compiler not supported"
#endif

/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_cm0plus_h_ */
