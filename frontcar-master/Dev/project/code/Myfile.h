#ifndef MYFILE_H_
#define MYFILE_H_

#define BEEP_ON gpio_set_level(C13,1)
#define BEEP_OFF gpio_set_level(C13,0)

#include "zf_common_headfile.h"
#include "GyroScope.h"
#include "bluetooth.h"
#include "Read_ADC.h"
#include "All_init.h"
#include "Debug.h"
#include "Motor.h"
#include "Servo.h"
#include "math.h"
#include "Key.h"
#include "Tof.h"

#endif /* MYFILE_H_ */
