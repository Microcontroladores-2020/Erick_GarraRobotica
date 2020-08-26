################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
008GarraRobotica.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
008GarraRobotica.list \

OBJCOPY_BIN += \
008GarraRobotica.bin \


# All Target
all: 008GarraRobotica.elf secondary-outputs

# Tool invocations
008GarraRobotica.elf: $(OBJS) $(USER_OBJS) C:\Users\eriic\Downloads\Embedded-C\My_workspace\target_nucleo\008GarraRobotica\STM32F401RETX_FLASH.ld
	arm-none-eabi-gcc -o "008GarraRobotica.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\eriic\Downloads\Embedded-C\My_workspace\target_nucleo\008GarraRobotica\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="008GarraRobotica.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

008GarraRobotica.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "008GarraRobotica.list"
	@echo 'Finished building: $@'
	@echo ' '

008GarraRobotica.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "008GarraRobotica.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
