/*
 * control.h
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "zf_common_headfile.h"
extern  int16 averight,Cam_Servo_add;
extern int32 speed_define;
extern int lpH,lpW;
extern int point1,point2;
extern int guaidian_max,guaidian_min;
extern int place;
extern long int output_last1,output_last2;
extern long int motor_left,motor_right;//分别为给左电机的pwm占空比值和右电机的pwm占空比值（越大 电机电压越高）
extern long int set_speed_left,set_speed_right;

extern int obstacle_once_flag;//横断路障TFmini标志位
extern int obstacle_flag;//横断路障标志位
extern int ramp_flag;//坡道标志位
extern int obstacle_go_flag;//横断前进标志位
extern int obstacle_last_flag;//横断路障回正标志位
extern int16 fullcharge_flag;//满电标志位

extern float V_Now;
extern int16 V_L_Now;
extern int16 V_R_Now;//当前相对速度
extern int16 V_L_Now_last;
extern int16 V_R_Now_last;//上次速度
extern int16 pulse_L[2];
extern int16 pulse_R[2];//脉冲值
extern int pace_flag;//开始计步标志位
extern float erage_path;//用于累加速度记路程
extern uint8 count_of_obstacle;//当前为第几个横断，遇到第一个横断时即为1
extern uint8 step_num;//当前为计步第几步
extern float Dutyresult;
extern int adc_kp,adc_kd;
extern int Kp_sum;
extern int Kd_sum;//Kp,Kp1,Kp2,Kd的加和(用于LCD显示)
void adc_servo_Control(void);
void huandao_control(void);
void right_xunji(void);
void left_xunji(void);
void find_avebianjie(void);
void zhongxian_xunji(void);
void motor_control1(void);
void motor_control(void);
void add_line(void);
void main_control(void);
int buxian_line(int x1,int y1,int x2,int y2);
void R_blackfuzhi(float A, float B, int start_point, int end_point);
void leftlinefuzhi(float A, float B, int start_point, int end_point);
void reset_pid(void);
void shizi_control(void);
void chuku_control(void);
void Speed_Get(void);
void obstacle_display1(void);
void obstacle_servo_control(void);
void ruku_control(void);
void motor_control2(void);
#endif /* CONTROL_H_ */
