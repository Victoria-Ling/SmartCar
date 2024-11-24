#ifndef SEROR_H_
#define SEROR_H_
//
void ZW_judge(void);
void S3010_Direation_Control(void);
void caculation(void);
void Circular_zuo(void);
void Circular_syou(void);
void Circular(void);
float Fuzzy_P(float E, float EC);
float Fuzzy_D(float E, float EC);
void Out_storage(void);
void In_ku(void);
void Position_Jud(void);

extern int16 S3010_mid, S3010_Left_Max, S3010_Right_Max;
extern uint8 space_flag;
extern int Island_time, chuku_time, ruku_time;
extern int8 Island_Left, Island_Right;
extern float Error, Error_last;
extern float Error_angle_out;
extern float kp, kd;
extern float ruhuan_p, ruhuan_d;
extern float huanz_p, huanz_d;
extern float chuhuan_p, chuhuan_d;
extern int8 hengduan;
extern uint8 out_ku, out_garage;
extern uint8 inku;
extern float ad_referens, spaceflag;
extern int16 b;
extern short a;
extern float zhidao_p, zhidao_d;
extern int8 library;
extern uint8 out_ku;
extern int SL_In_xishu, SL_Out_xishu, BL_In_xishu, BL_Out_xishu;
extern int SR_In_xishu, SR_Out_xishu, BR_In_xishu, BR_Out_xishu;
extern float error_xie, error_shu;
extern float rp;
extern float Difference_error, error_value, error_value_old;
extern int16 yaw_angle;
extern float road_temp;
extern int16 charge_time;

#endif
