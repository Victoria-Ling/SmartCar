/*
 * tof.c
 *
 *  Created on: Apr 12, 2023
 *      Author: 86157
 */

#include "tof.h"
#include "zf_device_dl1a.h"

int flag_bizhang=0;
uint16 given_distance_mm=500;

//uint16 meter1,meter2,meter3;
//uint16 xie_distance;

uint16 pit_ms_count = 0;


void pit_handler (void)
{
    if(0 == pit_ms_count % 40)                                                  // 每 40ms 获取一次测距信息 周期 40 ms 频率 25Hz
    {
        dl1a_get_distance();                                                    // 测距调用频率不应高于 30Hz 周期不应低于 33.33ms
    }
    distance=dl1a_distance_mm;
    pit_ms_count = (pit_ms_count == 995) ? (0) : (pit_ms_count + 5);            // 1000ms 周期计数
}

