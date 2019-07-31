################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Project.axf

# Tool invocations
Project.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibFreeRTOS\Debug" -L"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibLPC17xx\Debug" -L"O:\Documents\.3rd Year\EMbedded\BUGGY\Problem 2\Problem 2\LibCMSIS\Debug" -Xlinker -Map="Project.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "FreeRTOSProject_Debug.ld" -o "Project.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Project.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Project.axf"; # arm-none-eabi-objcopy -O binary "Project.axf" "Project.bin" ; checksum -p LPC1769 -d "Project.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
