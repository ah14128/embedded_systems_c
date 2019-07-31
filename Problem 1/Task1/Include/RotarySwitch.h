/***************************************************************************//**
 * 
 * @file		RotarySwitch.h
 * @brief		Header file for rotary switch driver
 * @author		Embedded Artists AB
 * @author		Geoffrey Daniels
 * @version		1.0
 * @date		14 March. 2012
 * @warning		Initialize GPIO before calling any functions in this file.
 * 
 * Copyright(C) 2009, Embedded Artists AB
 * All rights reserved.
 *
*******************************************************************************/

#ifndef ROTARYSWITCH_H
#define ROTARYSWITCH_H

#define ROTARY_WAIT  0
#define ROTARY_RIGHT 1
#define ROTARY_LEFT  2

/// @brief 		Initialize rotary switch driver
/// @warning	Initialize GPIO before calling any functions in this file.
void RotarySwitch_Init(void);

/// @brief 		Read rotary switch state
/// @return		Rotary switch state
/// @warning	Initialize the rotary switch driver before running this function
uint8_t RotarySwitch_Read(void);

#endif // ROTARYSWITCH_H
