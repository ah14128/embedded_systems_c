/**************************************************************************//**
 *
 * @file        Main.c
 * @brief       Entry point for the program
 * @author      Geoffrey Daniels, Dimitris Agrafiotis
 * @author		Sam Walder, Jeremy Dalton 12/2012
 * @version     1.0
 * @date        19 July. 2012
 *
 * Copyright(C) 2012, University of Bristol
 * All rights reserved.
 *
******************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/
// Standard C library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// LPC17xx definitions for CMSIS
#include "LPC17xx.h"

// LPC17xx drivers (that use CMSIS)
#include "LPC17xx_Types.h"
#include "LPC17xx_PinSelect.h"
#include "LPC17xx_GPIO.h"
#include "LPC17xx_SSP.h"
#include "LPC17xx_I2C.h"
#include "LPC17xx_ADC.h"
#include "LPC17xx_UART.h"
#include "LPC17xx_Timer.h"
#include "LPC17xx_SysTick.h"
#include "LPC17xx_LED2.h"

// Baseboard drivers (that use LPC17xx drivers)
#include "dfrobot.h"
#include "OLED.h"
#include "Buttons.h"
#include "RotarySwitch.h"
#include "SevenSegment.h"
#include "Tune.h"
#include "pca9532.h"
#include "joystick.h"
#include "new_string.h"


/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/
// PCADC / PCAD
#define ADC_POWERON (1 << 12)
#define PCLK_ADC 24
#define PCLK_ADC_MASK (3 << 24)

// AD0.0 - P0.23, PINSEL1 [15:14] = 01
#define SELECT_ADC0 (0x1<<14)

// ADOCR constants
#define START_ADC (1<<24)
#define OPERATIONAL_ADC (1 << 21)
#define SEL_AD0 (1 <<0)
#define ADC_DONE_BIT	(1 << 31)

/******************************************************************************
 * Global variables
 *****************************************************************************/
uint8_t Stop = 0;
uint8_t idle = 0;
float IdleCounter = 0;
uint16_t ADCval;
uint32_t string1;
char c[1] = {0};
float systimer = 0;
float ult = 0;
char s[1] = {0};
uint32_t timertimer = 0;
int MusicFlag = 0;
uint32_t CurrentNote = 0;
uint32_t CurrentDuration = 0;
uint32_t CurrentPause = 0;
uint32_t timer = 0;
char* SongStringPointer = 0;
int flag2 = 0;
int flagA = 0;
int flagB = 0;
int rotaryCount = 0;
int8_t i = 0;

/******************************************************************************
 * Local Functions
 *****************************************************************************/
void StopSong(void);
void ResumeSong(void);
void PauseSong(void);
void Song_Handler(uint32_t duration);
void init_timer ( uint8_t timer_num, uint32_t TimerInterval );
void Song_Information(char* SongString);
void Play_Tunes(char* SongString);
 /******************************************************************************
 * Description:
 *    Simple delaying function. Not good. Blocking code.
 *****************************************************************************/


/******************************************************************************
 * Description:
 *    Flash the LED on the LPC1769 as a heart beat
 *****************************************************************************/
void SysTick_Handler(void)    {

	LED2_Invert();
	if (idle == 0)
	{
		IdleCounter++;
	}
	systimer++;

	if(systimer == 10000)
	{
		ult = (IdleCounter/systimer)*100;
		sprintf(c,"%.2f", ult);
		WriteOLEDString((uint8_t*)c, 0, 11);
		WriteOLEDString((uint8_t*)"%", 0, 15);
		IdleCounter = 0;
		systimer = 0;
	}






}

void Init_SysTick1000ms(void) {
	if (SysTick_Config(SystemCoreClock / 1))
	{
		while(1) { ; }
	}
}
void Init_SysTick100ms(void)  {
	if (SysTick_Config(SystemCoreClock / 10))
	{
		while(1) { ; }
	}
}
void Init_SysTick10ms(void)   {
	if (SysTick_Config(SystemCoreClock / 100))
	{
		while(1) { ; }
	}
}
void Init_SysTick1ms(void)    {
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		while(1) { ; }
	}
}
void Init_SysTick100us(void)    {
	if (SysTick_Config(SystemCoreClock / 10000))
	{
		while(1) { ; }
	}
}

