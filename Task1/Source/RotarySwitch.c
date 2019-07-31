/***************************************************************************//**
 * 
 * @file		RotarySwitch.c
 * @brief		Driver for the rotary switch
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

// Includes
#include "LPC17xx_GPIO.h"

#include "RotarySwitch.h"

//------------------------------------------------------------------------------

// Defines and typedefs
#define ROTARY_READ_STATE() ((GPIO_ReadValue(0) >> 24) & 0x03)
//#define ROTARY_READ_STATE() ( (LPC_GPIO2->DATA >> 1) & 0x03)
//#define ROTARY_READ_STATE() ( (LPC_GPIO1->DATA) & 0x03)

#define R_W  0
#define R_L1 1
#define R_L2 2
#define R_L3 3
#define R_R1 4
#define R_R2 5
#define R_R3 6

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
void RotarySwitch_Init(void)
{
    GPIO_SetDir( 0, (1<<24 | 1 << 25), 0 );
}

uint8_t RotarySwitch_Read(void)
{
    // p0.24 and p0.25
    uint8_t State = ROTARY_READ_STATE();
    uint8_t Event = ROTARY_WAIT;
    uint8_t E = R_W;

    if (State == 0x03) return ROTARY_WAIT;

    while (State != 0x03)
    {
        switch (E)
        {
        case R_W:
            if (State == 0x01)      E = R_L1;
            else if (State == 0x02) E = R_R1;
            break;
        case R_L1:
            if (State == 0x00)      E = R_R2;
            break;
        case R_L2:
            if (State == 0x01)
            {
                E = R_R3;
                Event = ROTARY_RIGHT;
            }
            break;
        case R_R1:
            if (State == 0x00)      E = R_L2;
            break;
        case R_R2:
            if (State == 0x02)
            {
                E = R_L3;
                Event = ROTARY_LEFT;
            }
            break;
        }

        State = ROTARY_READ_STATE();
    }

    return Event;
}
