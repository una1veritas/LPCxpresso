################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/blockdev_flash.c \
../src/cr_startup_lpc176x.c \
../src/diskimage.c \
../src/main_bootloader.c \
../src/msc_bot.c \
../src/msc_scsi.c \
../src/msc_usb_start.c \
../src/sbl_iap.c 

OBJS += \
./src/blockdev_flash.o \
./src/cr_startup_lpc176x.o \
./src/diskimage.o \
./src/main_bootloader.o \
./src/msc_bot.o \
./src/msc_scsi.o \
./src/msc_usb_start.o \
./src/sbl_iap.o 

C_DEPS += \
./src/blockdev_flash.d \
./src/cr_startup_lpc176x.d \
./src/diskimage.d \
./src/main_bootloader.d \
./src/msc_bot.d \
./src/msc_scsi.d \
./src/msc_usb_start.d \
./src/sbl_iap.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv2p00_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/RDB1768cmsis2_usbstack/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/RDB1768cmsis2_LCDlib/inc" -I../inc -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc176x.o: ../src/cr_startup_lpc176x.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv2p00_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p00_LPC17xx/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/RDB1768cmsis2_usbstack/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/RDB1768cmsis2_LCDlib/inc" -I../inc -O0 -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc176x.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


