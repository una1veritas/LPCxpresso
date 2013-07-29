################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: Blinky.axf

dependents:
	-cd /Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC11Uxx/Debug && $(MAKE) clean all
	-cd /Users/sin/Documents/LPCxpresso/workspace/LPC11Uxx_Driver_Lib/Debug && $(MAKE) clean all

# Tool invocations
Blinky.axf: $(OBJS) $(USER_OBJS) /Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a /Users/sin/Documents/LPCxpresso/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/sin/Documents/LPCxpresso/workspace/LPC11Uxx_Driver_Lib/Debug" -L"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC11Uxx/Debug" -L"/Users/sin/Documents/LPCxpresso/workspace/LPC11Uxx_Driver_Lib" -Xlinker -Map="Blinky.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "Blinky_Debug.ld" -o "Blinky.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Blinky.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Blinky.axf"; # arm-none-eabi-objcopy -O binary "Blinky.axf" "Blinky.bin" ; checksum -p LPC11U24_401 -d "Blinky.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC11Uxx/Debug/libCMSISv2p00_LPC11Uxx.a:
/Users/sin/Documents/LPCxpresso/workspace/LPC11Uxx_Driver_Lib/Debug/libLPC11Uxx_Driver_Lib.a:

-include ../makefile.targets
