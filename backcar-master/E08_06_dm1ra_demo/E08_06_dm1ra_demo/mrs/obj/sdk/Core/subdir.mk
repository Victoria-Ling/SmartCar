################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/youqu/E08_06_dm1ra_demo/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: D:/MounRiver/youqu/E08_06_dm1ra_demo/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\Libraries\doc" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\sdk\Core" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\sdk\Ld" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\sdk\Peripheral" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\sdk\Startup" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\E08_06_dm1ra_demo\user\inc" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\zf_common" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\zf_device" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\E08_06_dm1ra_demo\code" -I"D:\MounRiver\youqu\E08_06_dm1ra_demo\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

