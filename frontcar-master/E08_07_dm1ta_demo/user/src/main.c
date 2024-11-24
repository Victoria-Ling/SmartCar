/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"


// 本例程是 有去模块（无 MCU 版本 DM1TA） 的使用例程 本例程仅演示如何使用 DM1TA 进行测距信号发送 本例程不显示数据
// 本例程是 有去模块（无 MCU 版本 DM1TA） 的使用例程 本例程仅演示如何使用 DM1TA 进行测距信号发送 本例程不显示数据
// 本例程是 有去模块（无 MCU 版本 DM1TA） 的使用例程 本例程仅演示如何使用 DM1TA 进行测距信号发送 本例程不显示数据


// *************************** 例程硬件连接说明 ***************************
// 使用逐飞科技调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
//
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 B10
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 B11
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源
//
// 接入 DM1TA 模块
//      模块管脚            单片机管脚
//      FB                  查看 zf_device_dm1xa.h 中 DM1XA_FB_PIN  宏定义 默认 E15
//      EN                  查看 zf_device_dm1xa.h 中 DM1XA_EN_PIN  宏定义 默认 E14
//      VCC                 5V 电源
//      GND                 电源地


// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程
//
// 2.在断电情况下，单独使用核心板与调试下载器或者 USB-TTL 模块连接，并连接好 DM1TA 模块
//      ( 如果使用配套的学习主板测试，则直接将 DM1TA 模块接到对应的接口位置 )
//
// 3.使用 Type-C 给核心板供电，将调试下载器或者 USB-TTL 模块连接到电脑
//      ( 如果使用配套的学习主板测试，则需要直接使用电池供电，2S锂电池/蓝电池电压不应低于7.8V，3S锂电池电压不应低于11.3V )
//
// 4.DM1TA 模块上蓝灯会低亮度常亮（50Hz闪烁 短点亮时间 看起来就是低亮度常亮）
//
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查


// **************************** 代码区域 ****************************
#define LED1                    (E9 )
#define S_MOTOR_PIN    (TIM2_PWM_MAP3_CH1_A15)      //定义舵机引脚


long int speed1,speed2;//真左右电机的速度，需要由编码器和线性函数求得
//int show[60][160];
int mode_flag=0;
int16 send_speed=0;
int16 speed1_show,speed2_show;
float distance;//障碍距离


uint16 pit_ms_count = 0;

int main (void)
{
       clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 120MHz
        debug_init();                                                               // 初始化默认 Debug UART

    // 此处编写用户代码 例如外设初始化代码等

       tft180_set_dir(TFT180_CROSSWISE_180);                                           // 需要先横屏 不然显示不下
       tft180_init();
       tft180_show_int(120,108,17,4);
       gpio_init(D12, GPO, 0, GPO_PUSH_PULL);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
       pwm_init(PWM_CH2, 17000, 0);                                             // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
       pwm_init(PWM_CH4, 17000, 0);                                      // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
       gpio_init(D14, GPO, 0, GPO_PUSH_PULL);
       encoder_dir_init(TIM1_ENCOEDER,  TIM1_ENCOEDER_MAP3_CH1_E9,  TIM1_ENCOEDER_MAP3_CH2_E11);
       encoder_dir_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);
                                           //独立按键初始化
       gpio_init(C7, GPO, 0, GPO_PUSH_PULL);
       gpio_init(A8, GPO, 0, GPO_PUSH_PULL);
       gpio_init(B0, GPO, 0, GPO_PUSH_PULL);
       gpio_init(B12, GPI, 0, GPI_PULL_DOWN);
       gpio_init(D8, GPI, 0, GPI_PULL_DOWN);
       gpio_init(C6, GPI, 0, GPI_PULL_DOWN);


       gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//蜂鸣器

     uart_init(UART_4, 115200, UART4_MAP3_TX_E0, UART4_MAP3_RX_E1);


      // wireless_uart_init();//    二者等价都为蓝牙串口初始化
       uart_init(UART_7, 115200, UART7_MAP3_TX_E12,  UART7_MAP3_RX_E13);
       dm1xa_init();                     //有来有去的发送端初始化
       dl1a_init();
       imu660ra_init();                //icm20602初始化
       mt9v03x_init();                //初始化摄像头
       pwm_init(S_MOTOR_PIN, 50, 735);//舵机初始化
       Adc_init();                  //adc初始化
       pit_ms_init(TIM3_PIT, 10);  //电机定时器初始化
       pit_ms_init(TIM6_PIT, 20); //ADC计算偏差值，元素识别和主控制放进中断
       pit_ms_init(TIM7_PIT, 5); //tof模块

       gyroOffsetInit();        //陀螺仪零漂初始化
