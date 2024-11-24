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
int16 Cam_Servo_add;
long int output_last1,output_last2;
long int motor_left,motor_right;//�ֱ�Ϊ��������pwmռ�ձ�ֵ���ҵ����pwmռ�ձ�ֵ��Խ�� �����ѹԽ�ߣ�
long int set_speed_left=150,set_speed_right=150;//�趨���������ٶ�
int place;
int lpH,lpW;
int point1,point2;
int guaidian_max,guaidian_min;
float Error_e=0.0,LastError_e=0.0,Error_d=0.0,sum=0.0;
int32 speed_define=310;
int adc_kp=15,adc_kd=9;

int obstacle_once_flag=0;//���·��TFmini��־λ
int obstacle_flag=0;//���·�ϱ�־λ
int ramp_flag=0;//�µ���־λ
int obstacle_go_flag=0;//���ǰ����־λ
int obstacle_last_flag=0;//���·�ϻ�����־λ

float Dutyresult;
void main_control(void)
{
        if(flag_go==1)
        {
//            flag_go=3;
            chuku_control();
        }
        else if(!flag_hd&&!flag_sz&&!obstacle_flag&&flag_go==3)
        {
//            Cam_error();
//            zhongxian_xunji();
            adc_servo_Control();
        }

        else if(flag_hd&&!obstacle_flag&&flag_go==3)
        {
//            adc_servo_Control();
            huandao_control();
        }
        else if(flag_sz&&!obstacle_flag&&flag_go==3)
        {
            adc_servo_Control();
           //shizi_control();
        }
        else if(obstacle_flag&&flag_go==3)
        {
            obstacle_display1();//��ϴ���(�����Ǳջ�)
            obstacle_servo_control();
        }
        else if(flag_go==4)
        {
          adc_servo_Control();
          ruku_control();
//             ;
        //huandao_control();
        }

}

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


int16 fullcharge_flag=0;//�����־λ
void chuku_control(void)
{
   pace_flag=1;

   if(erage_path>-53)
   {
       pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Servo_min);
   }
   else
   {
       flag_go=2;
       pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Servo_mid);
   }
//   else if(flag_go==1&&erage_path<-50)
//   {
//       pace_flag=0;
//       speed_define=0;
//   }


}
void ruku_control(void)
{


        pace_flag=1;
//        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Servo_mid);
        if(erage_path>=60)
        {
            speed_define=0;
//            output_last1=39000;
//            output_last2=39000;
            pace_flag=0;
         }
}
void shizi_control()
{
    int i,j,k;
    int l_up,r_up,l_down,r_down;
    if(flag_sz==1)
    {
        buxian_line(1,70,60,20);
        buxian_line(1,95,60,140);
    }
    if(flag_sz==2)
    {
    //����ѭ��
        zhongxian_xunji();
    }
    if(flag_sz==3)
    {
        adc_servo_Control();//���ѭ��

    }
    if(flag_sz==4)
    {
        adc_servo_Control();//���ѭ��

    }

    if(flag_sz==5)
    {
        adc_servo_Control();//���ѭ��

    }

    if(flag_sz==6) //ǰ�ָոս���׵����л�Ϊ����ѭ��
    {

        zhongxian_xunji();
    }

    if(flag_sz==7)
    {

        zhongxian_xunji();
    }

    if(flag_sz==8)
    {
        zhongxian_xunji();
    }


}


