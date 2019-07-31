/***************************************************************************//**
 *
 * @file		LED2.c
 * @brief		Source file for the LED2 driver
 * @author		Geoffrey Daniels
 * @version		1.0
 * @date		24 March. 2012
 * @warning		Initialize GPIO before calling any functions in this file.
 *
 * Copyright(C) 2012, Geoffrey Daniels, GPDaniels.com
 * All rights reserved.
 *
*******************************************************************************/

#include "LPC17xx_PinSelect.h"

void LED2_Init(void)
{
	// Set P0_22 to 00 - GPIO
	LPC_PINCON->PINSEL1	&= (~(3 << 12));
	// Set GPIO - P0_22 - to be output
	LPC_GPIO0->FIODIR |= (1 << 22);
}

void LED2_On(void)
{
	LPC_GPIO0->FIOSET = (1 << 22);
}

void LED2_Off(void)
{
	LPC_GPIO0->FIOCLR = (1 << 22);
}

void LED2_Invert(void)
{
	int LEDState;

	// Read current state of GPIO P0_0..31, which includes LED2
	LEDState = LPC_GPIO0->FIOPIN;
	// Turn off LED2 if it is on
	// (ANDing to ensure we only affect the LED output)
	LPC_GPIO0->FIOCLR = LEDState & (1 << 22);
	// Turn on LED2 if it is off
	// (ANDing to ensure we only affect the LED output)
	LPC_GPIO0->FIOSET = ((~LEDState) & (1 << 22));
}
