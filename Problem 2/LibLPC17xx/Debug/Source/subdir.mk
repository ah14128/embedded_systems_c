################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/LPC17xx_ADC.c \
../Source/LPC17xx_CAN.c \
../Source/LPC17xx_ClockPower.c \
../Source/LPC17xx_Config.c \
../Source/LPC17xx_DAC.c \
../Source/LPC17xx_EMAC.c \
../Source/LPC17xx_EXTI.c \
../Source/LPC17xx_GPDMA.c \
../Source/LPC17xx_GPIO.c \
../Source/LPC17xx_I2C.c \
../Source/LPC17xx_I2S.c \
../Source/LPC17xx_IAP.c \
../Source/LPC17xx_LED2.c \
../Source/LPC17xx_MCPWM.c \
../Source/LPC17xx_NVIC.c \
../Source/LPC17xx_PWM.c \
../Source/LPC17xx_PinSelect.c \
../Source/LPC17xx_QEI.c \
../Source/LPC17xx_RIT.c \
../Source/LPC17xx_RTC.c \
../Source/LPC17xx_SPI.c \
../Source/LPC17xx_SSP.c \
../Source/LPC17xx_SysTick.c \
../Source/LPC17xx_Timer.c \
../Source/LPC17xx_UART.c \
../Source/LPC17xx_WDT.c 

OBJS += \
./Source/LPC17xx_ADC.o \
./Source/LPC17xx_CAN.o \
./Source/LPC17xx_ClockPower.o \
./Source/LPC17xx_Config.o \
./Source/LPC17xx_DAC.o \
./Source/LPC17xx_EMAC.o \
./Source/LPC17xx_EXTI.o \
./Source/LPC17xx_GPDMA.o \
./Source/LPC17xx_GPIO.o \
./Source/LPC17xx_I2C.o \
./Source/LPC17xx_I2S.o \
./Source/LPC17xx_IAP.o \
./Source/LPC17xx_LED2.o \
./Source/LPC17xx_MCPWM.o \
./Source/LPC17xx_NVIC.o \
./Source/LPC17xx_PWM.o \
./Source/LPC17xx_PinSelect.o \
./Source/LPC17xx_QEI.o \
./Source/LPC17xx_RIT.o \
./Source/LPC17xx_RTC.o \
./Source/LPC17xx_SPI.o \
./Source/LPC17xx_SSP.o \
./Source/LPC17xx_SysTick.o \
./Source/LPC17xx_Timer.o \
./Source/LPC17xx_UART.o \
./Source/LPC17xx_WDT.o 

C_DEPS += \
./Source/LPC17xx_ADC.d \
./Source/LPC17xx_CAN.d \
./Source/LPC17xx_ClockPower.d \
./Source/LPC17xx_Config.d \
./Source/LPC17xx_DAC.d \
./Source/LPC17xx_EMAC.d \
./Source/LPC17xx_EXTI.d \
./Source/LPC17xx_GPDMA.d \
./Source/LPC17xx_GPIO.d \
./Source/LPC17xx_I2C.d \
./Source/LPC17xx_I2S.d \
./Source/LPC17xx_IAP.d \
./Source/LPC17xx_LED2.d \
./Source/LPC17xx_MCPWM.d \
./Source/LPC17xx_NVIC.d \
./Source/LPC17xx_PWM.d \
./Source/LPC17xx_PinSelect.d \
./Source/LPC17xx_QEI.d \
./Source/LPC17xx_RIT.d \
./Source/LPC17xx_RTC.d \
./Source/LPC17xx_SPI.d \
./Source/LPC17xx_SSP.d \
./Source/LPC17xx_SysTick.d \
./Source/LPC17xx_Timer.d \
./Source/LPC17xx_UART.d \
./Source/LPC17xx_WDT.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__NEWLIB__ -U__REDLIB__ -U__CODE_RED -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibLPC17xx\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibCMSIS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


