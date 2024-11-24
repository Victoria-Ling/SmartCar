#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

extern uint8 uart_buff;
extern uint8 fullcharge_flag;    //Âúµç±êÖ¾

void send_data1(int16 dat);
void send_data2(int16 dat);
void receive_data1(void);
void receive_data2(void);
void communicate(void);

#endif /* BLUETOOTH_H_ */
