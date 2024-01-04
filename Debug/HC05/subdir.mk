################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HC05/HC05.c 

OBJS += \
./HC05/HC05.o 

C_DEPS += \
./HC05/HC05.d 


# Each subdirectory must supply rules for building sources it contributes
HC05/%.o HC05/%.su HC05/%.cyclo: ../HC05/%.c HC05/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/30919/STM32CubeIDE/workspace_1.13.0/HC05/HC05" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HC05

clean-HC05:
	-$(RM) ./HC05/HC05.cyclo ./HC05/HC05.d ./HC05/HC05.o ./HC05/HC05.su

.PHONY: clean-HC05

