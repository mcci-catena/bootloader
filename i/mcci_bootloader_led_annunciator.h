/*

Module:	mcci_bootloader_led_annunciator.h

Function:
	Bootloader LED annunciator library functions

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#ifndef _mcci_bootloader_led_annunciator_h_
#define _mcci_bootloader_led_annunciator_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// @brief symbolic type for the structure representing the bootloader LED state
typedef struct McciBootloader_LED_Annunciator_s McciBootloader_LED_Annunciator_t;

/// @brief The states of the Bootloader LED finite state machine.
typedef enum
	{
	McciBootloader_LED_Annunciator_stNoChange = -1, ///< internal: don't change state.
	McciBootloader_LED_Annunciator_stInitial,	///< not initialized
	McciBootloader_LED_Annunciator_stIdle,		///< not displaying
	McciBootloader_LED_Annunciator_stLedOn,		///< light is on
	McciBootloader_LED_Annunciator_stBitGap,	///< displaying bit gap
	McciBootloader_LED_Annunciator_stByteGap,	///< displaying byte gap
	} McciBootloader_LED_AnnunciatorBitState_t;

/// @brief The bootloader LED annunciator state object.
struct McciBootloader_LED_Annunciator_s
	{
	/// @brief incremented every systick
	uint32_t					tick;
	///
	/// @brief Mask of pattern to be displayed on the LED.
	/// 
	/// @details
	///	The display pattern mask in ::display always
	///	ends in a 1, followed by all zeroes to the right. This trailing is
	///	the "stop bit", and is not displayed. ::display itself it is not
	///	shifted; it is used to refresh the shift register, which is ::value.
 	///	For example, to display 0b101, annunciatorIndicateState adds a stop bit,
	///	making 0b1011, then left-justifies in a uint32_t, making 0xB0000000.
	///
	///	This is then copied to ::value after the inter-pattern gap. The update
	///	routine (assumed to be called from the clock tick handler) shifts
	///	::value left, successively yielding 1, 0, 1. The FSM then flashed the LED
	///	for 3 bit times, 1 bit time, and 3 bit times, with a 1-bit time pause between
	///	each bit. The FSM discovers when shifting the stop bit that ::value is
	///	now zero, and changes state to displaying the gap betwen words
	///	(turning off the LED) for two bit times.
	///
	uint32_t					display;
	///
	/// @brief bit pattern being displayed. Shifted left each systick. 1 means LED on,
	///	0 means LED off. When zero, there's nothing left to display for the
	///	current pattern.
	///
	uint32_t					value;
	///
	/// @brief number of systicks per bit. Usually, one systick is assumed to be
	///	one millisecond, but this value is used to stretch bit times to something
	///	perceptually useful.
	///
	uint32_t					bittime;
	/// @brief tick count at which next thing should happen.
	uint32_t					timer;
	/// @brief current state of the LED FSM.
	McciBootloader_LED_AnnunciatorBitState_t	bitState;
	};

bool
McciBootloader_LED_handleSysTick(
	void
	);

void
McciBootloader_LED_annunciatorIndicateState(
	McciBootloaderState_t state
	);

void
McciBootloader_LED_annunciatorInit(
	void
	);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_led_annunciator_h_ */
