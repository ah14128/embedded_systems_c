################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Buttons.c \
../Source/Font5x7.c \
../Source/Main.c \
../Source/NoSystem.c \
../Source/OLED.c \
../Source/RotarySwitch.c \
../Source/SevenSegment.c \
../Source/Startup.c \
../Source/Tune.c \
../Source/dfrobot.c \
../Source/joystick.c \
../Source/new_string.c \
../Source/pca9532.c 

OBJS += \
./Source/Buttons.o \
./Source/Font5x7.o \
./Source/Main.o \
./Source/NoSystem.o \
./Source/OLED.o \
./Source/RotarySwitch.o \
./Source/SevenSegment.o \
./Source/Startup.o \
./Source/Tune.o \
./Source/dfrobot.o \
./Source/joystick.o \
./Source/new_string.o \
./Source/pca9532.o 

C_DEPS += \
./Source/Buttons.d \
./Source/Font5x7.d \
./Source/Main.d \
./Source/NoSystem.d \
./Source/OLED.d \
./Source/RotarySwitch.d \
./Source/SevenSegment.d \
./Source/Startup.d \
./Source/Tune.d \
./Source/dfrobot.d \
./Source/joystick.d \
./Source/new_string.d \
./Source/pca9532.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__NEWLIB__ -U__REDLIB__ -U__CODE_RED -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 1\Task1\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 1\LibLPC17xx\Include" -I"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 1\LibCMSIS\Include" -I/DFRobot/Source -I/LibDFRobot/Source -I/LibCMSIS/Source -I/LibLPC17xx/Source -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


