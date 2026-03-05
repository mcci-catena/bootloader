/*

Module:	mcci_arm_cm7.h

Function:
	ARM cm7 definitions without CMSIS overhead.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#ifndef _mcci_arm_cm7_h_
#define _mcci_arm_cm7_h_	/* prevent multiple includes */

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
|	Special function register values
|
\****************************************************************************/

/// \name CPU Special function registers
/// @{
#define	MCCI_CM7_SYSM_APSR		UINT32_C(0x00)	///< Flags from previous instructions
#define	MCCI_CM7_SYSM_IAPSR		UINT32_C(0x01)	///< Composite of IPSR and APSR
#define	MCCI_CM7_SYSM_EAPSR		UINT32_C(0x02)	///< Composite of EPSR and APSR
#define	MCCI_CM7_SYSM_XPSR		UINT32_C(0x03)	///< Composite of EPSR, IPSR and APSR
#define	MCCI_CM7_SYSM_IPSR		UINT32_C(0x05)	///< Interrupt status register
#define	MCCI_CM7_SYSM_EPSR		UINT32_C(0x06)	///< Exception status register
#define	MCCI_CM7_SYSM_IEPSR		UINT32_C(0x07)	///< Composite of IPSR and EPSR
#define	MCCI_CM7_SYSM_MSP		UINT32_C(0x08)	///< Main stack pointer
#define	MCCI_CM7_SYSM_PSP		UINT32_C(0x09)	///< Process stack pointer
#define	MCCI_CM7_SYSM_PRIMASK		UINT32_C(0x10)	///< priority mask register
#define	MCCI_CM7_SYSM_BASEPRI		UINT32_C(0x11)	///< base priority register
#define	MCCI_CM7_SYSM_BASEPRI_MAX	UINT32_C(0x12)	///< base priority max register
#define	MCCI_CM7_SYSM_FAULTMASK		UINT32_C(0x13)	///< register to raise priority to the HardFault level
#define	MCCI_CM7_SYSM_CONTROL		UINT32_C(0x14)	///< control register

/// \name PRIMASK special register fields
///	@{
#define	MCCI_CM7_SR_PRIMASK_DISABLE	(UINT32_C(1) << 0)	///< the bit to disable interrupts
///	@}

/// \name BASEPRI special register fields
///	@{
#define	MCCI_CM7_SR_BASEPRI_MASK	(UINT32_C(0xFF) << 0)	///< the base priority mask
#define	MCCI_CM7_SR_BASEPRI_VAL(n)	((n) << 0)		///< the base priority value
///	@}

/// \name FAULTMASK special register fields
///	@{
#define	MCCI_CM7_SR_FAULTMASK_FM	(UINT32_C(1) << 0)	///< the fault mask
///	@}

/* end of special-function registers */
/// @}

/****************************************************************************\
|
|	Register addresses
|
\****************************************************************************/

#define	MCCI_CM7_SCS_BASE		UINT32_C(0xE000E000)

/// \name SCnSCB (System Controls not in SCB) registers
///	@{
#define	MCCI_CM7_ICTR			UINT32_C(0xE000E004)
#define	MCCI_CM7_ACTLR			UINT32_C(0xE000E008)
///	@}

/// \name SYSTICK registers
///	@{
#define	MCCI_CM7_SYSTICK		UINT32_C(0xE000E010)
#define	MCCI_CM7_SYSTICK_CSR		(MCCI_CM7_SYSTICK + 0x0)
#define	MCCI_CM7_SYSTICK_RVR		(MCCI_CM7_SYSTICK + 0x4)
#define	MCCI_CM7_SYSTICK_CVR		(MCCI_CM7_SYSTICK + 0x8)
#define	MCCI_CM7_SYSTICK_CALIB		(MCCI_CM7_SYSTICK + 0xC)
///	@}

