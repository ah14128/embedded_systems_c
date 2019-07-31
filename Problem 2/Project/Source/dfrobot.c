/*****************************************************************************
 *   dfrobot.c:  Driver for the DF Robot chassis with wheel encoders
 *
 *   Notes: -> I'd like to say this is thread safe but it's not.
 *          -> Possible clash on ADC configuration.
 *
 *   Copyright(C) 2015, Jeremy Dalton (jd0185@my.bristol.ac.uk)
 *   All rights reserved.
 *
 ******************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "lpc17xx_gpio.h"
#include "lpc17xx_pwm.h"
#include "dfrobot.h"

#include "LPC17xx_PinSelect.h"
#include "LPC17xx_ADC.h"

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/
#define DFR_FORWARD 0x01
#define DFR_REVERSE 0x00

#define DFR_100		0xFF
#define DFR_75		0xBE
#define DFR_50		0x7F
#define DFR_25		0x40
#define DFR_0		0x00


/******************************************************************************
 * External global variables
 *****************************************************************************/


/******************************************************************************
 * Local variables
 *****************************************************************************/
int DFR_PWMRate = 1000;

uint8_t DFR_Gear = 1;
 
uint8_t RightWheelCount = 0;
uint8_t RightWheelDestination = 0;
uint8_t LeftWheelCount = 0;
uint8_t LeftWheelDestination = 0;


/******************************************************************************
 * Local Functions
 *****************************************************************************/

/******************************************************************************
 * Description:
 *    Initialize PWM channels needed for motor driver in SINGLE Edge PWM mode
 *****************************************************************************/
void DFR_PWMInit (void)
{
	// -> power up pwm hardware
	// -> set clock source
	// -> reset counter
	// -> set pre-scale
	// -> set match condition
	// -> set MR0
	// -> set MRx registers
	// -> set PCR register
	// -> latch in MR0 and MRx values
	// -> enable counter, set PWM mode, reset counter
	// -> enable counter and set PWM mode
	
	// pwmout0 & pwmout5
	LPC_SC->PCONP |= (1 << 6);					// PWM on
	LPC_PINCON->PINSEL4 &=~( (3<<0)|(3<<11) );	// reset ([0:1] are 1)
	LPC_PINCON->PINSEL4 |= ( (1<<0)|(1<<10) );	// set PWM1.1 at P2.0
	LPC_PWM1->TCR = 2;							// counter reset
	LPC_PWM1->PR = 24;							// clock /4 / prescaler (= PR +1) = 1 �s
	LPC_PWM1->MCR = (1<<1)|(1<<3)|(1<<18);		// reset on MR0
	LPC_PWM1->MR0 = 1000;						// set PWM cycle 1khz
	LPC_PWM1->MR1 = 500;						// set duty
	LPC_PWM1->MR6 = 500;						// set duty
	LPC_PWM1->LER = (1<<0)|(1<<1)|(1<<6);		// latch MR0 & MR1
	LPC_PWM1->PCR = (1<<9)|(1<<14);				// PWM1 output enable
	LPC_PWM1->TCR = (1<<0)|(1<<3);				// counter enable, PWM enable
}

/******************************************************************************
 * Description:
 *    Set duty cycle for both channels and enable latch on next MR0 match.
 *****************************************************************************/
int DFR_SetPWM (int right, int left)
{
	// Channel (MRx) match value cannot equal timer match (MR0) value.
	// As far as I can tell bad things will happen if it does.
	// Probably worth a try to make sure.
	if((right < DFR_PWMRate) && (left < DFR_PWMRate))
	{
		// set MRx registers
		LPC_PWM1->MR1 = DFR_ScalePWM(left);
		LPC_PWM1->MR6 = DFR_ScalePWM(right);
		
		// set LER for MR0, MR1 & MR6
		LPC_PWM1->LER = (1<<0)|(1<<1)|(1<<6);
	
		return 1;
	}
	else 
	{
		// Failure
		return -1;
	}
}

/******************************************************************************
 * Description:
 *    Set duty cycle for right channel and enable latch on next MR0 match.
 *****************************************************************************/
int DFR_SetRightPWM (int right)
{
	if(right < DFR_PWMRate)
	{
		// set MR6
		LPC_PWM1->MR6 = DFR_ScalePWM(right);
		
		// set LER for MR6
		LPC_PWM1->LER = (1<<6);
		
		return 1;
	}
	else
	{
		// Failure
		return -1;
	}
}

