/*

Module:	mccibootloaderboard_catenaabz_annunciator.c

Function:
	Annunciator (LED flashing) functions for ABZ-based Catena boards

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena_abz.h"

#include "mcci_bootloader.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

typedef struct CatenaAbz_Annuciator_s CatenaAbz_Annuciator_t;

typedef enum
	{
	stNoChange = -1, ///< internal: don't change state.
	stIdle,		///< not displaying
	stLedOn,	///< light is on
	stBitGap,	///< displaying bit gap
	stByteGap,	///< displaying byte gap
	} AnnunciatorBitState_t;

struct CatenaAbz_Annuciator_s
	{
	uint32_t		tick;
	uint32_t		display;
	uint32_t		value;
	uint32_t		bittime;
	uint32_t		timer;
	McciBootloaderState_t	bootState;
	AnnunciatorBitState_t	bitState;
	};

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

static CatenaAbz_Annuciator_t annunciator;

void
McciBootloaderBoard_CatenaAbz_annunciatorInit(
	void
	)
	{
	/// enable interrupts
	McciArm_setPRIMASK(0);
	annunciator.bittime = 100; // 100 ms per bit.
	}

void
McciBootloaderBoard_CatenaAbz_annunciatorIndicateState(
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
		annunciator.display = (uint32_t)display << (32 - nBits);
		}
	else
		annunciator.display = 0;
	}

static bool
nextBit(void)
	{
	bool nextBit = !!(annunciator.value & UINT32_C(0x80000000));
	annunciator.value <<= 1;
	if (annunciator.value == 0)
		return false;

	McciBootloaderBoard_CatenaAbz_setLed();
	annunciator.timer = annunciator.tick + annunciator.bittime * (1 + 2 * nextBit);
	return true;
	}

void
McciBootloaderBoard_CatenaAbz_handleSysTick(
	void
	)
	{
	const uint32_t now = annunciator.tick + 1;
	annunciator.tick = now;
	AnnunciatorBitState_t nextState = stNoChange;

	if (annunciator.bootState == McciBootloaderState_Initial)
		return;

	switch (annunciator.bitState)
		{
	default:
		nextState = McciBootloaderState_Initial;
		break;

	case stIdle:
		if (annunciator.bootState != McciBootloaderState_Initial)
			{
			annunciator.value = annunciator.display;
			nextBit();
			nextState = stLedOn;
			}
		break;

	case stLedOn:
		if ((int32_t)(now - annunciator.timer) >= 0)
			{
			McciBootloaderBoard_CatenaAbz_clearLed();
			annunciator.timer = now + annunciator.bittime;
			nextState = stBitGap;
			}
		break;

	case stBitGap:
		if ((int32_t)(now - annunciator.timer) >= 0)
			{
			if (nextBit())
				nextState = stLedOn;
			else
				{
				nextState = stByteGap;
				annunciator.timer = now + 2 * annunciator.bittime;
				}
			}
	
	case stByteGap:
		if ((int32_t)(now - annunciator.timer) >= 0)
			{
			annunciator.value = annunciator.display;
			if (nextBit())
				nextState = stLedOn;
			else
				{
				nextState = stIdle;
				}
			}
		break;
		}

	if (nextState != stNoChange)
		annunciator.bitState = nextState;
	}

/**** end of mccibootloaderboard_catenaabz_annunciator.c ****/