/// \name NVIC registers
///	@{
#define	MCCI_CM7_NVIC			UINT32_C(0xE000E100)
#define	MCCI_CM7_NVIC_ISER		(MCCI_CM7_NVIC + 0x000)
#define	MCCI_CM7_NVIC_ISER0		(MCCI_CM7_NVIC + 0x000)
#define	MCCI_CM7_NVIC_ISER1		(MCCI_CM7_NVIC + 0x004)
#define	MCCI_CM7_NVIC_ISER2		(MCCI_CM7_NVIC + 0x008)
#define	MCCI_CM7_NVIC_ISER3		(MCCI_CM7_NVIC + 0x00C)
#define	MCCI_CM7_NVIC_ISER4		(MCCI_CM7_NVIC + 0x010)
#define	MCCI_CM7_NVIC_ISER5		(MCCI_CM7_NVIC + 0x014)
#define	MCCI_CM7_NVIC_ISER6		(MCCI_CM7_NVIC + 0x018)
#define	MCCI_CM7_NVIC_ISER7		(MCCI_CM7_NVIC + 0x01C)
#define	MCCI_CM7_NVIC_ICER		(MCCI_CM7_NVIC + 0x080)
#define	MCCI_CM7_NVIC_ICER0		(MCCI_CM7_NVIC + 0x080)
#define	MCCI_CM7_NVIC_ICER1		(MCCI_CM7_NVIC + 0x084)
#define	MCCI_CM7_NVIC_ICER2		(MCCI_CM7_NVIC + 0x088)
#define	MCCI_CM7_NVIC_ICER3		(MCCI_CM7_NVIC + 0x08C)
#define	MCCI_CM7_NVIC_ICER4		(MCCI_CM7_NVIC + 0x090)
#define	MCCI_CM7_NVIC_ICER5		(MCCI_CM7_NVIC + 0x094)
#define	MCCI_CM7_NVIC_ICER6		(MCCI_CM7_NVIC + 0x098)
#define	MCCI_CM7_NVIC_ICER7		(MCCI_CM7_NVIC + 0x09C)
#define	MCCI_CM7_NVIC_ISPR		(MCCI_CM7_NVIC + 0x100)
#define	MCCI_CM7_NVIC_ISPR0		(MCCI_CM7_NVIC + 0x100)
#define	MCCI_CM7_NVIC_ISPR1		(MCCI_CM7_NVIC + 0x104)
#define	MCCI_CM7_NVIC_ISPR2		(MCCI_CM7_NVIC + 0x108)
#define	MCCI_CM7_NVIC_ISPR3		(MCCI_CM7_NVIC + 0x10C)
#define	MCCI_CM7_NVIC_ISPR4		(MCCI_CM7_NVIC + 0x110)
#define	MCCI_CM7_NVIC_ISPR5		(MCCI_CM7_NVIC + 0x114)
#define	MCCI_CM7_NVIC_ISPR6		(MCCI_CM7_NVIC + 0x118)
#define	MCCI_CM7_NVIC_ISPR7		(MCCI_CM7_NVIC + 0x11C)
#define	MCCI_CM7_NVIC_ICPR		(MCCI_CM7_NVIC + 0x180)
#define	MCCI_CM7_NVIC_ICPR0		(MCCI_CM7_NVIC + 0x180)
#define	MCCI_CM7_NVIC_ICPR1		(MCCI_CM7_NVIC + 0x184)
#define	MCCI_CM7_NVIC_ICPR2		(MCCI_CM7_NVIC + 0x188)
#define	MCCI_CM7_NVIC_ICPR3		(MCCI_CM7_NVIC + 0x18C)
#define	MCCI_CM7_NVIC_ICPR4		(MCCI_CM7_NVIC + 0x190)
#define	MCCI_CM7_NVIC_ICPR5		(MCCI_CM7_NVIC + 0x194)
#define	MCCI_CM7_NVIC_ICPR6		(MCCI_CM7_NVIC + 0x198)
#define	MCCI_CM7_NVIC_ICPR7		(MCCI_CM7_NVIC + 0x19C)
#define	MCCI_CM7_NVIC_IABR		(MCCI_CM7_NVIC + 0x200)
#define	MCCI_CM7_NVIC_IABR0		(MCCI_CM7_NVIC + 0x200)
#define	MCCI_CM7_NVIC_IABR1		(MCCI_CM7_NVIC + 0x204)
#define	MCCI_CM7_NVIC_IABR2		(MCCI_CM7_NVIC + 0x208)
#define	MCCI_CM7_NVIC_IABR3		(MCCI_CM7_NVIC + 0x20C)
#define	MCCI_CM7_NVIC_IABR4		(MCCI_CM7_NVIC + 0x210)
#define	MCCI_CM7_NVIC_IABR5		(MCCI_CM7_NVIC + 0x214)
#define	MCCI_CM7_NVIC_IABR6		(MCCI_CM7_NVIC + 0x218)
#define	MCCI_CM7_NVIC_IABR7		(MCCI_CM7_NVIC + 0x21C)
#define	MCCI_CM7_NVIC_IPR		(MCCI_CM7_NVIC + 0x300)
#define	MCCI_CM7_NVIC_IPR0		(MCCI_CM7_NVIC + 0x300)
#define	MCCI_CM7_NVIC_IPR1		(MCCI_CM7_NVIC + 0x304)
#define	MCCI_CM7_NVIC_IPR2		(MCCI_CM7_NVIC + 0x308)
#define	MCCI_CM7_NVIC_IPR3		(MCCI_CM7_NVIC + 0x30C)
#define	MCCI_CM7_NVIC_IPR4		(MCCI_CM7_NVIC + 0x310)
#define	MCCI_CM7_NVIC_IPR5		(MCCI_CM7_NVIC + 0x314)
#define	MCCI_CM7_NVIC_IPR6		(MCCI_CM7_NVIC + 0x318)
#define	MCCI_CM7_NVIC_IPR7		(MCCI_CM7_NVIC + 0x31C)
#define	MCCI_CM7_NVIC_IPR8		(MCCI_CM7_NVIC + 0x320)
#define	MCCI_CM7_NVIC_IPR9		(MCCI_CM7_NVIC + 0x324)
#define	MCCI_CM7_NVIC_IPR10		(MCCI_CM7_NVIC + 0x328)
#define	MCCI_CM7_NVIC_IPR11		(MCCI_CM7_NVIC + 0x32C)
#define	MCCI_CM7_NVIC_IPR12		(MCCI_CM7_NVIC + 0x330)
#define	MCCI_CM7_NVIC_IPR13		(MCCI_CM7_NVIC + 0x334)
#define	MCCI_CM7_NVIC_IPR14		(MCCI_CM7_NVIC + 0x338)
#define	MCCI_CM7_NVIC_IPR15		(MCCI_CM7_NVIC + 0x33C)
#define	MCCI_CM7_NVIC_IPR16		(MCCI_CM7_NVIC + 0x340)
#define	MCCI_CM7_NVIC_IPR17		(MCCI_CM7_NVIC + 0x344)
#define	MCCI_CM7_NVIC_IPR18		(MCCI_CM7_NVIC + 0x348)
#define	MCCI_CM7_NVIC_IPR19		(MCCI_CM7_NVIC + 0x34C)
#define	MCCI_CM7_NVIC_IPR20		(MCCI_CM7_NVIC + 0x350)
#define	MCCI_CM7_NVIC_IPR21		(MCCI_CM7_NVIC + 0x354)
#define	MCCI_CM7_NVIC_IPR22		(MCCI_CM7_NVIC + 0x358)
#define	MCCI_CM7_NVIC_IPR23		(MCCI_CM7_NVIC + 0x35C)
#define	MCCI_CM7_NVIC_IPR24		(MCCI_CM7_NVIC + 0x360)
#define	MCCI_CM7_NVIC_IPR25		(MCCI_CM7_NVIC + 0x364)
#define	MCCI_CM7_NVIC_IPR26		(MCCI_CM7_NVIC + 0x368)
#define	MCCI_CM7_NVIC_IPR27		(MCCI_CM7_NVIC + 0x36C)
#define	MCCI_CM7_NVIC_IPR28		(MCCI_CM7_NVIC + 0x370)
#define	MCCI_CM7_NVIC_IPR29		(MCCI_CM7_NVIC + 0x374)
#define	MCCI_CM7_NVIC_IPR30		(MCCI_CM7_NVIC + 0x378)
#define	MCCI_CM7_NVIC_IPR31		(MCCI_CM7_NVIC + 0x37C)
#define	MCCI_CM7_NVIC_IPR32		(MCCI_CM7_NVIC + 0x380)
#define	MCCI_CM7_NVIC_IPR33		(MCCI_CM7_NVIC + 0x384)
#define	MCCI_CM7_NVIC_IPR34		(MCCI_CM7_NVIC + 0x388)
#define	MCCI_CM7_NVIC_IPR35		(MCCI_CM7_NVIC + 0x38C)
#define	MCCI_CM7_NVIC_IPR36		(MCCI_CM7_NVIC + 0x390)
#define	MCCI_CM7_NVIC_IPR37		(MCCI_CM7_NVIC + 0x394)
#define	MCCI_CM7_NVIC_IPR38		(MCCI_CM7_NVIC + 0x398)
#define	MCCI_CM7_NVIC_IPR39		(MCCI_CM7_NVIC + 0x39C)
#define	MCCI_CM7_NVIC_IPR40		(MCCI_CM7_NVIC + 0x3A0)
#define	MCCI_CM7_NVIC_IPR41		(MCCI_CM7_NVIC + 0x3A4)
#define	MCCI_CM7_NVIC_IPR42		(MCCI_CM7_NVIC + 0x3A8)
#define	MCCI_CM7_NVIC_IPR43		(MCCI_CM7_NVIC + 0x3AC)
#define	MCCI_CM7_NVIC_IPR44		(MCCI_CM7_NVIC + 0x3B0)
#define	MCCI_CM7_NVIC_IPR45		(MCCI_CM7_NVIC + 0x3B4)
#define	MCCI_CM7_NVIC_IPR46		(MCCI_CM7_NVIC + 0x3B8)
#define	MCCI_CM7_NVIC_IPR47		(MCCI_CM7_NVIC + 0x3BC)
#define	MCCI_CM7_NVIC_IPR48		(MCCI_CM7_NVIC + 0x3C0)
#define	MCCI_CM7_NVIC_IPR49		(MCCI_CM7_NVIC + 0x3C4)
#define	MCCI_CM7_NVIC_IPR50		(MCCI_CM7_NVIC + 0x3C8)
#define	MCCI_CM7_NVIC_IPR51		(MCCI_CM7_NVIC + 0x3CC)
#define	MCCI_CM7_NVIC_IPR52		(MCCI_CM7_NVIC + 0x3D0)
#define	MCCI_CM7_NVIC_IPR53		(MCCI_CM7_NVIC + 0x3D4)
#define	MCCI_CM7_NVIC_IPR54		(MCCI_CM7_NVIC + 0x3D8)
#define	MCCI_CM7_NVIC_IPR55		(MCCI_CM7_NVIC + 0x3DC)
#define	MCCI_CM7_NVIC_IPR56		(MCCI_CM7_NVIC + 0x3E0)
#define	MCCI_CM7_NVIC_IPR57		(MCCI_CM7_NVIC + 0x3E4)
#define	MCCI_CM7_NVIC_IPR58		(MCCI_CM7_NVIC + 0x3E8)
#define	MCCI_CM7_NVIC_IPR59		(MCCI_CM7_NVIC + 0x3EC)
///	@}