void huandao_control(void)
{

    if(flag_hd==left1)
   {
      right_xunji();

    }
     if(flag_hd==left2)
    {
       right_xunji();
    }
     if(flag_hd==left3)
    {
       right_xunji();
    }
    if(flag_hd==left4)
    {
//        Cam_Servo_error=0;
       Cam_Servo_add=-45;
       pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,787);//785��Ҫ�������Ĵ�С
       //left_xunji();
    }
    if(flag_hd==left5)
    {
        adc_servo_Control();//��߽���ǿ����zhongxian_xunji(
//    left_pid.kp=1.8;
//     left_xunji();
    }
    if(flag_hd==left6)
    {

          left_xunji();
    }
    if(flag_hd==left7)
    {

           left_xunji();
    }
    if(flag_hd==left8)
    {   reset_pid();
        right_xunji();
    }
    if(flag_hd==left9)
    {
        Cam_error();
//        Cam_Servo_add=0;
//        Cam_Servo_error=0;
        zhongxian_xunji();
//        adc_servo_Control();
    }
    if(flag_hd==right1)
    {
        left_xunji();
    }
    if(flag_hd==right2)
      {
          left_xunji();
      }
    if(flag_hd==right3)
      {
          left_xunji();
      }
    if(flag_hd==right4)
      {
        Cam_Servo_add=45;
        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,670);//��Ҫ�������Ĵ�С
    //      right_xunji();
      }
    if(flag_hd==right5)
        {
            adc_servo_Control();
        }
    if(flag_hd==right6)
        {
            right_pid.kp=1.8;
            right_xunji();
        }
    if(flag_hd==right7)
        {
            right_xunji();
        }
    if(flag_hd==right8)
        {
          reset_pid();
            left_xunji();
        }

}


