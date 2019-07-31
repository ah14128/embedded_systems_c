/**************************************************************************//**
 *
 * @file        IOUtilsCharQueueTxAndRx.c
 * @brief       Part of FreeRTOS+IO
 * @author      Real Time Engineers Ltd.
 * @version     1.0.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2012 Real Time Engineers ltd.
 * All rights reserved.
 *
******************************************************************************/

/* Standard includes. */
#include "string.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOS_Task.h"
#include "FreeRTOS_Semaphore.h"

/* Device specific library includes. */
#include "FreeRTOS_DriverInterface.h"
#include "FreeRTOS_IOUtilsCommon.h"

/*-----------------------------------------------------------*/

void xIOUtilsSetTxQueueTimeout( Peripheral_Control_t * const pxPeripheralControl, const portTickType xMaxWaitTime )
{
Transfer_Control_t *pxTransferControlState = pxPeripheralControl->pxTxControl;
Character_Queue_State_t *pxTxQueueState;

	pxTxQueueState = ( Character_Queue_State_t * ) ( pxTransferControlState->pvTransferState );
	pxTxQueueState->xBlockTime = xMaxWaitTime;
}
/*-----------------------------------------------------------*/

void vIOUtilsSetRxQueueTimeout( Peripheral_Control_t * const pxPeripheralControl, const portTickType xMaxWaitTime )
{
Transfer_Control_t *pxTransferControlState = pxPeripheralControl->pxRxControl;
Character_Queue_State_t *pxRxQueueState;

	pxRxQueueState = ( Character_Queue_State_t * ) ( pxTransferControlState->pvTransferState );
	pxRxQueueState->xBlockTime = xMaxWaitTime;
}
/*-----------------------------------------------------------*/

portBASE_TYPE xIOUtilsConfigureTransferQueue( Peripheral_Control_t * const pxPeripheralControl, const uint32_t ulRequest, const unsigned portBASE_TYPE ulQueueLength )
{
portBASE_TYPE xReturn = pdFAIL;
Character_Queue_State_t *pxQueueState;
Transfer_Control_t **ppxTransferControl;

	if( ulRequest == ioctlUSE_CHARACTER_QUEUE_TX )
	{
		ppxTransferControl = &( pxPeripheralControl->pxTxControl );
	}
	else
	{
		ppxTransferControl = &( pxPeripheralControl->pxRxControl );
	}

	/* A peripheral is going to use a a FreeRTOS queue to control
	transmission or reception. */
	vIOUtilsCreateTransferControlStructure( ppxTransferControl );
	configASSERT( *ppxTransferControl );

	if( *ppxTransferControl != NULL )
	{
		/* Create the necessary structure. */
		pxQueueState = pvPortMalloc( sizeof( Character_Queue_State_t ) );

		if( pxQueueState != NULL )
		{
			pxQueueState->xQueue = NULL;

			/* The structure just created contains a Queue handle.  Create
			the queue too. */
			pxQueueState->xQueue = xQueueCreate( ulQueueLength, sizeof( uint8_t ) );

			if( pxQueueState->xQueue != NULL )
			{
				/* The queue was created correctly.  Fill in the private data
				structure. */
				pxQueueState->xBlockTime = portMAX_DELAY;
				pxQueueState->usErrorState = pdFALSE;
				( *ppxTransferControl )->pvTransferState = ( void * ) pxQueueState;
				( *ppxTransferControl )->ucType = ( uint8_t ) ulRequest;
				xReturn = pdPASS;
			}
			else
			{
				/* The queue was not created successfully, free the
				Character_Queue_State_t structure and just return an error. */
				vPortFree( pxQueueState );
				pxQueueState = NULL;
			}
		}

		if( pxQueueState == NULL )
		{
			/* The transfer structure, or a member it contains,  could not
			be created,	so the Tx control structure (which should point to it)
			should also	be deleted. */
			/* _RB_ Test this path. */
			vPortFree( *ppxTransferControl );
			*ppxTransferControl = NULL;
		}
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

size_t xIOUtilsReceiveCharsFromRxQueue( Peripheral_Control_t * const pxPeripheralControl, uint8_t * const pucBuffer, const size_t xTotalBytes )
{
size_t xBytesReceived = 0U;
portTickType xTicksToWait;
xTimeOutType xTimeOut;
Character_Queue_State_t *pxTransferState = prvRX_CHAR_QUEUE_STATE( pxPeripheralControl );

	xTicksToWait = pxTransferState->xBlockTime;
	vTaskSetTimeOutState( &xTimeOut );

	/* Are there any more bytes to be received? */
	while( xBytesReceived < xTotalBytes )
	{
		/* Receive the next character. */
		if( xQueueReceive( pxTransferState->xQueue, &( pucBuffer[ xBytesReceived ] ), xTicksToWait ) == pdPASS )
		{
			xBytesReceived++;
		}

		if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE )
		{
			/* Time out has expired. */
			break;
		}
	}

	return xBytesReceived;
}
/*-----------------------------------------------------------*/

size_t xIOUtilsSendCharsToTxQueue( Peripheral_Control_t * const pxPeripheralControl, uint8_t * const pucBuffer, const size_t xTotalBytes )
{
const uint8_t ucFF = 0xffU;
Character_Queue_State_t *pxTxState = prvTX_CHAR_QUEUE_STATE( pxPeripheralControl );
portBASE_TYPE xSentToQueue;
size_t xBytesSent;

	for( ( xBytesSent ) = 0U; ( xBytesSent ) < xTotalBytes; ( xBytesSent )++ )
	{
		/* Attempt to send to the queue.  Having a null buffer just means send
		0xff.  This is necessary for SPI/SSP. */
		if( pucBuffer == NULL )
		{
			xSentToQueue = xQueueSend( pxTxState->xQueue, &ucFF, 0U );
		}
		else
		{
			xSentToQueue = xQueueSend( pxTxState->xQueue, &( pucBuffer[ ( xBytesSent ) ] ), 0U );
		}

		if( xSentToQueue != pdPASS )
		{
			break;
		}
	}

	return xBytesSent;
}
/*-----------------------------------------------------------*/

portBASE_TYPE xIOUtilsWaitTxQueueEmpty( Peripheral_Control_t * const pxPeripheralControl, const portTickType xMaxWaitTime )
{
portBASE_TYPE xReturn = pdTRUE;
Character_Queue_State_t *pxTransferControlState = prvTX_CHAR_QUEUE_STATE( pxPeripheralControl );
portTickType xTimeOnEntering;
const portTickType xPollDelay = ( portTickType ) 2;

	configASSERT( pxTransferControlState );

	xTimeOnEntering = xTaskGetTickCount();
	while( uxQueueMessagesWaiting( pxTransferControlState->xQueue ) != 0U )
	{
		/* This is not a satisfactory solution - although the task will not use
		any CPU time while in the Blocked state (between polls). */
		vTaskDelay( xPollDelay );
		if( ( xTaskGetTickCount() - xTimeOnEntering ) >= xMaxWaitTime )
		{
			xReturn = pdFALSE;
			break;
		}
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

void xIOUtilsClearRxCharQueue( Peripheral_Control_t * const pxPeripheralControl )
{
Character_Queue_State_t *pxCharQueueState = prvTX_CHAR_QUEUE_STATE( pxPeripheralControl );

	configASSERT( pxCharQueueState );
	xQueueReset( pxCharQueueState->xQueue );
}













