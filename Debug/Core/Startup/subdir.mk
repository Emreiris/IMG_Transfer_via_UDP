################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f746nghx.s 

OBJS += \
./Core/Startup/startup_stm32f746nghx.o 

S_DEPS += \
./Core/Startup/startup_stm32f746nghx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32f746nghx.o: ../Core/Startup/startup_stm32f746nghx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f746nghx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

