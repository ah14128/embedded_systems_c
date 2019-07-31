/***************************************************************************//**
 *
 * @file		OLED.h
 * @brief		Header file for OLED Display (SSD1305)
 * @author		Embedded Artists AB
 * @author		Geoffrey Daniels
 * @version		1.0
 * @date		14 March. 2012
 * @warning		Initialize I2C or SPI, and GPIO before calling any functions in
 *              this file.
 *
 * Copyright(C) 2009, Embedded Artists AB
 * All rights reserved.
 *
*******************************************************************************/

#ifndef OLED_H
#define OLED_H

#define OLED_DISPLAY_WIDTH  96
#define OLED_DISPLAY_HEIGHT 64

typedef enum
{
    OLED_COLOR_BLACK,
    OLED_COLOR_WHITE
} OLED_Colour;

/// @brief 		Initialize the OLED display driver
/// @warning	Initialize I2C or SPI, and GPIO before calling any functions in
///             this file.
void OLED_Init(Peripheral_Descriptor_t SPIPortIn);

/// @brief 		Clear the entire screen
/// @param[in]  Colour - Colour to fill the screen with
/// @warning	Initialize the OLED driver before running this function
void OLED_ClearScreen(OLED_Colour Colour);

/// @brief 		Draw one pixel on the display
/// @param[in]  X - X position
/// @param[in]  Y - Y position
/// @param[in]  Colour - Colour of the pixel
/// @warning	Initialize the OLED driver before running this function
void OLED_Pixel(uint8_t X, uint8_t Y, OLED_Colour Colour);

/// @brief 		Draw a character at location X,Y
/// @param[in]  X - X location
/// @param[in]  Y - Y location
/// @param[in]  Character - Character
/// @param[in]  Forground - Colour of the letter
/// @param[in]  Background - Colour of the background
/// @return     1 on success, 0 if the location is outside of the display
/// @warning	Initialize the OLED driver before running this function
uint8_t OLED_Char(uint8_t X, uint8_t Y, uint8_t Character, OLED_Colour Forground, OLED_Colour Background);

/// @brief 		Draw a string of characters starting at location X,Y
/// @param[in]  X - X location
/// @param[in]  Y - Y location
/// @param[in]  S - String
/// @param[in]  Forground - Colour of the letter
/// @param[in]  Background - Colour of the background
/// @warning	Initialize the OLED driver before running this function
void OLED_String(uint8_t X, uint8_t Y, uint8_t *String, OLED_Colour Forground, OLED_Colour Background);

#endif // OLED_H
