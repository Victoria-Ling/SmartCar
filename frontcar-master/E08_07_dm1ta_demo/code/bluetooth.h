/*
 * bluetooth.h
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "zf_common_headfile.h"
extern uint8 uart_buff;
void send_data1(int16 dat);
void send_data2(int16 dat);
void receive_data1(void);
void receive_data2(void);
void sent_data3(int A,int B,int C,int D,int E,int F);
void communicate(void);
extern int pace;

#endif /* BLUETOOTH_H_ */
