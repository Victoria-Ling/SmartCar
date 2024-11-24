################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_adc.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_delay.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_dvp.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_encoder.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_exti.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_flash.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_gpio.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_iic.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_pit.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_pwm.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_iic.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_spi.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_spi.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_timer.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_uart.c \
D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_usb_cdc.c 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_iic.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_soft_spi.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_iic.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_soft_spi.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_iic.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_spi.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_soft_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: D:/MounRiver/有来有去超声波无MCU版本/例程/CH32V307VCT6/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\有来有去超声波无MCU版本\例程\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

