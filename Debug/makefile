################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/LwIP/src/netif/ppp/subdir.mk
-include Middlewares/Third_Party/LwIP/src/netif/subdir.mk
-include Middlewares/Third_Party/LwIP/src/core/ipv6/subdir.mk
-include Middlewares/Third_Party/LwIP/src/core/ipv4/subdir.mk
-include Middlewares/Third_Party/LwIP/src/core/subdir.mk
-include Middlewares/Third_Party/LwIP/src/apps/mqtt/subdir.mk
-include Middlewares/Third_Party/LwIP/src/api/subdir.mk
-include LWIP/Target/subdir.mk
-include LWIP/App/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/lvgl/src/lv_widgets/subdir.mk
-include Core/lvgl/src/lv_themes/subdir.mk
-include Core/lvgl/src/lv_misc/subdir.mk
-include Core/lvgl/src/lv_hal/subdir.mk
-include Core/lvgl/src/lv_gpu/subdir.mk
-include Core/lvgl/src/lv_font/subdir.mk
-include Core/lvgl/src/lv_draw/subdir.mk
-include Core/lvgl/src/lv_core/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Modules/Screen/Touch_Screen/subdir.mk
-include Core/Modules/Screen/Displayer/subdir.mk
-include Core/Modules/SDRAM/subdir.mk
-include Core/Modules/Network/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := IMG_Transfer_via_TCP
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
IMG_Transfer_via_TCP.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
IMG_Transfer_via_TCP.list \

OBJCOPY_BIN += \
IMG_Transfer_via_TCP.bin \


# All Target
all: main-build

# Main-build Target
main-build: IMG_Transfer_via_TCP.elf secondary-outputs

# Tool invocations
IMG_Transfer_via_TCP.elf: $(OBJS) $(USER_OBJS) D:\Warm\ up\ Projects\Embedded\ Software\ Projects\ST\ Projects\STM32F7\IMG_Transfer_via_TCP\STM32F746NGHX_FLASH.ld
	arm-none-eabi-gcc -o "IMG_Transfer_via_TCP.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"D:\Warm up Projects\Embedded Software Projects\ST Projects\STM32F7\IMG_Transfer_via_TCP\STM32F746NGHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="IMG_Transfer_via_TCP.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

IMG_Transfer_via_TCP.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "IMG_Transfer_via_TCP.list"
	@echo 'Finished building: $@'
	@echo ' '

IMG_Transfer_via_TCP.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "IMG_Transfer_via_TCP.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
