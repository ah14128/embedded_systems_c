/**************************************************************************//**
 *
 * @file        IOUtilsCommon.h
 * @brief       Part of FreeRTOS+IO
 * @author      Real Time Engineers Ltd.
 * @version     1.0.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2012 Real Time Engineers ltd.
 * All rights reserved.
 *
******************************************************************************/

#ifndef FREERTOS_IO_UTILS_H
#define FREERTOS_IO_UTILS_H

#include "FreeRTOS_IOUtilsCharQueueTxAndRx.h"
#include "FreeRTOS_IOUtilsCircularBufferRx.h"
#include "FreeRTOS_IOUtilsZeroCopyTx.h"

/* For internal use only. */
void vIOUtilsCreateTransferControlStructure( Transfer_Control_t **ppxTransferControl );

#endif


