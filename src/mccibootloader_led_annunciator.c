/*

Module:	mccibootloaderboard_led_annunciator.c

Function:
	Hardaware-independent Annunciator (LED flashing) library functions.

Copyright notice:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_led_annunciator.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

static McciBootloader_LED_Annuciator_t annunciator;


/*

Name:	McciBootloader_LED_annunciatorInit()

Function:
	Initialize the opt-in annunciator framework.

Definition:
	void McciBootloader_LED_annunciatorInit(
		void
		);

Description:
	Set up the FSM that can be used to control a LED that displays system
	boot status.

Returns:
	No explicit result

Notes:
	Doesn't actually touch hardware.

*/

#define FUNCTION "McciBootloader_LED_annunciatorInit"

void
McciBootloader_LED_annunciatorInit(
	void
	)
	{
	annunciator.bittime = 100; // 100 ms per bit.
	annunciator.bitState = McciBootloader_LED_Annunciator_stIdle;
	}

#undef FUNCTION

/*

Name:	McciBootloader_LED_annunciatorIndicateState()

Function:
	Pass the bootloader state to the annunciator FSM

Definition:
	void McciBootloader_LED_annunciatorIndicateState(
		McciBootloaderState_t state
		);

Description:
	Boards that use the McciBootloader_LED framework call this function in
	response to a bootloader state change. This function just modifies
	software state; hardware updates are done based on systick.

	If state is zero, the LED is turned off. Otherwise, state is interpreted
	as a number and scheduled for bit-serial display based on clock
	interrutps. Numbers are displayed using long flashes for 1, short
	flashes for 0. 	Leading zeroes are suppressed. The number is displayed
	over and over until changed by another call to thie routine.

Returns:
	No explicit result.

Notes:
	Normally this is called as a result of a call to the platform 
	Annuciator.pIndicateState functtion.

*/

#define FUNCTION "McciBootloader_LED_annunciatorIndicateState"

void
McciBootloader_LED_annunciatorIndicateState(
	McciBootloaderState_t state
	)
	{
	if (state != 0)
		{
		uint32_t display = ((uint32_t)state << 1) | 1;
		unsigned nBits;
		// always put at least 2 bits
		for (nBits = 31; nBits > 2; --nBits)
			{
			if (display & (UINT32_C(1) << nBits))
				break;
			}

		// if display is 2^k-1, then add a bit, so we have
		// a time contrast on long pulses.
		if (((display + 1) & display) == 0)
			++nBits;

		annunciator.display = (uint32_t)display << (31 - nBits);
		}
	else
		annunciator.display = 0;
	}

#undef FUNCTION

///
/// @brief process the next bit from the current word, and set timers
/// @return \c true if the there was a next bit to process, otherwise \c false
///
/// @details
/// 	::timer is set to go off in either 1 or 3 bit times, depending on
/// 	whether the next bit is a 1 or a 0.
///
/// 	If this routine returns true, the caller should light the LED, which
///	should not be on. Otherwise, leave the LED off.
///
static bool
nextBit(void)
	{
	const bool fNextBit = !!(annunciator.value & UINT32_C(0x80000000));

	annunciator.value <<= 1;
	if (annunciator.value == 0)
		return false;

	annunciator.timer = annunciator.tick + annunciator.bittime * (1 + 2 * fNextBit);
	return true;
	}

bool
McciBootloader_LED_handleSysTick(
	void
	)
	{
	const uint32_t now = annunciator.tick + 1;

	annunciator.tick = now;
	McciBootloader_LED_AnnunciatorBitState_t nextState =
		McciBootloader_LED_Annunciator_stNoChange;

	switch (annunciator.bitState)
		{
	default:
	case McciBootloader_LED_Annunciator_stInitial:
		nextState = McciBootloader_LED_Annunciator_stInitial;
		annunciator.bitState = McciBootloader_LED_Annunciator_stInitial;
		return false;

	// in this state, nothing is being displayed
	case McciBootloader_LED_Annunciator_stIdle:
		// if someone sets ::display non zero, we start displayign
		if (annunciator.display != 0)
			{
			annunciator.value = annunciator.display;
			if (nextBit())
				{
				nextState = McciBootloader_LED_Annunciator_stLedOn;
				}
			}
		break;

	case McciBootloader_LED_Annunciator_stLedOn:
		if ((int32_t)(now - annunciator.timer) >= 0)
			{
			annunciator.timer = now + annunciator.bittime;
			nextState = McciBootloader_LED_Annunciator_stBitGap;
			}
		break;

	case McciBootloader_LED_Annunciator_stBitGap:
		if ((int32_t)(now - annunciator.timer) >= 0)
			{
			if (nextBit())
				{
				nextState = McciBootloader_LED_Annunciator_stLedOn;
				}
			else
				{
				nextState = McciBootloader_LED_Annunciator_stByteGap;
				annunciator.timer = now + 2 * annunciator.bittime;
				}
			}
		break;

	case McciBootloader_LED_Annunciator_stByteGap:
		if ((int32_t)(now - annunciator.timer) >= 0)
			{
			annunciator.value = annunciator.display;
			if (nextBit())
				nextState = McciBootloader_LED_Annunciator_stLedOn;
			else
				{
				nextState = McciBootloader_LED_Annunciator_stIdle;
				}
			}
		break;
		}

	if (nextState != McciBootloader_LED_Annunciator_stNoChange)
		annunciator.bitState = nextState;

	return annunciator.bitState == McciBootloader_LED_Annunciator_stLedOn;
	}
