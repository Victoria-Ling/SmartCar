/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"


// �������� ��ȥģ�飨�� MCU �汾 DM1TA�� ��ʹ������ �����̽���ʾ���ʹ�� DM1TA ���в���źŷ��� �����̲���ʾ����
// �������� ��ȥģ�飨�� MCU �汾 DM1TA�� ��ʹ������ �����̽���ʾ���ʹ�� DM1TA ���в���źŷ��� �����̲���ʾ����
// �������� ��ȥģ�飨�� MCU �汾 DM1TA�� ��ʹ������ �����̽���ʾ���ʹ�� DM1TA ���в���źŷ��� �����̲���ʾ����


// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ���������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
//
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� B10
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� B11
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ
//
// ���� DM1TA ģ��
//      ģ��ܽ�            ��Ƭ���ܽ�
//      FB                  �鿴 zf_device_dm1xa.h �� DM1XA_FB_PIN  �궨�� Ĭ�� E15
//      EN                  �鿴 zf_device_dm1xa.h �� DM1XA_EN_PIN  �궨�� Ĭ�� E14
//      VCC                 5V ��Դ
//      GND                 ��Դ��


// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ�����
//
// 2.�ڶϵ�����£�����ʹ�ú��İ���������������� USB-TTL ģ�����ӣ������Ӻ� DM1TA ģ��
//      ( ���ʹ�����׵�ѧϰ������ԣ���ֱ�ӽ� DM1TA ģ��ӵ���Ӧ�Ľӿ�λ�� )
//
// 3.ʹ�� Type-C �����İ幩�磬���������������� USB-TTL ģ�����ӵ�����
//      ( ���ʹ�����׵�ѧϰ������ԣ�����Ҫֱ��ʹ�õ�ع��磬2S﮵��/����ص�ѹ��Ӧ����7.8V��3S﮵�ص�ѹ��Ӧ����11.3V )
//
// 4.DM1TA ģ�������ƻ�����ȳ�����50Hz��˸ �̵���ʱ�� ���������ǵ����ȳ�����
//
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


// **************************** �������� ****************************
#define LED1                    (E9 )
#define S_MOTOR_PIN    (TIM2_PWM_MAP3_CH1_A15)      //����������


long int speed1,speed2;//�����ҵ�����ٶȣ���Ҫ�ɱ����������Ժ������
//int show[60][160];
int mode_flag=0;
int16 send_speed=0;
int16 speed1_show,speed2_show;
float distance;//�ϰ�����


uint16 pit_ms_count = 0;

int main (void)
{
       clock_init(SYSTEM_CLOCK_144M);                                              // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz
        debug_init();                                                               // ��ʼ��Ĭ�� Debug UART

    // �˴���д�û����� ���������ʼ�������

       tft180_set_dir(TFT180_CROSSWISE_180);                                           // ��Ҫ�Ⱥ��� ��Ȼ��ʾ����
       tft180_init();
       tft180_show_int(120,108,17,4);
       gpio_init(D12, GPO, 0, GPO_PUSH_PULL);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
       pwm_init(PWM_CH2, 17000, 0);                                             // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
       pwm_init(PWM_CH4, 17000, 0);                                      // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
       gpio_init(D14, GPO, 0, GPO_PUSH_PULL);
       encoder_dir_init(TIM1_ENCOEDER,  TIM1_ENCOEDER_MAP3_CH1_E9,  TIM1_ENCOEDER_MAP3_CH2_E11);
       encoder_dir_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);
                                           //����������ʼ��
       gpio_init(C7, GPO, 0, GPO_PUSH_PULL);
       gpio_init(A8, GPO, 0, GPO_PUSH_PULL);
       gpio_init(B0, GPO, 0, GPO_PUSH_PULL);
       gpio_init(B12, GPI, 0, GPI_PULL_DOWN);
       gpio_init(D8, GPI, 0, GPI_PULL_DOWN);
       gpio_init(C6, GPI, 0, GPI_PULL_DOWN);


       gpio_init(C13, GPO, 0, GPO_PUSH_PULL);//������

     uart_init(UART_4, 115200, UART4_MAP3_TX_E0, UART4_MAP3_RX_E1);


      // wireless_uart_init();//    ���ߵȼ۶�Ϊ�������ڳ�ʼ��
       uart_init(UART_7, 115200, UART7_MAP3_TX_E12,  UART7_MAP3_RX_E13);
       dm1xa_init();                     //������ȥ�ķ��Ͷ˳�ʼ��
       dl1a_init();
       imu660ra_init();                //icm20602��ʼ��
       mt9v03x_init();                //��ʼ������ͷ
       pwm_init(S_MOTOR_PIN, 50, 735);//�����ʼ��
       Adc_init();                  //adc��ʼ��
       pit_ms_init(TIM3_PIT, 10);  //�����ʱ����ʼ��
       pit_ms_init(TIM6_PIT, 20); //ADC����ƫ��ֵ��Ԫ��ʶ��������ƷŽ��ж�
       pit_ms_init(TIM7_PIT, 5); //tofģ��

       gyroOffsetInit();        //��������Ư��ʼ��
