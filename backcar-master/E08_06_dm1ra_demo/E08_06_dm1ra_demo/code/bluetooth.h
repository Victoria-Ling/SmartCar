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
void communicate(void);
extern uint8 fullcharge_flag;

#endif /* BLUETOOTH_H_ */
