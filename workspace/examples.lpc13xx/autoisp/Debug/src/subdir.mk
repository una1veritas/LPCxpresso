################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/autoisp_main.c \
../src/clkconfig.c \
../src/cr_startup_lpc13.c \
../src/gpio.c 

OBJS += \
./src/autoisp_main.o \
./src/clkconfig.o \
./src/cr_startup_lpc13.o \
./src/gpio.o 

C_DEPS += \
./src/autoisp_main.d \
./src/clkconfig.d \
./src/cr_startup_lpc13.d \
./src/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


