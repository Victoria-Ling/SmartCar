#include "Myfile.h"

//编码器采集回来的数值
int16 templ_pluse = 0;
int16 tempr_pluse = 0;
uint8 lost_flag = 0;

//期望速度
int exp_speed_r = 0, exp_speed_l = 0;
int base = 125;
int base_straight = 130, base_bend = 150, base_loop = 150, base_ramp = 100, base_hengduan = 150, base_ku = 180;

//期望与实际的误差
float L_err[3] = {0, 0, 0};
float R_err[3] = {0, 0, 0};

//电机pid参数
float KP_L = 125, KD_L = 0, KI_L = 20;
float KP_R = 125, KD_R = 0, KI_R = 20;

//电机输出占空比
int32 L_duty = 0, R_duty = 0;
int16 L_sum = 0;
int16 R_sum = 0;
int flag_0 = 0;

//实际速度
int16 L_speed = 0, R_speed = 0;

//实际路程
float road_L = 0, road_R = 0, road_sum = 0;

/*******************************************************************************
 * 函 数 名       :motor_control()
 * 函数功能        : 电机驱动函数
 * 输    入       : 无
 * 输    出        : 无
 *******************************************************************************/
void motor_control(void)
{
        if (L_duty > 0)
        {
            gpio_set_level(D12, 0);
            pwm_set_duty(TIM4_PWM_MAP1_CH2_D13, L_duty);
        }
        else if (L_duty < 0)
        {
            gpio_set_level(D12, 1);
            pwm_set_duty(TIM4_PWM_MAP1_CH2_D13, -L_duty);
        }
        if (R_duty > 0)
        {
            gpio_set_level(D15, 0);
            pwm_set_duty(TIM4_PWM_MAP1_CH3_D14, R_duty);
        }
        else if (R_duty < 0)
        {
            gpio_set_level(D15, 1);
            pwm_set_duty(TIM4_PWM_MAP1_CH3_D14, -R_duty);
        }
}

/*******************************************************************************
 * 函 数 名       :encode()
 * 函数功能          : 编码器测速函数
 * 输    入       : 无
 * 输    出        : 无
 *******************************************************************************/
void encode(void)
{
    templ_pluse = encoder_get_count(TIM1_ENCOEDER);
    tempr_pluse = encoder_get_count(TIM9_ENCOEDER);

    if(D12 == 1)        templ_pluse = -templ_pluse;
    if(D15 == 1)        tempr_pluse = -tempr_pluse;

    L_speed = templ_pluse; //左轮速度
    R_speed = tempr_pluse; //右轮速度

    //计数器清零
    encoder_clear_count(TIM1_ENCOEDER);
    encoder_clear_count(TIM9_ENCOEDER);

    road_L += (L_speed * 0.201f) / 2250;
    road_R += (R_speed * 0.201f) / 2250;;
    road_sum = (road_R - road_L) / 2;
}

/*******************************************************************************
 * 函 数 名       :motor_CHA()
 * 函数功能        :差速
 * 输    入       : 无
 * 输    出        : 无
 *******************************************************************************/
void different_chaspeed(void)
{
        exp_speed_l = -base;
        exp_speed_r = base;

        //直道差速
        if (space_flag == 1)
        {
            if (Error_angle_out > 0)
            {
                exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.005f) + 0.8f);
                exp_speed_r = base + (int16)(Error_angle_out * 0.1f);
            }
            if (Error_angle_out < 0)
            {
                exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.005f) + 0.8f);
                exp_speed_l = - (base + (int16)(Error_angle_out * 0.1f));
            }
        }

        //弯道差速
        if(space_flag != 1 && out_ku != 0)
        {
            if (Error_angle_out > 0)
            {
                exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.006f) + 0.80f);
                exp_speed_r = base + Error_angle_out * 0.15f;
            }
            if (Error_angle_out < 0)
            {
                exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.006f) + 0.80f);
                exp_speed_l = -(base + Error_angle_out * 0.15f);
            }
        }

        //出库差速
        if(out_ku == 0)
        {
            if (Error_angle_out > 0)
            {
                exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.008f) + 0.68f);
                exp_speed_l = -(base);
            }
            if (Error_angle_out < 0)
            {
                exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.008f) + 0.68f);
                exp_speed_l = -(base);
            }
        }
}

/*******************************************************************************
 * 函 数 名       :motor_pid()
 * 函数功能      : 电机pid函数
 * 输    入       : 无
 * 输    出        : 无
 *******************************************************************************/
void motor_pid(void)
{
        if (MAD <= 30 && QLAD <= 30 && QRAD <= 30 && inku == 0 && out_ku != 0 && space_flag != 3) //出赛道保护
            lost_flag = 1;
        else
            lost_flag = 0;

        if (lost_flag == 0)
        {
            different_chaspeed();
        }
        else
        {
            base = 0;
            exp_speed_r = 0;
            exp_speed_l = 0;
        }

        //右轮误差
        L_err[2] = L_err[1];
        L_err[1] = L_err[0];
        L_err[0] = exp_speed_l - L_speed;
        //右轮误差累计
        L_sum += L_err[0];

        //左轮误差
        R_err[2] = R_err[1];
        R_err[1] = R_err[0];
        R_err[0] = exp_speed_r - R_speed;
        //左轮误差累计
        R_sum += R_err[0];
        //右轮限幅
        if (L_sum > A) // L_sum>1000 L_sum=1000
            L_sum = A;
        if (L_sum < -A)
            L_sum = -A;
        //左轮限幅
        if (R_sum > A) // L_sum>1000 L_sum=1000
            R_sum = A;
        if (R_sum < -A)
            R_sum = -A;

        L_duty = (int32)(KP_L * L_err[0] + KI_L * L_sum + KD_L * (L_err[0] - L_err[1]));
        R_duty = (int32)(KP_R * R_err[0] + KI_R * R_sum + KD_R * (R_err[0] - R_err[1]));

        if (L_duty > C)
            L_duty = C;
        if (L_duty < -C)
            L_duty = -C;

        if (R_duty > C)
            R_duty = C;
        if (R_duty < -C)
            R_duty = -C;
}