/// \name SCB registers
///	@{
#define	MCCI_CM7_SCB			UINT32_C(0xE000ED00)
#define	MCCI_CM7_SCB_CPUID		(MCCI_CM7_SCB + 0x00)
#define	MCCI_CM7_SCB_ICSR		(MCCI_CM7_SCB + 0x04)
#define	MCCI_CM7_SCB_VTOR		(MCCI_CM7_SCB + 0x08)
#define	MCCI_CM7_SCB_AIRCR		(MCCI_CM7_SCB + 0x0C)
#define	MCCI_CM7_SCB_SCR		(MCCI_CM7_SCB + 0x10)
#define	MCCI_CM7_SCB_CCR		(MCCI_CM7_SCB + 0x14)
#define	MCCI_CM7_SCB_SHPR1		(MCCI_CM7_SCB + 0x18)
#define	MCCI_CM7_SCB_SHPR2		(MCCI_CM7_SCB + 0x1C)
#define	MCCI_CM7_SCB_SHPR3		(MCCI_CM7_SCB + 0x20)
#define	MCCI_CM7_SCB_SHCSR		(MCCI_CM7_SCB + 0x24)
#define	MCCI_CM7_SCB_CFSR		(MCCI_CM7_SCB + 0x28)
#define	MCCI_CM7_SCB_HFSR		(MCCI_CM7_SCB + 0x2C)
#define	MCCI_CM7_SCB_DFSR		(MCCI_CM7_SCB + 0x30)
#define	MCCI_CM7_SCB_MMFAR		(MCCI_CM7_SCB + 0x34)
#define	MCCI_CM7_SCB_BFAR		(MCCI_CM7_SCB + 0x38)
#define	MCCI_CM7_SCB_ID_PFR0		(MCCI_CM7_SCB + 0x40)
#define	MCCI_CM7_SCB_ID_PFR1		(MCCI_CM7_SCB + 0x44)
#define	MCCI_CM7_SCB_ID_DFR0		(MCCI_CM7_SCB + 0x48)
#define	MCCI_CM7_SCB_ID_AFR0		(MCCI_CM7_SCB + 0x4C)
#define	MCCI_CM7_SCB_ID_MMFR0		(MCCI_CM7_SCB + 0x50)
#define	MCCI_CM7_SCB_ID_MMFR1		(MCCI_CM7_SCB + 0x54)
#define	MCCI_CM7_SCB_ID_MMFR2		(MCCI_CM7_SCB + 0x58)
#define	MCCI_CM7_SCB_ID_MMFR3		(MCCI_CM7_SCB + 0x5C)
#define	MCCI_CM7_SCB_ID_ISAR0		(MCCI_CM7_SCB + 0x60)
#define	MCCI_CM7_SCB_ID_ISAR1		(MCCI_CM7_SCB + 0x64)
#define	MCCI_CM7_SCB_ID_ISAR2		(MCCI_CM7_SCB + 0x68)
#define	MCCI_CM7_SCB_ID_ISAR3		(MCCI_CM7_SCB + 0x6C)
#define	MCCI_CM7_SCB_ID_ISAR4		(MCCI_CM7_SCB + 0x70)
#define	MCCI_CM7_SCB_CLIDR		(MCCI_CM7_SCB + 0x78)
#define	MCCI_CM7_SCB_CTR		(MCCI_CM7_SCB + 0x7C)
#define	MCCI_CM7_SCB_CCSIDR		(MCCI_CM7_SCB + 0x80)
#define	MCCI_CM7_SCB_CSSELR		(MCCI_CM7_SCB + 0x84)
#define	MCCI_CM7_SCB_CPACR		(MCCI_CM7_SCB + 0x88)
#define	MCCI_CM7_SCB_STIR		(MCCI_CM7_SCB + 0x200)
#define	MCCI_CM7_SCB_ICIALLU		(MCCI_CM7_SCB + 0x250)
#define	MCCI_CM7_SCB_ICIMVAU		(MCCI_CM7_SCB + 0x258)
#define	MCCI_CM7_SCB_DCIMVAC		(MCCI_CM7_SCB + 0x25C)
#define	MCCI_CM7_SCB_DCISW		(MCCI_CM7_SCB + 0x260)
#define	MCCI_CM7_SCB_DCCMVAU		(MCCI_CM7_SCB + 0x264)
#define	MCCI_CM7_SCB_DCCMVAC		(MCCI_CM7_SCB + 0x268)
#define	MCCI_CM7_SCB_DCCSW		(MCCI_CM7_SCB + 0x26C)
#define	MCCI_CM7_SCB_DCCIMVAC		(MCCI_CM7_SCB + 0x270)
#define	MCCI_CM7_SCB_DCCISW		(MCCI_CM7_SCB + 0x274)
#define	MCCI_CM7_SCB_BPIALL		(MCCI_CM7_SCB + 0x278)
#define	MCCI_CM7_SCB_ITCMCR		(MCCI_CM7_SCB + 0x290)
#define	MCCI_CM7_SCB_DTCMCR		(MCCI_CM7_SCB + 0x294)
#define	MCCI_CM7_SCB_AHBPCR		(MCCI_CM7_SCB + 0x298)
#define	MCCI_CM7_SCB_CACR		(MCCI_CM7_SCB + 0x29C)
#define	MCCI_CM7_SCB_AHBSCR		(MCCI_CM7_SCB + 0x2A0)
#define	MCCI_CM7_SCB_ABFSR		(MCCI_CM7_SCB + 0x2A8)
#define	MCCI_CM7_SCB_IEBR0		(MCCI_CM7_SCB + 0x2B0)
#define	MCCI_CM7_SCB_IEBR1		(MCCI_CM7_SCB + 0x2B4)
#define	MCCI_CM7_SCB_DEBR0		(MCCI_CM7_SCB + 0x2B8)
#define	MCCI_CM7_SCB_DEBR1		(MCCI_CM7_SCB + 0x2BC)
#define	MCCI_CM7_SCB_PID4		(MCCI_CM7_SCB + 0x2D0)
#define	MCCI_CM7_SCB_PID5		(MCCI_CM7_SCB + 0x2D4)
#define	MCCI_CM7_SCB_PID6		(MCCI_CM7_SCB + 0x2D8)
#define	MCCI_CM7_SCB_PID7		(MCCI_CM7_SCB + 0x2DC)
#define	MCCI_CM7_SCB_PID0		(MCCI_CM7_SCB + 0x2E0)
#define	MCCI_CM7_SCB_PID1		(MCCI_CM7_SCB + 0x2E4)
#define	MCCI_CM7_SCB_PID2		(MCCI_CM7_SCB + 0x2E8)
#define	MCCI_CM7_SCB_PID3		(MCCI_CM7_SCB + 0x2EC)
#define	MCCI_CM7_SCB_CID0		(MCCI_CM7_SCB + 0x2F0)
#define	MCCI_CM7_SCB_CID1		(MCCI_CM7_SCB + 0x2F4)
#define	MCCI_CM7_SCB_CID2		(MCCI_CM7_SCB + 0x2F8)
#define	MCCI_CM7_SCB_CID3		(MCCI_CM7_SCB + 0x2FC)
///	@}

