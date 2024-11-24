################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/E08_07_dm1ta_demo/user/src/isr.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/E08_07_dm1ta_demo/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/E08_07_dm1ta_demo/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/E08_07_dm1ta_demo/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

