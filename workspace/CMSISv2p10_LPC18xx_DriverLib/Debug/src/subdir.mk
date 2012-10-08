################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/debug_frmwrk.c \
../src/lpc18xx_adc.c \
../src/lpc18xx_atimer.c \
../src/lpc18xx_can.c \
../src/lpc18xx_cgu.c \
../src/lpc18xx_dac.c \
../src/lpc18xx_emc.c \
../src/lpc18xx_evrt.c \
../src/lpc18xx_gpdma.c \
../src/lpc18xx_gpio.c \
../src/lpc18xx_i2c.c \
../src/lpc18xx_i2s.c \
../src/lpc18xx_lcd.c \
../src/lpc18xx_mcpwm.c \
../src/lpc18xx_nvic.c \
../src/lpc18xx_pwr.c \
../src/lpc18xx_qei.c \
../src/lpc18xx_rgu.c \
../src/lpc18xx_rit.c \
../src/lpc18xx_rtc.c \
../src/lpc18xx_sct.c \
../src/lpc18xx_scu.c \
../src/lpc18xx_sdif.c \
../src/lpc18xx_sdmmc.c \
../src/lpc18xx_ssp.c \
../src/lpc18xx_timer.c \
../src/lpc18xx_uart.c \
../src/lpc18xx_utils.c \
../src/lpc18xx_wwdt.c \
../src/system_LPC18xx.c 

OBJS += \
./src/debug_frmwrk.o \
./src/lpc18xx_adc.o \
./src/lpc18xx_atimer.o \
./src/lpc18xx_can.o \
./src/lpc18xx_cgu.o \
./src/lpc18xx_dac.o \
./src/lpc18xx_emc.o \
./src/lpc18xx_evrt.o \
./src/lpc18xx_gpdma.o \
./src/lpc18xx_gpio.o \
./src/lpc18xx_i2c.o \
./src/lpc18xx_i2s.o \
./src/lpc18xx_lcd.o \
./src/lpc18xx_mcpwm.o \
./src/lpc18xx_nvic.o \
./src/lpc18xx_pwr.o \
./src/lpc18xx_qei.o \
./src/lpc18xx_rgu.o \
./src/lpc18xx_rit.o \
./src/lpc18xx_rtc.o \
./src/lpc18xx_sct.o \
./src/lpc18xx_scu.o \
./src/lpc18xx_sdif.o \
./src/lpc18xx_sdmmc.o \
./src/lpc18xx_ssp.o \
./src/lpc18xx_timer.o \
./src/lpc18xx_uart.o \
./src/lpc18xx_utils.o \
./src/lpc18xx_wwdt.o \
./src/system_LPC18xx.o 

C_DEPS += \
./src/debug_frmwrk.d \
./src/lpc18xx_adc.d \
./src/lpc18xx_atimer.d \
./src/lpc18xx_can.d \
./src/lpc18xx_cgu.d \
./src/lpc18xx_dac.d \
./src/lpc18xx_emc.d \
./src/lpc18xx_evrt.d \
./src/lpc18xx_gpdma.d \
./src/lpc18xx_gpio.d \
./src/lpc18xx_i2c.d \
./src/lpc18xx_i2s.d \
./src/lpc18xx_lcd.d \
./src/lpc18xx_mcpwm.d \
./src/lpc18xx_nvic.d \
./src/lpc18xx_pwr.d \
./src/lpc18xx_qei.d \
./src/lpc18xx_rgu.d \
./src/lpc18xx_rit.d \
./src/lpc18xx_rtc.d \
./src/lpc18xx_sct.d \
./src/lpc18xx_scu.d \
./src/lpc18xx_sdif.d \
./src/lpc18xx_sdmmc.d \
./src/lpc18xx_ssp.d \
./src/lpc18xx_timer.d \
./src/lpc18xx_uart.d \
./src/lpc18xx_utils.d \
./src/lpc18xx_wwdt.d \
./src/system_LPC18xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -I"/Users/sin/Documents/LPCxpresso/workspace/CMSISv2p10_LPC18xx_DriverLib/inc" -I"/Users/sin/Documents/LPCxpresso/workspace/LPC1830_Xplorer_UsbVcomLib/inc" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


