################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf_driver/subdir.mk
-include zf_device/subdir.mk
-include zf_common/subdir.mk
-include user_c/subdir.mk
-include sdk/Startup/subdir.mk
-include sdk/Peripheral/subdir.mk
-include sdk/Core/subdir.mk
-include code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
E08_06_dm1ra_demo.hex \

SECONDARY_LIST += \
E08_06_dm1ra_demo.lst \

SECONDARY_SIZE += \
E08_06_dm1ra_demo.siz \


# All Target
all: E08_06_dm1ra_demo.elf secondary-outputs

# Tool invocations
E08_06_dm1ra_demo.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\zf_device" -Wl,-Map,"E08_06_dm1ra_demo.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -Wl,--print-memory-usage -o "E08_06_dm1ra_demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
E08_06_dm1ra_demo.hex: E08_06_dm1ra_demo.elf
	@	riscv-none-embed-objcopy -O ihex "E08_06_dm1ra_demo.elf"  "E08_06_dm1ra_demo.hex"
	@	@
E08_06_dm1ra_demo.lst: E08_06_dm1ra_demo.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "E08_06_dm1ra_demo.elf" > "E08_06_dm1ra_demo.lst"
	@	@
E08_06_dm1ra_demo.siz: E08_06_dm1ra_demo.elf
	@	riscv-none-embed-size --format=berkeley "E08_06_dm1ra_demo.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) E08_06_dm1ra_demo.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
