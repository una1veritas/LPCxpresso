################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/blinky_main.c \
../src/clkconfig.c \
../src/cr_startup_lpc13.c \
../src/gpio.c \
../src/timer32.c 

OBJS += \
./src/blinky_main.o \
./src/clkconfig.o \
./src/cr_startup_lpc13.o \
./src/gpio.o \
./src/timer32.o 

C_DEPS += \
./src/blinky_main.d \
./src/clkconfig.d \
./src/cr_startup_lpc13.d \
./src/gpio.d \
./src/timer32.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC13xx -D__CODE_RED -D__REDLIB__ -I"/Users/sin/Documents/LPCxpresso/workspace/examples.lpc13xx/CMSISv1p30_LPC13xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


