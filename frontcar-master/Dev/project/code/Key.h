/*
 * Key.h
 *
 *  Created on: 2023年6月18日
 *      Author: 86166
 */

#ifndef KEY_H_
#define KEY_H_

extern unsigned char Key_Number;
extern unsigned char Key_Switch;

void Key_Scan(void);    //按键扫描
void Key_ON(void);      //屏幕开启/关闭

#endif /* KEY_H_ */
