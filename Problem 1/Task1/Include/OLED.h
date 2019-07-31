/***************************************************************************//**
 * 
 * @file		OLED.h
 * @brief		Header file for OLED Display (SSD1305)
 * @author		Embedded Artists AB
 * @author		Geoffrey Daniels, Dimitris Agrafiotis
 * @version		1.0
 * @date		14 March. 2012
 * @warning		Initialize I2C or SPI, and GPIO before calling any functions in
 *              this file.
 *
 * @edit		Jeremy Dalton 12/2012
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
void OLED_Init(void);

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

/// @brief 		Draw a line starting at X0,Y0 and ending at X1,Y1
/// @param[in]  X0 - Start x position
/// @param[in]  Y0 - Start y position
/// @param[in]  X1 - End x position
/// @param[in]  Y1 - End y position
/// @param[in]  Colour - Colour of the line
/// @warning	Initialize the OLED driver before running this function
void OLED_Line(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, OLED_Colour Colour);

/// @brief 		Draw a circle centered at X0,Y0 with radius R
/// @param[in]  X - Start x position
/// @param[in]  Y - Start y position
/// @param[in]  R - Radius
/// @param[in]  Colour - Colour of the circle
/// @warning	Initialize the OLED driver before running this function
void OLED_LineCircle(uint8_t X, uint8_t Y, uint8_t R, OLED_Colour Colour);

/// @brief 		Draw a filled circle centered at X0,Y0 with radius R
/// @param[in]  X - Start x position
/// @param[in]  Y - Start y position
/// @param[in]  R - Radius
/// @param[in]  Colour - Colour of the circle
/// @warning	Initialize the OLED driver before running this function
void OLED_FillCircle(uint8_t X, uint8_t Y, uint8_t R, OLED_Colour Colour);

/// @brief 		Draw a rectangle starting at X0,Y0 and ending at X1,Y1
/// @param[in]  X0 - Start x position
/// @param[in]  Y0 - Start y position
/// @param[in]  X1 - End x position
/// @param[in]  Y1 - End y position
/// @param[in]  Colour - Colour of the rectangle
/// @warning	Initialize the OLED driver before running this function
void OLED_LineRect(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, OLED_Colour Colour);

/// @brief 		Draw a filled rectangle starting at X0,Y0 and ending at X1,Y1
/// @param[in]  X0 - Start x position
/// @param[in]  Y0 - Start y position
/// @param[in]  X1 - End x position
/// @param[in]  Y1 - End y position
/// @param[in]  Colour - Colour of the rectangle
/// @warning	Initialize the OLED driver before running this function
void OLED_FillRect(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, OLED_Colour Colour);

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

void WriteOLEDString(uint8_t* String, uint8_t Line, uint8_t Position);

#endif // OLED_H
