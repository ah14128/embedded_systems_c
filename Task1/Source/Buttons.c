/**************************************************************************//**
 *
 * @file		Buttons.c
 * @brief		Source file for the buttons driver
 * @author		Geoffrey Daniels, Dimitris Agrafiotis
 * @version		1.0
 * @date		19 July. 2012
 * @warning		Initialize GPIO before calling any functions in this file.
 *
 * Copyright(C) 2012, University of Bristol
 * All rights reserved.
 *
******************************************************************************/

// Includes
#include "LPC17xx_GPIO.h"

#include "Buttons.h"

//------------------------------------------------------------------------------

// Defines and typedefs
//...

//------------------------------------------------------------------------------

// External global variables
//...

//------------------------------------------------------------------------------

// Local variables
//...

//------------------------------------------------------------------------------

// Local Functions
//...

//------------------------------------------------------------------------------

// Public Functions
void Buttons_Init(void)
{
	GPIO_SetDir( 0, (1<<4), 0 );
	GPIO_SetDir( 1, (1<<31), 0 );
}

// Ensure Jumper 26 is in the lower position
uint8_t Buttons_Read1(void)
{
	return ((GPIO_ReadValue(0) >> 4) & 0x01);
}

// Ensure Jumper 28 is removed
// This jumper is also used for BNC input
uint8_t Buttons_Read2(void)
{
	return ((GPIO_ReadValue(1) >> 31) & 0x01);
}



