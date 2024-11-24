/*
 * bluetooth.c
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */
#include"bluetooth.h"
uint8 uart_buff;
int   x=750;
int pace=2000;
/************************************************************/
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
//send_data����Ϊ�ض��ķ���16λ���ݵĺ���
//������ѭ���е���receive_data1��������������
//ע���������ڲ��ɷ�����������

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
        else if(uart_buff=='f'){adc_kd+=0.5;send_data1(adc_kd);}
        else if(uart_buff=='o'){adc_kd-=0.5;send_data1(adc_kd);}
        //7
//        else if(uart_buff=='g'){skp+=3;send_data1(skp);}
//        else if(uart_buff=='p'){skp-=2;send_data1(skp);}
        //8
        else if(uart_buff=='h'){skd+=3;send_data1(skd);}
        else if(uart_buff=='q'){skd-=2;send_data1(skd);}
        //9
        else if(uart_buff=='i'){adc_kp+=0.5;send_data1((int)(adc_kp));}
        else if(uart_buff=='r'){adc_kp-=0.5;send_data1((int)(adc_kp));}
        else if(uart_buff=='t'){speed_define=0;send_data1((int)(ski*100));}
        else if(uart_buff=='c'){if(mode_flag==0)mode_flag=1;  uart_write_byte(UART_7,mode_flag); }//ģʽѡ��ѭ��ģʽ��ң��ģʽ
        else if(uart_buff=='1'){gpio_set_level(C13,1);}
             else if(uart_buff=='0'){gpio_set_level(C13,0);}

    }
}
u8 BUFF[30];
void sent_data3(int A,int B,int C,int D,int E,int F)
{
    int i;
    u8 sumcheck = 0;
    u8 addcheck = 0;
    u8 _cnt=0;
    BUFF[_cnt++]=0xAA;//֡ͷ
    BUFF[_cnt++]=0xFF;//Ŀ���ַ
    BUFF[_cnt++]=0xF1;//������
    BUFF[_cnt++]=0x0C;//���ݳ���
    BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
    BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
    BUFF[_cnt++]=BYTE0(B);
    BUFF[_cnt++]=BYTE1(B);
    BUFF[_cnt++]=BYTE0(C);
    BUFF[_cnt++]=BYTE1(C);
    BUFF[_cnt++]=BYTE0(D);
    BUFF[_cnt++]=BYTE1(D);
        BUFF[_cnt++]=BYTE0(E);
    BUFF[_cnt++]=BYTE1(E);
        BUFF[_cnt++]=BYTE0(F);
    BUFF[_cnt++]=BYTE1(F);
    //SC��AC��У��ֱ�ӳ�������������ļ���
    for(i=0;i<BUFF[3]+4;i++)
    {
        sumcheck+=BUFF[i];
        addcheck+=sumcheck;
    }
    BUFF[_cnt++]=sumcheck;
    BUFF[_cnt++]=addcheck;

    for(i=0;i<_cnt;i++) uart_write_byte(UART_7,BUFF[i]);//���������������
}
void receive_data2()
{


    if(uart_query_byte(UART_4, &uart_buff))

    {
        if(uart_buff=='a')  { fullcharge_flag=1;}

    }
//    if(time>=7)
//    {
//        fullcharge_flag=1;
//    }

}
void communicate(void)
{
//    if(send_speed)
//    {
//
//        uart_write_byte(UART_4,speed_define/10);
//        send_speed=0;
//    }
        if(flag_hd==left5||flag_hd==right5)
            {
                uart_write_byte(UART_4,'a');
            }
        else if(flag_hd==left8||flag_hd==right8)
             {
                uart_write_byte(UART_4,'b');
             }
        else if(flag_go==4)
            {
                uart_write_byte(UART_4,'c');
            }
}
