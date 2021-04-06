/*

Module:	mcci_flash_sfdp.h

Function:
	Suport for flash chip SFDP spec (JEDEC spec JESD216)

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	April 2021

*/

#ifndef _mcci_flash_sfdp_h_
#define _mcci_flash_sfdp_h_	/* prevent multiple includes */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

///
/// \brief the SFTD header
///
typedef struct mcci_flash_sfdp_header_s
	{
	uint8_t		signature[4];	///< the signature value for the header.
	uint8_t		properties[4];	///< the properties for the header.
	} mcci_flash_sfdp_header_t;

///
/// \brief get value of a 32-bit SFDP entry
///
/// \param [in] pValue points to a 4-byte field to be fetched.
///
static inline uint32_t
McciFlashSfdp_get32(
	const uint8_t pValue[4]
	)
	{
	return  ((uint32_t)pValue[0] <<  0) |
		((uint32_t)pValue[1] <<  8) |
		((uint32_t)pValue[2] << 16) |
		((uint32_t)pValue[3] << 24);
	}

/// \brief return the signature value from an SFDP header
static inline uint32_t
McciFlashSfdpHeader_getSignature(const mcci_flash_sfdp_header_t *p)
	{
	return McciFlashSfdp_get32(p->signature);
	}

///
/// \brief signature of a SFDP header
///
/// This is the same as 'S', 'F', 'D', 'P' considered as a little-endian
/// value.
///
#define	MCCI_FLASH_SFDP_HEADER_SIGNATURE	\
	((UINT32_C(0x50) << 24) | (UINT32_C(0x44) << 16) | (UINT32_C(0x46) << 8) | 0x53)

/// \brief return the access protocol value from an SFDP header
static inline uint8_t
McciFlashSfdpHeader_getProtocol(const mcci_flash_sfdp_header_t *p)
	{
	return p->properties[3];
	}

///
/// \brief SFDP access protocol values
///   @{
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND1_216D	0xF0	///< NAND class 1 from JESD216D
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND2_216D	0xF1	///< NAND class 2 from JESD216D
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND3_CLASS1_D	0xF2	///< reserved for NOR + NAND1
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND3_CLASS2_D	0xF3	///< reserved for NOR + NAND2
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND1_216B	0xF4	///< NAND class 1 from JESD216B
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND2_216B	0xF5	///< NAND class 2 from JESD216B
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND3_RSV1	0xF6	///< reserved for NOR + NAND1
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NAND3_RSV2	0xF7	///< reserved for NOR + NAND2
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_RSV248		0xF8	///< reserved
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_RSV249		0xF9	///< reserved
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NOR2		0xFA	///< NOR xSPI profile 2, 5-byte addressing SFDP cmd
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_RSV251		0xFB	///< reserved
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NOR1_3_8W	0xFC	///< NOR xSPI profile 1, 3-byte, 8 wait
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NOR1_4_20W	0xFD	///< NOR xSPI profile 1, 4 byte, 20 wait
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NOR1_4_8W	0xFE	///< NOR xSPI profile 1, 4 byte, 8 wait
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_PROTOCOL_NOR		0xFF	///< Legacy NOR, JESD216B, 3-byte SFDP command w/ 8 wait states
///   @}

///
/// \brief Get SFDP version compliance claimed by header.
///
///   @{
static inline uint16_t McciFlashSfdpHeader_getVersion(const mcci_flash_sfdp_header_t *p)
	{
	return  ((uint16_t) p->properties[0] << 0) |
		((uint16_t) p->properties[1] << 8);
	}

/// \brief Major and minor version codes
#define	MCCI_FLASH_SFDP_HEADER_PROPERTY_VERSION_JES216D	UINT16_C(0x0108)	///< version for JESD216D
#define MCCI_FLASH_SFDP_HEADER_PROPERTY_VERSION_JES216C	UINT16_C(0x0107)	///< version for JESD216C
#define MCCI_FLASH_SFDP_HEADER_PROPERTY_VERSION_JES216B	UINT16_C(0x0106)	///< version for JESD216B
#define MCCI_FLASH_SFDP_HEADER_PROPERTY_VERSION_JES216A	UINT16_C(0x0105)	///< version for JESD216A
///   @}


