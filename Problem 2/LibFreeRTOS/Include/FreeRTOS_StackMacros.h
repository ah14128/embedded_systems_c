/**************************************************************************//**
 *
 * @file        StackMacros.h
 * @brief       Part of FreeRTOS
 * @author      Real Time Engineers Ltd.
 * @version     7.1.0
 * @date        25 July. 2012
 *
 * Copyright (C) 2011 Real Time Engineers Ltd.
 * All rights reserved.
 *
******************************************************************************/

#ifndef STACK_MACROS_H
#define STACK_MACROS_H

/*
 * Call the stack overflow hook function if the stack of the task being swapped
 * out is currently overflowed, or looks like it might have overflowed in the
 * past.
 *
 * Setting configCHECK_FOR_STACK_OVERFLOW to 1 will cause the macro to check
 * the current stack state only - comparing the current top of stack value to
 * the stack limit.  Setting configCHECK_FOR_STACK_OVERFLOW to greater than 1
 * will also cause the last few stack bytes to be checked to ensure the value
 * to which the bytes were set when the task was created have not been
 * overwritten.  Note this second test does not guarantee that an overflowed
 * stack will always be recognised.
 */

/*-----------------------------------------------------------*/

#if( configCHECK_FOR_STACK_OVERFLOW == 0 )

	/* FreeRTOSConfig.h is not set to check for stack overflows. */
	#define taskFIRST_CHECK_FOR_STACK_OVERFLOW()
	#define taskSECOND_CHECK_FOR_STACK_OVERFLOW()

#endif /* configCHECK_FOR_STACK_OVERFLOW == 0 */
/*-----------------------------------------------------------*/

#if( configCHECK_FOR_STACK_OVERFLOW == 1 )

	/* FreeRTOSConfig.h is only set to use the first method of
	overflow checking. */
	#define taskSECOND_CHECK_FOR_STACK_OVERFLOW()

#endif
/*-----------------------------------------------------------*/

#if( ( configCHECK_FOR_STACK_OVERFLOW > 0 ) && ( portSTACK_GROWTH < 0 ) )

	/* Only the current stack state is to be checked. */
	#define taskFIRST_CHECK_FOR_STACK_OVERFLOW()														\
	{																									\
		/* Is the currently saved stack pointer within the stack limit? */								\
		if( pxCurrentTCB->pxTopOfStack <= pxCurrentTCB->pxStack )										\
		{																								\
			vApplicationStackOverflowHook( ( xTaskHandle ) pxCurrentTCB, pxCurrentTCB->pcTaskName );	\
		}																								\
	}

#endif /* configCHECK_FOR_STACK_OVERFLOW > 0 */
/*-----------------------------------------------------------*/

#if( ( configCHECK_FOR_STACK_OVERFLOW > 0 ) && ( portSTACK_GROWTH > 0 ) )

	/* Only the current stack state is to be checked. */
	#define taskFIRST_CHECK_FOR_STACK_OVERFLOW()														\
	{																									\
																										\
		/* Is the currently saved stack pointer within the stack limit? */								\
		if( pxCurrentTCB->pxTopOfStack >= pxCurrentTCB->pxEndOfStack )									\
		{																								\
			vApplicationStackOverflowHook( ( xTaskHandle ) pxCurrentTCB, pxCurrentTCB->pcTaskName );	\
		}																								\
	}

#endif /* configCHECK_FOR_STACK_OVERFLOW == 1 */
/*-----------------------------------------------------------*/

#if( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) && ( portSTACK_GROWTH < 0 ) )

	#define taskSECOND_CHECK_FOR_STACK_OVERFLOW()																								\
	{																																			\
	static const unsigned char ucExpectedStackBytes[] = {	tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE };	\
																																				\
																																				\
		/* Has the extremity of the task stack ever been written over? */																		\
		if( memcmp( ( void * ) pxCurrentTCB->pxStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) != 0 )					\
		{																																		\
			vApplicationStackOverflowHook( ( xTaskHandle ) pxCurrentTCB, pxCurrentTCB->pcTaskName );											\
		}																																		\
	}

#endif /* #if( configCHECK_FOR_STACK_OVERFLOW > 1 ) */
/*-----------------------------------------------------------*/

#if( ( configCHECK_FOR_STACK_OVERFLOW > 1 ) && ( portSTACK_GROWTH > 0 ) )

	#define taskSECOND_CHECK_FOR_STACK_OVERFLOW()																								\
	{																																			\
	char *pcEndOfStack = ( char * ) pxCurrentTCB->pxEndOfStack;																					\
	static const unsigned char ucExpectedStackBytes[] = {	tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE,		\
															tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE, tskSTACK_FILL_BYTE };	\
																																				\
																																				\
		pcEndOfStack -= sizeof( ucExpectedStackBytes );																							\
																																				\
		/* Has the extremity of the task stack ever been written over? */																		\
		if( memcmp( ( void * ) pcEndOfStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) != 0 )							\
		{																																		\
			vApplicationStackOverflowHook( ( xTaskHandle ) pxCurrentTCB, pxCurrentTCB->pcTaskName );											\
		}																																		\
	}

#endif /* #if( configCHECK_FOR_STACK_OVERFLOW > 1 ) */
/*-----------------------------------------------------------*/

#endif /* STACK_MACROS_H */

