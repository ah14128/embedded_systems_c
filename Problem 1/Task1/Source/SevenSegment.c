/***************************************************************************//**
 * 
 * @file		SevenSegment.c
 * @brief		Driver for the 7 segment display
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

// Includes
#include "LPC17xx_GPIO.h"
#include "LPC17xx_SSP.h"

#include "SevenSegment.h"

//------------------------------------------------------------------------------

// Defines and typedefs
#define LED7_CS_OFF() GPIO_SetValue(2, (1<<2))
#define LED7_CS_ON()  GPIO_ClearValue(2, (1<<2))

//------------------------------------------------------------------------------

// External global variables
//...

//------------------------------------------------------------------------------

// Local variables
static uint8_t CharacterMap[] = {
        /* '-', '.' */
        0xFB, 0xDF, 0xFF,
        /* digits 0 - 9 */
        0x24, 0x7D, 0xE0, 0x70, 0x39, 0x32, 0x22, 0x7C, 0x20, 0x30,
        /* ':' to '@' are invalid */
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        /* A to J */
        0x21, 0x38, 0x74, 0xA8, 0x70, 0x71, 0x10, 0x29, 0x8F, 0xAC,
        /* K to T */
        0xFF, 0x7C,  0xFF, 0xB9, 0x04, 0x61, 0x03, 0xF9, 0x12, 0x78,
        /* U to Z */
        0x2C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        /* '[' to '`' */
        0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF,
        /* a to j */
        0x21, 0x38, 0xF8, 0xA8, 0x70, 0x71, 0x02, 0x39, 0x8F, 0xAC,
        /* k to t */
        0xFF, 0x7C,  0xFF, 0xB9, 0xB8, 0x61, 0x03, 0xF9, 0x12, 0x78,
        /* u to z */
        0xBC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        /* { to '|' */
        0xFF, 0x7D,
};

//------------------------------------------------------------------------------

// Local Functions
//...

//------------------------------------------------------------------------------

// Public Functions
void SevenSegment_Init(void)
{
    //GPIO_SetDir( 2, 2, 1 );
	GPIO_SetDir(2, (1<<2), 1);
    LED7_CS_OFF();
}

void SevenSegment_SetCharacter(uint8_t Character, uint32_t RawMode)
{
    uint8_t Value = 0xFF;
    SSP_DATA_SETUP_Type TransferConfig;

    if (RawMode)
    {
        Value = Character;
    }
    else
    {
    	if ((Character >= '-') && (Character <= '|'))
    		Value = CharacterMap[Character - '-'];
    }

	TransferConfig.tx_data = &Value;
	TransferConfig.rx_data = NULL;
	TransferConfig.length = 1;

    // Select the 7 segment display
    LED7_CS_ON();
    
    // Send data
    SSP_ReadWrite(LPC_SSP1, &TransferConfig, SSP_TRANSFER_POLLING);

    // De-select the 7 segment display
    LED7_CS_OFF();
}

