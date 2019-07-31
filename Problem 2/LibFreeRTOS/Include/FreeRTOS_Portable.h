/**************************************************************************//**
 *
 * @file        Portable.h
 * @brief       Part of FreeRTOS
 * @author      Real Time Engineers Ltd.
 * @version     7.1.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2011 Real Time Engineers Ltd.
 * All rights reserved.
 *
******************************************************************************/

/*-----------------------------------------------------------
 * Portable layer API.  Each function must be defined for each port.
 *----------------------------------------------------------*/

#ifndef PORTABLE_H
#define PORTABLE_H

/* Include the macro file relevant to the port being used. */

#ifdef OPEN_WATCOM_INDUSTRIAL_PC_PORT
	#include "..\..\Source\portable\owatcom\16bitdos\pc\FreeRTOS_PortMacro.h"
	typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef OPEN_WATCOM_FLASH_LITE_186_PORT
	#include "..\..\Source\portable\owatcom\16bitdos\flsh186\FreeRTOS_PortMacro.h"
	typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef GCC_MEGA_AVR
	#include "../portable/GCC/ATMega323/FreeRTOS_PortMacro.h"
#endif

#ifdef IAR_MEGA_AVR
	#include "../portable/IAR/ATMega323/FreeRTOS_PortMacro.h"
#endif

#ifdef MPLAB_PIC24_PORT
	#include "..\..\Source\portable\MPLAB\PIC24_dsPIC\FreeRTOS_PortMacro.h"
#endif

#ifdef MPLAB_DSPIC_PORT
	#include "..\..\Source\portable\MPLAB\PIC24_dsPIC\FreeRTOS_PortMacro.h"
#endif

#ifdef MPLAB_PIC18F_PORT
	#include "..\..\Source\portable\MPLAB\PIC18F\FreeRTOS_PortMacro.h"
#endif

#ifdef MPLAB_PIC32MX_PORT
	#include "..\..\Source\portable\MPLAB\PIC32MX\FreeRTOS_PortMacro.h"
#endif

#ifdef _FEDPICC
	#include "libFreeRTOS/Include/FreeRTOS_PortMacro.h"
#endif

#ifdef SDCC_CYGNAL
	#include "../../Source/portable/SDCC/Cygnal/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_ARM7
	#include "../../Source/portable/GCC/ARM7_LPC2000/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_ARM7_ECLIPSE
	#include "FreeRTOS_PortMacro.h"
#endif

#ifdef ROWLEY_LPC23xx
	#include "../../Source/portable/GCC/ARM7_LPC23xx/FreeRTOS_PortMacro.h"
#endif

#ifdef IAR_MSP430
	#include "..\..\Source\portable\IAR\MSP430\FreeRTOS_PortMacro.h"
#endif
	
#ifdef GCC_MSP430
	#include "../../Source/portable/GCC/MSP430F449/FreeRTOS_PortMacro.h"
#endif

#ifdef ROWLEY_MSP430
	#include "../../Source/portable/Rowley/MSP430F449/FreeRTOS_PortMacro.h"
#endif

#ifdef ARM7_LPC21xx_KEIL_RVDS
	#include "..\..\Source\portable\RVDS\ARM7_LPC21xx\FreeRTOS_PortMacro.h"
#endif

#ifdef SAM7_GCC
	#include "../../Source/portable/GCC/ARM7_AT91SAM7S/FreeRTOS_PortMacro.h"
#endif

#ifdef SAM7_IAR
	#include "..\..\Source\portable\IAR\AtmelSAM7S64\FreeRTOS_PortMacro.h"
#endif

#ifdef SAM9XE_IAR
	#include "..\..\Source\portable\IAR\AtmelSAM9XE\FreeRTOS_PortMacro.h"
#endif

#ifdef LPC2000_IAR
	#include "..\..\Source\portable\IAR\LPC2000\FreeRTOS_PortMacro.h"
#endif

#ifdef STR71X_IAR
	#include "..\..\Source\portable\IAR\STR71x\FreeRTOS_PortMacro.h"
#endif