/******************************************************************************
 * Description: Initialise the SPI hardware
 *    
 *****************************************************************************/
static void Init_SSP(void)
{
	SSP_CFG_Type SSP_Config;
	PINSEL_CFG_Type PinConfig;

	// Initialize SPI pin connect
	// P0.7 - SCK; P0.8 - MISO; P0.9 - MOSI; P2.2 - SSEL - used as GPIO
	PinConfig.Funcnum = 2;
	PinConfig.OpenDrain = 0;
	PinConfig.Pinmode = 0;
	PinConfig.Portnum = 0;
	PinConfig.Pinnum = 7;
	PINSEL_ConfigPin(&PinConfig);
	PinConfig.Pinnum = 8;
	PINSEL_ConfigPin(&PinConfig);
	PinConfig.Pinnum = 9;
	PINSEL_ConfigPin(&PinConfig);
	PinConfig.Funcnum = 0;
	PinConfig.Portnum = 2;
	PinConfig.Pinnum = 2;
	PINSEL_ConfigPin(&PinConfig);
	SSP_ConfigStructInit(&SSP_Config);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_Config);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);
}

/******************************************************************************
 * Description: Initialise the I2C hardware
 *    
 *****************************************************************************/
static void Init_I2C(void)
{
	PINSEL_CFG_Type PinConfig;

	/* Initialize I2C2 pin connect */
	PinConfig.Funcnum = 2;
	PinConfig.Pinnum = 10;
	PinConfig.Portnum = 0;
	PINSEL_ConfigPin(&PinConfig);
	PinConfig.Pinnum = 11;
	PINSEL_ConfigPin(&PinConfig);

	// Initialize I2C peripheral
	I2C_Init(LPC_I2C2, 100000);

	// Enable I2C1 operation
 	I2C_Cmd(LPC_I2C2, I2C_MASTER_MODE, ENABLE);
}

/******************************************************************************
 * Description: Configure an ADC channel
 *    
 *****************************************************************************/
static void Init_ADC(void)
{
	/*
	PINSEL_CFG_Type PinConfig;
	PinConfig.Funcnum = 1;
	PinConfig.OpenDrain = 0;
	PinConfig.Pinmode = 0;
	PinConfig.Pinnum = 23;			// Channel AD0.0
	PinConfig.Portnum = 0;
    PINSEL_ConfigPin(&PinConfig);


	ADC_Init(LPC_ADC, 200000);
	ADC_ChannelCmd(LPC_ADC,0,ENABLE);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,SET);
	ADC_BurstCmd(LPC_ADC,1);
	ADC_StartCmd(LPC_ADC,ADC_START_CONTINUOUS);
	*/
}

/******************************************************************************
 * Description: Run some init functions
 *    
 *****************************************************************************/
void Init(void)
{
	// LPC1769
	LED2_Init();
	Init_SysTick100us();
	Init_SSP();
	Init_I2C();
	//Init_ADC();
	LED2_On();

	// Baseboard
	Tune_Init();
	OLED_Init();
	RotarySwitch_Init();
	SevenSegment_Init();
	pca9532_init();
	joystick_init();

	// Extra Hardware
	DFR_RobotInit();

	// GPIO Interrupts Enable

	// SW3
	//GPIO_IntCmd(0,1 << 4, 0);
	// Joystick
	//GPIO_IntCmd(2, 1<< 11|1<<12,0); //encoders
	GPIO_IntCmd(0,1 << 4 | 1 << 16| 1 << 15 | 1 << 24 | 1 << 25 | 1 << 17, 0); // SW4
	GPIO_IntCmd(2,1 << 3 | 1 << 4 | 1 << 11 | 1<< 12, 0); // ENCODERS AND JOYSTICK
	// Enable Timer 0 interrupt
	NVIC_EnableIRQ(TIMER0_IRQn);
	// Enable GPIO Interrupts
	NVIC_EnableIRQ(EINT3_IRQn);
}

