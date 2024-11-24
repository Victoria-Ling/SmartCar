/*
 * control.c
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */



#include "control.h"
#define DISTANDE_RATIO (11475.0f)//1M记到的路程，用于换算成实际的路程，5ms记录一次
int16 rightfix[60];
int16 leftfix[60];
int16 averight;
int16 aveleft;
int16 avesum;
int16 Cam_Servo_add;
long int output_last1,output_last2,output_last3;
long int motor_left,motor_right;//分别为给左电机的pwm占空比值和右电机的pwm占空比值（越大 电机电压越高）
long int set_speed_left=150,set_speed_right=150;//设定的左右轮速度
float Error_e=0.0,LastError_e=0.0,Error_d=0.0,sum=0.0;
int32 speed_define=440;
int16 speed_receive;
int adc_kp=17,adc_kd=15;

int obstacle_once_flag=0;//横断路障TFmini标志位
int obstacle_flag=0;//横断路障标志位
int ramp_flag=0;//坡道标志位
int obstacle_go_flag=0;//横断前进标志位
int obstacle_last_flag=0;//横断路障回正标志位

float Dutyresult;
float chahe;

float V_Now=0;
int16 V_L_Now=0;
int16 V_R_Now=0;//当前相对速度
int16 V_L_Now_last=0;
int16 V_R_Now_last=0;//上次速度
int16 pulse_L[2];
int16 pulse_R[2];//脉冲值
int pace_flag=0;//开始计步标志位
float erage_path=0;//用于累加速度记路程

void Speed_Get(void)
{
    pulse_L[1]=pulse_L[0];
    pulse_R[1]=pulse_R[0];
    pulse_L[0]=encoder_get_count(TIM1_ENCOEDER);
    pulse_R[0]=-encoder_get_count(TIM9_ENCOEDER);
    encoder_clear_count(TIM1_ENCOEDER);//编码器定时器清零
    encoder_clear_count(TIM9_ENCOEDER);//编码器定时器清零
//    V_L_Now_last=V_L_Now;
//    V_R_Now_last=V_R_Now;//上次速度(用于前馈)
    V_L_Now=(pulse_L[0]+pulse_L[1])/2;
    V_R_Now=(pulse_R[0]+pulse_R[1])/2;//编码器脉冲值滤波
    V_Now=(float)(V_L_Now+V_R_Now)/2;//当前车速
    if(pace_flag==1)//开始计步
        erage_path+=(float)(V_Now/DISTANDE_RATIO)*100;//单位是厘米
    else
        erage_path=0;
}
void main_control(void)
{
    if(!flag_status)
    {
        seek_light_error();
        zhongxian_xunji();
    }
    else if(flag_status==1) //白点丢失切换为电磁循迹
    {
        seek_light_error();
        adc_servo_Control();
    }
    else if(flag_status==stop&&flag_go!=3)
    {
        ruku_control();
    }
}
void chuku_control(void)
{
   pace_flag=1;
   if(erage_path<25)
   {
       pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,735);
   }
   else if(erage_path>=20&&erage_path<=97)
   {
       pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,675);
   }
   else
   {
    pace_flag=0;
    flag_go=1;
   }

}
float compensate=0;
void ruku_control(void)
{
        int16 once_flag=0;
        pace_flag=1;
        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,750);
//        if(car_distance<=4600&&car_distance>=1700&&!once_flag)
//        {
//            compensate=distance_calculate(car_distance);
//            once_flag=1;
//        }
//        else if(!once_flag&&car_distance>=4600&&car_distance<=1700)
//        {
//                compensate=0;
//        }
//       if(compensate)
//       {
                if(erage_path>=20)//+compensate
                {
                    pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Servo_min);
                 }
                if(erage_path>=82)//+compensate
                {
                    flag_go=3;
                    pace_flag=0;
                }
//       }
}
int16 car_distance_def=2000;
void car_distance_control()
{
//    if(car_distance<=3600&&car_distance>=400)
//    {
//    loc_pid_calculate(&speed_diff1,car_distance,car_distance_def);
//    }
//    else if(car_distance>3600)
//    speed_diff1.output=200;
//    else if(car_distance==6800)
//    {
//        speed_diff1.output=0;
//    }
//    else
//    speed_diff1.output=0;
//    speed_define=speed_diff1.output+410;
    if(flag_status==0)
    {speed_define=340-speed_diff2.output;}
    if(flag_status==1)
    {
        speed_define=340;
    }
}