#ifdef STR75X_IAR
	#include "..\..\Source\portable\IAR\STR75x\FreeRTOS_PortMacro.h"
#endif
	
#ifdef STR75X_GCC
	#include "..\..\Source\portable\GCC\STR75x\FreeRTOS_PortMacro.h"
#endif

#ifdef STR91X_IAR
	#include "..\..\Source\portable\IAR\STR91x\FreeRTOS_PortMacro.h"
#endif
	
#ifdef GCC_H8S
	#include "../../Source/portable/GCC/H8S2329/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_AT91FR40008
	#include "../../Source/portable/GCC/ARM7_AT91FR40008/FreeRTOS_PortMacro.h"
#endif

#ifdef RVDS_ARMCM3_LM3S102
	#include "../../Source/portable/RVDS/ARM_CM3/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_ARMCM3_LM3S102
	#include "../../Source/portable/GCC/ARM_CM3/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_ARMCM3
	#include "../../Source/portable/GCC/ARM_CM3/FreeRTOS_PortMacro.h"
#endif

#ifdef IAR_ARM_CM3
	#include "../../Source/portable/IAR/ARM_CM3/FreeRTOS_PortMacro.h"
#endif

#ifdef IAR_ARMCM3_LM
	#include "../../Source/portable/IAR/ARM_CM3/FreeRTOS_PortMacro.h"
#endif
	
#ifdef HCS12_CODE_WARRIOR
	#include "../../Source/portable/CodeWarrior/HCS12/FreeRTOS_PortMacro.h"
#endif	

#ifdef MICROBLAZE_GCC
	#include "../../Source/portable/GCC/MicroBlaze/FreeRTOS_PortMacro.h"
#endif

#ifdef TERN_EE
	#include "..\..\Source\portable\Paradigm\Tern_EE\small\FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_HCS12
	#include "../../Source/portable/GCC/HCS12/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_MCF5235
    #include "../../Source/portable/GCC/MCF5235/FreeRTOS_PortMacro.h"
#endif

#ifdef COLDFIRE_V2_GCC
	#include "../../../Source/portable/GCC/ColdFire_V2/FreeRTOS_PortMacro.h"
#endif

#ifdef COLDFIRE_V2_CODEWARRIOR
	#include "../../Source/portable/CodeWarrior/ColdFire_V2/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_PPC405
	#include "../../Source/portable/GCC/PPC405_Xilinx/FreeRTOS_PortMacro.h"
#endif

#ifdef GCC_PPC440
	#include "../../Source/portable/GCC/PPC440_Xilinx/FreeRTOS_PortMacro.h"
#endif

#ifdef _16FX_SOFTUNE
	#include "..\..\Source\portable\Softune\MB96340\FreeRTOS_PortMacro.h"
#endif

#ifdef BCC_INDUSTRIAL_PC_PORT
	/* A short file name has to be used in place of the normal
	FreeRTOSConfig.h when using the Borland compiler. */
	#include "frconfig.h"
	#include "..\portable\BCC\16BitDOS\PC\prtmacro.h"
    typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef BCC_FLASH_LITE_186_PORT
	/* A short file name has to be used in place of the normal
	FreeRTOSConfig.h when using the Borland compiler. */
	#include "frconfig.h"
	#include "..\portable\BCC\16BitDOS\flsh186\prtmacro.h"
    typedef void ( __interrupt __far *pxISR )();
#endif

#ifdef __GNUC__
   #ifdef __AVR32_AVR32A__
	   #include "FreeRTOS_PortMacro.h"
   #endif
#endif

#ifdef __ICCAVR32__
   #ifdef __CORE__
      #if __CORE__ == __AVR32A__
	      #include "FreeRTOS_PortMacro.h"
      #endif
   #endif
#endif

#ifdef __91467D
	#include "FreeRTOS_PortMacro.h"
#endif

#ifdef __96340
	#include "FreeRTOS_PortMacro.h"
#endif


#ifdef __IAR_V850ES_Fx3__
	#include "../../Source/portable/IAR/V850ES/FreeRTOS_PortMacro.h"
#endif

#ifdef __IAR_V850ES_Jx3__
	#include "../../Source/portable/IAR/V850ES/FreeRTOS_PortMacro.h"
