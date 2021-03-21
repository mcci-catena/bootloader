/*

Module:	mcci_arm_cm0plus.h

Function:
	ARM cm0plus definitions without CMSIS overhead.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_arm_cm0plus_h_
#define _mcci_arm_cm0plus_h_	/* prevent multiple includes */

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

/// \name SYSTICK registers
///	@{
#define	MCCI_CM0PLUS_SYSTICK		UINT32_C(0xE000E010)
#define	MCCI_CM0PLUS_SYSTICK_CSR	(MCCI_CM0PLUS_SYSTICK + 0x0)
#define	MCCI_CM0PLUS_SYSTICK_RVR	(MCCI_CM0PLUS_SYSTICK + 0x4)
#define	MCCI_CM0PLUS_SYSTICK_CVR	(MCCI_CM0PLUS_SYSTICK + 0x8)
#define	MCCI_CM0PLUS_SYSTICK_CALIB	(MCCI_CM0PLUS_SYSTICK + 0xC)
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
#define	MCCI_CM0PLUS_SCB_SHPR2		(MCCI_CM0PLUS_SCB + 0x1C)
#define	MCCI_CM0PLUS_SCB_SHPR3		(MCCI_CM0PLUS_SCB + 0x20)
#define	MCCI_CM0PLUS_SCB_SHCSR		(MCCI_CM0PLUS_SCB + 0x24)
#define	MCCI_CM0PLUS_SCB_DFSR		(MCCI_CM0PLUS_SCB + 0x30)
///	@}

/// \name MPU registers
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

/// \name SYSTICK CSR bits
///	@{
#define MCCI_CM0PLUS_SYSTICK_CSR_RSV17		UINT32_C(0xFFFE0000)	///< reserved 
#define MCCI_CM0PLUS_SYSTICK_CSR_COUNTFLAG	(UINT32_C(1) << 16)	///< timer has counted to zero
#define MCCI_CM0PLUS_SYSTICK_CSR_RSV3		UINT32_C(0x0000FFF8)	///< reserved
#define MCCI_CM0PLUS_SYSTICK_CSR_CLKSOURCE	(UINT32_C(1) << 2)	///< use processor (not external) clock
#define MCCI_CM0PLUS_SYSTICK_CSR_TICKINT	(UINT32_C(1) << 1)	///< enable tick exception
#define MCCI_CM0PLUS_SYSTICK_CSR_ENABLE		(UINT32_C(1) << 0)	///< enable counter
///	@}

/// \name SYSTICK RVR bits
///	@{
#define MCCI_CM0PLUS_SYSTICK_RVR_RSV24		UINT32_C(0xFF000000)	///< reserved, zero
#define MCCI_CM0PLUS_SYSTICK_RVR_RELOAD		UINT32_C(0x00FFFFFF)	///< reload value
///	@}

/// \name SYSTICK CVR bits
///	@{
#define MCCI_CM0PLUS_SYSTICK_CVR_RSV24		UINT32_C(0xFF000000)	///< reserved, read as zero
#define MCCI_CM0PLUS_SYSTICK_CVR_CURRENT	UINT32_C(0x00FFFFFF)	///< current value
///	@}

/// \name SYSTICK CALIB bits
///	@{
#define MCCI_CM0PLUS_SYSTICK_CALIB_NOREF	(UINT32_C(1) << 31)	///< reference clock is not implemented
#define MCCI_CM0PLUS_SYSTICK_CALIB_SKEW		(UINT32_C(1) << 30)	///< 10ms cal value is inexact
#define MCCI_CM0PLUS_SYSTICK_CALIB_RSV24	(UINT32_C(0x3F) << 24)	///< reserved, zero
#define MCCI_CM0PLUS_SYSTICK_CALIB_TENMS	UINT32_C(0x00FFFFFF)	///< if non-zero, use this as reload value for 10ms ticks
///	@}

/// \name NVIC IPR bits

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

/// \name SCB SHPR access
///	@{
#define	MCCI_CM0PLUS_SCB_SHPR_PRI	(UINT32_C(3) << 6)	///< priority bits within a byte

#define	MCCI_CM0PLUS_PRI_INDEX_SVC	UINT32_C(11)	///< priority of systick
#define	MCCI_CM0PLUS_PRI_INDEX_PENDSV	UINT32_C(14)	///< priority of systick
#define	MCCI_CM0PLUS_PRI_INDEX_SYSTICK	UINT32_C(15)	///< priority of systick

