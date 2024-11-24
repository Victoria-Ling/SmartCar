#include "zf_common_headfile.h"
#include "zf_device_dm1xa.h"
// *************************** 例程硬件连接说明 ***************************
// 接入 DM1RA 模块
//      模块管脚            单片机管脚
//      S                   查看 zf_device_dm1xa.h 中 DM1XA_S_PIN  宏定义 默认 E15
//      L                   查看 zf_device_dm1xa.h 中 DM1XA_L_PIN  宏定义 默认 E14
//      VCC                 5V 电源
//      GND                 电源地

// **************************** 代码区域 ****************************
#define S_MOTOR_PIN             (TIM2_PWM_MAP3_CH1_A15)      //定义舵机引脚

long int speed1,speed2;//真左右电机的速度，需要由编码器和线性函数求得
//int show[RESULT_ROW][RESULT_COL];
int mode_flag=0;
float distance;//障碍距离
int16 speed1_show,speed2_show;
int adc_charge;
int main (void)
{



          clock_init(SYSTEM_CLOCK_144M);                                              // 初始化芯片时钟 工作频率为 144MHz
          debug_init();                                                               // 初始化默认 Debug UAR
   // 此处编写用户代码 例如外设初始化代码等
          tft180_set_dir(TFT180_CROSSWISE_180);                                           // 需要先横屏 不然显示不下
          tft180_init();
          gpio_init(D12, GPO, 0, GPO_PUSH_PULL);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
          pwm_init(PWM_CH2, 17000, 0);                                             // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
          pwm_init(PWM_CH4, 17000, 0);                                      // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
          gpio_init(D14, GPO, 0, GPO_PUSH_PULL);
          encoder_dir_init(TIM1_ENCOEDER,  TIM1_ENCOEDER_MAP3_CH1_E9,  TIM1_ENCOEDER_MAP3_CH2_E11);
          encoder_dir_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);

          gpio_init(C7, GPO, 0, GPO_PUSH_PULL);//独立按键初始化
          gpio_init(A8, GPO, 0, GPO_PUSH_PULL);
          gpio_init(B0, GPO, 0, GPO_PUSH_PULL);
          gpio_init(B12, GPI, 0, GPI_PULL_DOWN);
          gpio_init(D8, GPI, 0, GPI_PULL_DOWN);
          gpio_init(C6, GPI, 0, GPI_PULL_DOWN);
          gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//蜂鸣器

         uart_init(UART_4, 115200, UART4_MAP3_TX_E0, UART4_MAP3_RX_E1);
         uart_init(UART_7, 115200, UART7_MAP3_TX_E12,  UART7_MAP3_RX_E13);//二者等价都为蓝牙串口初始化  //  wireless_uart_init();
//          dl1a_init();
          dm1xa_init();              //有来有去的发送端初始化
//          imu660ra_init();             //imu660ra初始化
          mt9v03x_init();                //初始化摄像头
          pwm_init(S_MOTOR_PIN, 50, 750);//舵机初始化
          Adc_init();                    //adc初始化
          pit_ms_init(TIM3_PIT, 10);     //电机定时器初始化
          pit_ms_init(TIM6_PIT, 20);    //ADC计算偏差值，元素识别和主控制放进中断
          pit_ms_init(TIM7_PIT, 5);     //tof模块
          gyroOffsetInit();             //陀螺仪零漂初始化
//          ImagePerspective_Init();
          loc_pid_init(&speed_diff1,0.12,0,0.15,200,400);
          loc_pid_init(&speed_diff2,5,0,2,100,150);
          loc_pid_init(&left_pid,2,0,2,500,100);
          loc_pid_init(&right_pid,2,0,2,500,100);
          tft180_show_int(120,108,17,4);

    // 此处编写用户代码 例如外设初始化代码等
          flag_go=1;                    //后车刚刚启动
        while(1)
        {
//               tft180_show_int(64,108,car_distance,4);
            // 此处编写需要循环执行的代码
                    if(mt9v03x_finish_flag)
                    {

//                         sendimg(mt9v03x_image[0], 160, 60);
                           communicate();
                     //   ad0=adc_mean_filter_convert(ADC1_IN15_C5, 10);
                      //   tft180_show_gray_image(0,0,mt9v03x_image[0], MT9V03X_W,MT9V03X_H ,MT9V03X_W,MT9V03X_H,99);


                   //      erzhihua();
                  //         find_avebianjie();用来计算左右边界循迹的量值
                  //       main_check();//舵机放中断
                   //      add_line();//补线操作
//                         dm1xa_receiver_ranging();
            //             get_distance();
                           receive_data1();
                           receive_data2();

            //             *findCenterLine( *mt9v03x_image[MT9V03X_W]);
            //--------------方法1.这两个函数通过差和比用来控制，计算并得到中线
//                           image_boundary_process();
//                           black_check();
//                           show_line();

//                           zhongxian_xunji();
            //-------------------------------------------------
             //              image_process();         //方法2.八邻域寻线
            //-------------------------------------------------
                 //         motor_control1();
                    //        main_control();
//                             main_check();
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
                           if(flag_go==2&&!flag_status)
                           {
                           get_cardistance();
                           car_distance_control();
                           }
                  //      left_xunji();
                  //      right_xunji();
                  //      zhongxian_xunji();
                           lcd_show();//独立按键显示函数初始化
                          mt9v03x_finish_flag = 0;
                    }
                    // 此处编写需要循环执行的代码
                }
    }
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
//
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
//
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
//
// 问题3：串口输出 DM1RA init error.
//      检查 DM1RA 的接线是否正确是否松动
//      检查 DM1RA 的模块是不是坏了
//
// 问题4：DM1RA 数值异常 显示 6800
//      确认 DM1TA 板子接好并下载好程序在正常工作
//      把 DM1TA 和 DM1RA 模块对正 中间无遮挡
//      看看两个模块是否蓝灯亮起来 DM1TA 不亮蓝灯就去检查 DM1TA 如果 DM1RA 不亮蓝灯就联系客服
