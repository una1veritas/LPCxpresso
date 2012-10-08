################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Usb_MassStorage/src/DiskImg.c \
../src/Usb_MassStorage/src/mscuser.c \
../src/Usb_MassStorage/src/usbcore.c \
../src/Usb_MassStorage/src/usbdesc.c \
../src/Usb_MassStorage/src/usbhw.c \
../src/Usb_MassStorage/src/usbuser.c 

OBJS += \
./src/Usb_MassStorage/src/DiskImg.o \
./src/Usb_MassStorage/src/mscuser.o \
./src/Usb_MassStorage/src/usbcore.o \
./src/Usb_MassStorage/src/usbdesc.o \
./src/Usb_MassStorage/src/usbhw.o \
./src/Usb_MassStorage/src/usbuser.o 

C_DEPS += \
./src/Usb_MassStorage/src/DiskImg.d \
./src/Usb_MassStorage/src/mscuser.d \
./src/Usb_MassStorage/src/usbcore.d \
./src/Usb_MassStorage/src/usbdesc.d \
./src/Usb_MassStorage/src/usbhw.d \
./src/Usb_MassStorage/src/usbuser.d 


# Each subdirectory must supply rules for building sources it contributes
src/Usb_MassStorage/src/%.o: ../src/Usb_MassStorage/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p10_LPC18xx_DriverLib -DCORE_M3 -D__LPC18XX__ -I"F:\lpc1830_Xplorer_LPCXpresso_v4_23\CMSISv2p10_LPC18xx_DriverLib\inc" -I"F:\lpc1830_Xplorer_LPCXpresso_v4_23\LPC1830_Xplorer_UsbDevice\src\Usb_MassStorage\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


