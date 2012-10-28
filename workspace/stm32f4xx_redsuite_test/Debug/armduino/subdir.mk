################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../armduino/usart.cpp 

C_SRCS += \
../armduino/gpio.c 

OBJS += \
./armduino/gpio.o \
./armduino/usart.o 

C_DEPS += \
./armduino/gpio.d 

CPP_DEPS += \
./armduino/usart.d 


# Each subdirectory must supply rules for building sources it contributes
armduino/%.o: ../armduino/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DSTM32F4XX -DCPP_USE_HEAP -I"/Users/sin/Documents/LPCxpresso/workspace/stm32f4xx_redsuite_test/armduino" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/STM32F4xx" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/STM32F4xx_StdPeriph_Driver/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fsingle-precision-constant -std=c99 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

armduino/%.o: ../armduino/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DSTM32F4XX -DCPP_USE_HEAP -I"/Users/sin/Documents/LPCxpresso/workspace/stm32f4xx_redsuite_test/armduino" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/STM32F4xx" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/STM32F4xx_StdPeriph_Driver/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


