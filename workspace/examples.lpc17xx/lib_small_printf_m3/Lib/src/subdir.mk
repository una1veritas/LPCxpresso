################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/small_printf_float.c \
../src/small_printf_nofloat.c \
../src/small_printf_support.c \
../src/small_utils.c 

OBJS += \
./src/small_printf_float.o \
./src/small_printf_nofloat.o \
./src/small_printf_support.o \
./src/small_utils.o 

C_DEPS += \
./src/small_printf_float.d \
./src/small_printf_nofloat.d \
./src/small_printf_support.d \
./src/small_utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/lib_small_printf_m3/inc" -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


