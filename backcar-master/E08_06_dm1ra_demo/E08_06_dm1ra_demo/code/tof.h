/*
 * tof.h
 *
 *  Created on: Apr 12, 2023
 *      Author: 86157
 */

#ifndef TOF_H_
#define TOF_H_
#include "zf_common_headfile.h"
//extern float  tof_distance;                             //������
//extern uint8  tof_ranging_flage = 0x00;                 // ���״̬
//extern uint8  tof_receipt_data;                //���ܵ�������
//extern uint8  tof_dat[3]={0};                 //��Ŷ�ʱ������ֵ������
//extern uint8  tof_num=0;                        //״̬��־λ
//extern uint8  high_time;                      //������ģ�鷵�ظߵ�ƽ��ʱ��

//extern uint16 given_distance_mm=1000;
//extern uint16 get_distance;
//extern uint16 meter1,meter2,meter3;
//extern uint16 xie_distance;
extern void pit_handler (void);
extern void tof_bizhang(void);
extern uint16 pit_ms_count ;
#endif /* TOF_H_ */
