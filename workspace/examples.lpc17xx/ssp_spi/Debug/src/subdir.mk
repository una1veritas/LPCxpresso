################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/lpc17xx_clkpwr.c \
../src/lpc17xx_libcfg_default.c \
../src/lpc17xx_ssp.c \
../src/main.c 

OBJS += \
./src/cr_startup_lpc17.o \
./src/lpc17xx_clkpwr.o \
./src/lpc17xx_libcfg_default.o \
./src/lpc17xx_ssp.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/lpc17xx_clkpwr.d \
./src/lpc17xx_libcfg_default.d \
./src/lpc17xx_ssp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC17xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/nxp/Desktop/linuxtest1/CMSISv1p30_LPC17xx/inc" -I"/home/nxp/Desktop/linuxtest1/ssp_spi/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


