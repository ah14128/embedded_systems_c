/**************************************************************************//**
 *
 * @file        IOConfig.h
 * @brief       Part of FreeRTOS+IO
 * @author      Real Time Engineers Ltd.
 * @version     1.0.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2012 Real Time Engineers ltd.
 * All rights reserved.
 *
******************************************************************************/

/*
 * These settings are described in the Configuration section of the FreeRTOS+IO
 * documentation: http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_IO/
 */

#ifndef FREERTOS_IO_CONFIG_H
#define FREERTOS_IO_CONFIG_H

/* Globally include or exclude transfer modes. -------------------------------*/
#define ioconfigUSE_ZERO_COPY_TX							1
#define ioconfigUSE_TX_CHAR_QUEUE  							1
#define ioconfigUSE_CIRCULAR_BUFFER_RX 						1
#define ioconfigUSE_RX_CHAR_QUEUE 							1

/* Peripheral options --------------------------------------------------------*/
#define ioconfigINCLUDE_UART								1
	#define ioconfigUSE_UART_POLLED_TX						1
	#define ioconfgiUSE_UART_POLLED_RX						1
	#define ioconfigUSE_UART_ZERO_COPY_TX					1
	#define ioconfigUSE_UART_TX_CHAR_QUEUE					1
	#define ioconfigUSE_UART_CIRCULAR_BUFFER_RX				1
	#define ioconfigUSE_UART_RX_CHAR_QUEUE					1

#define ioconfigINCLUDE_SSP									1
	#define ioconfigUSE_SSP_POLLED_TX						1
	#define ioconfigUSE_SSP_POLLED_RX						1
	#define ioconfigUSE_SSP_ZERO_COPY_TX					0
	#define ioconfigUSE_SSP_CIRCULAR_BUFFER_RX				0
	#define ioconfigUSE_SSP_RX_CHAR_QUEUE					0
	#define ioconfigUSE_SSP_TX_CHAR_QUEUE					0

#define ioconfigINCLUDE_I2C									1
	#define ioconfigUSE_I2C_POLLED_TX						1
	#define ioconfigUSE_I2C_POLLED_RX						1
	#define ioconfigUSE_I2C_ZERO_COPY_TX					1
	#define ioconfigUSE_I2C_CIRCULAR_BUFFER_RX				1
	#define ioconfigUSE_I2C_TX_CHAR_QUEUE					1




/* Sanity check configuration.  Do not edit below this line. */
#if ( ioconfigINCLUDE_UART == 1 ) && ( ioconfigUSE_UART_ZERO_COPY_TX == 1 ) && ( ioconfigUSE_ZERO_COPY_TX != 1 )
	#error ioconfigUSE_ZERO_COPY_TX must also be set to 1 if ioconfigUSE_UART_ZERO_COPY_TX is set to 1
#endif

#if ( ioconfigINCLUDE_UART == 1 ) && ( ioconfigUSE_UART_TX_CHAR_QUEUE == 1 ) && ( ioconfigUSE_TX_CHAR_QUEUE != 1 )
	#error ioconfigUSE_TX_CHAR_QUEUE must also be set to 1 if ioconfigUSE_UART_TX_CHAR_QUEUE is set to 1
#endif

#if ( ioconfigINCLUDE_UART == 1 ) && ( ioconfigUSE_UART_CIRCULAR_BUFFER_RX == 1 ) && ( ioconfigUSE_CIRCULAR_BUFFER_RX != 1 )
	#error ioconfigUSE_CIRCULAR_BUFFER_RX must also be set to 1 if ioconfigUSE_UART_CIRCULAR_BUFFER_RX is set to 1
#endif

#if ( ioconfigINCLUDE_UART == 1 ) && ( ioconfigUSE_UART_RX_CHAR_QUEUE == 1 ) && ( ioconfigUSE_RX_CHAR_QUEUE != 1 )
	#error ioconfigUSE_RX_CHAR_QUEUE must also be set to 1 if ioconfigUSE_UART_RX_CHAR_QUEUE is set to 1
#endif

#if ( ioconfigUSE_SSP == 1 ) && ( ioconfigUSE_SSP_ZERO_COPY_TX == 1 ) && ( ioconfigUSE_ZERO_COPY_TX != 1 )
	#error ioconfigUSE_ZERO_COPY_TX must also be set to 1 if ioconfigUSE_SSP_ZERO_COPY_TX is set to 1
#endif

#if ( ioconfigINCLUDE_SSP == 1 ) && ( ioconfigUSE_SSP_CIRCULAR_BUFFER_RX == 1 ) && ( ioconfigUSE_CIRCULAR_BUFFER_RX != 1 )
	#error ioconfigUSE_CIRCULAR_BUFFER_RX must also be set to 1 if ioconfigUSE_SSP_CIRCULAR_BUFFER_RX is set to 1
#endif

#if ( ioconfigINCLUDE_SSP == 1 ) && ( ioconfigUSE_SSP_TX_CHAR_QUEUE == 1 ) && ( ioconfigUSE_TX_CHAR_QUEUE != 1 )
	#error ioconfigUSE_TX_CHAR_QUEUE must also be set to 1 if ioconfigUSE_SSP_TX_CHAR_QUEUE is set to 1
#endif

#if ( ioconfigINCLUDE_SSP == 1 ) && ( ioconfigUSE_SSP_RX_CHAR_QUEUE == 1 ) && ( ioconfigUSE_RX_CHAR_QUEUE != 1 )
	#error ioconfigUSE_RX_CHAR_QUEUE must also be set to 1 if ioconfigUSE_SSP_RX_CHAR_QUEUE is set to 1
#endif

#if ( ioconfigUSE_I2C == 1 ) && ( ioconfigUSE_I2C_ZERO_COPY_TX == 1 ) && ( ioconfigUSE_ZERO_COPY_TX != 1 )
	#error ioconfigUSE_ZERO_COPY_TX must also be set to 1 if ioconfigUSE_I2C_ZERO_COPY_TX is set to 1
#endif

#if ( ioconfigINCLUDE_I2C == 1 ) && ( ioconfigUSE_I2C_TX_CHAR_QUEUE == 1 ) && ( ioconfigUSE_TX_CHAR_QUEUE != 1 )
	#error ioconfigUSE_TX_CHAR_QUEUE must also be set to 1 if ioconfigUSE_I2C_TX_CHAR_QUEUE is set to 1
#endif

#if ( ioconfigINCLUDE_I2C == 1 ) && ( ioconfigUSE_I2C_CIRCULAR_BUFFER_RX == 1 ) && ( ioconfigUSE_CIRCULAR_BUFFER_RX != 1 )
	#error ioconfigUSE_CIRCULAR_BUFFER_RX must also be set to 1 if ioconfigUSE_I2C_CIRCULAR_BUFFER_RX is set to 1
#endif

#endif /* FREERTOS_IO_CONFIG_H */


