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
all: usbhid_rom_tiny.axf

dependents:
	-cd /home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/Debug && $(MAKE) clean all

# Tool invocations
usbhid_rom_tiny.axf: $(OBJS) $(USER_OBJS) /home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/Debug/libCMSISv1p30_LPC13xx.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/Debug" -Xlinker --gc-sections -Xlinker -Map=usbhid_rom_tiny.map -mcpu=cortex-m3 -mthumb -T "../ld/usb_buffer.ld" -o"usbhid_rom_tiny.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) usbhid_rom_tiny.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size usbhid_rom_tiny.axf; # arm-none-eabi-objcopy -O ihex usbhid_rom_tiny.axf usbhid_rom_tiny.hex ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/Debug/libCMSISv1p30_LPC13xx.a:

-include ../makefile.targets
