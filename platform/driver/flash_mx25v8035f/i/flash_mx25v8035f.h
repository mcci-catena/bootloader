/*

Module:	flash_mx25v8035f.h

Function:
	Definitions for Macronix MX258035F flash chip.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _flash_mx25v8035f_h_
#define _flash_mx25v8035f_h_	/* prevent multiple includes */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/* MX25V8035F commands */
#define	MX25V8035F_CMD_READ		0x03u	/* Read */
#define	MX25V8035F_CMD_FAST_READ	0x0Bu	/* Fast read */
#define	MX25V8035F_CMD_PP		0x02u	/* Page Program */
#define	MX25V8035F_CMD_SE		0x20u	/* Sector Erase */
#define	MX25V8035F_CMD_BE_32K		0x52u	/* Block Erase 32KB */
#define	MX25V8035F_CMD_BE		0xD8u	/* Block Erase 64KB */
#define	MX25V8035F_CMD_CE		0x60u	/* Chip Erase */
#define	MX25V8035F_CMD_RDSFDP		0x5Au	/* Read SFDP */
#define	MX25V8035F_CMD_WREN		0x06u	/* Write Enable */
#define	MX25V8035F_CMD_WRDI		0x04u	/* Write Disable */
#define	MX25V8035F_CMD_RDSR		0x05u	/* Read Status Register */
#define	MX25V8035F_CMD_RDCR		0x15u	/* Read Configuration Register */
#define	MX25V8035F_CMD_WRSR		0x01u	/* Write Status Register */
#define	MX25V8035F_CMD_SUSPEND		0x75u	/* PGM/ERS Suspend */
#define	MX25V8035F_CMD_RESUME		0x7Au	/* PGM/ERS Resume */
#define	MX25V8035F_CMD_DP		0xB9u	/* Deep Power Down */
#define	MX25V8035F_CMD_SBL		0xC0u	/* Set Burst Length */
#define	MX25V8035F_CMD_RDID		0x9Fu	/* Read Identification */
#define	MX25V8035F_CMD_RES		0xABu	/* Read Electronic ID */
#define	MX25V8035F_CMD_REMS		0x90u	/* Read Electronic Manu & Dev ID */
#define	MX25V8035F_CMD_ENSO		0xB1u	/* Enter Secured OTP */
#define	MX25V8035F_CMD_EXSO		0xC1u	/* Exit Secured OTP */
#define	MX25V8035F_CMD_RDSCUR		0x2Bu	/* Read Security Register */
#define	MX25V8035F_CMD_WRSCUR		0x2Fu	/* Write Security Register */
#define	MX25V8035F_CMD_NOP		0x00u	/* No operation */
#define	MX25V8035F_CMD_RSTEN		0x66u	/* Reset Enable */
#define	MX25V8035F_CMD_RST		0x99u	/* Reset Memory */
#define	MX25V8035F_CMD_RRE		0xFFu	/* Release Read Enhanced */

/* MX25V8035F status bits */
#define	MX25V8035F_STS_WIP		(1u << 0) /* Write In Progress */
#define	MX25V8035F_STS_WEL		(1u << 1) /* Write Enable Latch */
#define	MX25V8035F_STS_BP_MASK		(15u << 2) /* the BP bits */
#define	MX25V8035F_STS_QE		(1u << 6) /* Quad Enable */
#define	MX25V8035F_STS_SRWD		(1u << 7) /* Status Regster Write Protect */

/* MX25V8035F configuration bits */
#define	MX25V8035F_CFG_TB		(1u << 3) /* 0=Top, 1=Bottom area protect */

/* MX25V8035F Security bits */
#define	MX25V8035F_SCUR_OTP		(1u << 0) /* 1=Factory lock (2nd 4Kb) */
#define	MX25V8035F_SCUR_LDSO		(1u << 1) /* 1=Lock-Down (1st 4Kb) */
#define	MX25V8035F_SCUR_PSB		(1u << 2) /* Program Suspend */
#define	MX25V8035F_SCUR_ESB		(1u << 3) /* Erase Suspend */
#define	MX25V8035F_SCUR_P_FAIL		(1u << 5) /* Program Failed */
#define	MX25V8035F_SCUR_E_FAIL		(1u << 6) /* Erase Failed */

#define	MX25V8035F_MANUFACTURER_ID	0xC2u
#define	MX25V8035F_DEVICE_ID		0x2314u

#define	MX25V8035F_PAGE_SIZE		UINT32_C(256)
#define	MX25V8035F_SECTOR_SIZE		UINT32_C(4096)
#define	MX25V8035F_PAGE_PER_SECTOR	(MX25V8035F_SECTOR_SIZE / MX25V8035F_PAGE_SIZE)
#define	MX25V8035F_BLOCK32_SIZE		(UINT32_C(32) * 1024)
#define	MX25V8035F_SECTOR_PER_BLOCK32	(MX25V8035F_BLOCK32_SIZE / MX25V8035F_SECTOR_SIZE)
#define	MX25V8035F_PAGE_PER_BLOCK32	(MX25V8035F_BLOCK32_SIZE / MX25V8035F_PAGE_SIZE)
#define	MX25V8035F_BLOCK64_SIZE		(UINT32_C(64) * 1024)
#define	MX25V8035F_SECTOR_PER_BLOCK64	(MX25V8035F_BLOCK64_SIZE / MX25V8035F_SECTOR_SIZE)
#define	MX25V8035F_PAGE_PER_BLOCK64	(MX25V8035F_BLOCK64_SIZE / MX25V8035F_PAGE_SIZE)

/* protection level values: MSB is the "TB" value, bits 0..3 are the BP bits */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_NONE		0x00	/* no blocks protected */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_TOP_1		0x01	/* protect 1 block at top */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_TOP_2		0x02	/* protect 2 blocks at top */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_TOP_4		0x03	/* protect 4 blocks at top */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_TOP_8		0x04	/* protect 8 blocks at top */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_BASE_1		0x81	/* protect 1 block at bottom */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_BASE_2		0x82	/* protect 2 blocks at bottom */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_BASE_4		0x83	/* protect 4 blocks at bottom */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_BASE_8		0x84	/* protect 8 blocks at bottom */
#define	MCCI_BOOTLOADER_MX25V8035F_PL_ALL		0x8F	/* protect 16 blocks */

#define	MCCI_BOOTLOADER_MX25V8035F_PAGE_BASE(a)		((a) & ~(MX25V8035F_PAGE_SIZE - 1))
#define	MCCI_BOOTLOADER_MX25V8035F_SECTOR_BASE(a)	((a) & ~(MX25V8035F_SECTOR_SIZE - 1))
#define	MCCI_BOOTLOADER_MX25V8035F_BLOCK32_BASE(a)	((a) & ~(MX25V8035F_BLOCK32_SIZE - 1))
#define	MCCI_BOOTLOADER_MX25V8035F_BLOCK64_BASE(a)	((a) & ~(MX25V8035F_BLOCK64_SIZE - 1))


#ifdef __cplusplus
}
#endif

#endif /* _flash_mx25v8035f_h_ */
