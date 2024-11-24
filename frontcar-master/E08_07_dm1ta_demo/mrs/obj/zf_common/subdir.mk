################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_clock.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_debug.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_fifo.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_font.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_function.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_interrupt.c 

OBJS += \
./zf_common/zf_common_clock.o \
./zf_common/zf_common_debug.o \
./zf_common/zf_common_fifo.o \
./zf_common/zf_common_font.o \
./zf_common/zf_common_function.o \
./zf_common/zf_common_interrupt.o 

C_DEPS += \
./zf_common/zf_common_clock.d \
./zf_common/zf_common_debug.d \
./zf_common/zf_common_fifo.d \
./zf_common/zf_common_font.d \
./zf_common/zf_common_function.d \
./zf_common/zf_common_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
zf_common/zf_common_clock.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_clock.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_debug.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_debug.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_fifo.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_fifo.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_font.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_font.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_function.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_function.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_common/zf_common_interrupt.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_common/zf_common_interrupt.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

