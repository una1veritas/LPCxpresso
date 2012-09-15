################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RDB1768cmsis2_EasyWeb.axf

# Tool invocations
RDB1768cmsis2_EasyWeb.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map=RDB1768cmsis2_EasyWeb.map -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "RDB1768cmsis_EasyWeb_Debug.ld" -o"RDB1768cmsis2_EasyWeb.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) RDB1768cmsis2_EasyWeb.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size RDB1768cmsis2_EasyWeb.axf; arm-none-eabi-objcopy -O binary RDB1768cmsis2_EasyWeb.axf RDB1768cmsis2_EasyWeb.bin ; checksum -p LPC1768 -d RDB1768cmsis2_EasyWeb.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
