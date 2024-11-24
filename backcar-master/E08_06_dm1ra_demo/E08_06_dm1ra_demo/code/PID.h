/*
 * PID.h
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */

#ifndef PID_H_
#define PID_H_

#include "zf_common_headfile.h"

typedef struct P_PID_HANDLE
{
    u8 enable_lim_sum_error : 1;    //�����޷�ʹ��
    u8 enable_lim_ouput     : 1;    //����޷�ʹ��

    float kp;           //��������
    float ki;           //���ֲ���
    float kd;           //΢�ֲ���
//  float sum_error_lim;
    float kiout_lim;    //�������޷�
    float lim_output;       //����޷� ��ֹ�������

    float sum_error;        //������
    float last_error;       //��һ�ε����
    float last_last_error;  //����һ�ε����

    float kd_output;
    float ki_output;
    float kp_output;

    float output;
    float error;
}  pid_init;


float loc_pid_calculate(pid_init* pid, float input, float measure);

void loc_pid_init(pid_init* pid,float kp,float ki,float kd,float kiout_lim,float lim_output);

extern pid_init speed_diff1;
extern pid_init speed_diff2;
extern pid_init left_pid;
extern pid_init right_pid;


extern int Cam_Servo_Kp;//20
extern int Cam_Servo_Kd;//21
extern int Cam_Servo_Ki;

extern float error_1,lasterror_1,error_2,lasterror_2,lastlasterror_2;
extern float skp,skd;
extern float ski;
extern int kp1,kd1,ki_limit,lim_output;
extern float ki1,out;
extern int Cam_Servo_error_pre_pre;
extern int Cam_Servo_error_pre;
extern int Cam_Servo_error;

float wzsPID(float reference,float feedback);

float left_PID(float reference,float nowplace);
float right_PID(float reference,float nowplace);
void left_motor_pid(void);//��������ʽPID
void right_motor_pid(void);//�ҵ������ʽPID



#endif /* PID_H_ */