/// \name MPU registers
///	@{
#define	MCCI_CM7_MPU			UINT32_C(0xE000EF30)
#define	MCCI_CM7_MPU_FPCCR		(MCCI_CM7_MPU + 0x04)	//<
#define	MCCI_CM7_MPU_FPCAR		(MCCI_CM7_MPU + 0x08)	//<
#define	MCCI_CM7_MPU_FPDSCR		(MCCI_CM7_MPU + 0x0C)	//<
#define	MCCI_CM7_MPU_MVFR0		(MCCI_CM7_MPU + 0x10)	//<
#define	MCCI_CM7_MPU_MVFR1		(MCCI_CM7_MPU + 0x14)	//<
#define	MCCI_CM7_MPU_MVFR2		(MCCI_CM7_MPU + 0x18)	//<
///	@}

/****************************************************************************\
|
|	Register bits
|
\****************************************************************************/

/// \name SYSTICK CSR bits
///	@{
#define MCCI_CM7_SYSTICK_CSR_RSV17		UINT32_C(0xFFFE0000)	///< reserved
#define MCCI_CM7_SYSTICK_CSR_COUNTFLAG		(UINT32_C(1) << 16)	///< timer has counted to zero
#define MCCI_CM7_SYSTICK_CSR_RSV3		UINT32_C(0x0000FFF8)	///< reserved
#define MCCI_CM7_SYSTICK_CSR_CLKSOURCE		(UINT32_C(1) << 2)	///< use processor (not external) clock
#define MCCI_CM7_SYSTICK_CSR_TICKINT		(UINT32_C(1) << 1)	///< enable tick exception
#define MCCI_CM7_SYSTICK_CSR_ENABLE		(UINT32_C(1) << 0)	///< enable counter
///	@}

