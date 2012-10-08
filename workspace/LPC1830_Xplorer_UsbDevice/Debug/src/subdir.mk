################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc18xx.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc18xx.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc18xx.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/cr_startup_lpc18xx.o: ../src/cr_startup_lpc18xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p10_LPC18xx_DriverLib -DCORE_M3 -D__LPC18XX__ -I"F:\lpc1830_Xplorer_LPCXpresso_v4_23\CMSISv2p10_LPC18xx_DriverLib\inc" -I"F:\lpc1830_Xplorer_LPCXpresso_v4_23\LPC1830_Xplorer_UsbDevice\src\Usb_MassStorage\inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc18xx.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p10_LPC18xx_DriverLib -DCORE_M3 -D__LPC18XX__ -I"F:\lpc1830_Xplorer_LPCXpresso_v4_23\CMSISv2p10_LPC18xx_DriverLib\inc" -I"F:\lpc1830_Xplorer_LPCXpresso_v4_23\LPC1830_Xplorer_UsbDevice\src\Usb_MassStorage\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


