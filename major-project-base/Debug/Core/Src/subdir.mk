################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LaptopInterface.c \
../Core/Src/Serial.c \
../Core/Src/buttonhandler.c \
../Core/Src/buzzer.c \
../Core/Src/lidar_sweep.c \
../Core/Src/main.c \
../Core/Src/pot.c \
../Core/Src/ptu_i2c.c \
../Core/Src/stm32f3xx_hal_msp.c \
../Core/Src/stm32f3xx_it.c \
../Core/Src/sweep_flag.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f3xx.c \
../Core/Src/timer.c 

OBJS += \
./Core/Src/LaptopInterface.o \
./Core/Src/Serial.o \
./Core/Src/buttonhandler.o \
./Core/Src/buzzer.o \
./Core/Src/lidar_sweep.o \
./Core/Src/main.o \
./Core/Src/pot.o \
./Core/Src/ptu_i2c.o \
./Core/Src/stm32f3xx_hal_msp.o \
./Core/Src/stm32f3xx_it.o \
./Core/Src/sweep_flag.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f3xx.o \
./Core/Src/timer.o 

C_DEPS += \
./Core/Src/LaptopInterface.d \
./Core/Src/Serial.d \
./Core/Src/buttonhandler.d \
./Core/Src/buzzer.d \
./Core/Src/lidar_sweep.d \
./Core/Src/main.d \
./Core/Src/pot.d \
./Core/Src/ptu_i2c.d \
./Core/Src/stm32f3xx_hal_msp.d \
./Core/Src/stm32f3xx_it.d \
./Core/Src/sweep_flag.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f3xx.d \
./Core/Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/LaptopInterface.cyclo ./Core/Src/LaptopInterface.d ./Core/Src/LaptopInterface.o ./Core/Src/LaptopInterface.su ./Core/Src/Serial.cyclo ./Core/Src/Serial.d ./Core/Src/Serial.o ./Core/Src/Serial.su ./Core/Src/buttonhandler.cyclo ./Core/Src/buttonhandler.d ./Core/Src/buttonhandler.o ./Core/Src/buttonhandler.su ./Core/Src/buzzer.cyclo ./Core/Src/buzzer.d ./Core/Src/buzzer.o ./Core/Src/buzzer.su ./Core/Src/lidar_sweep.cyclo ./Core/Src/lidar_sweep.d ./Core/Src/lidar_sweep.o ./Core/Src/lidar_sweep.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pot.cyclo ./Core/Src/pot.d ./Core/Src/pot.o ./Core/Src/pot.su ./Core/Src/ptu_i2c.cyclo ./Core/Src/ptu_i2c.d ./Core/Src/ptu_i2c.o ./Core/Src/ptu_i2c.su ./Core/Src/stm32f3xx_hal_msp.cyclo ./Core/Src/stm32f3xx_hal_msp.d ./Core/Src/stm32f3xx_hal_msp.o ./Core/Src/stm32f3xx_hal_msp.su ./Core/Src/stm32f3xx_it.cyclo ./Core/Src/stm32f3xx_it.d ./Core/Src/stm32f3xx_it.o ./Core/Src/stm32f3xx_it.su ./Core/Src/sweep_flag.cyclo ./Core/Src/sweep_flag.d ./Core/Src/sweep_flag.o ./Core/Src/sweep_flag.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f3xx.cyclo ./Core/Src/system_stm32f3xx.d ./Core/Src/system_stm32f3xx.o ./Core/Src/system_stm32f3xx.su ./Core/Src/timer.cyclo ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su

.PHONY: clean-Core-2f-Src