/// \name SYSTICK RVR bits
///	@{
#define MCCI_CM7_SYSTICK_RVR_RSV24		UINT32_C(0xFF000000)	///< reserved, zero
#define MCCI_CM7_SYSTICK_RVR_RELOAD		UINT32_C(0x00FFFFFF)	///< reload value
///	@}

/// \name SYSTICK CVR bits
///	@{
#define MCCI_CM7_SYSTICK_CVR_RSV24		UINT32_C(0xFF000000)	///< reserved, read as zero
#define MCCI_CM7_SYSTICK_CVR_CURRENT		UINT32_C(0x00FFFFFF)	///< current value
///	@}

/// \name SYSTICK CALIB bits
///	@{
#define MCCI_CM7_SYSTICK_CALIB_NOREF		(UINT32_C(1) << 31)	///< reference clock is not implemented
#define MCCI_CM7_SYSTICK_CALIB_SKEW		(UINT32_C(1) << 30)	///< 10ms cal value is inexact
#define MCCI_CM7_SYSTICK_CALIB_RSV24		(UINT32_C(0x3F) << 24)	///< reserved, zero
#define MCCI_CM7_SYSTICK_CALIB_TENMS		UINT32_C(0x00FFFFFF)	///< if non-zero, use this as reload value for 10ms ticks
///	@}

/// \name NVIC IPR bits

/// \name SCB CPUID fields
/// 	@{
#define	MCCI_CM7_SCB_CPUID_IMPLEMENTER		(UINT32_C(0xFF) << 24)	///< Implementer code
#define	MCCI_CM7_SCB_CPUID_VARIANT		(UINT32_C(0xF) << 20)	///< Variant code
#define	MCCI_CM7_SCB_CPUID_ARCHITECTURE		(UINT32_C(0xF) << 16)	///< Architecture code
#define	MCCI_CM7_SCB_CPUID_PARTNO		(UINT32_C(0xFFF) << 4)	///< Part number
#define	MCCI_CM7_SCB_CPUID_REVISION		(UINT32_C(0xF) << 0)	///< Revision
///	@}

/// \name SCB ICSR fields
///	@{
#define	MCCI_CM7_SCB_ICSR_NMIPENDSET		(UINT32_C(1) << 31)	///<
#define	MCCI_CM7_SCB_ICSR_RSV29			(UINT32_C(3) << 29)	///<
#define	MCCI_CM7_SCB_ICSR_PENDSVSET		(UINT32_C(1) << 28)	///<
#define	MCCI_CM7_SCB_ICSR_PENDSVCLR		(UINT32_C(1) << 27)	///<
#define	MCCI_CM7_SCB_ICSR_PENDSTSET		(UINT32_C(1) << 26)	///<
#define	MCCI_CM7_SCB_ICSR_PENDSTCLR		(UINT32_C(1) << 25)	///<
#define	MCCI_CM7_SCB_ICSR_RSV24			(UINT32_C(1) << 24)	///<
#define	MCCI_CM7_SCB_ICSR_ISRPREEMPT		(UINT32_C(1) << 23)	///<
#define	MCCI_CM7_SCB_ICSR_ISRPENDING		(UINT32_C(1) << 22)	///<
#define	MCCI_CM7_SCB_ICSR_VECTPENDING		(UINT32_C(0x1FF) << 12)	///<
#define	MCCI_CM7_SCB_ICSR_RETTOBASE		(UINT32_C(1) << 11)	///<
#define	MCCI_CM7_SCB_ICSR_VECTACTIVE		(UINT32_C(0x1FF) << 0)	///<
///	@}

/// \name SCB VTOR fields
///	@{
#define	MCCI_CM7_SCB_VTOR_TBLOFF		UINT32_C(0xFFFFFF80)	///<
///	@}

/// \name SCB AIRCR fields (Appplication Interrupt and Reset Control)
///	@{
#define	MCCI_CM7_SCB_AIRCR_VECTKEY		(UINT32_C(0xFFFF) << 16)	///< Vector key
#define	MCCI_CM7_SCB_AIRCR_VECTKEY_VALUE	(UINT32_C(0x05FA) << 16)	///< Value to write to unlock regster.
#define	MCCI_CM7_SCB_AIRCR_ENDIANNESS		(UINT32_C(1) << 15)		///< 0=little, 1=big endian
#define	MCCI_CM7_SCB_AIRCR_PRIGROUP		(UINT32_C(7) << 8)		///< Priority grouping position
#define	MCCI_CM7_SCB_AIRCR_PRIGROUP_N(n)	((n) << 8)			///<
#define	MCCI_CM7_SCB_AIRCR_SYSRESETREQ		(UINT32_C(1) << 2)		///< System reset request
#define	MCCI_CM7_SCB_AIRCR_VECTCLRACTIVE	(UINT32_C(1) << 1)		///<
#define	MCCI_CM7_SCB_AIRCR_VECTRESET		(UINT32_C(1) << 0)		///<
///	@}

/// \name SCB SCR fields
///	@{
#define	MCCI_CM7_SCB_SCR_SEVONPEND		(UINT32_C(1) << 4)	///<
#define	MCCI_CM7_SCB_SCR_SLEEPDEEP		(UINT32_C(1) << 2)	///<
#define	MCCI_CM7_SCB_SCR_SLEEPONEXIT		(UINT32_C(1) << 1)	///<
///	@}

/// \name SCB Configuration Control Register bits
///	@{
#define	MCCI_CM7_SCB_CCR_BP			(UINT32_C(1) << 18)	///<
#define	MCCI_CM7_SCB_CCR_IC			(UINT32_C(1) << 17)	///<
#define	MCCI_CM7_SCB_CCR_DC			(UINT32_C(1) << 16)	///<
#define	MCCI_CM7_SCB_CCR_STKALIGN		(UINT32_C(1) << 9)	///<
#define	MCCI_CM7_SCB_CCR_BFHFNMIGN		(UINT32_C(1) << 8)	///<
#define	MCCI_CM7_SCB_CCR_DIV_0_TRP		(UINT32_C(1) << 4)	///<
#define	MCCI_CM7_SCB_CCR_UNALIGN_TRP		(UINT32_C(1) << 3)	///<
#define	MCCI_CM7_SCB_CCR_USERSETMPEND		(UINT32_C(1) << 1)	///<
#define	MCCI_CM7_SCB_CCR_NONBASETHRDENA		(UINT32_C(1) << 0)	///<
///	@}

