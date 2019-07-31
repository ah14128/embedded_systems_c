/**************************************************************************//**
 *
 * @file        LPC17xx_DriverInterface.c
 * @brief       Part of FreeRTOS+IO
 * @author      Real Time Engineers Ltd.
 * @version     1.0.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2012 Real Time Engineers ltd.
 * All rights reserved.
 *
******************************************************************************/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOS_Task.h"

/* FreeRTOS IO library includes. */
#include "FreeRTOS_DriverInterface.h"
#include "FreeRTOS_UART.h"
#include "FreeRTOS_SSP.h"
#include "FreeRTOS_I2C.h"

portBASE_TYPE vFreeRTOS_lpc17xx_PopulateFunctionPointers( const Peripheral_Types_t ePeripheralType, Peripheral_Control_t * const pxPeripheralControl )
{
portBASE_TYPE xReturn = pdFALSE;

	switch( ePeripheralType )
	{
		/* Open the peripheral. */
		case eUART_TYPE	:

			#if ioconfigINCLUDE_UART == 1
			{
				xReturn = FreeRTOS_UART_open( pxPeripheralControl );
			}
			#endif /* ioconfigINCLUDE_UART */
			break;


		case eSSP_TYPE :

			#if ioconfigINCLUDE_SSP == 1
			{
				xReturn = FreeRTOS_SSP_open( pxPeripheralControl );
			}
			#endif /* ioconfigINCLUDE_SSP */
			break;
			

		case eI2C_TYPE :
		
			#if ioconfigINCLUDE_I2C == 1
			{
				xReturn = FreeRTOS_I2C_open( pxPeripheralControl );
			}
			#endif /* ioconfigINCLUDE_I2C */
			break;


		default :
		
			/* Nothing to do here.  xReturn is already set to pdFALSE. */
			configASSERT( xReturn );
			break;
	}
	
	/* Just to prevent compiler warnings should FreeRTOSIOConfig.h be
	configured to exclude the above FreeRTOS_nnn_open() calls. */
	( void ) pxPeripheralControl;

	return xReturn;
}