/// 	\brief return register for a given handler index
static inline uint32_t
McciCm0Plus_SCB_SHPR_getRegister(
	uint32_t	handlerIndex
	)
	{
	// map to either SPHR2 or SHPR3.
	return MCCI_CM0PLUS_SCB_SHPR2 + (handlerIndex & 4);
	}

///	\brief return byte mask for a given handler index
static inline uint32_t
McciCm0Plus_SCB_SHPR_getMask(
	uint32_t	handlerIndex
	)
	{
	// compute and return the mask for a given bit
	return UINT32_C(0xE0) << (8 * (handlerIndex & 3));
	}
///	@}

/// \name SCB System Handler Control and State Register bits
///	@{
#define	MCCI_CM0PLUS_SCB_SHCSR_SVCALLPENDED	(UINT32_C(1) << 15)	///<
///	@}

/****************************************************************************\
|
|	Register access primitives
|
\****************************************************************************/

/// \brief write a 32-bit value to a cm0plus register
static inline uint32_t
McciArm_putReg(uint32_t reg, uint32_t val)
	{
	*(volatile uint32_t *)reg = val;
	return val;
	}

/// \brief read a 32-bit value from a cm0plus register
static inline uint32_t
McciArm_getReg(uint32_t reg)
	{
	return *(volatile uint32_t *)reg;
	}

/// \brief and/or 32-bit values to a cm0plus register
static inline uint32_t
McciArm_putRegAndOr(uint32_t reg, uint32_t andVal, uint32_t orVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		(rValue & andVal) | orVal
		);
	}

/// \brief or 32-bit values to a cm0plus register
static inline uint32_t
McciArm_putRegOr(uint32_t reg, uint32_t orVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		rValue | orVal
		);
	}

/// \brief clear out 32-bit values to a cm0plus register
static inline uint32_t
McciArm_putRegClear(uint32_t reg, uint32_t clearVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		rValue & ~clearVal
		);
	}

/// \brief clear and set 32-bit values to a cm0plus register
static inline uint32_t
McciArm_putRegClearSet(uint32_t reg, uint32_t clearVal, uint32_t setVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	setVal &= ~clearVal;
	return McciArm_putReg(
		reg,
		(rValue & ~clearVal) | setVal
		);
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
McciArm_setMSP(
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
|	Vectors and so forth
|
\****************************************************************************/

///
/// \brief application entry contents
///
/// Every Cortex M0 application begins with two DWORDs. The first is
/// the stack pointer; the second is the program counter.
///
/// We use MCCI Russian Doll structure nesting; this is the root
/// of the hierarchy that forms the page zero vectors.
///
typedef struct Mcci_CortexAppEntryContents_s
	{
	uint32_t	stack;	//< Initial stack pointer must be multiple of 4
	uint32_t	entry;	//< Initial entry point; must be odd.
	} Mcci_CortexAppEntryContents_t;

///
/// \brief application entry object
///
/// This union wraps the app entry contents, so that we can always reference
/// with a consistent name (`AppEntry.stack` etc.), regardless of how general
/// or specific the pointer is.
///
typedef union Mcci_CortexAppEntry_u
	{
	Mcci_CortexAppEntryContents_t	CortexAppEntry;	//< reference name for application entry view.
	} Mcci_CortexAppEntry_t;

///
/// \brief Cortex M0 interrupt vectors (low level view)
///
/// This structure represents the vectors page as an aray of 96 32-bit vectors.
/// It's used mostly for initialization and for building up larger structures.
/// It's marked "align(256)" so that it will be properly aligned for the
/// interrupt vector page register.
///
typedef struct Mcci_CortexVectorsContents_s
	{
	uint32_t	vectors[192/4];
	} __attribute__((__aligned__(256)))
	Mcci_CortexVectorsContents_t;

///
/// \brief Cortex M0 interrupt vector object
///
/// This union wraps the interrupt vector contents, both so we can always
/// reference fields with consistent names (`AppEntry.stack` etc.), and to allow
/// us to view the vectors as either an AppEntry description or a table of
/// vectors.
///
typedef union Mcci_CortexVectors_u
	{
	Mcci_CortexAppEntryContents_t	CortexAppEntry;		//< View instance as a CortexM0 AppEntry.
	Mcci_CortexAppEntry_t	CortexAppEntryCast;		//< Downcast to an AppEntry without explicit casting
	Mcci_CortexVectorsContents_t CortexVectors;		//< View instance as vectors.
	} Mcci_CortexVectors_t;

/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_arm_cm0plus_h_ */