/******************************************************************************
 * Description: Main program entry point
 *    
 *****************************************************************************/
int main (void)
{
	// Globally disable interrupts
	__disable_irq();

	// Initialise
	Init();

	// Globally enable interrupts
	__enable_irq();

  	// Initialise OLED contents
	//IdleCounter = 1;
	//char c[1] = {0};
	//sprintf(c, "%d", IdleCounter);
	OLED_ClearScreen(OLED_COLOR_BLACK);
	//WriteOLEDString((uint8_t*)"Feed Me a Stray", 3, 0);
	WriteOLEDString((uint8_t*)"CPU Usage:", 0, 0);
	WriteOLEDString((uint8_t*)"Pitch:", 3, 0);
	WriteOLEDString((uint8_t*)"Tempo:", 5, 0);
	sprintf(s,"%d",Tune_GetTempo());
	WriteOLEDString((uint8_t*)s, 5, 7);
	sprintf(s,"%d",Tune_GetPitch());
	WriteOLEDString((uint8_t*)s, 3, 7);

	//WriteOLEDString((uint8_t*)"UP to stop and", 4, 0);
	//WriteOLEDString((uint8_t*)"play tune.", 5, 0);

	// Set the seven segment to 0
//	i = Tune_GetTempo();
//	itoa(s,i,2);
	SevenSegment_SetCharacter('4', FALSE);

	// Main program loop
	while (1) //IDLE LOOP
	{
		idle = 1;
	}
}


/******************************************************************************
 * Interrupt Service Routines
 *****************************************************************************/
void EINT3_IRQHandler (void)
{


	idle = 0;
	//BUTTON (Clear everything)
	if ((((LPC_GPIOINT->IO0IntStatR) >> 4)& 0x1) == ENABLE)
	{
		StopSong();
		DFR_DriveStop();
		DFR_ClearWheelCounts();
		Stop = 0;
	}
	// Encoder input 1 (Left)
	if ((((LPC_GPIOINT->IO2IntStatR) >> 11)& 0x1) == ENABLE)
	{
		DFR_IncLeftWheelCount();
		if (DFR_GetLeftWheelCount() == DFR_GetLeftWheelDestination())
		{
			DFR_DriveStop();
			DFR_ClearWheelCounts();
		}

	}

	// Encoder input 2 (Right)
	else if ((((LPC_GPIOINT->IO2IntStatR) >> 12)& 0x1) == ENABLE)
	{
		DFR_IncRightWheelCount();
		if (DFR_GetRightWheelCount() == DFR_GetRightWheelDestination())
		{
			DFR_DriveStop();
			DFR_ClearWheelCounts();
		}
	}

	// Joystick DOWN
	if ((((LPC_GPIOINT->IO0IntStatR) >> 15)& 0x1) == ENABLE)
	{
		pca9532_setLeds(0b0000000110000000, 0xffff);
		//Play_Tunes(Tune_SampleSongs[9]);
		DFR_DriveBackward (400);


	}
	// JOY UP
	if ((((LPC_GPIOINT->IO2IntStatR) >> 3)& 0x1) == ENABLE)
	{

		Play_Tunes(Tune_SampleSongs[0]);
		//DFR_IncreaseLeftDistance(20);
		//DFR_IncreaseRightDistance(20);
		DFR_SetLeftWheelDestination(20);
		DFR_SetRightWheelDestination(20);
		DFR_DriveForward(400);

	}
	//JOY RIGHT
	if ((((LPC_GPIOINT->IO0IntStatR) >> 16)& 0x1) == ENABLE)
	{
		DFR_IncreaseRightDistance(20);
		//DFR_SetRightWheelDestination(22);
		DFR_DriveRight (400);
		Play_Tunes(Tune_SampleSongs[8]);
	}
	//JOY LEFT
	if ((((LPC_GPIOINT->IO2IntStatR) >> 4)& 0x1) == ENABLE)
	{
		DFR_SetLeftWheelDestination(22);
		DFR_DriveLeft (400);
		Play_Tunes(Tune_SampleSongs[3]);
	}
	//Joystick Press
	if ((((LPC_GPIOINT->IO0IntStatR) >> 17)& 0x1) == ENABLE)
	{
		if(MusicFlag != 4)
		{
			PauseSong();
			SevenSegment_SetCharacter('P', FALSE);
		}
		else if(MusicFlag == 4)
		{
			ResumeSong();
			SevenSegment_SetCharacter('4', FALSE);
		}
		else{
			//Should not happen
		}
	}

	//ROTARY A (CW)
	if ((((LPC_GPIOINT->IO0IntStatR) >> 24)& 0x1) == ENABLE)
	{

		if(flagA == 1)
		{
			if (Buttons_Read2()  == 0)
			{
				Tune_IncPitch();
				flagA = 0;
				sprintf(s,"%d",Tune_GetPitch());
				WriteOLEDString((uint8_t*)s, 3, 7);
			}
			else
			{
				Tune_IncTempo();
				flagA = 0;
				sprintf(s,"%d",Tune_GetTempo());
				WriteOLEDString((uint8_t*)s, 5, 7);
			}
		}
		else
		{
			flagA = 1;
		}

	}

	//ROTARY B (CCW)
	else if ((((LPC_GPIOINT->IO0IntStatR) >>  25)& 0x1) == ENABLE)
	{
		if(flagA == 1)
		{
			if (Buttons_Read2()  == 0)
			{
				Tune_DecPitch();
				flagA = 0;
				sprintf(s,"%d",Tune_GetPitch());
				WriteOLEDString((uint8_t*)s, 3, 7);
			}
			else
			{
				Tune_DecTempo();
				flagA = 0;
				sprintf(s,"%d",Tune_GetTempo());
				WriteOLEDString((uint8_t*)s, 5, 7);
			}
		}
		else
		{
			flagA = 1;
		}

	}
	// Clear GPIO Interrupt Flags
	// SW3 | Joystick
    GPIO_ClearInt(0,1 << 4 | 1 << 15 | 1 << 16 | 1 << 24 | 1 << 25 | 1 << 17);
    // Joystick | Encoder | Encoder
    GPIO_ClearInt(2,1 << 3 | 1 << 11 | 1 << 12 | 1 << 4);

}


