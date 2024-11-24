#include "zf_common_headfile.h"
#include "zf_device_dm1xa.h"
// *************************** ����Ӳ������˵�� ***************************
// ���� DM1RA ģ��
//      ģ��ܽ�            ��Ƭ���ܽ�
//      S                   �鿴 zf_device_dm1xa.h �� DM1XA_S_PIN  �궨�� Ĭ�� E15
//      L                   �鿴 zf_device_dm1xa.h �� DM1XA_L_PIN  �궨�� Ĭ�� E14
//      VCC                 5V ��Դ
//      GND                 ��Դ��

// **************************** �������� ****************************
#define S_MOTOR_PIN             (TIM2_PWM_MAP3_CH1_A15)      //����������

long int speed1,speed2;//�����ҵ�����ٶȣ���Ҫ�ɱ����������Ժ������
//int show[RESULT_ROW][RESULT_COL];
int mode_flag=0;
float distance;//�ϰ�����
int16 speed1_show,speed2_show;
int adc_charge;
int main (void)
{



          clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 144MHz
          debug_init();                                                               // ��ʼ��Ĭ�� Debug UAR
   // �˴���д�û����� ���������ʼ�������
          tft180_set_dir(TFT180_CROSSWISE_180);                                           // ��Ҫ�Ⱥ��� ��Ȼ��ʾ����
          tft180_init();
          gpio_init(D12, GPO, 0, GPO_PUSH_PULL);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
          pwm_init(PWM_CH2, 17000, 0);                                             // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
          pwm_init(PWM_CH4, 17000, 0);                                      // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
          gpio_init(D14, GPO, 0, GPO_PUSH_PULL);
          encoder_dir_init(TIM1_ENCOEDER,  TIM1_ENCOEDER_MAP3_CH1_E9,  TIM1_ENCOEDER_MAP3_CH2_E11);
          encoder_dir_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);

          gpio_init(C7, GPO, 0, GPO_PUSH_PULL);//����������ʼ��
          gpio_init(A8, GPO, 0, GPO_PUSH_PULL);
          gpio_init(B0, GPO, 0, GPO_PUSH_PULL);
          gpio_init(B12, GPI, 0, GPI_PULL_DOWN);
          gpio_init(D8, GPI, 0, GPI_PULL_DOWN);
          gpio_init(C6, GPI, 0, GPI_PULL_DOWN);
          gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//������

         uart_init(UART_4, 115200, UART4_MAP3_TX_E0, UART4_MAP3_RX_E1);
         uart_init(UART_7, 115200, UART7_MAP3_TX_E12,  UART7_MAP3_RX_E13);//���ߵȼ۶�Ϊ�������ڳ�ʼ��  //  wireless_uart_init();
//          dl1a_init();
          dm1xa_init();              //������ȥ�ķ��Ͷ˳�ʼ��
//          imu660ra_init();             //imu660ra��ʼ��
          mt9v03x_init();                //��ʼ������ͷ
          pwm_init(S_MOTOR_PIN, 50, 750);//�����ʼ��
          Adc_init();                    //adc��ʼ��
          pit_ms_init(TIM3_PIT, 10);     //�����ʱ����ʼ��
          pit_ms_init(TIM6_PIT, 20);    //ADC����ƫ��ֵ��Ԫ��ʶ��������ƷŽ��ж�
          pit_ms_init(TIM7_PIT, 5);     //tofģ��
          gyroOffsetInit();             //��������Ư��ʼ��
//          ImagePerspective_Init();
          loc_pid_init(&speed_diff1,0.12,0,0.15,200,400);
          loc_pid_init(&speed_diff2,5,0,2,100,150);
          loc_pid_init(&left_pid,2,0,2,500,100);
          loc_pid_init(&right_pid,2,0,2,500,100);
          tft180_show_int(120,108,17,4);

    // �˴���д�û����� ���������ʼ�������
          flag_go=1;                    //�󳵸ո�����
        while(1)
        {
//               tft180_show_int(64,108,car_distance,4);
            // �˴���д��Ҫѭ��ִ�еĴ���
                    if(mt9v03x_finish_flag)
                    {

//                         sendimg(mt9v03x_image[0], 160, 60);
                           communicate();
                     //   ad0=adc_mean_filter_convert(ADC1_IN15_C5, 10);
                      //   tft180_show_gray_image(0,0,mt9v03x_image[0], MT9V03X_W,MT9V03X_H ,MT9V03X_W,MT9V03X_H,99);


                   //      erzhihua();
                  //         find_avebianjie();�����������ұ߽�ѭ������ֵ
                  //       main_check();//������ж�
                   //      add_line();//���߲���
//                         dm1xa_receiver_ranging();
            //             get_distance();
                           receive_data1();
                           receive_data2();

            //             *findCenterLine( *mt9v03x_image[MT9V03X_W]);
            //--------------����1.����������ͨ����ͱ��������ƣ����㲢�õ�����
//                           image_boundary_process();
//                           black_check();
//                           show_line();

//                           zhongxian_xunji();
            //-------------------------------------------------
             //              image_process();         //����2.������Ѱ��
            //-------------------------------------------------
                 //         motor_control1();
                    //        main_control();
//                             main_check();
                  //        sent_image();//ͼ����
            //
            //              for(int i=0;i<RESULT_ROW;i++)//��͸�Ӽ������
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


                  //      getmidline();           //ͨ����ֵ���������ߣ����߿ɽ���ʹ��
                           if(flag_go==2&&!flag_status)
                           {
                           get_cardistance();
                           car_distance_control();
                           }
                  //      left_xunji();
                  //      right_xunji();
                  //      zhongxian_xunji();
                           lcd_show();//����������ʾ������ʼ��
                          mt9v03x_finish_flag = 0;
                    }
                    // �˴���д��Ҫѭ��ִ�еĴ���
                }
    }
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
//
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ��������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
//
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
//
// ����3��������� DM1RA init error.
//      ��� DM1RA �Ľ����Ƿ���ȷ�Ƿ��ɶ�
//      ��� DM1RA ��ģ���ǲ��ǻ���
//
// ����4��DM1RA ��ֵ�쳣 ��ʾ 6800
//      ȷ�� DM1TA ���ӽӺò����غó�������������
//      �� DM1TA �� DM1RA ģ����� �м����ڵ�
//      ��������ģ���Ƿ����������� DM1TA �������ƾ�ȥ��� DM1TA ��� DM1RA �������ƾ���ϵ�ͷ�
