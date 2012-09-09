################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DiskImg.c \
../src/cr_startup_lpc13.c \
../src/msccallback.c \
../src/usbdesc.c \
../src/usbmemrom_main.c 

OBJS += \
./src/DiskImg.o \
./src/cr_startup_lpc13.o \
./src/msccallback.o \
./src/usbdesc.o \
./src/usbmemrom_main.o 

C_DEPS += \
./src/DiskImg.d \
./src/cr_startup_lpc13.d \
./src/msccallback.d \
./src/usbdesc.d \
./src/usbmemrom_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/usbmsd_rom/inc" -I"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