void init_timer ( uint8_t timer_num, uint32_t TimerInterval )
{
	if ( timer_num == 0 )
	{
		LPC_TIM0->MR0 = TimerInterval;
		LPC_TIM0->MCR = 3;				/* Interrupt and Reset on MR0 */
	}
}
void PauseSong(void)
{
	MusicFlag = 4;
}
void ResumeSong(void)
{
	MusicFlag = 0;

}
void StopSong(void)
{
	SongStringPointer = NULL;
}



void Song_Handler(uint32_t duration)
{
	LPC_TIM0->TCR = 0x02;
	init_timer(0, duration*30);
	LPC_TIM0->TCR = 1;
}

void Play_Tunes(char* SongString)
{
	SongStringPointer = SongString;
	Song_Handler(2500);
}


void TIMER0_IRQHandler(void)
{
	idle = 0;
	LPC_TIM0->IR = 1;
	if (MusicFlag ==0)
	{
		CurrentNote = Tune_GetNote(*SongStringPointer++);
		CurrentDuration = Tune_GetDuration(*SongStringPointer++);
		CurrentPause = Tune_GetPause(*SongStringPointer++);
		MusicFlag = 1;
	}
	if(timertimer >= CurrentDuration*1000)
		{
			MusicFlag = 0;
			timer= CurrentPause*1000;
			timertimer = 0;
			if(*SongStringPointer == 0)
			{
				LPC_TIM0->TCR = 0x02;
				return;
			}
		}
	else if(MusicFlag == 1) //SPEAKER ON
	{
		Tune_PlayNote();
		MusicFlag = 2;
		timer = CurrentNote/2;
		timertimer += CurrentNote/2;
	}
	else if(MusicFlag == 2) //SPEAKER OFF
	{
		Tune_StopNote();
		timer = CurrentNote/2;
		timertimer += CurrentNote/2;
		MusicFlag = 1;
	}
	if(MusicFlag == 4)
	{
		timer = 25000;
	}
	Song_Handler(timer);
}
