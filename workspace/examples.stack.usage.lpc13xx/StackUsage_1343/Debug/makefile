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
all: pre-build main-build

# Main-build Target
main-build: StackUsage_1343.axf

# Tool invocations
StackUsage_1343.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Documents and Settings\nxp21346\Desktop\LPCXpresso_Fix_Examples\LPCE\CMSISv1p30_LPC13xx\Debug" -L"C:\Documents and Settings\nxp21346\Desktop\LPCXpresso_Fix_Examples\LPCE\lib_small_printf_m3\Lib" -Xlinker -Map=StackUsage_1343.map -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "stackusage_1343_Debug.ld" -o"StackUsage_1343.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) StackUsage_1343.axf
	-@echo ' '

pre-build:
	-cat "C:\Documents and Settings\nxp21346\Desktop\LPCXpresso_Fix_Examples\LPCE\StackUsage_1343\Docs"/abstract.txt;
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-cat ../Docs/abstract.txt; arm-none-eabi-size StackUsage_1343.axf; arm-none-eabi-objcopy -O binary StackUsage_1343.axf StackUsage_1343.bin ; checksum -d StackUsage_1343.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
