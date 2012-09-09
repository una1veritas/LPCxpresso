################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc13_tiny.c \
../src/usbhidrom_tiny_main.c 

OBJS += \
./src/cr_startup_lpc13_tiny.o \
./src/usbhidrom_tiny_main.o 

C_DEPS += \
./src/cr_startup_lpc13_tiny.d \
./src/usbhidrom_tiny_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DTINY -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/inc" -I"/home/nxp/Desktop/linuxtest1/usbhid_rom_tiny/inc" -O0 -Os -mword-relocations -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


