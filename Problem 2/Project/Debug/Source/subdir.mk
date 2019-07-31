################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Font5x7.c \
../Source/Main.c \
../Source/NoSystem.c \
../Source/OLED.c \
../Source/Startup.c \
../Source/WavPlayer.c \
../Source/dfrobot.c \
../Source/joystick.c \
../Source/pca9532.c 

OBJS += \
./Source/Font5x7.o \
./Source/Main.o \
./Source/NoSystem.o \
./Source/OLED.o \
./Source/Startup.o \
./Source/WavPlayer.o \
./Source/dfrobot.o \
./Source/joystick.o \
./Source/pca9532.o 

C_DEPS += \
./Source/Font5x7.d \
./Source/Main.d \
./Source/NoSystem.d \
./Source/OLED.d \
./Source/Startup.d \
./Source/WavPlayer.d \
./Source/dfrobot.d \
./Source/joystick.d \
./Source/pca9532.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -U__CODE_RED -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibCMSIS\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\Project\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibLPC17xx\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibFreeRTOS\Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


