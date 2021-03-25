/*

Module:	mcci_bootloader_bits.h

Function:
	Bit macros for the MCCI bootloader.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_bits_h_
#define _mcci_bootloader_bits_h_	/* prevent multiple includes */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

///
/// \brief compute log2 of an power of 2.
///
/// This can be used at compile time or run time.
///
/// \see Knuth V4 7.1.3 (49).
///
#define MCCI_BOOTLOADER_LOG2_POW2(x)			\
    ((x) == 0 ? -1 :					\
     (((x) & 0x5555555555555555u) == 0 ? 1 : 0) +	\
     (((x) & 0x3333333333333333u) == 0 ? 2 : 0) +	\
     (((x) & 0x0f0f0f0f0f0f0f0fu) == 0 ? 4 : 0) +	\
     (((x) & 0x00FF00FF00FF00FFu) == 0 ? 8 : 0) +	\
     (((x) & 0x0000FFFF0000FFFFu) == 0 ? 16 : 0) +	\
     (((x) & 0x00000000FFFFFFFFu) == 0 ? 32 : 0))

///
/// \brief get shift count from field mask.
///
/// \param[in] x	field mask; bitmask should be of form 0*11*0*
///
/// \details
///	We might have some 64-bit fields, so...
/// 	this goes through through bit 63. We use `~(x)+1` to form the unsigned twos-
/// 	complement of \c x without trying to negate an unsigned or doing
/// 	a type-cast. Avoids warnings on some compilers.  This is exactly
/// 	what Knuth calls "rho" (the ruler function).
///
/// \see Knuth V4 7.1.3.
///
#define MCCI_BOOTLOADER_FIELD_SHIFT(x) 	MCCI_BOOTLOADER_LOG2_POW2((x) & (~(x)+1))

/*! get LSB from field mask */
#define	MCCI_BOOTLOADER_FIELD_LSB(fmask)			\
	((fmask) & (~(fmask) + 1u))

/*! generate field value (properly positioned) */
#define	MCCI_BOOTLOADER_VALUE_MAKE_FIELD(val, fmask)		\
	(MCCI_BOOTLOADER_FIELD_LSB(fmask) * (val))

/*! generate field value (properly positioned) */
#define	MCCI_BOOTLOADER_FIELD_SET_VALUE(fmask, val)		\
	(MCCI_BOOTLOADER_FIELD_LSB(fmask) * (val))

/*! extract and normalize value of field */
#define	MCCI_BOOTLOADER_VALUE_GET_FIELD(val, fmask)		\
	(((val) & (fmask)) >> MCCI_BOOTLOADER_FIELD_SHIFT(fmask))

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_bits_h_ */
