################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cdcuser.c \
../src/cr_startup_lpc13.c \
../src/serial.c \
../src/usbcore.c \
../src/usbdesc.c \
../src/usbhw.c \
../src/usbuser.c \
../src/vcomdemo.c 

OBJS += \
./src/cdcuser.o \
./src/cr_startup_lpc13.o \
./src/serial.o \
./src/usbcore.o \
./src/usbdesc.o \
./src/usbhw.o \
./src/usbuser.o \
./src/vcomdemo.o 

C_DEPS += \
./src/cdcuser.d \
./src/cr_startup_lpc13.d \
./src/serial.d \
./src/usbcore.d \
./src/usbdesc.d \
./src/usbhw.d \
./src/usbuser.d \
./src/vcomdemo.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC13xx/inc" -I"/home/nxp/Desktop/linuxtest1/usbcdc/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