void right_xunji(void)
{   int i;
    int16 sum=0;

   for( i=60;i>30;i--)
       {
        sum+=rightedge[i];
       }
       averight=sum/29;
       loc_pid_calculate(&right_pid,128,averight);
       Cam_Servo_add=right_pid.output;
      if(Cam_Servo_add>83)Cam_Servo_add=83;
      if(Cam_Servo_add<-83)Cam_Servo_add=-83;
      sum=0;
      pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Servo_mid+Cam_Servo_add);

}
void left_xunji(void)
{
       int i;
       int16 sum=0;

       for( i=60;i>30;i--)
           {
            sum+=leftedge[i];
           }
           aveleft=sum/29;
           loc_pid_calculate(&left_pid,28,aveleft);
           Cam_Servo_add=left_pid.output;
          if(Cam_Servo_add>62)Cam_Servo_add=62;
          if(Cam_Servo_add<-62)Cam_Servo_add=-62;
          sum=0;
          pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Servo_mid+Cam_Servo_add);

}
/******************************************************************************/
/*!
 *  @brief      ������ƺ���(����ͷ)
 *  @since      2018.12.6
 *  @note       ��ͮ��
 */


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
            Cam_Servo_out=Servo_mid+Cam_Servo_add;

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


    changeduty = Error_e*adc_kp+Error_d*adc_kd;
    Cam_Servo_add=-changeduty;
    if((my_abs(Cam_Servo_add))<5)
                {
                Cam_Servo_add=0;//��������
                }
    Dutyresult = (float)( Servo_mid+Cam_Servo_add );
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
int16 back_distance_def=-54;
void motor_control2(void)
{
    float a;
    loc_pid_calculate(&daoche_pid,erage_path,back_distance_def);
    speed_define=-daoche_pid.output;
//    if(speed_define==0)
//    {
//        skd=13;
//        ski=10;
//        skp=20;
//    }
//    else {
//        skd=0;
//              ski=0.5;
//              skp=2.6;
//          }
    Cam_Servo_add=-75;
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
          left_motor_pid_back();//����pid
           right_motor_pid_back();//�ҵ��pid
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
void add_line(void)//��ʶ���ٲ���
{    int i;
//     int i,y1,y2;
//     float k;

     if(flag_hd==left2)
     {

      buxian_line(cpH,cpW,30,126);
     }
     if(flag_hd==left4)
    {
         for(i=10;i<30;i++)
            {
                if(leftedge[i]<2)
                   break;
            }
            lpH=i+1;
         buxian_line(lpH,0,cpH,cpW);
//            buxian_line(10,10,30,60);
     }
    if(flag_sz==shizi1)
    {
        guaidian_max=leftedge[60];
        guaidian_min=rightedge[60];
        for(i=59;i>=12;i--)//�ڶ��ַ����ҹյ�
        {
          if(leftedge[i]>guaidian_max)
              {guaidian_max=leftedge[i];point1=i;}
        }
        buxian_line(point1,guaidian_max,0,80);

        for(i=58;i>=12;i--)
        {
            if(rightedge[i]<guaidian_min)
            {guaidian_min=rightedge[i];point2=i;}
        }
        buxian_line(point2,guaidian_min,0,108);
//        for(i=60;i>=10;i--)
//         {
//             if((leftedge[i+2]-leftedge[i])>10&&(leftedge[i+3]-leftedge[i])>9&&(leftedge[i+3]-leftedge[i])>8)
//               {  point1=i;
//                  y1=leftedge[point1];
//                  buxian_line(point1,y1,0,80);
//                  break;}
//          }
//        for(i=60;i>=10;i--)
//         {
//             if((rightedge[i+2]-rightedge[i])<-10&&(rightedge[i+3]-rightedge[i])<-9&&(rightedge[i+3]-rightedge[i])<-8)
//             { point2=i;
//               y2=rightedge[point2];
//               buxian_line(point2,y2,0,108);
//               break;}
//          }



    }
}

int buxian_line(int x1,int y1,int x2,int y2)//4�� x�� y�У�y,x)���У��У�
{
    float slope,k1,k2;
    int i,Y0,X0,j;
     k1=1.0*(y1-y2)/(float)(x1-x2);
     k2=1.0*(x1-x2)/(float)(y1-y2);


//     lcd_showfloat(0,6,slope);
//     lcd_showfloat(0,6 ,slope,3,6);
     int sumX=0,sumY=0,sumlines,averageX,averageY;
     float  parameterB,parameterA,sumUp=0,sumDown=0;
     if(k1>1&&k1<-1)
 {     slope=k1;
    if  (x1<x2)
    {
        sumlines=0;

        for(i=x1;i<x2;i++)
        {

            Y0=(int)(y1+(i-x1)*slope);
            mt9v03x_image[i][Y0]=0;
            mt9v03x_image[i][Y0+1]=0;
            mt9v03x_image[i+1][Y0]=0;
            sumX += i;
            sumY +=Y0;
        }
        sumlines=(x2-x1);
                   if (sumlines == 0) sumlines = 1;
                   averageY = (float)(sumY / sumlines);     //x��ƽ��ֵ
                   averageX =(float)( sumX / sumlines);     //y��ƽ��ֵ
                   for (i = x1; i < x2; i++)
                   {
                       Y0=(int)(y1+(i-x1)*slope);
                       sumUp += (Y0 - averageY) * (i - averageX);
                       sumDown += (i - averageX) * (i - averageX);
                   }
                   if (sumDown == 0) parameterB = 0;
                   else parameterB = sumUp / sumDown;
                   parameterA = averageY - parameterB * averageX;
                   R_blackfuzhi(parameterA, parameterB, x1, x2);
    }
    if(x1>x2 )
    {
        sumlines=0;
                for(i=x2;i<x1;i++)
                {

                    Y0=(int)(y1+(i-x2)*slope);
                    mt9v03x_image[i][Y0]=0;
                    mt9v03x_image[i][Y0+1]=0;
                    mt9v03x_image[i+1][Y0]=0;
                   sumY += i;
                   sumX +=Y0;
                }
                sumlines=(x1-x2);
                           if (sumlines == 0) sumlines = 1;
                           averageY = (float)(sumY / sumlines);     //x��ƽ��ֵ
                           averageX =(float)( sumX / sumlines);     //y��ƽ��ֵ
                           for(i=x2;i<x1;i++)
                           {
                               Y0=(int)(y1+(i-x2)*slope);
                               sumUp += (Y0 - averageX) * (i - averageY);
                               sumDown += (i - averageY) * (i - averageY);
                           }
                           if (sumDown == 0) parameterB = 0;
                           else parameterB = sumUp / sumDown;
                           parameterA = averageX - parameterB * averageY;
                           leftlinefuzhi(parameterA, parameterB, x2, x1);
    }
    if(x1==x2)
    {
        if(y1>y2)
        {
            for(i=y1;i>=y2;i--)
            {
                mt9v03x_image[x1][i]=0;

            }
        }
        else
        {
            for(i=y1;i<=y2;i++)
            {
                mt9v03x_image[x1][i]=0;
            }
        }
    }
}
     else
     {
         slope=k2;
         if  (y1<y2)
             {
                 sumlines=0;

                 for(j=y1;j<y2;j++)
                 {

                     X0=(int)(x1+(j-y1)*slope);
                     mt9v03x_image[X0][j]=0;
                     mt9v03x_image[X0+1][j]=0;
                     mt9v03x_image[X0][j+1]=0;
                     sumX += X0;
                     sumY +=j;
                 }
                 sumlines+=(y2-y1);
                 if (sumlines == 0) sumlines = 1;
                                averageY = (float)(sumY / sumlines);     //x��ƽ��ֵ
                                averageX =(float)( sumX / sumlines);     //y��ƽ��ֵ
                                for (j = y1; j < y2; j++)
                                {
                                    X0=(int)(x1+(j-y1)*slope);
                                    sumUp += (j - averageY) * (X0 - averageX);
                                    sumDown += (X0 - averageX) * (X0 - averageX);
                                }
                                if (sumDown == 0) parameterB = 0;
                                else parameterB = sumUp / sumDown;
                                parameterA = averageY - parameterB * averageX;
                                R_blackfuzhi(parameterA, parameterB, x1, x2);
             }
                 if  (y1>y2)
                             {
                                 sumlines=0;

                                 for(j=y2;j<y1;j++)
                                 {

                                     X0=(int)(x2+(j-y2)*slope);
                                     mt9v03x_image[X0][j]=0;
                                     mt9v03x_image[X0+1][j]=0;
                                     mt9v03x_image[X0][j+1]=0;
                                     sumX += X0;
                                     sumY +=j;
                                 }
                    sumlines=(y1-y2);
                                 if (sumlines == 0) sumlines = 1;
                                                averageY = (float)(sumY / sumlines);     //x��ƽ��ֵ
                                                averageX =(float)( sumX / sumlines);     //y��ƽ��ֵ
                                                for(j=y2;j<y1;j++)
                                                {
                                                    X0=(int)(x2+(j-y2)*slope);
                                                    sumUp += (j - averageY) * (X0 - averageX);
                                                    sumDown += (X0 - averageX) * (X0 - averageX);
                                                }
                                                if (sumDown == 0) parameterB = 0;
                                                else parameterB = sumUp / sumDown;
                                                parameterA = averageY - parameterB * averageX;
                                                R_blackfuzhi(parameterA, parameterB, x1, x2);
                             }
                                 if(y1==y2)
                                 {
                                     if(x1>x2)
                                     {
                                         for(j=x1;j>=x2;j--)
                                         {
                                             mt9v03x_image[j][y1]=0;
                                         }
                                     }
                                     else
                                     {
                                         for(j=x1;j<=x2;j++)
                                         {
                                             mt9v03x_image[j][y1]=0;
                                         }
                                     }
                                 }
     }
return 0;
}
void R_blackfuzhi(float A, float B, int start_point, int end_point)
{
    int m;

    for (m = start_point; m <= end_point; m++)
    {

        if ((B * m + A) < 0) {rightedge[m] = 0; }
      else if((B * m + A) >=0&&(B * m + A)<=188) rightedge[m] = (int)(B * m + A);
        if((B * m + A)>=188)rightedge[m]=188;
    }
}
void leftlinefuzhi(float A, float B, int start_point, int end_point)
{
     int m;
     for (m = start_point; m <= end_point; m++)
     {
         if((B * m + A)>=188) leftedge[m]=188;
         if((B * m + A)<=0) leftedge[m]=0;
         else if(0<(B * m + A)&&(B * m + A)<188)leftedge[m] = (int)(B * m + A);
     }
}

void reset_pid(void)
{
   left_pid.kp=2.5;
   right_pid.kp=2.5;
}


int obstacle_mod[3]={1,2,1};//ģʽ  (1:������ 2:������ 3:������ 4:������)
int angle_out[3]={7,7,7};//�ճ�ȥ�ĽǶ� (0��9ÿ��10��0-90��) �����Ҹ�
int angle_special=3;//�ڹճ��Ļ����Ϲջض���,��ʱ��Ҫ���������(�����ڶ��ι���Ч)
int angle_in[3]={7,7,7};//�ս����ĽǶ�  (0��9ÿ��10��0-90��)
int step1[3]={4,4,4};//����Ʋ�(1-10)
int step2[3]={11,9,10};//�����Ʋ�(1-10)
int step3[3]={2,3,3};//��ؼƲ�(1-10)    Ĭ������������
int step_back=3;//�����Ʋ�
//int num_of_obstacle=1;//�������

uint8 step_num=0;//��ǰΪ�Ʋ��ڼ���
uint8 count_of_obstacle=0;//��ǰΪ�ڼ�����ϣ�������һ�����ʱ��Ϊ1
uint8 worry_obstacle_flag=0;//����Ӻ�ϱ�־λ

int obstacle_kp=70;//44
int obstacle_kd=65;//65
int obstacle_error[2]={0,0};
int angle_want;
int16 once_flag=1;
int Kp_sum,Kp_sum_last;
int Kd_sum,Kd_sum_last;//Kp,Kp1,Kp2,Kd�ļӺ�(����LCD��ʾ)

void obstacle_display1(void)//��ϴ���
{
    /********�����ϴ�ƫ��*******/

    obstacle_error[1]=obstacle_error[0];
    Kp_sum_last=Kp_sum;
    Kd_sum_last=Kd_sum;
    /*****�õ����������Ƕ�*****/
    if(obstacle_flag&&once_flag)
        {
              yaw1_obstacle=yaw1;
              once_flag=0;
        }
    if(obstacle_mod[count_of_obstacle-1]==1)//�����
    {
        if(step_num==1)
            angle_want=10*angle_out[count_of_obstacle-1];
        else if(step_num==2)
        {
            yaw1_obstacle=yaw1;
            angle_want=-10*angle_in[count_of_obstacle-1];
        }
        else if(step_num==3)
        {
            yaw1_obstacle=yaw1;
            angle_want=10*angle_in[count_of_obstacle-1];
        }
    }
    else if(obstacle_mod[count_of_obstacle-1]==2)//���ҹ�
    {
        if(step_num==1)
            angle_want=-10*angle_out[count_of_obstacle-1];
        else if(step_num==2)
        {
            yaw1_obstacle=yaw1;
            angle_want=10*angle_in[count_of_obstacle-1];;//
        }
        else if(step_num==3)
        {
            yaw1_obstacle=yaw1;
            angle_want=-10*angle_in[count_of_obstacle-1];
        }
    }

    /*********�õ�ƫ��**********/

    obstacle_error[0]=angle_want+yaw1_obstacle-yaw1;

    /********�õ�PID��ֵ********/


        Kp_sum=(int)(obstacle_kp*obstacle_error[0])/10;
        Kd_sum=(int)(obstacle_kd*(obstacle_error[0]-obstacle_error[1]))/10;
       if(my_abs(Kp_sum-Kp_sum_last)>500)
           Kp_sum=0;
       if(my_abs(Kd_sum-Kd_sum_last)>500)
                 Kd_sum=0;
    /*********�Ʋ�����**********/
    pace_flag=1;//��ʼ�Ʋ�

     if(erage_path<(step1[count_of_obstacle-1])*10)
    {
        BEEP_ON;
        step_num=1;
    }
    else if(erage_path<(step1[count_of_obstacle-1]+step2[count_of_obstacle-1])*10)
    {
        BEEP_OFF;
        step_num=2;
    }
    else if(erage_path<(step1[count_of_obstacle-1]+step2[count_of_obstacle-1]+step3[count_of_obstacle-1])*10)
    {
        BEEP_ON;
        step_num=3;
    }
    else//�����к�ϱ�־λ
    {
       // stop_enable=0;//ͣ��������ʱʧ��

        obstacle_flag=0;
        obstacle_last_flag=0;
        pace_flag=0;
     //   broken_last_flag=1;
        BEEP_OFF;
    }
}

void obstacle_servo_control(void)
{

    Cam_Servo_add=(Kp_sum+Kd_sum)/10;
    Dutyresult=Servo_mid+Cam_Servo_add;
    if( Dutyresult > Servo_max){
            Dutyresult =Servo_max;
        } else if (Dutyresult < Servo_min)
        {
            Dutyresult = Servo_min;
        }
    pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,Dutyresult);
}
