/***************************************************************************//**
 * 
 * @file		OLED.c
 * @brief		Driver for the OLED Display (SSD1305)
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

// Includes
#include <string.h>

#include "LPC17xx_GPIO.h"
#include "LPC17xx_I2C.h"
#include "LPC17xx_SSP.h"

#include "OLED.h"
#include "Font5x7.h"

//------------------------------------------------------------------------------

// Defines and typedefs
//#define OLED_USE_I2C

#ifdef OLED_USE_I2C
    #define I2CDEV LPC_I2C2
    #define OLED_I2C_ADDR (0x3c)
#else
    #define OLED_CS_OFF() GPIO_SetValue(0, (1<<6))
    #define OLED_CS_ON()  GPIO_ClearValue(0, (1<<6))
    #define OLED_DATA()   GPIO_SetValue(2, (1<<7))
    #define OLED_CMD()    GPIO_ClearValue(2, (1<<7))
#endif

// The display controller can handle a resolutiom of 132x64. The OLED on the
// base board is 96x64.
#define X_OFFSET 18

#define SHADOW_FB_SIZE (OLED_DISPLAY_WIDTH*OLED_DISPLAY_HEIGHT >> 3)

#define SetAddress(Page, LowerAddress, HigherAddress)\
    WriteCommand(Page);\
    WriteCommand(LowerAddress);\
    WriteCommand(HigherAddress);

//------------------------------------------------------------------------------

// External global variables
//...

//------------------------------------------------------------------------------

// Local variables
static uint8_t const  Font_Mask[8] = {0x80, 0x40, 0x20, 0X10, 0X08, 0X04, 0X02, 0X01};

// The SSD1305 doesn't support reading from the display memory when using serial
// mode (only parallel mode). Since it isn't possible to write only one pixel to
// the display (a minimum of one column, 8 pixels, is always wriiten) a shadow
// framebuffer is needed to keep track of the display data.
static uint8_t ShadowFB[SHADOW_FB_SIZE];

//------------------------------------------------------------------------------

// Local Functions
#ifdef OLED_USE_I2C
static int I2C_Read(uint8_t Address, uint8_t* Buffer, uint32_t Length)
{
	I2C_M_SETUP_Type RXSetup;

	RXSetup.sl_addr7bit = Address;
	RXSetup.tx_data = NULL;
	RXSetup.tx_length = 0;
	RXSetup.rx_data = Buffer;
	RXSetup.rx_length = Length;
	RXSetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &RXSetup, I2C_TRANSFER_POLLING) == SUCCESS)
		return 0;
	
	return -1;
}

static int I2C_Write(uint8_t Address, uint8_t* Buffer, uint32_t Length)
{
	I2C_M_SETUP_Type TXSetup;

	TXSetup.sl_addr7bit = Address;
	TXSetup.tx_data = Buffer;
	TXSetup.tx_length = Length;
	TXSetup.rx_data = NULL;
	TXSetup.rx_length = 0;
	TXSetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &TXSetup, I2C_TRANSFER_POLLING) == SUCCESS)
		return 0;

	return -1;
}
#endif

static void WriteCommand(uint8_t Data)
{
#ifdef OLED_USE_I2C
    uint8_t Buffer[2];

    Buffer[0] = 0X00; // Write Co & D/C bits
    Buffer[1] = Data; // Data

    I2C_Write(OLED_I2C_ADDR, Buffer, 2);
#else
    SSP_DATA_SETUP_Type TransferConfig;
    
	TransferConfig.tx_data = &Data;
	TransferConfig.rx_data = NULL;
	TransferConfig.length  = 1;

    // Globally disable interrupts
    __disable_irq();

    // Indicate incoming command
    OLED_CMD();
    
    // Select the OLED
    OLED_CS_ON();

    SSP_ReadWrite(LPC_SSP1, &TransferConfig, SSP_TRANSFER_POLLING);

    // De-select the OLED
    OLED_CS_OFF();

    // Globally enable interrupts
    __enable_irq();
#endif
}

static void WriteData(uint8_t Data)
{
#ifdef OLED_USE_I2C
    uint8_t Buffer[2];

    Buffer[0] = 0x40; // Write Co & D/C bits
    Buffer[1] = Data; // Data

    I2C_Write(OLED_I2C_ADDR, Buffer, 2);
#else
    SSP_DATA_SETUP_Type TransferConfig;

	TransferConfig.tx_data = &Data;
	TransferConfig.rx_data = NULL;
	TransferConfig.length  = 1;

    // Globally disable interrupts
    __disable_irq();

    // Indicate incoming data
    OLED_DATA();
    
    // Select the OLED
    OLED_CS_ON();

    SSP_ReadWrite(LPC_SSP1, &TransferConfig, SSP_TRANSFER_POLLING);

    // De-select the OLED
    OLED_CS_OFF();

    // Globally enable interrupts
    __enable_irq();
#endif
}

/// @todo Optimize (at least from a RAM point of view)
static void WriteDataLength(unsigned char Data, unsigned int Length)
{
#ifdef OLED_USE_I2C
    uint8_t Buffer[140];
    int i;

    Buffer[0] = 0x40; // Write Co & D/C bits

    // Fill buffer
    for (i = 1; i < Length+1; i++)
        Buffer[i] = Data;

    I2C_Write(OLED_I2C_ADDR, Buffer, Length+1);
#else
    uint8_t Buffer[140];
    int i;
    SSP_DATA_SETUP_Type TransferConfig;

    // Fill buffer
    for (i = 0; i < Length; i++)
        Buffer[i] = Data;

	TransferConfig.tx_data = Buffer;
	TransferConfig.rx_data = NULL;
	TransferConfig.length  = Length;

    // Globally disable interrupts
    __disable_irq();

    // Indicate incoming data
    OLED_DATA();
    
    // Select the OLED
    OLED_CS_ON();

    SSP_ReadWrite(LPC_SSP1, &TransferConfig, SSP_TRANSFER_POLLING);

    //SSPSend( (uint8_t *)buf, len );

    // De-select the OLED
    OLED_CS_OFF();

    // Globally enable interrupts
    __enable_irq();
#endif
}

static void RunInitSequence(void)
{
    // Recommended Initial code according to manufacturer

    WriteCommand(0X02); // Set low column address
    WriteCommand(0X12); // Set high column address
    WriteCommand(0x40); // (Display start set)
    WriteCommand(0x2e); // (Stop horzontal scroll)
    WriteCommand(0x81); // (Set contrast control register)
    WriteCommand(0x32); // ?
    WriteCommand(0x82); // (Brightness for color banks)
    WriteCommand(0x80); // (Display on)
    WriteCommand(0xa1); // (Set segment re-map)
    WriteCommand(0xa6); // (Set normal/inverse display)
  //WriteCommand(0xa7); // (Set inverse display)
    WriteCommand(0xa8); // (Set multiplex ratio)
    WriteCommand(0x3F); // ?
    WriteCommand(0xd3); // (Set display offset)
    WriteCommand(0x40); // ?
    WriteCommand(0xad); // (Set dc-dc on/off)
    WriteCommand(0x8E); // ?
    WriteCommand(0xc8); // (Set com output scan direction)
    WriteCommand(0xd5); // (Set display clock divide ratio/oscillator/frequency)
    WriteCommand(0xf0); // ?
    WriteCommand(0xd8); // (Set area color mode on/off & low power display mode )
    WriteCommand(0X05); // ?
    WriteCommand(0xd9); // (Set pre-charge period)
    WriteCommand(0xF1); // ?
    WriteCommand(0xda); // (Set com pins hardware configuration)
    WriteCommand(0X12); // ?
    WriteCommand(0xdb); // (Set vcom deselect level)
    WriteCommand(0x34); // ?
    WriteCommand(0x91); // (Set look up table for area color)
    WriteCommand(0x3f); // ?
    WriteCommand(0x3f); // ?
    WriteCommand(0x3f); // ?
    WriteCommand(0x3f); // ?
    WriteCommand(0xaf); // (Display on)
    WriteCommand(0xa4); // (Display on)
}

/// @todo Optimise
static void HorizontalLine(uint8_t X0, uint8_t Y0, uint8_t X1, OLED_Colour Colour)
{
    uint8_t Temp;

    // Ensure left point is less than right point
    if (X0 > X1)
    {
        Temp = X1;
        X1 = X0;
        X0 = Temp;
    }

    // Move along line colouring pixels
    while(X1 >= X0)
    {
        OLED_Pixel(X0, Y0, Colour);
        X0++;
    }
}

static void VerticalLine(uint8_t X0, uint8_t Y0, uint8_t Y1, OLED_Colour Colour)
{
    uint8_t Temp;

    // Ensure bottom point is less than top point
    if(Y0 > Y1)
    {
        Temp = Y1;
        Y1 = Y0;
        Y0 = Temp;
    }

    // Move along line colouring pixels
    while(Y1 >= Y0)
    {
        OLED_Pixel(X0, Y0, Colour);
        Y0++;
    }
    return;
}

//------------------------------------------------------------------------------

// Public Functions
void OLED_Init(void)
{
    volatile int Delay = 0;

    //GPIO_SetDir(PORT0, 0, 1);
    GPIO_SetDir(2, (1<<1), 1);
    GPIO_SetDir(2, (1<<7), 1);
    GPIO_SetDir(0, (1<<6), 1);

    // Make sure power is off
    GPIO_ClearValue(2, (1<<1) );

#ifdef OLED_USE_I2C
    GPIO_ClearValue(2, (1<<7)); // D/C#
    GPIO_ClearValue(0, (1<<6)); // CS#
#else
    OLED_CS_OFF();
#endif

    // Send the initialization commands to the display
    RunInitSequence();

    // Zero the shadow framebuffer
    memset(ShadowFB, 0, SHADOW_FB_SIZE);

    // Small delay before turning on power
    for (Delay = 0; Delay < 0xffff; Delay++);

    // Power on
    GPIO_SetValue( 2, (1<<1) );
}

void OLED_ClearScreen(OLED_Colour Colour)
{
    uint8_t i;
    uint8_t c = 0;

    if (Colour == OLED_COLOR_WHITE)
        c = 0xff;

    // Go through all 8 pages
    for(i=0xB0; i<0xB8; i++)
    {            
        SetAddress(i, 0X00, 0X10);
        WriteDataLength(c, 132);
    }
    
    // Erase framebuffer
    memset(ShadowFB, c, SHADOW_FB_SIZE);
}

void OLED_Pixel(uint8_t X, uint8_t Y, OLED_Colour Colour)
{
    uint8_t Page;
    uint16_t Add;
    uint8_t LowAddress;
    uint8_t HighAddress;
    uint8_t Mask;
    uint32_t ShadowPos = 0;

    if (X > OLED_DISPLAY_WIDTH)
        return;
        
    if (Y > OLED_DISPLAY_HEIGHT)
        return;

    // Page address
         if(Y < 8)  Page = 0xB0;
    else if(Y < 16) Page = 0xB1;
    else if(Y < 24) Page = 0xB2;
    else if(Y < 32) Page = 0xB3;
    else if(Y < 40) Page = 0xB4;
    else if(Y < 48) Page = 0xB5;
    else if(Y < 56) Page = 0xB6;
    else            Page = 0xB7;

    Add = X + X_OFFSET;
    LowAddress = 0X0F & Add;        // Low address
    HighAddress = 0X10 | (Add >> 4);// High address

    // Calculate mask from rows basically do a y%8 and remainder is bit position
    Add = Y>>3;         // Divide by 8
    Add <<= 3;          // Multiply by 8
    Add = Y - Add;      // Calculate bit position
    Mask = 1 << Add;    // Left shift 1 by bit position



    // Set the address (sets the page, lower and higher column address pointers)
    SetAddress(Page, LowAddress, HighAddress);
     
    ShadowPos = (Page-0xB0) * OLED_DISPLAY_WIDTH + X;

    if(Colour > 0)
        ShadowFB[ShadowPos] |= Mask;
    else
        ShadowFB[ShadowPos] &= ~Mask;

    WriteData(ShadowFB[ShadowPos]);

}

void OLED_Line(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, OLED_Colour Colour)
{
    int16_t   dX = 0, dY = 0;
    int8_t    dX_Symbol = 0, dY_Symbol = 0;
    int16_t   TwodX = 0, TwodY = 0;
    int16_t   dI = 0;

    dX = X1-X0;
    dY = Y1-Y0;

    // Vertical line
    if(dX == 0) { VerticalLine(X0, Y0, Y1, Colour); return; }
    // Horizontal line
    if(dY == 0) { HorizontalLine(X0, Y0, Y1, Colour); return; }
    
    if(dX > 0)  dX_Symbol =  1;
    else        dX_Symbol = -1;

    if(dY > 0)  dY_Symbol =  1;
    else        dY_Symbol = -1;

    dX = dX_Symbol * dX;
    dY = dY_Symbol * dY;

    TwodX = dX*2;
    TwodY = dY*2;

    if(dX >= dY)
    {
        dI = TwodY - dX;
        while(X0 != X1)
        {

            OLED_Pixel(X0, Y0, Colour);
            X0 += dX_Symbol;
            if (dI < 0)
            {
                dI += TwodY;
            }
            else
            {
                dI += TwodY - TwodX;
                Y0 += dY_Symbol;
            }
        }
        OLED_Pixel(X0, Y0, Colour);
    }
    else
    {
        dI = TwodX - dY;
        while(Y0 != Y1)
        {
            OLED_Pixel(X0, Y0, Colour);
            Y0 += dY_Symbol;
            if (dI < 0)
            {
                dI += TwodX;
            }
            else
            {
                dI += TwodX - TwodY;
                X0 += dX_Symbol;
            }
        }
        OLED_Pixel(X0, Y0, Colour);
    }
}

void OLED_LineCircle(uint8_t X, uint8_t Y, uint8_t R, OLED_Colour Colour)
{
    int16_t Draw_X0, Draw_Y0;
    int16_t Draw_X1, Draw_Y1;
    int16_t Draw_X2, Draw_Y2;
    int16_t Draw_X3, Draw_Y3;
    int16_t Draw_X4, Draw_Y4;
    int16_t Draw_X5, Draw_Y5;
    int16_t Draw_X6, Draw_Y6;
    int16_t Draw_X7, Draw_Y7;
    int16_t XX, YY;
    int16_t dI;

    // No radius
    if(R == 0) return;
    
    // 90 degree
    Draw_X0 = Draw_X1 = X;
    Draw_Y0 = Draw_Y1 = Y + R;
    if(Draw_Y0 < OLED_DISPLAY_HEIGHT) OLED_Pixel(Draw_X0, Draw_Y0, Colour);

    // 270 degree
    Draw_X2 = Draw_X3 = X;
    Draw_Y2 = Draw_Y3 = Y - R;
    if(Draw_Y2 >= 0) OLED_Pixel(Draw_X2, Draw_Y2, Colour);

    // 0 degree
    Draw_X4 = Draw_X6 = X + R;
    Draw_Y4 = Draw_Y6 = Y;
    if(Draw_X4 < OLED_DISPLAY_WIDTH) OLED_Pixel(Draw_X4, Draw_Y4, Colour);

    // 180 degree
    Draw_X5 = Draw_X7 = X - R;
    Draw_Y5 = Draw_Y7 = Y;
    if(Draw_X5>=0) OLED_Pixel(Draw_X5, Draw_Y5, Colour);

    if(R == 1) return;

    dI = 3 - 2*R;
    XX = 0;
    YY = R;
    while(XX < YY)
    {

        if(dI < 0)
        {
            dI += 4*XX + 6;
        }
        else
        {
            dI += 4*(XX - YY) + 10;
            YY--;
            Draw_Y0--;
            Draw_Y1--;
            Draw_Y2++;
            Draw_Y3++;
            Draw_X4--;
            Draw_X5++;
            Draw_X6--;
            Draw_X7++;
        }
        XX++;
        Draw_X0++;
        Draw_X1--;
        Draw_X2++;
        Draw_X3--;
        Draw_Y4++;
        Draw_Y5++;
        Draw_Y6--;
        Draw_Y7--;

        if((Draw_X0 <= OLED_DISPLAY_WIDTH) && (Draw_Y0>=0))                     OLED_Pixel(Draw_X0, Draw_Y0, Colour);
        if((Draw_X1 >= 0) && (Draw_Y1 >= 0))                                    OLED_Pixel(Draw_X1, Draw_Y1, Colour);
        if((Draw_X2 <= OLED_DISPLAY_WIDTH) && (Draw_Y2 <= OLED_DISPLAY_HEIGHT)) OLED_Pixel(Draw_X2, Draw_Y2, Colour);
        if((Draw_X3 >=0 ) && (Draw_Y3 <= OLED_DISPLAY_HEIGHT))                  OLED_Pixel(Draw_X3, Draw_Y3, Colour);
        if((Draw_X4 <= OLED_DISPLAY_WIDTH) && (Draw_Y4 >= 0))                   OLED_Pixel(Draw_X4, Draw_Y4, Colour);
        if((Draw_X5 >= 0) && (Draw_Y5 >= 0))                                    OLED_Pixel(Draw_X5, Draw_Y5, Colour);
        if((Draw_X6 <= OLED_DISPLAY_WIDTH) && (Draw_Y6 <= OLED_DISPLAY_HEIGHT)) OLED_Pixel(Draw_X6, Draw_Y6, Colour);
        if((Draw_X7 >= 0) && (Draw_Y7 <= OLED_DISPLAY_HEIGHT))                  OLED_Pixel(Draw_X7, Draw_Y7, Colour);
    }
    return;
}

/// @todo Optimise
void OLED_FillCircle(uint8_t X, uint8_t Y, uint8_t R, OLED_Colour Colour)
{
    while (R > 0)
    {
        OLED_LineCircle(X, Y, R, Colour);
        R--;
    }
    
    // Not sure if required:
    //OLED_Pixel(X, Y, Colour);
}

void OLED_LineRect(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, OLED_Colour Colour)
{
    HorizontalLine(X0, Y0, X1, Colour);
    HorizontalLine(X0, Y1, X1, Colour);
    VerticalLine(X0, Y0, Y1, Colour);
    VerticalLine(X1, Y0, Y1, Colour);
}

void OLED_FillRect(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, OLED_Colour Colour)
{
    uint8_t Temp = 0;

    if (X0 > X1)
    {
        Temp  = X0;
        X0 = X1;
        X1 = Temp;
    }

    if (Y0 > Y1)
    {
        Temp  = Y0;
        Y0 = Y1;
        Y1 = Temp;
    }

    if (Y0 == Y1)
    {
        HorizontalLine(X0, Y0, X1, Colour);
        return;
    }

    if(X0 == X1)
    {
        VerticalLine(X0, Y0, Y1, Colour);
        return;
    }

    while(Y0 <= Y1)
    {
        HorizontalLine(X0, Y0, X1, Colour);
        Y0++;
    }
}

uint8_t OLED_Char(uint8_t X, uint8_t Y, uint8_t Character, OLED_Colour Forground, OLED_Colour Background)
{
    unsigned char Data = 0;
    unsigned char i = 0, j = 0;

    if ((X >= (OLED_DISPLAY_WIDTH - 8)) || (Y >= (OLED_DISPLAY_HEIGHT - 8)))
        return 0;

    // Unknown character will be set to blank
    if((Character < 0x20) || (Character > 0x7f))
        Character = 0x20;

    Character -= 0x20;
    for (i = 0; i < 8; i++)
    {
        Data = Font5x7[Character][i];
        for(j = 0; j < 6; j++)
        {
            if((Data & Font_Mask[j]) == 0)
                OLED_Pixel(X, Y, Background);
            else
                OLED_Pixel(X, Y, Forground);
            X++;
        }
        Y++;
        X -= 6;
    }
    return 1;
}

void OLED_String(uint8_t X, uint8_t Y, uint8_t *String, OLED_Colour Forground, OLED_Colour Background)
{
    while(1)
    {
        if ((*String)=='\0') return;
        if (OLED_Char(X, Y, *String++, Forground, Background) == 0) return;
        X += 6;
    }
}

void WriteOLEDString(uint8_t* String, uint8_t Line, uint8_t Position)
{
	// Calculate current X position for character
	uint8_t X = Position*6 + 1;
	// Calculate current Y position for character
	const uint8_t Y = Line*8 + 1;
	// Store writing result
	uint8_t Result = 1;
	// Loop until the end of the string
	while(1) {
		// If the next character is a null character, stop.
		if ((*String)=='\0') return;

		// Write the current character to the OLED
		Result = OLED_Char(X, Y, *String++, OLED_COLOR_WHITE, OLED_COLOR_BLACK);

		// If the result of the write is a 0, then we are off the edge of the OLED and should stop
		if (Result == 0) return;

		// Increment the X location for the next character
		X += 6;
	}
}
