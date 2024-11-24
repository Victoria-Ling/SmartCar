#ifndef MOTOR_H_
#define MOTOR_H_

//累加值限幅
#define A (500)
//占空比限幅
#define C (6000)


void encode(void);
void motor_pid(void);
void motor_control(void);
void different_chaspeed(void);

extern int flag_0;
extern int base, base_bend, base_loop, base_straight, base_ramp, base_hengduan, base_ku;
extern int exp_speed_l, exp_speed_r;
extern uint8 lost_flag;
extern int16 templ_pluse, tempr_pluse;
extern float KP_L, KD_L, KI_L;
extern float KP_R, KD_R, KI_R;
extern int16 L_speed, R_speed;
extern int32 L_duty, R_duty;
extern float road_L, road_R, road_sum;

#endif