#endif

#ifdef __IAR_V850ES_Jx3_L__
	#include "../../Source/portable/IAR/V850ES/FreeRTOS_PortMacro.h"
#endif

#ifdef __IAR_V850ES_Jx2__
	#include "../../Source/portable/IAR/V850ES/FreeRTOS_PortMacro.h"
#endif

#ifdef __IAR_V850ES_Hx2__
	#include "../../Source/portable/IAR/V850ES/FreeRTOS_PortMacro.h"
#endif

#ifdef __IAR_78K0R_Kx3__
	#include "../../Source/portable/IAR/78K0R/FreeRTOS_PortMacro.h"
#endif
	
#ifdef __IAR_78K0R_Kx3L__
	#include "../../Source/portable/IAR/78K0R/FreeRTOS_PortMacro.h"
#endif
	
/* Catch all to ensure FreeRTOS_PortMacro.h is included in the build.  Newer demos
have the path as part of the project options, rather than as relative from
the project location.  If portENTER_CRITICAL() has not been defined then
FreeRTOS_PortMacro.h has not yet been included - as every FreeRTOS_PortMacro.h provides a
portENTER_CRITICAL() definition.  Check the demo application for your demo
to find the path to the correct FreeRTOS_PortMacro.h file. */
#ifndef portENTER_CRITICAL
	#include "FreeRTOS_PortMacro.h"
#endif
	
#if portBYTE_ALIGNMENT == 8
	#define portBYTE_ALIGNMENT_MASK ( 0x0007 )
#endif

#if portBYTE_ALIGNMENT == 4
	#define portBYTE_ALIGNMENT_MASK	( 0x0003 )
#endif

#if portBYTE_ALIGNMENT == 2
	#define portBYTE_ALIGNMENT_MASK	( 0x0001 )
#endif

#if portBYTE_ALIGNMENT == 1
	#define portBYTE_ALIGNMENT_MASK	( 0x0000 )
#endif

#ifndef portBYTE_ALIGNMENT_MASK
	#error "Invalid portBYTE_ALIGNMENT definition"
#endif

#ifndef portNUM_CONFIGURABLE_REGIONS
	#define portNUM_CONFIGURABLE_REGIONS 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS_MPUWrappers.h"

/*
 * Setup the stack of a new task so it is ready to be placed under the
 * scheduler control.  The registers have to be placed on the stack in
 * the order that the port expects to find them.
 *
 */
#if( portUSING_MPU_WRAPPERS == 1 )
	portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters, portBASE_TYPE xRunPrivileged ) PRIVILEGED_FUNCTION;
#else
	portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters );
#endif

/*
 * Map to the memory management routines required for the port.
 */
void *pvPortMalloc( size_t xSize ) PRIVILEGED_FUNCTION;
void vPortFree( void *pv ) PRIVILEGED_FUNCTION;
void vPortInitialiseBlocks( void ) PRIVILEGED_FUNCTION;
size_t xPortGetFreeHeapSize( void ) PRIVILEGED_FUNCTION;

/*
 * Setup the hardware ready for the scheduler to take control.  This generally
 * sets up a tick interrupt and sets timers for the correct tick frequency.
 */
portBASE_TYPE xPortStartScheduler( void ) PRIVILEGED_FUNCTION;

/*
 * Undo any hardware/ISR setup that was performed by xPortStartScheduler() so
 * the hardware is left in its original condition after the scheduler stops
 * executing.
 */
void vPortEndScheduler( void ) PRIVILEGED_FUNCTION;

/*
 * The structures and methods of manipulating the MPU are contained within the
 * port layer.
 *
 * Fills the xMPUSettings structure with the memory region information
 * contained in xRegions.
 */
#if( portUSING_MPU_WRAPPERS == 1 ) 
	struct xMEMORY_REGION;
	void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION * const xRegions, portSTACK_TYPE *pxBottomOfStack, unsigned short usStackDepth ) PRIVILEGED_FUNCTION;
#endif

#ifdef __cplusplus
}
#endif

#endif /* PORTABLE_H */

