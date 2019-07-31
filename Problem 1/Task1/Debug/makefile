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
all: Task1.axf

# Tool invocations
Task1.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\thisi\Documents\1UNVERSITY WORK\ERTS\Problem_1\Problem 1\LibLPC17xx\Debug" -L"C:\Users\thisi\Documents\1UNVERSITY WORK\ERTS\Problem_1\Problem 1\LibCMSIS\Debug" -Xlinker -Map="Task1.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Project_Debug.ld" -o"Task1.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Task1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Task1.axf"; # arm-none-eabi-objcopy -O binary "Task1.axf" "Task1.bin" ; checksum -p LPC1769 -d "Task1.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