/******************************************************************************
 * Description:
 *    Set duty cycle for left channel and enable latch on next MR0 match.
 *****************************************************************************/
int DFR_SetLeftPWM (int left)
{
	if(left < DFR_PWMRate)
	{
		// Set MR 1
		LPC_PWM1->MR1 = DFR_ScalePWM(left);
		
		// set LER for MR1
		LPC_PWM1->LER = (1<<1);
		
		return 1;
	}
	else
	{
		// Failure
		return -1;
	}
}

/******************************************************************************
 * Description:
 *    Scale 0-100% onto the defined PWM frequency linearly.
 *****************************************************************************/
int DFR_ScalePWM (int value)
{
	// We need to choose PWM rates sensibly so this divides nicely. Can't use
	// floats as the MRx registers will object to it. +ve integers only.
	
	// We'll just have to rely on truncation in hardware sorting out decimal
	// places and hope. Problem is the user could enter anything from
	// 0-100% and we just have to deal with the consequences.
	
	// Gear only really limits top speed but for the same speed demand a higher
	// gear will result in going faster.
	
	int x = value;
	int in_min = 0;
	int in_max = 100;
	int out_min = 0;
	int out_max = 0;
	
	if(DFR_Gear == 1)
	{
		out_max = 250;
	}
	else if(DFR_Gear == 2)
	{
		out_max = 500;
	}
	else if(DFR_Gear == 3)
	{
		out_max = 750;
	}
	else if(DFR_Gear == 4)
	{
		out_max = 1000;
	}
	else
	{
		out_max = 0;
	}

	if (value <= 100)
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
	else
	{
		return 0;
	}
}

/******************************************************************************
 * Description:
 *    Initialise the ADC channel needed for the range finder
 *****************************************************************************/
void DFR_ADCInit (void)
{
	PINSEL_CFG_Type PinConfig;
	PinConfig.Funcnum = 1;			// Set first alternative function
	PinConfig.OpenDrain = 0;
	PinConfig.Pinmode = 0;			// Set input
	PinConfig.Pinnum = 26;			// Pin 26 - Channel AD0.3
	PinConfig.Portnum = 0;			// I/O Port 0
    PINSEL_ConfigPin(&PinConfig);

	ADC_Init(LPC_ADC, 200000);
	ADC_ChannelCmd(LPC_ADC,3,ENABLE);			// This could be wrong
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,SET);	// This could be wrong
	ADC_BurstCmd(LPC_ADC,1);					// This could be wrong
	ADC_StartCmd(LPC_ADC,ADC_START_CONTINUOUS);	// This could be wrong

	// We could be really smart and get information from the range finder
	// by DMA transfer into memory every time a conversion is done so
	// there is always a current value irrespective of how broken the 
	// rest of the code gets. Could be complicated. Sounds like time.
	
	// Enabling this breaks the world and/or Google +/- 10%.
	// Also, it turns on the ADC interrupts and we get stuck in the ISR
	//NVIC_EnableIRQ(ADC_IRQn);
}


/******************************************************************************
 * Public Functions
 *****************************************************************************/

/******************************************************************************
 * Description:
 *    Initialize motor driver and wheel encoder driver
 *****************************************************************************/
void DFR_RobotInit (void)
{
    GPIO_SetDir(2, 1, 1 );		// PWM Output 1 [RGB Red]	[PIO1.9]	(Left)
    GPIO_SetDir(2, (1<<5), 1 );	// PWM Output 2 [Eth led2]	[PIO2.5]	(Right)
    GPIO_SetDir(2, 1 << 6, 1);	// Direction Output 1		[PIO2.6]	(Left)
    GPIO_SetDir(2, 1 << 10, 1);	// Direction Output 2		[PIO2.9]	(Right)
    GPIO_SetDir(2, 1 << 11, 0);	// Encoder Input 1			[PIO2.10]	(Left)
    GPIO_SetDir(2, 1 << 12, 0);	// Encoder Input 2			[PIO3.3]	(Right)

    // Clear control pins to make sure
    GPIO_ClearValue(2, 1 | 1 << 5 | 1 << 6 | 1 << 10);

    // Enable rising edge interrupts for the encoder inputs
    // Read current state of IO2IntEnR register
    unsigned gpioTemp = 0;
    gpioTemp = LPC_GPIOINT->IO2IntEnR;

    // Set the 11th and 12th bits
    gpioTemp |= 1 << 11;
    gpioTemp |= 1 << 12;

    // Write it back out to IO2IntEnR
    GPIO_IntCmd(2, gpioTemp, 0);
	
	// Both of these need trying. Second is more complete than first.
	DFR_PWMInit();
	DFR_SetPWM(0, 0);

	// Initialise the ADC channel needed for the range finder
	//DFR_ADCInit();
}

