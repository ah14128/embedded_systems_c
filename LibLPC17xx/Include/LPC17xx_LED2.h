/***************************************************************************//**
 *
 * @file		LED2.h
 * @brief		Header file for the LED2 driver
 * @author		Geoffrey Daniels
 * @version		1.0
 * @date		24 March. 2012
 * @warning		Initialize GPIO before calling any functions in this file.
 *
 * Copyright(C) 2012, Geoffrey Daniels, GPDaniels.com
 * All rights reserved.
 *
*******************************************************************************/

#ifndef LED2_H
#define LED2_H

/// @brief 		Initialize the LED2 driver
/// @warning	Initialize GPIO before calling any functions in this file.
void LED2_Init(void);

/// @brief 		Turn on the LED
/// @warning	Initialize the LED2 driver before running this function
void LED2_On(void);

/// @brief 		Turn off the LED
/// @warning	Initialize the LED2 driver before running this function
void LED2_Off(void);

/// @brief 		Invert the state of the LED
/// @warning	Initialize the LED2 driver before running this function
void LED2_Invert(void);

#endif // LED2_H