int Kp_sum;
int Kd_sum;//Kp,Kp1,Kp2,Kd的加和(用于LCD显示)
int32 Kp1_sum;
int32 Kp2_sum;
int obstacle_error_last=0;//用于横断标志位判断拐的方向
int circle_mode=1;//正常模式2低速模式
int Cam_Servo_out;
void zhongxian_xunji(void)
{

        Kp_sum=(float)(Cam_Servo_error*Cam_Servo_Kp)/10;
        Kd_sum=Cam_Servo_Kd*(float)((Cam_Servo_error-Cam_Servo_error_pre)/10);
        Cam_Servo_add=(int32)(Kp_sum+Kd_sum+Cam_Servo_Ki*(Cam_Servo_error+Cam_Servo_error_pre+Cam_Servo_error_pre_pre));//输出增量
        if(Cam_Servo_add>(100))
            Cam_Servo_add=100;
        else if(Cam_Servo_add<(-100))
            Cam_Servo_add=-100;
        if((my_abs(Cam_Servo_add))<5)
            {
            Cam_Servo_add=0;//消除静差
            }
            Cam_Servo_out=750+Cam_Servo_add;

        ///////////输出限幅///////////

        if(Cam_Servo_out>Servo_max)
            Cam_Servo_out=Servo_max;
        else if(Cam_Servo_out<Servo_min)
            Cam_Servo_out=Servo_min;
        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Cam_Servo_out);
//       int i,sum=0;
//      for (i=55; i >35; i--)
//         {
//          sum += midline[i];
//         }
//          avesum = sum / 19;
//
//         place=wzsPID(80,avesum);//舵机位置判断
//         if(place>83)place=83;
//         if(place<-83)place=-83;
//         sum=0;//累和置零，常见错误
//         pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,735+place);//);

}
void adc_servo_Control(void)
{
    int changeduty = 0;
    Error_e=adc_error/100;

    Error_d=Error_e-LastError_e;

    LastError_e=Error_e;
//    chahe = (float)(ad3 - ad1)/(ad3 + ad1);
//        if(chahe <= 0.40 || chahe >= -0.40)
//        {
//            adc_kp = 5;
//            adc_kd = 15;
//        }
//        if(chahe >= 0.40 || chahe <= -0.40)
//        {
//            adc_kp = 30;
//            adc_kd = 38;
//        }

    changeduty = Error_e*adc_kp+Error_d*adc_kd;
    Cam_Servo_add=-changeduty;
    if((my_abs(Cam_Servo_add))<5)
               {
               Cam_Servo_add=0;//消除静差
               }
    Dutyresult = (float)( 750+Cam_Servo_add );

    if( Dutyresult > Servo_max){
        Dutyresult = Servo_max;
    } else if (Dutyresult < Servo_min){
        Dutyresult = Servo_min;
    }

     pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Dutyresult);

     LastError_e=Error_e;
}

void motor_control(void)//差速控制
{   float a;
    if( Cam_Servo_add>0)//差速计算 输出值为motor_left，motor_right
       {
         //  if(differential>=100){if(output_last1<output_last2)output_last2=output_last1;}
           a =0.005*Cam_Servo_add*Cam_Servo_add+(0.251*Cam_Servo_add);//0.00005 建立舵机差值与大的速度和小的速度之比的关系a
           a=1+(a/100);
           set_speed_left=2*speed_define/(1+a);
           set_speed_right=speed_define*a;//set_speed_right
       }

       if(Cam_Servo_add<=0)//差速计算 输出值为motor_left，motor_right
       {
          // if(differential>=100){if(output_last1>output_last2)output_last1=output_last2;}
           a =0.005*Cam_Servo_add*Cam_Servo_add-(0.251*Cam_Servo_add);//0.00005
           a=1+(a/100);
           set_speed_right=2*speed_define/(1+a);
           set_speed_left=speed_define*a;//set_speed_left
       }
       left_motor_pid();//左电机pid
       right_motor_pid();//右电机pid
       if(motor_left<0)
           {
           pwm_set_duty(PWM_CH2,-motor_left);//左电机
           gpio_set_level(D12,1);//左电机高电平反转
           }
           else
           {
               pwm_set_duty(PWM_CH2,motor_left);//左电机
               gpio_set_level(D12,0);//左电机高电平反转
           }
               if(motor_right<0)
           {
                pwm_set_duty(PWM_CH4,-motor_right);//右电机
                gpio_set_level(D14,1);//右电机高电平正转
           }
           else
           {
                pwm_set_duty(PWM_CH4,motor_right);//右电机
                gpio_set_level(D14,0);//右电机高电平正转
           }
}


void motor_control1(void)//电机控制函数 无差速控制的
{
       pwm_set_duty(PWM_CH2,10*speed_define);//左电机
       gpio_set_level(D12,1);//左电机高电平反转
       pwm_set_duty(PWM_CH4,10*speed_define);//右电机
       gpio_set_level(D14,1);//右电机高电平正转
}