/******************************************************************************
 * Description:
 *    Go forwards at desired speed
 *****************************************************************************/
void DFR_DriveForward (int speed)
{
	GPIO_SetValue(2, 1 << 6 | 1 << 10); // Set direction outputs high
	DFR_SetPWM(speed, speed); // set PWM outputs to speed
}

/******************************************************************************
 * Description:
 *    Go backwards at desired speed
 *****************************************************************************/
void DFR_DriveBackward (int speed)
{
	GPIO_ClearValue(2, 1 << 6 | 1 << 10); // Set direction outputs low
	DFR_SetPWM(speed, speed); // set PWM outputs to speed
}

/******************************************************************************
 * Description:
 *    Tank turn right at desired speed
 *****************************************************************************/
void DFR_DriveRight (int speed)
{
	GPIO_SetValue(2, 1 << 6); // Set left motor forward
	GPIO_ClearValue(2, 1 << 10); // Set Right motor backward
	DFR_SetPWM(speed, speed); // set motor outputs to speed
}

/******************************************************************************
 * Description:
 *    Tank turn left at desired speed
 *****************************************************************************/
void DFR_DriveLeft (int speed)
{
	GPIO_SetValue(2, 1 << 10); // Set left motor forward
	GPIO_ClearValue(2, 1 << 6); // Set Right motor backward
	DFR_SetPWM(speed, speed); // set motor outputs to speed
}

/******************************************************************************
 * Description:
 *    Skid steer right at desired speed
 *****************************************************************************/
void DFR_SkidRight (int speed)
{
	DFR_SetRightPWM(0);
	GPIO_SetValue(2, 1 << 6); // Set left motor forward
	DFR_SetLeftPWM(speed); // set left motor output to speed
}

/******************************************************************************
 * Description:
 *    Skid steer left at desired speed
 *****************************************************************************/
void DFR_SkidLeft (int speed)
{
	DFR_SetLeftPWM(0);
	GPIO_SetValue(2, 1 << 10); // Set right motor forward
	DFR_SetRightPWM(speed); // set right motor output to speed
}

/******************************************************************************
 * Description:
 *    Stop both motors
 *****************************************************************************/
void DFR_DriveStop (void)
{
	GPIO_ClearValue(2, 1 << 6 | 1 << 10);
	DFR_SetPWM(DFR_0, DFR_0); // set motor outputs to zero
}

/******************************************************************************
 * Description:
 *    Set right motor only
 *****************************************************************************/
void DFR_SetRightDrive (uint8_t direction, int speed)
{
	if(direction == DFR_FORWARD)
	{
		GPIO_SetValue(2, 1 << 10); // Set Right motor backward
		DFR_SetRightPWM(speed); // set right motor output to speed
	}
	else if(direction == DFR_REVERSE)
	{
		GPIO_ClearValue(2, 1 << 10); // Set Right motor backward
		DFR_SetRightPWM(speed); // set right motor output to speed
	}
	else
	{
		// It's gone a bit pear shaped if we get here
	}
}

/******************************************************************************
 * Description:
 *    Set left motor only
 *****************************************************************************/
void DFR_SetLeftDrive (uint8_t direction, int speed)
{
	if(direction == DFR_FORWARD)
	{
		GPIO_SetValue(2, 1 << 6); // Set left motor backward
		DFR_SetLeftPWM(speed); // set left motor output to speed
	}
	else if(direction == DFR_REVERSE)
	{
		GPIO_ClearValue(2, 1 << 6); // Set left motor backward
		DFR_SetLeftPWM(speed); // set left motor output to speed
	}
	else
	{
		// It's gone a bit pear shaped if we get here
	}
}

/******************************************************************************
 * Description:
 *    Return the current right wheel encoder count
 *****************************************************************************/
uint8_t DFR_GetRightWheelCount (void)
{
	return RightWheelCount;
}

/******************************************************************************
 * Description:
 *    Set the current right wheel encoder count
 *****************************************************************************/
