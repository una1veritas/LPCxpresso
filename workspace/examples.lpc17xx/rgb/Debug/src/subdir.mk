################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/debug.c \
../src/main.c \
../src/rgb.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/debug.o \
./src/main.o \
./src/rgb.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/debug.d \
./src/main.d \
./src/rgb.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -DDEBUG -DLIB_FLOAT_PRINTF -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC17xx/inc" -I"/home/nxp/Desktop/linuxtest1/lib_small_printf_m3/inc" -I"/home/nxp/Desktop/linuxtest1/rgb/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