/// \name SCB SHPR access
///	@{
#define	MCCI_CM7_SCB_SHPR_PRI			(UINT32_C(7) << 5)	///< priority bits within a byte

#define	MCCI_CM7_PRI_INDEX_MEM_MANAGE		UINT32_C(4)	///< priority of MemManage
#define	MCCI_CM7_PRI_INDEX_BUS_FAULT		UINT32_C(5)	///< priority of BusFault
#define	MCCI_CM7_PRI_INDEX_USAGE_FAULT		UINT32_C(6)	///< priority of UsageFault
#define	MCCI_CM7_PRI_INDEX_SVC			UINT32_C(11)	///< priority of SVCall
#define	MCCI_CM7_PRI_INDEX_DEBUG_MONITOR	UINT32_C(12)	///< priority of DebugMonitor
#define	MCCI_CM7_PRI_INDEX_PENDSV		UINT32_C(14)	///< priority of PendSV
#define	MCCI_CM7_PRI_INDEX_SYSTICK		UINT32_C(15)	///< priority of systick

/// 	\brief return register for a given handler index
static inline uint32_t
McciCm7_SCB_SHPR_getRegister(
	uint32_t	handlerIndex
	)
	{
	return handlerIndex < 8
		? MCCI_CM7_SCB_SHPR1
		: handlerIndex < 12 ? MCCI_CM7_SCB_SHPR2 : MCCI_CM7_SCB_SHPR3;
	}

///	\brief return byte mask for a given handler index
static inline uint32_t
McciCm7_SCB_SHPR_getMask(
	uint32_t	handlerIndex
	)
	{
	// compute and return the mask for a given bit
	return UINT32_C(0xE0) << (8 * (handlerIndex & 3));
	}
///	@}

/// \name SCB System Handler Control and State Register bits
///	@{
#define	MCCI_CM7_SCB_SHCSR_USGFAULTENA		(UINT32_C(1) << 18)	///<
#define	MCCI_CM7_SCB_SHCSR_BUSFAULTENA		(UINT32_C(1) << 17)	///<
#define	MCCI_CM7_SCB_SHCSR_MEMFAULTENA		(UINT32_C(1) << 16)	///<
#define	MCCI_CM7_SCB_SHCSR_SVCALLPENDED		(UINT32_C(1) << 15)	///<
#define	MCCI_CM7_SCB_SHCSR_BUSFAULTPENDED	(UINT32_C(1) << 14)	///<
#define	MCCI_CM7_SCB_SHCSR_MEMFAULTPENDED	(UINT32_C(1) << 13)	///<
#define	MCCI_CM7_SCB_SHCSR_USGFAULTPENDED	(UINT32_C(1) << 12)	///<
#define	MCCI_CM7_SCB_SHCSR_SYSTICKACT		(UINT32_C(1) << 11)	///<
#define	MCCI_CM7_SCB_SHCSR_PENDSVACT		(UINT32_C(1) << 10)	///<
#define	MCCI_CM7_SCB_SHCSR_MONITORACT		(UINT32_C(1) << 8)	///<
#define	MCCI_CM7_SCB_SHCSR_SVCALLACT		(UINT32_C(1) << 7)	///<
#define	MCCI_CM7_SCB_SHCSR_USGFAULTACT		(UINT32_C(1) << 3)	///<
#define	MCCI_CM7_SCB_SHCSR_BUSFAULTACT		(UINT32_C(1) << 1)	///<
#define	MCCI_CM7_SCB_SHCSR_MEMFAULTACT		(UINT32_C(1) << 0)	///<
///	@}

/****************************************************************************\
|
|	Interrupt Number Definition
|
\****************************************************************************/

/// \name Cortex-M Processor Exceptions Numbers
///	@{
#define	MCCI_CM7_IRQ_BASE		UINT32_C(256)				///< Cortext-M Processor Exception Number Base
#define	MCCI_CM7_IRQ_NonMaskableInt	(MCCI_CM7_IRQ_BASE + UINT32_C(2))	///< Non Maskable Interrupt
#define	MCCI_CM7_IRQ_HardFault		(MCCI_CM7_IRQ_BASE + UINT32_C(3))	///< Cortex-M Memory Management	Interrupt
#define	MCCI_CM7_IRQ_MemoryManagement	(MCCI_CM7_IRQ_BASE + UINT32_C(4))	///< Cortex-M Memory Management	Interrupt
#define	MCCI_CM7_IRQ_BusFault		(MCCI_CM7_IRQ_BASE + UINT32_C(5))	///< Cortex-M Bus Fault	Interrupt
#define	MCCI_CM7_IRQ_UsageFault		(MCCI_CM7_IRQ_BASE + UINT32_C(6))	///< Cortex-M Usage Fault Interrupt
#define	MCCI_CM7_IRQ_SVCall		(MCCI_CM7_IRQ_BASE + UINT32_C(11))	///< Cortex-M SV Call Interrupt
#define	MCCI_CM7_IRQ_DebugMonitor	(MCCI_CM7_IRQ_BASE + UINT32_C(12))	///< Cortex-M Debug Monitor Interrupt
#define	MCCI_CM7_IRQ_PendSV		(MCCI_CM7_IRQ_BASE + UINT32_C(14))	///< Cortex-M Pend SV Interrupt
#define	MCCI_CM7_IRQ_SysTick		(MCCI_CM7_IRQ_BASE + UINT32_C(15))	///< Cortex-M System Tick Interrupt
///	@}

/****************************************************************************\
|
|	Register access primitives
|
\****************************************************************************/

/// \brief write a 32-bit value to a cm7 register
__attribute__((__always_inline__))
static inline uint32_t
McciArm_putReg(uint32_t reg, uint32_t val)
	{
	*(volatile uint32_t *)reg = val;
	return val;
	}

/// \brief read a 32-bit value from a cm7 register
__attribute__((__always_inline__))
static inline uint32_t
McciArm_getReg(uint32_t reg)
	{
	return *(volatile uint32_t *)reg;
	}

