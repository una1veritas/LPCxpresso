################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cutecom-0.22.0/main.cpp \
../cutecom-0.22.0/qcppdialogimpl.cpp 

CXX_SRCS += \
../cutecom-0.22.0/moc_qcppdialogimpl.cxx 

OBJS += \
./cutecom-0.22.0/main.o \
./cutecom-0.22.0/moc_qcppdialogimpl.o \
./cutecom-0.22.0/qcppdialogimpl.o 

CPP_DEPS += \
./cutecom-0.22.0/main.d \
./cutecom-0.22.0/qcppdialogimpl.d 

CXX_DEPS += \
./cutecom-0.22.0/moc_qcppdialogimpl.d 


# Each subdirectory must supply rules for building sources it contributes
cutecom-0.22.0/%.o: ../cutecom-0.22.0/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/XBee" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/FatFs" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cutecom-0.22.0/%.o: ../cutecom-0.22.0/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/XBee" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/FatFs" -I"/Users/sin/Documents/LPCxpresso/workspace/eXodusino/src/core" -Os -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


