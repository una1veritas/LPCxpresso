################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include src/Usb_MassStorage/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPC1830_Xplorer_UsbDevice.axf

# Tool invocations
LPC1830_Xplorer_UsbDevice.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"F:\lpc1830_Xplorer_LPCXpresso_v4_23\CMSISv2p10_LPC18xx_DriverLib\Debug" -Xlinker -Map="LPC1830_Xplorer_UsbDevice.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "LPC1830_Xplorer_UsbDevice_Debug.ld" -o"LPC1830_Xplorer_UsbDevice.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) LPC1830_Xplorer_UsbDevice.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "LPC1830_Xplorer_UsbDevice.axf"; # arm-none-eabi-objcopy -O binary "LPC1830_Xplorer_UsbDevice.axf" "LPC1830_Xplorer_UsbDevice.bin" ; checksum -p LPC1830 -d "LPC1830_Xplorer_UsbDevice.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