/// \brief and/or 32-bit values to a cm7 register
__attribute__((__always_inline__))
static inline uint32_t
McciArm_putRegAndOr(uint32_t reg, uint32_t andVal, uint32_t orVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		(rValue & andVal) | orVal
		);
	}

/// \brief or 32-bit values to a cm7 register
__attribute__((__always_inline__))
static inline uint32_t
McciArm_putRegOr(uint32_t reg, uint32_t orVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		rValue | orVal
		);
	}

/// \brief clear out 32-bit values to a cm7 register
__attribute__((__always_inline__))
static inline uint32_t
McciArm_putRegClear(uint32_t reg, uint32_t clearVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		rValue & ~clearVal
		);
	}

///
/// \brief clear and set 32-bit values to a cm7 register
///
/// \param [in] reg register to be modified
/// \param [in] clearVal mask of bits to be cleared (1 in mask clears bit in reg)
/// \param [in] setVal mask of bits to be set
///
/// \note this is subtly different than \ref McciArm_putRegMasked,
///	in that \p setVal is not modified by \p clearVal. Any bits
///	set in \p setVal are unconditionally set in \p reg, whereas
///	\ref McciArm_putRegMasked only changes bits that are set
///	in its \c maskVal parameter.
///
/// \see McciArm_putRegMasked
///
__attribute__((__always_inline__))
static inline uint32_t
McciArm_putRegClearSet(uint32_t reg, uint32_t clearVal, uint32_t setVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		(rValue & ~clearVal) | setVal
		);
	}

///
/// \brief store to cm7 register under mask
///
/// \param [in] reg register to be modified
/// \param [in] maskVal mask of bits to be modifed
/// \param [in] modVal where \p maskVal is 1, provides values of bits
///
/// \note this is subtly different than \ref McciArm_putRegClearSet,
///	in that any bits in \b ~maskVal are not changed, regardless of
///	corresponding bits in \p modVal.
///
/// \see McciArm_putRegClearSet
/// \see https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
///
__attribute__((__always_inline__))
static inline uint32_t
McciArm_putRegMasked(uint32_t reg, uint32_t maskVal, uint32_t modVal)
	{
	uint32_t const rValue = McciArm_getReg(reg);

	return McciArm_putReg(
		reg,
		rValue ^ ((rValue ^ modVal) & maskVal)
		/* same as (rValue & ~maskVal) | (modVal & maskVal) */
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
	__asm volatile ("MSR msp,%0\n" :: "r"(stack): );
	}

///
/// \brief get priority mask
///
/// \return current value of PRIMASK register
///
/// \note only bit 0 is implemented on CM7 CPUs. If cleared, it enables
///	interrupts; if set it enables interrupts.
///
__attribute__((__always_inline__)) static inline
uint32_t
McciArm_getPRIMASK(
	void
	)
	{
	uint32_t primask;

	__asm volatile ("MRS %0,primask" : "=r"(primask));
	return primask;
	}

///
/// \brief set priority mask
///
/// \param [in] primask new value of PRIMASK register
///
/// \note only bit 0 is implemented on CM7 CPUs. If cleared, it enables
///	interrupts; if set it enables interrupts.
///
__attribute__((__always_inline__)) static inline
void
McciArm_setPRIMASK(
	uint32_t primask
	)
	{
	__asm volatile ("MSR primask,%0" :: "r"(primask) : "memory");
	}

///
/// \brief Disable interrupts and return previous state
///
/// \return previous value of PRIMASK register.
///
__attribute__((__always_inline__)) static inline
uint32_t
McciArm_disableInterrupts(
	void
	)
	{
	uint32_t const primask = McciArm_getPRIMASK();
	__asm volatile ("cpsid i" ::: "memory");
	return primask;
	}

///
/// \brief insert a instruction synchronization barrier
///
/// \details
///	Force flush the pipeline in the processor, so that all instructions
///	following the ISB are fetched from cache or memory, after the
///	instruction has been completed.
///
__attribute__((always_inline)) static inline
void McciArm_InstructionSynchBarrier(
	void
	)
	{
	__asm volatile ("isb 0xF" ::: "memory");
	}

///
/// \brief insert a data synchronization barrier
///
/// \details
///	Force all pending memory operations to complete before
///	continuing.
///
__attribute__((always_inline)) static inline
void McciArm_DataSynchBarrier(
	void
	)
	{
	__asm volatile ("dsb 0xF" ::: "memory");
	}

///
/// \brief enable NVIC interrupt
///
/// \details
///	Enable NVIC interrupt
///
/// \param [in] interruptNumber device specific interrupt number
///
__attribute__((always_inline)) static inline
void McciArm_NvicEnableIrq(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		__asm volatile ("" ::: "memory");
		McciArm_putReg(
			MCCI_CM7_NVIC_ISER + (interruptNumber >> 5) * 4,
			(1u << (interruptNumber & 31u))
			);
		__asm volatile ("" ::: "memory");
		}
	}

///
/// \brief disable NVIC interrupt
///
/// \details
///	Disable NVIC interrupt
///
/// \param [in] interruptNumber device specific interrupt number
///
__attribute__((always_inline)) static inline
void McciArm_NvicDisableIrq(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		McciArm_putReg(
			MCCI_CM7_NVIC_ICER + (interruptNumber >> 5) * 4,
			(1u << (interruptNumber & 31u))
			);
		__asm volatile ("dsb 0xF" ::: "memory");
		__asm volatile ("isb 0xF" ::: "memory");
		}
	}

///
/// \brief get NVIC interrupt enable state
///
/// \details
///	Get NVIC interrupt enable state
///
/// \param [in] interruptNumber device specific interrupt number
///
/// \return interrupt enable state
///
__attribute__((always_inline)) static inline
int McciArm_NvicGetEnableIrq(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		return McciArm_getReg(
			MCCI_CM7_NVIC_ISER + (interruptNumber >> 5) * 4
			) & (1u << (interruptNumber & 31u)) ? 1 : 0;
		}
	else
		{
		return 0;
		}
	}