void DFR_SetRightWheelCount (uint8_t val)
{
	RightWheelCount = val;
}

/******************************************************************************
 * Description:
 *    Increment the current right wheel encoder count and return result
 *****************************************************************************/
uint8_t DFR_IncRightWheelCount (void)
{
	RightWheelCount++;
	return RightWheelCount;
}

/******************************************************************************
 * Description:
 *    Decrement the current right wheel encoder count and return result
 *****************************************************************************/
uint8_t DFR_DecRightWheelCount (void)
{
	RightWheelCount++;
	return RightWheelCount;
}

/******************************************************************************
 * Description:
 *    Set the distance desired in the destination variable
 *****************************************************************************/
void DFR_SetRightWheelDestination (uint8_t distance)
{
	RightWheelDestination = distance;
}

/******************************************************************************
 * Description:
 *    Get the distance stored in the destination variable
 *****************************************************************************/
uint8_t DFR_GetRightWheelDestination (void)
{
	return RightWheelDestination;
}

/******************************************************************************
 * Description:
 *    Return the current left wheel encoder count
 *****************************************************************************/
uint8_t DFR_GetLeftWheelCount (void)
{
	return LeftWheelCount;
}

/******************************************************************************
 * Description:
 *    Set the current left wheel encoder count
 *****************************************************************************/
void DFR_SetLeftWheelCount (uint8_t val)
{
	LeftWheelCount = val;
}

/******************************************************************************
 * Description:
 *    Increment the current left wheel encoder count and return result
 *****************************************************************************/
uint8_t DFR_IncLeftWheelCount (void)
{
	LeftWheelCount++;
	return LeftWheelCount;
}

/******************************************************************************
 * Description:
 *    Decrement the current left wheel encoder count and return result
 *****************************************************************************/
uint8_t DFR_DecLeftWheelCount (void)
{
	LeftWheelCount--;
	return LeftWheelCount;
}

/******************************************************************************
 * Description:
 *    Set the distance desired in the destination variable
 *****************************************************************************/
void DFR_SetLeftWheelDestination (uint8_t distance)
{
	LeftWheelDestination = distance;
}

/******************************************************************************
 * Description:
 *    Get the distance stored in the destination variable
 *****************************************************************************/
uint8_t DFR_GetLeftWheelDestination (void)
{
	return LeftWheelDestination;
}

/******************************************************************************
 * Description:
 *    Clears the distance stored in the wheel count variables.
 *****************************************************************************/
void DFR_ClearWheelCounts (void)
{
	DFR_SetRightWheelCount(0);
	DFR_SetLeftWheelCount(0);
}

/******************************************************************************
 * Description:
 *    Increment the soft gear
 *****************************************************************************/
void DFR_IncGear (void)
{
	DFR_Gear++;
	if(DFR_Gear > 4) DFR_Gear = 4;
}

/******************************************************************************
 * Description:
 *    Decrement the soft gear
 *****************************************************************************/
void DFR_DecGear (void)
{
	DFR_Gear--;
	if(DFR_Gear < 1) DFR_Gear = 1;
}

/******************************************************************************
 * Description:
 *    Return the current soft gear
 *****************************************************************************/
uint8_t DFR_GetGear (void)
{
	return DFR_Gear;
}

void DFR_IncRightWheelDestination (void)
{
	RightWheelDestination += 10;
}

void DFR_IncLeftWheelDestination (void)
{
	LeftWheelDestination += 10;
}
void DFR_DecRightWheelDestination (void)
{
	RightWheelDestination -= 10;
}

void DFR_DecLeftWheelDestination (void)
{
	LeftWheelDestination -= 10;
}
/******************************************************************************
 * Description:
 *    Initialise flying sub-system and time circuits
 *****************************************************************************/
/*
void Hover (float Height)
{
	// Requires "Flux_Capacitor.h" to be included
	// Requires "DeLorean.h" to be included

	 #define	powerIn	1210000000
	 #define	velocityIn	88

	 date previousTime;
	 date currentTime;
	 date destinationTime;

	 destinationTime.year = 2015;
	 destinationTime.month = 10;
	 destinationTime.day = 21;

	 previousTime = currentTime;

	 time.circuitsOn(powerIn);
	 time.set(destinationTime);
	 currentTime = time.travel(destinationTime, previousTime, velocityIn)
}
*/
