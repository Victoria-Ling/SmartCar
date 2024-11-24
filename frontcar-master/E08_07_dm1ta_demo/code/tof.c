/*
 * tof.c
 *
 *  Created on: Apr 12, 2023
 *      Author: 86157
 */

#include "tof.h"

#include "zf_device_dl1a.h"
#include "zf_device_dm1xa.h"
int flag_bizhang=0;
uint16 given_distance_mm=500;

//uint16 meter1,meter2,meter3;
//uint16 xie_distance;

uint16 pit_ms_count1 = 0;
uint16 pit_ms_count2 = 0;
void tof_bizhang(void)
{

     if(dl1a_distance_mm<=given_distance_mm && flag_bizhang==0)
    {

//        meter1= encoder_get_count(TIM1_ENCOEDER);//�ҵ�� ֵΪ2700ʱ������2.8m,128
        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,735+45);
        flag_bizhang=1;
//        ��ʱ
//        ��� �����ñ��������߹��ľ���
//        if(dl1a_distance_mm>given_distance)

    }
//     if(flag_bizhang==1)
//     {
//         meter2= encoder_get_count(TIM1_ENCOEDER);//�ҵ�� ֵΪ2700ʱ������2.8m,128
//         if(((meter2-meter1)+100)/1000>=xie_distance)
//         {
//             flag_bizhang=2;
//         }
//     }
//     if(flag_bizhang==2)
//     {
//         pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,735);
//         meter3= encoder_get_count(TIM1_ENCOEDER);//�ҵ�� ֵΪ2700ʱ������2.8m,128
//         if(((meter2-meter1)+100)/1000>=xie_distance)
//          {
//             flag_bizhang=3;
//           }
//     }
//     if(flag_bizhang==3)
//     {
//         //ͨ����⵽���ֵ���л�������ͷѭ��������ת�����ٽ�������ͷѭ��
//     }

}
void pit_handler_tof (void)
{
    if(0 == pit_ms_count1 % 40)                                                  // ÿ 40ms ��ȡһ�β����Ϣ ���� 40 ms Ƶ�� 25Hz
    {
        dl1a_get_distance();                                                    // ������Ƶ�ʲ�Ӧ���� 30Hz ���ڲ�Ӧ���� 33.33ms
    }
    distance=dl1a_distance_mm;
    pit_ms_count1 = (pit_ms_count1 == 995) ? (0) : (pit_ms_count1 + 5);            // 1000ms ���ڼ���
}

// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
//
// ����1��������� DM1TA init error.
//      ��� DM1TA �Ľ����Ƿ���ȷ�Ƿ��ɶ�
//      ��� DM1TA ��ģ���ǲ��ǻ���
//
// ����2��DM1TA �����ƻ������Ʋ���
//      �������Ƿ���ȷ�Ƿ��ɶ�
//      ������Ƽ�鹩���Ƿ��������Ƿ��·

