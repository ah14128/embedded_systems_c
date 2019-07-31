/*****************************************************************************
 *   dfrobot.h:  Header file for DF Robot chassis with wheel encoders
 *
 *   Copyright(C) 2015, Jeremy Dalton (jd0185@my.bristol.ac.uk)
 *   All rights reserved.
 *
******************************************************************************/
#ifndef __DFROBOT_H
#define __DFROBOT_H

#define DFR_FORWARD 0x01
#define DFR_REVERSE 0x00

#define DFR_100		0xFF
#define DFR_75		0xBE
#define DFR_50		0x7F
#define DFR_25		0x40
#define DFR_0		0x00

void DFR_PWMInit (void);

int DFR_SetPWM (int right, int left);
int DFR_SetRightPWM (int right);
int DFR_SetLeftPWM (int left);

void DFR_ADCInit (void);

void DFR_RobotInit (void);
void DFR_DriveForward(int speed);
void DFR_DriveBackward(int speed);
void DFR_DriveRight(int speed);
void DFR_DriveLeft(int speed);
void DFR_SkidRight(uint8_t speed);
void DFR_SkidLeft(uint8_t speed);
void DFR_DriveStop(void);
void DFR_SetRightDrive(uint8_t direction, int speed);
void DFR_SetLeftDrive(uint8_t direction, int speed);

uint8_t DFR_GetRightWheelCount(void);
void DFR_SetRightWheelCount(uint8_t val);
uint8_t DFR_IncRightWheelCount(void);
uint8_t DFR_DecRightWheelCount(void);
void DFR_SetRightWheelDestination(uint8_t distance);
uint8_t DFR_GetRightWheelDestination(void);
uint8_t DFR_GetLeftWheelCount(void);
void DFR_SetLeftWheelCount(uint8_t val);
uint8_t DFR_IncLeftWheelCount(void);
uint8_t DFR_DecLeftWheelCount(void);
void DFR_SetLeftWheelDestination(uint8_t distance);
uint8_t DFR_GetLeftWheelDestination(void);
void DFR_ClearWheelCounts(void);
void DFR_IncreaseRightDistance(uint8_t distance);
void DFR_IncreaseLeftDistance(uint8_t distance);


//void Hover (float Height);

#endif /* end __DFROBOT_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