///
/// \brief get NVIC interrupt pending state
///
/// \details
///	Get NVIC interrupt pending state
///
/// \param [in] interruptNumber device specific interrupt number
///
/// \return interrupt pending state. 1 is interrupt pending.
///
__attribute__((always_inline)) static inline
int McciArm_NvicGetPendingIrq(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		return McciArm_getReg(
			MCCI_CM7_NVIC_ISPR + (interruptNumber >> 5) * 4
			) & (1u << (interruptNumber & 31u)) ? 1 : 0;
		}
	else
		{
		return 0;
		}
	}

///
/// \brief set NVIC interrupt pending state
///
/// \details
///	Set NVIC interrupt pending state
///
/// \param [in] interruptNumber device specific interrupt number
///
__attribute__((always_inline)) static inline
void McciArm_NvicSetPendingIrq(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		McciArm_putReg(
			MCCI_CM7_NVIC_ISPR + (interruptNumber >> 5) * 4,
			(1u << (interruptNumber & 31u))
			);
		}
	}

///
/// \brief clear NVIC interrupt pending state
///
/// \details
///	Clear NVIC interrupt pending state
///
/// \param [in] interruptNumber device specific interrupt number
///
__attribute__((always_inline)) static inline
void McciArm_NvicClearPendingIrq(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		McciArm_putReg(
			MCCI_CM7_NVIC_ICPR + (interruptNumber >> 5) * 4,
			(1u << (interruptNumber & 31u))
			);
		}
	}

///
/// \brief set NVIC priority group
///
/// \details
///	Set NVIC priority group
///
/// \param [in] priorityGroup priority grouping field
///
__attribute__((always_inline)) static inline
void McciArm_NvicSetPriorityGroup(
	uint32_t priorityGroup
	)
	{
	McciArm_putRegClearSet(
		MCCI_CM7_SCB_AIRCR,
		MCCI_CM7_SCB_AIRCR_VECTKEY | MCCI_CM7_SCB_AIRCR_PRIGROUP,
		MCCI_CM7_SCB_AIRCR_VECTKEY_VALUE | MCCI_CM7_SCB_AIRCR_PRIGROUP_N(priorityGroup & 7)
		);
	}

///
/// \brief get NVIC priority group
///
/// \details
///	Get NVIC priority group
///
/// \return priority grouping field
///
__attribute__((always_inline)) static inline
uint32_t McciArm_NvicGetPriorityGroup(
	void
	)
	{
	return MCCI_BOOTLOADER_VALUE_GET_FIELD(
		McciArm_getReg(MCCI_CM7_SCB_AIRCR),
		MCCI_CM7_SCB_AIRCR_PRIGROUP
		);
	}

///
/// \brief set NVIC interrupt priority
///
/// \details
///	Set NVIC interrupt priority
///
/// \param [in] interruptNumber Specific interrupt number
/// \param [in] priority Priority to set
///
__attribute__((always_inline)) static inline
void McciArm_NvicSetPriority(
	uint32_t interruptNumber,
	uint32_t priority
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		*(volatile uint8_t *)(MCCI_CM7_NVIC_IPR + interruptNumber) =
			(uint8_t)(priority << 4);
		}
	else if (interruptNumber >= MCCI_CM7_IRQ_MemoryManagement)
		{
		*(volatile uint8_t *)(MCCI_CM7_SCB_SHPR1 + interruptNumber - MCCI_CM7_IRQ_MemoryManagement) =
			(uint8_t)(priority << 4);
		}
	}

///
/// \brief get NVIC interrupt priority
///
/// \details
///	Get NVIC interrupt priority
///
/// \param [in] interruptNumber Specific interrupt number
///
/// \return interrupt priority
///
__attribute__((always_inline)) static inline
uint32_t McciArm_NvicGetPriority(
	uint32_t interruptNumber
	)
	{
	if (interruptNumber < MCCI_CM7_IRQ_BASE)
		{
		return *(volatile uint8_t *)(MCCI_CM7_NVIC_IPR + interruptNumber) >> 4;
		}
	else if (interruptNumber >= MCCI_CM7_IRQ_MemoryManagement)
		{
		return *(volatile uint8_t *)(MCCI_CM7_SCB_SHPR1 + interruptNumber - MCCI_CM7_IRQ_MemoryManagement) >> 4;
		}
	else
		{
		return 0;
		}
	}

///
/// \brief system reset
///
/// \details
///	Initiate a system reset request to reset the MCU.
///
__attribute__((__noreturn__)) __attribute__((always_inline)) static inline
void McciArm_NvicSystemReset(
	void
	)
	{
	__asm volatile ("dsb 0xF" ::: "memory");
	McciArm_putRegAndOr(
		MCCI_CM7_SCB_AIRCR,
		MCCI_CM7_SCB_AIRCR_PRIGROUP,
		MCCI_CM7_SCB_AIRCR_VECTKEY_VALUE | MCCI_CM7_SCB_AIRCR_SYSRESETREQ
		);
	__asm volatile ("dsb 0xF" ::: "memory");
	for (;;)
		{
		__asm volatile ("nop");
		}
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
/// Every Cortex M7 application begins with two DWORDs. The first is
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
/// \brief Cortex M7 interrupt vectors (low level view)
///
/// This structure represents the vectors page as an array of 256 32-bit vectors.
/// It's used mostly for initialization and for building up larger structures.
///
typedef struct Mcci_CortexM7VectorsContents_s
	{
	uint32_t	vectors[256];
	} Mcci_CortexM7VectorsContents_t;

///
/// \brief Cortex M7 interrupt vector object
///
/// This union wraps the interrupt vector contents, both so we can always
/// reference fields with consistent names (`AppEntry.stack` etc.), and to allow
/// us to view the vectors as either an AppEntry description or a table of
/// vectors.
///
typedef union Mcci_CortexM7Vectors_u
	{
	Mcci_CortexAppEntryContents_t	CortexAppEntry;		//< View instance as a CortexM7 AppEntry.
	Mcci_CortexAppEntry_t		CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	Mcci_CortexM7VectorsContents_t	CortexVectors;		//< View instance as vectors.
	} Mcci_CortexM7Vectors_t;

/****************************************************************************\
|
|	End of file
|
\****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _mcci_arm_cm7_h_ */
