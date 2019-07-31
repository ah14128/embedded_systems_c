################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Core_CM3.c \
../Source/System_LPC17xx.c 

OBJS += \
./Source/Core_CM3.o \
./Source/System_LPC17xx.o 

C_DEPS += \
./Source/Core_CM3.d \
./Source/System_LPC17xx.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__NEWLIB__ -U__CODE_RED -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibCMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