//          ImagePerspective_Init();
       loc_pid_init(&left_pid,2.5,0,2,500,100);
       loc_pid_init(&right_pid,2.5,0,2,500,100);
       loc_pid_init(&daoche_pid,5,0,9,500,500);
       send_speed=1;
//    interrupt_global_enable(0);
    // �˴���д�û����� ���������ʼ�������

        while(1)

        {
        // �˴���д��Ҫѭ��ִ�еĴ���
               if(mt9v03x_finish_flag)
               {

             //       printf("%d,%d\n",Kp_sum,Kd_sum);
//                    sendimg(mt9v03x_image[0], 160, 60);
                //  sent_data3(Cam_Servo_add,averight,speed1,speed2,set_speed_left,Cam_Servo_add);
                //   ad0=adc_mean_filter_convert(ADC1_IN15_C5, 10);
                 //   tft180_show_gray_image(0,0,mt9v03x_image[0], MT9V03X_W,MT9V03X_H ,MT9V03X_W,MT9V03X_H,0);
              //      erzhihua();
             //       find_avebianjie();�����������ұ߽�ѭ������ֵ
             //       main_check();//������ж�
              //      add_line();//���߲���
                      communicate();
                      receive_data1();
                      receive_data2();
       //--------------����1.����������ͨ����ͱ��������ƣ����㲢�õ�����
                       image_boundary_process();
//                       black_check();
                       show_line();
                       lcd_show();
       //-------------------------------------------------
       //               image_process();         //����2.������Ѱ��
        //              image_boundry_rec(MT9V03X_H,MT9V03X_W);

       //-------------------------------------------------
            //         motor_control1();
               //        main_control();

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


             //      left_xunji();
             //      right_xunji();
             //      zhongxian_xunji();
                     mt9v03x_finish_flag = 0;
               }
               // �˴���д��Ҫѭ��ִ�еĴ���
        }

}

//-------------------------------------------------------------------------------------------------------------------
// �������     PIT ���жϴ����� ����������� PIT ��Ӧ�Ķ�ʱ���жϵ��� ��� isr.c
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     pit_handler();
//-------------------------------------------------------------------------------------------------------------------
void pit_handler (void)
{
    if(0 == pit_ms_count % 20)                                                  // ÿ 20ms ����һ�β��
    {
        // ������Ƶ��Ӧ�� 50-100Hz ������ 10-20ms
        // ������Ƶ��Ӧ�� 50-100Hz ������ 10-20ms
        // ������Ƶ��Ӧ�� 50-100Hz ������ 10-20ms
        dm1xa_transmitter_ranging();
    }
    pit_ms_count = (pit_ms_count == 995) ? (0) : (pit_ms_count + 5);            // 1000ms ���ڼ���
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
