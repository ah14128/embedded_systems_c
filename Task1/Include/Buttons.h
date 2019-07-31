/**************************************************************************//**
 *
 * @file		Buttons.h
 * @brief		Header file for the buttons driver
 * @author		Geoffrey Daniels, Dimitris Agrafiotis
 * @version		1.0
 * @date		19 July. 2012
 * @warning		Initialize GPIO before calling any functions in this file.
 *
 * Copyright(C) 2012, University of Bristol
 * All rights reserved
 *
******************************************************************************/

#ifndef BUTTONS_H
#define BUTTONS_H

/// @brief      Initialize the buttons driver
/// @warning    Initialize GPIO before calling any functions in this file.
void Buttons_Init(void);

/// @brief      Read button state.
/// @return     The state of the buttons, 00 = Pressed Pressed
/// @warning    Initialize the buttons driver before calling this function
uint8_t Buttons_Read(void);

/// @brief      Read button 1 state.
/// @return     The state of the buttons, 0 = Pressed
/// @warning    Initialize the buttons driver before calling this function
uint8_t Buttons_Read1(void);

/// @brief      Read button 2 state.
/// @return     The state of the buttons, 0 = Pressed
/// @warning    Initialize the buttons driver before calling this function
uint8_t Buttons_Read2(void);

#endif // BUTTONS_H
