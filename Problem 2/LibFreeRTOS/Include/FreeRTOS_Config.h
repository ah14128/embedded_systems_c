/**************************************************************************//**
 *
 * @file        Config.h
 * @brief       Configuration file of FreeRTOS
 * @author      Real Time Engineers Ltd.
 * @version     7.1.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2011 Real Time Engineers Ltd.
 * All rights reserved.
 *
******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
extern uint32_t SystemCoreClock;

/* Priorities to assign to tasks created by this demo. */
#define configUART_COMMAND_CONSOLE_TASK_PRIORITY	( 3U )
#define configSPI_7_SEG_WRITE_TASK_PRIORITY			( 2U )
#define configI2C_TASK_PRIORITY						( 0U )

/* Stack sizes to assign to tasks created by this demo. */
#define configUART_COMMAND_CONSOLE_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
#define configSPI_7_SEG_WRITE_TASK_STACK_SIZE		( configMINIMAL_STACK_SIZE * 2 )
#define configI2C_TASK_STACK_SIZE					( configMINIMAL_STACK_SIZE * 4 )

/* Dimensions a buffer that can be used by the FreeRTOS+CLI command
interpreter.  Set this value to 1 to save RAM if FreeRTOS+CLI does not supply
the output butter.  See the FreeRTOS+CLI documentation for more information:
http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/ */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE			1024

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 * http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION			1
#define configMAX_PRIORITIES			( ( unsigned portBASE_TYPE ) 9 )
#define configCPU_CLOCK_HZ				( SystemCoreClock )
#define configTICK_RATE_HZ				( ( portTickType ) 1000 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 90 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 15 * 1024 ) )
#define configMAX_TASK_NAME_LEN			( 12 )
#define configIDLE_SHOULD_YIELD			0
#define configQUEUE_REGISTRY_SIZE		10
#define configUSE_TRACE_FACILITY		1
#define configUSE_16_BIT_TICKS			0
#define configUSE_MUTEXES				1
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )
#define configUSE_COUNTING_SEMAPHORES 	0
#define configUSE_ALTERNATIVE_API 		0
#define configUSE_RECURSIVE_MUTEXES		1

/* Hook function related definitions. */
#define configUSE_TICK_HOOK				0
#define configUSE_IDLE_HOOK				0
#define configUSE_MALLOC_FAILED_HOOK	1
#define configCHECK_FOR_STACK_OVERFLOW	2


/* Software timer related definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 3 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	configMINIMAL_STACK_SIZE

/* Run time stats gathering definitions. */
//#define configGENERATE_RUN_TIME_STATS	0
//#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() (void*)
//#define portGET_RUN_TIME_COUNTER_VALUE() (void*)


/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete					1
#define INCLUDE_vTaskCleanUpResources		0
#define INCLUDE_vTaskSuspend				1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay					1
#define INCLUDE_uxTaskGetStackHighWaterMark	1
#define INCLUDE_xTimerGetTimerTaskHandle	0
#define INCLUDE_xTaskGetIdleTaskHandle		0

#ifdef DEBUG
	#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
#endif


/* Use the system definition, if there is one */
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS       __NVIC_PRIO_BITS
#else
	#define configPRIO_BITS       5        /* 32 priority levels */
#endif

/* The maximum priority an interrupt that uses an interrupt safe FreeRTOS API
function can have.  Note that lower priority have numerically higher values.  */
#define configMAX_LIBRARY_INTERRUPT_PRIORITY	( 5 )

/* The minimum possible interrupt priority. */
#define configMIN_LIBRARY_INTERRUPT_PRIORITY	( 31 )

/* The lowest priority. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configMIN_LIBRARY_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Priority 5, or 248 as only the top five bits are implemented. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configMAX_LIBRARY_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVCall_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler



#endif /* FREERTOS_CONFIG_H */
