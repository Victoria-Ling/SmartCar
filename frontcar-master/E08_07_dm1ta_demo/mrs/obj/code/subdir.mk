################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/ADC.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/Draw_Line.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/PID.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/bluetooth.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/camera.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/control.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/element_discover.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/key.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/swj.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/tof.c \
D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/tuoluoyi.c 

OBJS += \
./code/ADC.o \
./code/Draw_Line.o \
./code/PID.o \
./code/bluetooth.o \
./code/camera.o \
./code/control.o \
./code/element_discover.o \
./code/key.o \
./code/swj.o \
./code/tof.o \
./code/tuoluoyi.o 

C_DEPS += \
./code/ADC.d \
./code/Draw_Line.d \
./code/PID.d \
./code/bluetooth.d \
./code/camera.d \
./code/control.d \
./code/element_discover.d \
./code/key.d \
./code/swj.d \
./code/tof.d \
./code/tuoluoyi.d 


# Each subdirectory must supply rules for building sources it contributes
code/ADC.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/ADC.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/Draw_Line.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/Draw_Line.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/PID.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/PID.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/bluetooth.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/bluetooth.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/camera.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/camera.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/control.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/control.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/element_discover.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/element_discover.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/key.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/key.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/swj.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/swj.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/tof.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/tof.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
code/tuoluoyi.o: D:/MounRiver/������ȥ��������MCU�汾/����/CH32V307VCT6/E08_07_dm1ta_demo/code/tuoluoyi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\Libraries\doc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Core" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Ld" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Peripheral" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\sdk\Startup" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\user\inc" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_common" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_device" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\E08_07_dm1ta_demo\code" -I"D:\MounRiver\������ȥ��������MCU�汾\����\CH32V307VCT6\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

