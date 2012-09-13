################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/src/core_cm3.c \
/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/src/system_LPC17xx.c 

OBJS += \
./CMICSv2p00/core_cm3.o \
./CMICSv2p00/system_LPC17xx.o 

C_DEPS += \
./CMICSv2p00/core_cm3.d \
./CMICSv2p00/system_LPC17xx.d 


# Each subdirectory must supply rules for building sources it contributes
CMICSv2p00/core_cm3.o: /Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/src/core_cm3.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/Users/sin/Documents/LPCxpresso/workspace/uart_v2p00/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMICSv2p00/system_LPC17xx.o: /Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/src/system_LPC17xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/Users/sin/Documents/LPCxpresso/workspace/uart_v2p00/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


