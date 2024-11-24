#include "Myfile.h"

void all_init(void)
{
    //电感初始化
    adc_init(ADC1_IN15_C5, ADC_10BIT);
    adc_init(ADC1_IN14_C4, ADC_10BIT);
    adc_init(ADC1_IN13_C3, ADC_10BIT);
    adc_init(ADC1_IN12_C2, ADC_10BIT);
    adc_init(ADC1_IN9_B1, ADC_10BIT);
    adc_init(ADC1_IN0_A0, ADC_10BIT);
    adc_init(ADC1_IN7_A7, ADC_10BIT);

    //按键初始化
    gpio_init(C7, GPO, 0, GPO_PUSH_PULL);
    gpio_init(A8, GPO, 0, GPO_PUSH_PULL);
    gpio_init(B0, GPO, 1, GPO_PUSH_PULL);
    gpio_init(B12, GPI, 0, GPI_PULL_DOWN);
    gpio_init(D8, GPI, 0, GPI_PULL_DOWN);
    gpio_init(C6, GPI, 0, GPI_PULL_DOWN);

    //蜂鸣器初始化
    gpio_init(C13, GPO, 0, GPO_PUSH_PULL);

    //Tof初始化
    dl1a_init();

    //有来有去的发送端初始化
    dm1xa_init();

    //imu660ra初始化
    imu660ra_init();
    gyro_Offset_Init();

    //摄像头初始化
    mt9v03x_init();

    //舵机初始化
    pwm_init(TIM2_PWM_MAP3_CH1_A15, 50, 750);

    //电机初始化
    gpio_init(D15, GPO, 0, GPO_PUSH_PULL);
    gpio_init(D12, GPO, 1, GPO_PUSH_PULL);
    pwm_init(TIM4_PWM_MAP1_CH2_D13, 17000, 0);
    pwm_init(TIM4_PWM_MAP1_CH3_D14, 17000, 0);

    //编码器初始化
    encoder_dir_init(TIM1_ENCOEDER,  TIM1_ENCOEDER_MAP3_CH1_E9, TIM1_ENCOEDER_MAP3_CH2_E11);
    encoder_dir_init(TIM9_ENCOEDER, TIM9_ENCOEDER_MAP3_CH1_D9, TIM9_ENCOEDER_MAP3_CH2_D11);

    //蓝牙、串口初始化
    uart_init(UART_4, 115200, UART4_MAP3_TX_E0, UART4_MAP3_RX_E1);
    uart_init(UART_7, 115200, UART7_MAP3_TX_E12, UART7_MAP3_RX_E13);

    //屏幕初始化
    tft180_set_dir(TFT180_CROSSWISE_180);       //横屏
//    tft180_set_font(TFT180_6X8_FONT);
    tft180_init();

    //定时器初始化
    pit_ms_init(TIM3_PIT, 5);

}
