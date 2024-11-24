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

//        meter1= encoder_get_count(TIM1_ENCOEDER);//右电机 值为2700时，走了2.8m,128
        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,735+45);
        flag_bizhang=1;
//        延时
//        打角 或者用编码器测走过的距离
//        if(dl1a_distance_mm>given_distance)

    }
//     if(flag_bizhang==1)
//     {
//         meter2= encoder_get_count(TIM1_ENCOEDER);//右电机 值为2700时，走了2.8m,128
//         if(((meter2-meter1)+100)/1000>=xie_distance)
//         {
//             flag_bizhang=2;
//         }
//     }
//     if(flag_bizhang==2)
//     {
//         pwm_set_duty(TIM2_PWM_MAP3_CH1_A15,735);
//         meter3= encoder_get_count(TIM1_ENCOEDER);//右电机 值为2700时，走了2.8m,128
//         if(((meter2-meter1)+100)/1000>=xie_distance)
//          {
//             flag_bizhang=3;
//           }
//     }
//     if(flag_bizhang==3)
//     {
//         //通过检测到电感值，切换到摄像头循迹或者先转个角再进行摄像头循迹
//     }

}
void pit_handler_tof (void)
{
    if(0 == pit_ms_count1 % 40)                                                  // 每 40ms 获取一次测距信息 周期 40 ms 频率 25Hz
    {
        dl1a_get_distance();                                                    // 测距调用频率不应高于 30Hz 周期不应低于 33.33ms
    }
    distance=dl1a_distance_mm;
    pit_ms_count1 = (pit_ms_count1 == 995) ? (0) : (pit_ms_count1 + 5);            // 1000ms 周期计数
}

// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
//
// 问题1：串口输出 DM1TA init error.
//      检查 DM1TA 的接线是否正确是否松动
//      检查 DM1TA 的模块是不是坏了
//
// 问题2：DM1TA 不亮灯或者蓝灯不亮
//      检查接线是否正确是否松动
//      不亮红灯检查供电是否正常，是否短路

