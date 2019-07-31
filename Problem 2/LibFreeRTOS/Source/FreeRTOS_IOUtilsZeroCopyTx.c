/**************************************************************************//**
 *
 * @file        IOUtilsZeroCopyTx.c
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
#include "FreeRTOS_Queue.h"

/* Device specific library includes. */
#include "FreeRTOS_DriverInterface.h"
#include "FreeRTOS_IOUtilsCommon.h"

/*-----------------------------------------------------------*/

portBASE_TYPE xIOUtilsConfigureZeroCopyTx( Peripheral_Control_t * const pxPeripheralControl )
{
portBASE_TYPE xReturn = pdFAIL;
Zero_Copy_Tx_State_t *pxZeroCopyState;

	/* A peripheral is going to use a Zero_Copy_Tx_State_t structure to control
	transmission. */
	vIOUtilsCreateTransferControlStructure( &( pxPeripheralControl->pxTxControl ) );
	configASSERT( pxPeripheralControl->pxTxControl );

	if( pxPeripheralControl->pxTxControl != NULL )
	{
		/* Create the necessary structure. */
		pxZeroCopyState = pvPortMalloc( sizeof( Zero_Copy_Tx_State_t ) );

		if( pxZeroCopyState != NULL )
		{
			pxZeroCopyState->xWriteAccessMutex = NULL;

			/* The structure just created contains a Semaphore handle.  Create
			the mutex type semaphore too. */
			pxZeroCopyState->xWriteAccessMutex = xSemaphoreCreateMutex();
			pxZeroCopyState->usBufferLength = 0U;

			if( pxZeroCopyState->xWriteAccessMutex != NULL )
			{
				/* The semaphore was created correctly.  Fill in the private
				data structure. */
				pxPeripheralControl->pxTxControl->pvTransferState = ( void * ) pxZeroCopyState;
				pxPeripheralControl->pxTxControl->ucType = ioctlUSE_ZERO_COPY_TX;
				xReturn = pdPASS;
			}
			else
			{
				/* The semaphore was not created successfully, free the
				Zero_Copy_Tx_State_t structure and just return an error. */
				vPortFree( pxZeroCopyState );
				pxZeroCopyState = NULL;
			}
		}

		if( pxZeroCopyState == NULL )
		{
			/* The Tx structure, or a member it contains,  could not be created,
			so the Tx control structure (which should point to it) should also
			be deleted. */
			vPortFree( pxPeripheralControl->pxTxControl );
			pxPeripheralControl->pxTxControl = NULL;
		}
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

portBASE_TYPE xIOUtilsGetZeroCopyWriteMutex( Peripheral_Control_t * const pxPeripheralControl, uint32_t ulRequest, const portTickType xMaxWaitTime )
{
portBASE_TYPE xReturn;
Transfer_Control_t *pxTransferControlState = pxPeripheralControl->pxTxControl;
Zero_Copy_Tx_State_t *pxZeroCopyState;

	configASSERT( pxTransferControlState );

	pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferControlState->pvTransferState );
	xReturn = xSemaphoreTake( pxZeroCopyState->xWriteAccessMutex, xMaxWaitTime );

	if( ( xReturn == pdPASS ) && ( ulRequest == ioctlWAIT_PREVIOUS_WRITE_COMPLETE ) )
	{
		/* The function was only called to wait until the current transmission
		was complete, so the task should not retain the mutex. */
		xSemaphoreGive( pxZeroCopyState->xWriteAccessMutex );
	}

	return xReturn;
}
/*-----------------------------------------------------------*/

portBASE_TYPE xIOUtilsReleaseZeroCopyWriteMutex( Peripheral_Control_t *pxPeripheralControl )
{
portBASE_TYPE xReturn;
Transfer_Control_t *pxTransferControlState = pxPeripheralControl->pxTxControl;
Zero_Copy_Tx_State_t *pxZeroCopyState;

	configASSERT( pxTransferControlState );

	pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferControlState->pvTransferState );
	xReturn = xSemaphoreGive( pxZeroCopyState->xWriteAccessMutex );
	return xReturn;
}
/*-----------------------------------------------------------*/