//          ImagePerspective_Init();
       loc_pid_init(&left_pid,2.5,0,2,500,100);
       loc_pid_init(&right_pid,2.5,0,2,500,100);
       loc_pid_init(&daoche_pid,5,0,9,500,500);
       send_speed=1;
//    interrupt_global_enable(0);
    // 此处编写用户代码 例如外设初始化代码等

        while(1)

        {
        // 此处编写需要循环执行的代码
               if(mt9v03x_finish_flag)
               {

             //       printf("%d,%d\n",Kp_sum,Kd_sum);
//                    sendimg(mt9v03x_image[0], 160, 60);
                //  sent_data3(Cam_Servo_add,averight,speed1,speed2,set_speed_left,Cam_Servo_add);
                //   ad0=adc_mean_filter_convert(ADC1_IN15_C5, 10);
                 //   tft180_show_gray_image(0,0,mt9v03x_image[0], MT9V03X_W,MT9V03X_H ,MT9V03X_W,MT9V03X_H,0);
              //      erzhihua();
             //       find_avebianjie();用来计算左右边界循迹的量值
             //       main_check();//舵机放中断
              //      add_line();//补线操作
                      communicate();
                      receive_data1();
                      receive_data2();
       //--------------方法1.这两个函数通过差和比用来控制，计算并得到中线
                       image_boundary_process();
//                       black_check();
                       show_line();
                       lcd_show();
       //-------------------------------------------------
       //               image_process();         //方法2.八邻域寻线
        //              image_boundry_rec(MT9V03X_H,MT9V03X_W);

       //-------------------------------------------------
            //         motor_control1();
               //        main_control();

             //        sent_image();//图像发送
       //
       //              for(int i=0;i<RESULT_ROW;i++)//逆透视检验操作
       //                             {
       //                                 for(int j=0;j<RESULT_COL;j++)
       //                                 {
       //                                     show[i][j]=ImageUsed[i][j];
       //                                     mt9v03x_image[i][j]=show[i][j];
       //                                 }
       //                             }
       //
       //              tft180_displayimage03x (mt9v03x_image[0], 100, 60);
       //



             //      getmidline();           //通过二值化来求中线，两者可交换使用


             //      left_xunji();
             //      right_xunji();
             //      zhongxian_xunji();
                     mt9v03x_finish_flag = 0;
               }
               // 此处编写需要循环执行的代码
        }

}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 的中断处理函数 这个函数将在 PIT 对应的定时器中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     pit_handler();
//-------------------------------------------------------------------------------------------------------------------
void pit_handler (void)
{
    if(0 == pit_ms_count % 20)                                                  // 每 20ms 发起一次测距
    {
        // 测距调用频率应在 50-100Hz 周期在 10-20ms
        // 测距调用频率应在 50-100Hz 周期在 10-20ms
        // 测距调用频率应在 50-100Hz 周期在 10-20ms
        dm1xa_transmitter_ranging();
    }
    pit_ms_count = (pit_ms_count == 995) ? (0) : (pit_ms_count + 5);            // 1000ms 周期计数
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
