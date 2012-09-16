################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cutecom-0.22.0/CMakeFiles/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./cutecom-0.22.0/CMakeFiles/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./cutecom-0.22.0/CMakeFiles/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
cutecom-0.22.0/CMakeFiles/CompilerIdC/%.o: ../cutecom-0.22.0/CMakeFiles/CompilerIdC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DNDEBUG -D__CODE_RED -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/FatFs" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/XBee" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/core" -Os -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


