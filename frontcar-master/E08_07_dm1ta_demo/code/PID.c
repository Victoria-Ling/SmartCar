/*
 * PID.c
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */





#include "PID.h"
int Cam_Servo_Kp=19;//20
int Cam_Servo_Kd=15;//21
int Cam_Servo_Ki=0;


float skp=2.6,skd=0;
int kp1=6,kd1=0,ki_limit=9500,lim_output=9500;
float ki1=0.15;
float ski=0.5;
//float error_1,lasterror_1=0;//error_1为舵机角度与中线的差值
//float error_2,lasterror_2=0,lastlasterror_2=0;
float out=0,lastout=0;
int Cam_Servo_error_pre_pre=0;
int Cam_Servo_error_pre=0;
int Cam_Servo_error=0;
int error1_show;
pid_init left_pid;
pid_init right_pid;
pid_init daoche_pid;


void left_motor_pid(void)//左电机增量式PID
{
    static long int derror1,dderror1,lasterror1,derror_last1;
    static long int motor_left_last;
    long int error1 = (set_speed_left-speed1);//所需速度减去编码器测出的实际速度为误差值f
    error1_show=error1;
    long int out_put1;//pid求出的增量值
    derror1 = error1 - lasterror1;//这次误差减去上次误差 即误差变化值
    lasterror1 = error1;//更新上一次误差值
    dderror1 = derror1 - derror_last1;//这次的误差变化值减去上次的误差变化值
    derror_last1 = derror1;//更新上一次误差变化率
    out_put1 =(skp*derror1)+(ski*error1)+(skd*dderror1) + output_last1;//求出的增量pid的增量加上上次的输出值，即为电机所需的电压值
    output_last1 = (long int)out_put1;//更新上一次的输出值
    motor_left=out_put1;//将pid所求值赋值给电机的改变pwm占空比的值

    if(motor_left>9500)motor_left=9500;//输出值限幅
    else if(motor_left<-7000)motor_left=-7000;
    //motor_left=(0.65*motor_left+0.35*motor_left_last)/2;//与上一次的电机输出取平均值，以达到滤波效果
    motor_left_last=motor_left;
}
void right_motor_pid(void)//右电机增量式PID
{
    static long int derror2,dderror2,lasterror2,derror_last2;
    static long int motor_right_last;
    long int error2 = (set_speed_right-speed2);
    long int out_put2;
    derror2 = error2 - lasterror2;
    lasterror2 = error2;
    dderror2 = derror2 - derror_last2;
    derror_last2 = derror2;
    out_put2 =(skp*derror2)+(ski*error2)+(skd*dderror2) + output_last2;
    output_last2 = (long int)out_put2;
    motor_right=out_put2;
    if(motor_right>9500)motor_right=9500;
    else if(motor_right<-7000)motor_right=-7000;
  //  motor_right=(0.65*motor_right+0.35*motor_right_last)/2;
    motor_right_last=motor_right;
}

void left_motor_pid_back(void)//左电机增量式PID
{
    static long int derror1,dderror1,lasterror1,derror_last1;
    static long int motor_left_last;
    long int error1 = (set_speed_left-speed1);//所需速度减去编码器测出的实际速度为误差值f
    error1_show=error1;
    long int out_put1;//pid求出的增量值
    derror1 = error1 - lasterror1;//这次误差减去上次误差 即误差变化值
    lasterror1 = error1;//更新上一次误差值
    dderror1 = derror1 - derror_last1;//这次的误差变化值减去上次的误差变化值
    derror_last1 = derror1;//更新上一次误差变化率
    out_put1 =(6*derror1)+(0.8*error1)+(0*dderror1) + output_last1;//求出的增量pid的增量加上上次的输出值，即为电机所需的电压值
    output_last1 = (long int)out_put1;//更新上一次的输出值
    motor_left=out_put1;//将pid所求值赋值给电机的改变pwm占空比的值

    if(motor_left>9500)motor_left=9500;//输出值限幅
    else if(motor_left<-7000)motor_left=-7000;
    //motor_left=(0.65*motor_left+0.35*motor_left_last)/2;//与上一次的电机输出取平均值，以达到滤波效果
    motor_left_last=motor_left;
}
void right_motor_pid_back(void)//右电机增量式PID
{
    static long int derror2,dderror2,lasterror2,derror_last2;
    static long int motor_right_last;
    long int error2 = (set_speed_right-speed2);
    long int out_put2;
    derror2 = error2 - lasterror2;
    lasterror2 = error2;
    dderror2 = derror2 - derror_last2;
    derror_last2 = derror2;
    out_put2 =(6*derror2)+(0.8*error2)+(0*dderror2) + output_last2;
    output_last2 = (long int)out_put2;
    motor_right=out_put2;
    if(motor_right>9500)motor_right=9500;
    else if(motor_right<-7000)motor_right=-7000;
  //  motor_right=(0.65*motor_right+0.35*motor_right_last)/2;
    motor_right_last=motor_right;
}

float abs1(float a)
{
    if (a<0)return -a;
    else return a;
}
float loc_pid_calculate(pid_init* pid, float input, float measure)
{
    pid->error = input - measure;         //计算误差
    pid->sum_error += pid->error;

    //误差积分限幅
        pid->kp_output = pid->kp * pid->error;
        pid->ki_output = pid->ki * pid->sum_error;
        pid->kd_output = pid->kd * (pid->error - pid->last_error);
        if((abs1(pid->ki_output) > pid->kiout_lim))
    {
        if(pid->ki_output > 0)
                {
            pid->ki_output = pid->kiout_lim;
                        pid->sum_error=pid->kiout_lim / pid->ki;
                }
        else
                {
            pid->ki_output = -pid->kiout_lim;
                        pid->sum_error=-pid->kiout_lim / pid->ki;
                }
        }
    pid->output = pid->kp_output + pid->ki_output + pid->kd_output ;

    //输出限幅
    if(abs1(pid->output) > pid->lim_output)
    {
        if(pid->output > 0)
            pid->output = pid->lim_output;
        else
            pid->output = -pid->lim_output;
    }
        pid->last_error = pid->error;
        return 0;
}

void loc_pid_init(pid_init* pid,float kp,float ki,float kd,float kiout_lim,float lim_output)
{
    pid->kp=kp;
    pid->ki=ki;
    pid->kd=kd;
    pid->kiout_lim=kiout_lim;
    pid->lim_output=lim_output;
}

void pid_updatee(pid_init* pid,float kp,float ki,float kd)
{
    pid->kp=kp;
    pid->ki=ki;
    pid->kd=kd;

}











