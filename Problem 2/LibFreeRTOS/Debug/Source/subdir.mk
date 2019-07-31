################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/FreeRTOS_CLI.c \
../Source/FreeRTOS_CoRoutine.c \
../Source/FreeRTOS_DriverInterface.c \
../Source/FreeRTOS_Heap.c \
../Source/FreeRTOS_I2C.c \
../Source/FreeRTOS_IOUtils.c \
../Source/FreeRTOS_IOUtilsCharQueueTxAndRx.c \
../Source/FreeRTOS_IOUtilsCircularBufferRx.c \
../Source/FreeRTOS_IOUtilsZeroCopyTx.c \
../Source/FreeRTOS_List.c \
../Source/FreeRTOS_Port.c \
../Source/FreeRTOS_Queue.c \
../Source/FreeRTOS_SSP.c \
../Source/FreeRTOS_Tasks.c \
../Source/FreeRTOS_Timers.c \
../Source/FreeRTOS_UART.c \
../Source/LPC17xx_DriverInterface.c 

OBJS += \
./Source/FreeRTOS_CLI.o \
./Source/FreeRTOS_CoRoutine.o \
./Source/FreeRTOS_DriverInterface.o \
./Source/FreeRTOS_Heap.o \
./Source/FreeRTOS_I2C.o \
./Source/FreeRTOS_IOUtils.o \
./Source/FreeRTOS_IOUtilsCharQueueTxAndRx.o \
./Source/FreeRTOS_IOUtilsCircularBufferRx.o \
./Source/FreeRTOS_IOUtilsZeroCopyTx.o \
./Source/FreeRTOS_List.o \
./Source/FreeRTOS_Port.o \
./Source/FreeRTOS_Queue.o \
./Source/FreeRTOS_SSP.o \
./Source/FreeRTOS_Tasks.o \
./Source/FreeRTOS_Timers.o \
./Source/FreeRTOS_UART.o \
./Source/LPC17xx_DriverInterface.o 

C_DEPS += \
./Source/FreeRTOS_CLI.d \
./Source/FreeRTOS_CoRoutine.d \
./Source/FreeRTOS_DriverInterface.d \
./Source/FreeRTOS_Heap.d \
./Source/FreeRTOS_I2C.d \
./Source/FreeRTOS_IOUtils.d \
./Source/FreeRTOS_IOUtilsCharQueueTxAndRx.d \
./Source/FreeRTOS_IOUtilsCircularBufferRx.d \
./Source/FreeRTOS_IOUtilsZeroCopyTx.d \
./Source/FreeRTOS_List.d \
./Source/FreeRTOS_Port.d \
./Source/FreeRTOS_Queue.d \
./Source/FreeRTOS_SSP.d \
./Source/FreeRTOS_Tasks.d \
./Source/FreeRTOS_Timers.d \
./Source/FreeRTOS_UART.d \
./Source/LPC17xx_DriverInterface.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -U__CODE_RED -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibFreeRTOS\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibLPC17xx\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibCMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


