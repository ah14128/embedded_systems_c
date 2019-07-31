/**************************************************************************//**
 *
 * @file		WavPlayer.h
 * @brief		Header file for a wav file player using the DAC
 * @author		Vlad Cazan
 * @author		Stephan Rochon
 * @author		Tom Coxon
 * @author		Geoffrey Daniels
 * @version		1.0
 * @date		19 July. 2012
 *
 * Copyright(C) 2012, Vlad Cazan and Stephan Rochon
 * All rights reserved.
 *
******************************************************************************/

#ifndef WAVPLAYER_H
#define WAVPLAYER_H

#ifdef WAVPLAYER_INCLUDE_SAMPLESONGS
	extern const uint8_t WavPlayer_Sample[];
	extern const uint32_t WavPlayer_SampleLength;
	#include "WavPlayer_Sample.h"
#endif

/// @brief 		Initialize the wav file player
void WavPlayer_Init(void);

/// @brief 		Play a wav file
/// @param[in]  WavArray - An array of bytes representing the file
/// @param[in]  Length - Number of bytes in the array
/// @warning	Initialize the wav file player before running this function
void WavPlayer_Play(const uint8_t *WavArray, const uint32_t Length);

/// @brief 		Check if currently playing
/// @returns    1 if playing 0 otherwise
/// @warning	Initialize the wav file player before running this function
uint8_t WavPlayer_IsPlaying(void);


#endif
