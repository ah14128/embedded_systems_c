/**************************************************************************//**
 *
 * @file		new_string.c
 * @brief		Contains home brew functions that relate to strings
 * @author		Sam Walder
 * @version		1.0
 * @date		05/12/2012
 *
******************************************************************************/

// Standard C library
#include <stdio.h>
#include <string.h>

// LPC17xx definitions for CMSIS
#include "LPC17xx.h"

//#define MAXIMUM_TEXT_SIZE 18U		// Defined by screen width in this case

// float to string
void floatToString(float value, char* text_array, int array_size) {
	/* This function converts a number to s string
	 * It's main aim of use if for printing numbers on the OLED of the LPCxpresso base board
	 */

	// Perform the conversion
	snprintf(text_array, array_size, "%3.3f", value);
}
