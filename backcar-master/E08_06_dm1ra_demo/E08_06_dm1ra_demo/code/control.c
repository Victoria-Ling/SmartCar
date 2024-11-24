/*
 * control.c
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */



#include "control.h"
#define DISTANDE_RATIO (11475.0f)//1M�ǵ���·�̣����ڻ����ʵ�ʵ�·�̣�5ms��¼һ��
int16 rightfix[60];
int16 leftfix[60];
int16 averight;
int16 aveleft;
int16 avesum;
int16 Cam_Servo_add;
long int output_last1,output_last2,output_last3;
long int motor_left,motor_right;//�ֱ�Ϊ��������pwmռ�ձ�ֵ���ҵ����pwmռ�ձ�ֵ��Խ�� �����ѹԽ�ߣ�
long int set_speed_left=150,set_speed_right=150;//�趨���������ٶ�
float Error_e=0.0,LastError_e=0.0,Error_d=0.0,sum=0.0;
int32 speed_define=440;
int16 speed_receive;
int adc_kp=17,adc_kd=15;

int obstacle_once_flag=0;//���·��TFmini��־λ
int obstacle_flag=0;//���·�ϱ�־λ
int ramp_flag=0;//�µ���־λ
int obstacle_go_flag=0;//���ǰ����־λ
int obstacle_last_flag=0;//���·�ϻ�����־λ

float Dutyresult;
float chahe;

float V_Now=0;
int16 V_L_Now=0;
int16 V_R_Now=0;//��ǰ����ٶ�
int16 V_L_Now_last=0;
int16 V_R_Now_last=0;//�ϴ��ٶ�
int16 pulse_L[2];
int16 pulse_R[2];//����ֵ
int pace_flag=0;//��ʼ�Ʋ���־λ
float erage_path=0;//�����ۼ��ٶȼ�·��

void Speed_Get(void)
{
    pulse_L[1]=pulse_L[0];
    pulse_R[1]=pulse_R[0];
    pulse_L[0]=encoder_get_count(TIM1_ENCOEDER);
    pulse_R[0]=-encoder_get_count(TIM9_ENCOEDER);
    encoder_clear_count(TIM1_ENCOEDER);//��������ʱ������
    encoder_clear_count(TIM9_ENCOEDER);//��������ʱ������
//    V_L_Now_last=V_L_Now;
//    V_R_Now_last=V_R_Now;//�ϴ��ٶ�(����ǰ��)
    V_L_Now=(pulse_L[0]+pulse_L[1])/2;
    V_R_Now=(pulse_R[0]+pulse_R[1])/2;//����������ֵ�˲�
    V_Now=(float)(V_L_Now+V_R_Now)/2;//��ǰ����
    if(pace_flag==1)//��ʼ�Ʋ�
        erage_path+=(float)(V_Now/DISTANDE_RATIO)*100;//��λ������
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
    else if(flag_status==1) //�׵㶪ʧ�л�Ϊ���ѭ��
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
int Kd_sum;//Kp,Kp1,Kp2,Kd�ļӺ�(����LCD��ʾ)
int32 Kp1_sum;
int32 Kp2_sum;
int obstacle_error_last=0;//���ں�ϱ�־λ�жϹյķ���
int circle_mode=1;//����ģʽ2����ģʽ
int Cam_Servo_out;
void zhongxian_xunji(void)
{

        Kp_sum=(float)(Cam_Servo_error*Cam_Servo_Kp)/10;
        Kd_sum=Cam_Servo_Kd*(float)((Cam_Servo_error-Cam_Servo_error_pre)/10);
        Cam_Servo_add=(int32)(Kp_sum+Kd_sum+Cam_Servo_Ki*(Cam_Servo_error+Cam_Servo_error_pre+Cam_Servo_error_pre_pre));//�������
        if(Cam_Servo_add>(100))
            Cam_Servo_add=100;
        else if(Cam_Servo_add<(-100))
            Cam_Servo_add=-100;
        if((my_abs(Cam_Servo_add))<5)
            {
            Cam_Servo_add=0;//��������
            }
            Cam_Servo_out=750+Cam_Servo_add;

        ///////////����޷�///////////

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
//         place=wzsPID(80,avesum);//���λ���ж�
//         if(place>83)place=83;
//         if(place<-83)place=-83;
//         sum=0;//�ۺ����㣬��������
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
               Cam_Servo_add=0;//��������
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

void motor_control(void)//���ٿ���
{   float a;
    if( Cam_Servo_add>0)//���ټ��� ���ֵΪmotor_left��motor_right
       {
         //  if(differential>=100){if(output_last1<output_last2)output_last2=output_last1;}
           a =0.005*Cam_Servo_add*Cam_Servo_add+(0.251*Cam_Servo_add);//0.00005 ���������ֵ�����ٶȺ�С���ٶ�֮�ȵĹ�ϵa
           a=1+(a/100);
           set_speed_left=2*speed_define/(1+a);
           set_speed_right=speed_define*a;//set_speed_right
       }

       if(Cam_Servo_add<=0)//���ټ��� ���ֵΪmotor_left��motor_right
       {
          // if(differential>=100){if(output_last1>output_last2)output_last1=output_last2;}
           a =0.005*Cam_Servo_add*Cam_Servo_add-(0.251*Cam_Servo_add);//0.00005
           a=1+(a/100);
           set_speed_right=2*speed_define/(1+a);
           set_speed_left=speed_define*a;//set_speed_left
       }
       left_motor_pid();//����pid
       right_motor_pid();//�ҵ��pid
       if(motor_left<0)
           {
           pwm_set_duty(PWM_CH2,-motor_left);//����
           gpio_set_level(D12,1);//�����ߵ�ƽ��ת
           }
           else
           {
               pwm_set_duty(PWM_CH2,motor_left);//����
               gpio_set_level(D12,0);//�����ߵ�ƽ��ת
           }
               if(motor_right<0)
           {
                pwm_set_duty(PWM_CH4,-motor_right);//�ҵ��
                gpio_set_level(D14,1);//�ҵ���ߵ�ƽ��ת
           }
           else
           {
                pwm_set_duty(PWM_CH4,motor_right);//�ҵ��
                gpio_set_level(D14,0);//�ҵ���ߵ�ƽ��ת
           }
}


void motor_control1(void)//������ƺ��� �޲��ٿ��Ƶ�
{
       pwm_set_duty(PWM_CH2,10*speed_define);//����
       gpio_set_level(D12,1);//�����ߵ�ƽ��ת
       pwm_set_duty(PWM_CH4,10*speed_define);//�ҵ��
       gpio_set_level(D14,1);//�ҵ���ߵ�ƽ��ת
}

