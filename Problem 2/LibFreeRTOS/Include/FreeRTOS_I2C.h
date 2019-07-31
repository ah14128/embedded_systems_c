/**************************************************************************//**
 *
 * @file        I2C.h
 * @brief       Part of FreeRTOS+IO
 * @author      Real Time Engineers Ltd.
 * @version     1.0.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2012 Real Time Engineers ltd.
 * All rights reserved.
 *
******************************************************************************/

#ifndef FREERTOS_IO_I2C_H
#define FREERTOS_IO_I2C_H

/* These are not public functions.  Do not call these functions directly.  Call
FreeRTOS_Open(), FreeRTOS_write(), FreeRTOS_read() and FreeRTOS_ioctl() only. */
portBASE_TYPE FreeRTOS_I2C_open( Peripheral_Control_t * const pxPeripheralControl );
size_t FreeRTOS_I2C_write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes );
size_t FreeRTOS_I2C_read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes );
portBASE_TYPE FreeRTOS_I2C_ioctl( Peripheral_Descriptor_t const pxPeripheral, uint32_t ulRequest, void *pvValue );

#endif /* FREERTOS_IO_IC2_H */

