################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DES-oute/d3DES.c 

OBJS += \
./DES-oute/d3DES.o 

C_DEPS += \
./DES-oute/d3DES.d 


# Each subdirectory must supply rules for building sources it contributes
DES-oute/%.o: ../DES-oute/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv2p00_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/uart_v2p00/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/uart_v2p00/DES-oute" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=c99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