///
/// \brief the SFDP parameter header
///
typedef struct mcci_flash_sfdp_param_s
	{
	uint8_t	dword1[4];			///< low order dword
	uint8_t dword2[4];			///< high-order dword
	} mcci_flash_sfdp_param_t;

/// \brief return length of parameter table in dwords.
static inline uint8_t
McciFlashSfdpParam_getLength(const mcci_flash_sfdp_param_t *p)
	{
	return p->dword1[3];
	}

/// \brief return version of parameter table
static inline uint16_t
McciFlashSfdpParam_getVersion(const mcci_flash_sfdp_param_t *p)
	{
	return (p->dword1[2] << 8) | p->dword1[1];
	}

/// \brief return ID of parameter table
///
/// @{
static inline uint16_t
McciFlashSfdpParam_getID(const mcci_flash_sfdp_param_t *p)
	{
	return (p->dword2[3] << 8) | p->dword1[0];
	}

/// \brief well-known parameter table IDs
///   @{
#define	MCCI_FLASH_SFDP_ID_BASIC_SPI	UINT16_C(0xFF00)	///< Basic SPI protocol
#define	MCCI_FLASH_SFDP_ID_SECTOR_MAP	UINT16_C(0xFF81)	///< Sector map
#define	MCCI_FLASH_SFDP_ID_RPMC		UINT16_C(0xFF03)	///< Replay Protected Monotonic Counters (RPMC)
#define	MCCI_FLASH_SFDP_ID_4BA_INSTR	UINT16_C(0xFF84)	///< 4-byte Address Instruction Table
#define	MCCI_FLASH_SFDP_ID_xSPI1	UINT16_C(0xFF05)	///< eXtended Serial Peripheral Interface (xSPI) Profile 1.0
#define	MCCI_FLASH_SFDP_ID_xSPI2	UINT16_C(0xFF06)	///< eXtended Serial Peripheral Interface (xSPI) Profile 2.0
#define	MCCI_FLASH_SFDP_ID_SCCR_MAP	UINT16_C(0xFF87)	///< Status, Control and Configuration Register Map
#define	MCCI_FLASH_SFDP_ID_SCCR_OFFSETS	UINT16_C(0xFF88)	///< Status, Control and Configuration Register Map Offsets for Multi-Chip SPI Memory Devices
#define	MCCI_FLASH_SFDP_ID_SCCR_xSPI2	UINT16_C(0xFF09)	///< Status, Control and Configuration Register Map for xSPI Profile 2.0
#define	MCCI_FLASH_SFDP_ID_OCTAL_DDR	UINT16_C(0xFF0A)	///< Command Sequences to change to Octal DDR (8D-8D-8D) mode
#define	MCCI_FLASH_SFDP_ID_LL_MSPT	UINT16_C(0xFF8B)	///< Long Latency NVM Media Specific Parameter Table (MSPT)
#define	MCCI_FLASH_SFDP_ID_QUAD_IO	UINT16_C(0xFF0C)	///< x4 Quad IO with DS
#define	MCCI_FLASH_SFDP_ID_QUAD_DDR	UINT16_C(0xFF8D)	///< Command Sequences to change to Quad DDR (4S-4D-4D) mode
#define	MCCI_FLASH_SFDP_ID_RSV8E	UINT16_C(0xFF8E)	///< Reserved for next Function Specific Table assignment
///   @}
/// @}

/// \brief return pointer to parameter table (PTP)
static inline uint32_t
McciFlashSfdpParam_getPTP(const mcci_flash_sfdp_param_t *p)
	{
	return  ((uint32_t)p->dword2[0] <<  0) |
		((uint32_t)p->dword2[1] <<  8) |
		((uint32_t)p->dword2[2] << 16)
		;
	}

#ifdef __cplusplus
}
#endif

#endif /* _mcci_flash_sfdp_h_ */
