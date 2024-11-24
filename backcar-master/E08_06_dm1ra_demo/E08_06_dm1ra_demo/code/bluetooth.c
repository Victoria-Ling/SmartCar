/*
 * bluetooth.c
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */
#include"bluetooth.h"
uint8 uart_buff;
int   x=750;

uint8 fullcharge_flag=0;
//send_data函数为特定的发送16位数据的函数
//主函数循环中调用receive_data1（）；函数即可
//注：蓝牙串口不可发送其它数据

void send_data1(int16 dat)
{
    uint8 a[5];
    uint8 i=0;
    a[0] = dat/256;
    a[1] = dat%256;
    while(i<2)
    {
        uart_write_byte(UART_7,a[i]);
        i++;
    }
}
void send_data2(int16 dat)
{
    uint8 a[5];
    uint8 i=0;
    a[0] = dat/256;
    a[1] = dat%256;
    while(i<2)
    {
        uart_write_byte(UART_4,a[i]);
        i++;
    }
}
void receive_data1()
{
    if(uart_query_byte(UART_7, &uart_buff))
    {
        //1
        if(uart_buff=='g'){speed_define+=10;send_data1(speed_define/10);}
        else if(uart_buff=='h'){speed_define-=10;send_data1(speed_define/10);}
        //2
        else if(uart_buff=='b'){Cam_Servo_Kp+=3;send_data1(Cam_Servo_Kp);}
        else if(uart_buff=='k'){Cam_Servo_Kp-=2;send_data1(Cam_Servo_Kp);}
        //3
        else if(uart_buff=='s'){Cam_Servo_Kd+=3;send_data1(Cam_Servo_Kd);}
        else if(uart_buff=='l'){Cam_Servo_Kd-=2;send_data1(Cam_Servo_Kd);}
        //4
        else if(uart_buff=='d'){skp+=3;send_data1(skp);}
        else if(uart_buff=='m'){skp-=2;send_data1(skp);}
        //5
        else if(uart_buff=='e'){ski+=0.05;send_data1(ski*100);}
        else if(uart_buff=='n'){ski-=0.03;send_data1(ski*100);}
        //6
        else if(uart_buff=='f'){ski+=0.05;send_data1(ski*100);}
        else if(uart_buff=='o'){ski-=0.03;send_data1(ski*100);}
        //7
//        else if(uart_buff=='g'){skp+=3;send_data1(skp);}
//        else if(uart_buff=='p'){skp-=2;send_data1(skp);}
        //8
        else if(uart_buff=='h'){skd+=3;send_data1(skd);}
        else if(uart_buff=='q'){skd-=2;send_data1(skd);}
        //9
        else if(uart_buff=='i'){ski+=0.05;send_data1((int)(ski*100));}
        else if(uart_buff=='r'){ski-=0.03;send_data1((int)(ski*100));}
        else if(uart_buff=='t'){speed_define=0;send_data1((int)(ski*100));}
        else if(uart_buff=='c'){if(mode_flag==0)mode_flag=1;  uart_write_byte(UART_7,mode_flag); }//模式选择，循迹模式和遥控模式
        else if(uart_buff=='1'){gpio_set_level(C13,1);}
             else if(uart_buff=='0'){gpio_set_level(C13,0);}

    }
}
void receive_data2()
{


    if(uart_query_byte(UART_4, &uart_buff))

    {
          if(uart_buff=='a'){   car_distance_def=2000;flag_hd=1;}
          else if(uart_buff=='b'){ car_distance_def=2000;flag_hd=0;}//后
          else if(uart_buff=='c'){ flag_status=stop;}//后退
//        pwm_set_duty(TIM4_PWM_MAP1_CH1_D12,pace);
//        pwm_set_duty(TIM4_PWM_MAP1_CH3_D14,0);//右电机
//        pwm_set_duty(TIM4_PWM_MAP1_CH4_D15,pace);}
//        else if(uart_buff=='c'){if(mode_flag==1)mode_flag=0;}
//        else if(uart_buff=='d'){x+=20; pwm_set_duty(TIM2_PWM_MAP3_CH1_A15 ,x);if(x>=820)x=820;}
//        else if(uart_buff=='e'){x-=20; pwm_set_duty(TIM2_PWM_MAP3_CH1_A15 ,x);if(x<=680)x=680;}
//        else if(uart_buff=='z'){pwm_set_duty(TIM4_PWM_MAP1_CH2_D13,0);//后退
//        pwm_set_duty(TIM4_PWM_MAP1_CH1_D12,0);
//        pwm_set_duty(TIM4_PWM_MAP1_CH3_D14,0);//右电机
//        pwm_set_duty(TIM4_PWM_MAP1_CH4_D15,0);}
//        else if(uart_buff=='g'){pace+=200;send_data(pace);}
//        else if(uart_buff=='h'){pace-=200;send_data(pace);}
//        else if(uart_buff=='1'){gpio_set_level(C13,1);}
//        else if(uart_buff=='0'){gpio_set_level(C13,0);}
    }

}
int16 onceflag=1;
void communicate(void)
{

    if(time>1)//这边要改成当充电的标志位adc_charge>=1000
    {

        if(onceflag)

            {
            fullcharge_flag='a';
             uart_write_byte(UART_4,fullcharge_flag);
             onceflag=0;
            }
    }

}
