/*
 * control.h
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "zf_common_headfile.h"

extern int32 speed_define;
extern int16 speed_receive;
extern long int output_last1,output_last2,output_last3;
extern long int motor_left,motor_right;//�ֱ�Ϊ��������pwmռ�ձ�ֵ���ҵ����pwmռ�ձ�ֵ��Խ�� �����ѹԽ�ߣ�
extern long int set_speed_left,set_speed_right;

extern int obstacle_once_flag;//���·��TFmini��־λ
extern int obstacle_flag;//���·�ϱ�־λ
extern int ramp_flag;//�µ���־λ
extern int obstacle_go_flag;//���ǰ����־λ
extern int obstacle_last_flag;//���·�ϻ�����־λ

extern int16 Cam_Servo_add;
extern int16 car_distance_def;
extern float V_Now;
extern int16 V_L_Now;
extern int16 V_R_Now;//��ǰ����ٶ�
extern int16 V_L_Now_last;
extern int16 V_R_Now_last;//�ϴ��ٶ�
extern int16 pulse_L[2];
extern int16 pulse_R[2];//����ֵ
extern int pace_flag;//��ʼ�Ʋ���־λ
extern float erage_path;//�����ۼ��ٶȼ�·��
extern uint8 count_of_obstacle;//��ǰΪ�ڼ�����ϣ�������һ�����ʱ��Ϊ1
extern uint8 step_num;//��ǰΪ�Ʋ��ڼ���
extern float Dutyresult;
extern int adc_kp,adc_kd;
extern int Kp_sum;
extern int Kd_sum;//Kp,Kp1,Kp2,Kd�ļӺ�(����LCD��ʾ)
extern float compensate;
extern float chahe;
void adc_servo_Control(void);
void zhongxian_xunji(void);
void motor_control1(void);
void motor_control(void);
void main_control(void);
void reset_pid(void);
void shizi_control(void);
void chuku_control(void);
void Speed_Get(void);
void obstacle_display1(void);
void obstacle_servo_control(void);
void ruku_control(void);
void car_distance_control(void);
#endif /* CONTROL_H_ */
