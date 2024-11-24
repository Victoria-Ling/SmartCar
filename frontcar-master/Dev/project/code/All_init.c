#include "Myfile.h"

void all_init(void)
{
    //��г�ʼ��
    adc_init(ADC1_IN15_C5, ADC_10BIT);
    adc_init(ADC1_IN14_C4, ADC_10BIT);
    adc_init(ADC1_IN13_C3, ADC_10BIT);
    adc_init(ADC1_IN12_C2, ADC_10BIT);
    adc_init(ADC1_IN9_B1, ADC_10BIT);
    adc_init(ADC1_IN0_A0, ADC_10BIT);
    adc_init(ADC1_IN7_A7, ADC_10BIT);

    //������ʼ��
    gpio_init(C7, GPO, 0, GPO_PUSH_PULL);
    gpio_init(A8, GPO, 0, GPO_PUSH_PULL);
    gpio_init(B0, GPO, 1, GPO_PUSH_PULL);
    gpio_init(B12, GPI, 0, GPI_PULL_DOWN);
    gpio_init(D8, GPI, 0, GPI_PULL_DOWN);
    gpio_init(C6, GPI, 0, GPI_PULL_DOWN);

    //��������ʼ��
    gpio_init(C13, GPO, 0, GPO_PUSH_PULL);

    //Tof��ʼ��
    dl1a_init();

    //������ȥ�ķ��Ͷ˳�ʼ��
    dm1xa_init();

    //imu660ra��ʼ��
    imu660ra_init();
    gyro_Offset_Init();

    //����ͷ��ʼ��
    mt9v03x_init();

    //�����ʼ��
    pwm_init(TIM2_PWM_MAP3_CH1_A15, 50, 750);

    //�����ʼ��
    gpio_init(D15, GPO, 0, GPO_PUSH_PULL);
    gpio_init(D12, GPO, 1, GPO_PUSH_PULL);
    pwm_init(TIM4_PWM_MAP1_CH2_D13, 17000, 0);
    pwm_init(TIM4_PWM_MAP1_CH3_D14, 17000, 0);

    //��������ʼ��
    encoder_dir_init(TIM1_ENCOEDER,  TIM1_ENCOEDER_MAP3_CH1_E9, TIM1_ENCOEDER_MAP3_CH2_E11);
    encoder_dir_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);

    //���������ڳ�ʼ��
    uart_init(UART_4, 115200, UART4_MAP3_TX_E0, UART4_MAP3_RX_E1);
    uart_init(UART_7, 115200, UART7_MAP3_TX_E12, UART7_MAP3_RX_E13);

    //��Ļ��ʼ��
    tft180_set_dir(TFT180_CROSSWISE_180);       //����
//    tft180_set_font(TFT180_6X8_FONT);
    tft180_init();

    //��ʱ����ʼ��
    pit_ms_init(TIM3_PIT, 5);

}
