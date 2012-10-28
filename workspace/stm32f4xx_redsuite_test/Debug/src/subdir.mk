################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cr_cpp_config.cpp \
../src/cr_startup_stm32f4xx.cpp \
../src/main.cpp 

OBJS += \
./src/cr_cpp_config.o \
./src/cr_startup_stm32f4xx.o \
./src/main.o 

CPP_DEPS += \
./src/cr_cpp_config.d \
./src/cr_startup_stm32f4xx.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DSTM32F4XX -DCPP_USE_HEAP -I"/Users/sin/Documents/LPCxpresso/workspace/stm32f4xx_redsuite_test/armduino" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/STM32F4xx" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/STM32F4xx_StdPeriph_Driver/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/Include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_stm32f4xx.o: ../src/cr_startup_stm32f4xx.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DSTM32F4XX -DCPP_USE_HEAP -I"/Users/sin/Documents/LPCxpresso/workspace/stm32f4xx_redsuite_test/armduino" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/STM32F4xx" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/STM32F4xx_StdPeriph_Driver/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/STM32Library/CMSIS/Include" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fsingle-precision-constant -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_stm32f4xx.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


