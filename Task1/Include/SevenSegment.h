/***************************************************************************//**
 * 
 * @file		SevenSegment.h
 * @brief		Header file for the 7 segment display
 * @author		Embedded Artists AB
 * @author		Geoffrey Daniels, Dimitris Agrafiotis
 * @version		1.0
 * @date		14 March. 2012
 * @warning		Initialize SPI & GPIO before calling any functions in this file.
 * 
 * Copyright(C) 2009, Embedded Artists AB
 * All rights reserved.
 *
*******************************************************************************/

#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

/// @brief 		Initialize the 7 segment display
/// @warning	Initialize SPI & GPIO before calling any functions in this file.
void SevenSegment_Init(void);

/// @brief 		Draw a character on the 7 segment display
/// @param[in]  Character - Character interpreted as an ascii character. Not all
///                         ascii characters can be realized on the display. If
///                         a character can't be realized all segments are off.
/// @param[in]  RawMode - Set to TRUE to use raw mode. In this case the
///                       character data won't be interpreted as ascii.
/// @warning	Initialize the 7 segment display before running this function
void SevenSegment_SetCharacter(uint8_t Character, uint32_t RawMode);

#endif // SEVENSEGMENT_H
