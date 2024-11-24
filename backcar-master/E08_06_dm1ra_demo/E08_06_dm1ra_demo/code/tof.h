/*
 * tof.h
 *
 *  Created on: Apr 12, 2023
 *      Author: 86157
 */

#ifndef TOF_H_
#define TOF_H_
#include "zf_common_headfile.h"
//extern float  tof_distance;                             //测距距离
//extern uint8  tof_ranging_flage = 0x00;                 // 测距状态
//extern uint8  tof_receipt_data;                //接受到的数据
//extern uint8  tof_dat[3]={0};                 //存放定时器计数值的数组
//extern uint8  tof_num=0;                        //状态标志位
//extern uint8  high_time;                      //超声波模块返回高电平的时间

//extern uint16 given_distance_mm=1000;
//extern uint16 get_distance;
//extern uint16 meter1,meter2,meter3;
//extern uint16 xie_distance;
extern void pit_handler (void);
extern void tof_bizhang(void);
extern uint16 pit_ms_count ;
#endif /* TOF_H_ */
