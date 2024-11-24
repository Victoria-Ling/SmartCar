/*
 * key.h
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */

#ifndef KEY_H_
#define KEY_H_

#include "zf_common_headfile.h"
#include "zf_device_dl1a.h"
extern int time;
#define ls0(a)      tft180_show_int(120,3,a,4)
#define ls1(a)      tft180_show_int(120,18,a,4)
#define ls2(a)      tft180_show_int(120,33,a,4)
#define ls3(a)      tft180_show_int(120,48,a,4)
#define ls4(a)      tft180_show_int(120,63,a,4)
#define ls5(a)      tft180_show_int(120,78,a,4)
#define ls6(a)      tft180_show_int(120,93,a,4)
#define ls7(a)      tft180_show_int(120,108,a,4)


#define yf2h0_nc  {tft180_show_string(16, 3,"sar_th");ls0(SAR_TH);}//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define yf2h1_nc  {tft180_show_string(16, 18,"th");ls1(th);}
#define yf2h2_nc  {tft180_show_string(16, 33,"Cam_Kp");ls2(Cam_Servo_Kp);}
#define yf2h3_nc  {tft180_show_string(16, 48, "Cam_Kd");ls3(Cam_Servo_Kd);}
#define yf2h4_nc  {tft180_show_string(16, 63, "left_pid.kp");ls4(left_pid.kp);}
#define yf2h5_nc  {tft180_show_string(16, 78, "left_pid.kd");ls5(left_pid.kd);}
#define yf2h6_nc  {tft180_show_string(16, 93, "right_pid.kp");ls6(right_pid.kp);}
#define yf2h7_nc  {tft180_show_string(16, 108, "right_pid.kd");ls7(right_pid.kd);}

#define yf2h0_c  //页(ye)-1 高度（high）0  (实时刷新)(change)少用，占内存
#define yf2h1_c
#define yf2h2_c
#define yf2h3_c
#define yf2h4_c
#define yf2h5_c
#define yf2h6_c
#define yf2h7_c

#define opr_yf2h0_add SAR_TH+=1  //按下按键时执行的操作 (oprate ye f2 high0)
#define opr_yf2h1_add th+=1
#define opr_yf2h2_add Cam_Servo_Kp+=1
#define opr_yf2h3_add Cam_Servo_Kd+=1
#define opr_yf2h4_add left_pid.kp+=1
#define opr_yf2h5_add left_pid.kd+=1
#define opr_yf2h6_add right_pid.kp+=1
#define opr_yf2h7_add right_pid.kd+=1

#define opr_yf2h0_cut SAR_TH-=1  //按下按键时执行的操作 (oprate ye f2 high0)
#define opr_yf2h1_cut th-=1
#define opr_yf2h2_cut Cam_Servo_Kp-=1
#define opr_yf2h3_cut Cam_Servo_Kd-=1
#define opr_yf2h4_cut left_pid.kp-=1
#define opr_yf2h5_cut left_pid.kd-=1
#define opr_yf2h6_cut right_pid.kp-=1
#define opr_yf2h7_cut right_pid.kd-=1


#define yf1h0_nc  tft180_show_string(8, 0 ,"page -1");ls0(-1);//页(ye)-1 高度（high）0  (只是按下时按键刷新)(no change)
#define yf1h1_nc  tft180_show_string(16, 15,"speed_def");ls1(speed_define);
#define yf1h2_nc  tft180_show_string(16, 31,"plus_th");ls2(plus_th);
#define yf1h3_nc  tft180_show_string(16, 46, "adc_kp");ls3(adc_kp);//显示实际的速度
#define yf1h4_nc  tft180_show_string(16, 61, "adc_kd");ls4(adc_kd);
#define yf1h5_nc  tft180_show_string(16, 76, "flag_hd");ls5(flag_hd);
#define yf1h6_nc  tft180_show_string(16, 92, "ski");ls6(ski);
#define yf1h7_nc  tft180_show_string(16, 108, "skp");ls7(skp);

#define yf1h0_c  //页(ye)-1 高度（high）0  (实时刷新)(no change)
#define yf1h1_c  ls1(speed_define);
#define yf1h2_c  ls2(plus_th)
#define yf1h3_c  ls3(adc_kp);
#define yf1h4_c  ls4(adc_kd);
#define yf1h5_c  ls5(flag_hd);
#define yf1h6_c
#define yf1h7_c

#define opr_yf1h0_add time-=1000  //按下按键时执行的操作 (oprate ye fu1 high0)
#define opr_yf1h1_add speed_define+=10
#define opr_yf1h2_add plus_th+=10
#define opr_yf1h3_add adc_kp+=1
#define opr_yf1h4_add adc_kd+=1
#define opr_yf1h5_add
#define opr_yf1h6_add ski+=1
#define opr_yf1h7_add skp+=1

#define opr_yf1h0_cut time-=1000  //按下按键w时执行的操作 (oprate ye fu1 high0)
#define opr_yf1h1_cut speed_define-=10
#define opr_yf1h2_cut plus_th-=10
#define opr_yf1h3_cut adc_kp-=1
#define opr_yf1h4_cut adc_kd-=1
#define opr_yf1h5_cut
#define opr_yf1h6_cut ski-=1
#define opr_yf1h7_cut skp-=1


#define y0h0_nc  {tft180_show_string(16, 0,"Kp_sum");ls0(Kp_sum);}//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y0h1_nc  {tft180_show_string(16, 15,"speed1");ls1(speed1_show);}
#define y0h2_nc  {tft180_show_string(16, 31,"speed2");ls2(speed2_show);}
#define y0h3_nc  {tft180_show_string(16, 46,"set_s_r");ls3(set_speed_right);}
#define y0h4_nc  {tft180_show_string(16, 61,"set_s_l");ls4(set_speed_left);}
#define y0h5_nc  {tft180_show_string(16, 76,"motor_right");ls5(motor_right);}
#define y0h6_nc  {tft180_show_string(16, 92,"motor_left");ls6(motor_left);}
#define y0h7_nc  {tft180_show_string(16, 108,"Kd_sum");ls7(Kd_sum);}

#define y0h0_c   ls0(Kp_sum)//页(ye)-1 高度（high）0  (实时刷新)(change)
#define y0h1_c   ls1(speed1_show)
#define y0h2_c   ls2(speed2_show)
#define y0h3_c   ls3(set_speed_right)
#define y0h4_c   ls4(set_speed_left)
#define y0h5_c   ls5(motor_right)
#define y0h6_c   ls6(motor_left)
#define y0h7_c   ls7(Kd_sum)

#define opr_y0h0_add  //time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y0h1_add
#define opr_y0h2_add
#define opr_y0h3_add set_speed_right+=50
#define opr_y0h4_add set_speed_left+=50
#define opr_y0h5_add
#define opr_y0h6_add
#define opr_y0h7_add

#define opr_y0h0_cut  //time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y0h1_cut
#define opr_y0h2_cut
#define opr_y0h3_cut set_speed_right-=50
#define opr_y0h4_cut set_speed_left-=50
#define opr_y0h5_cut
#define opr_y0h6_cut
#define opr_y0h7_cut


#define y1h0_nc  tft180_show_string(16, 0,"daoche_pid");ls0(daoche_pid.error);//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y1h1_nc  tft180_show_string(16, 15,"adc_error");ls1(adc_error);
#define y1h2_nc  tft180_show_string(16, 31,"distance");ls2(distance);
#define y1h3_nc  tft180_show_string(16, 46,"Servo_add");ls3(Cam_Servo_add);
#define y1h4_nc  tft180_show_string(16, 61,"yaw1");ls4(yaw1);
#define y1h5_nc  tft180_show_string(16, 76,"pitch");ls5(pitch);
#define y1h6_nc  tft180_show_string(16, 92,"roll");ls6(roll);
#define y1h7_nc  tft180_show_string(16, 108,"yaw1_obstacle");ls7(yaw1_obstacle);

#define y1h0_c  ls0(daoche_pid.error)//页(ye)-1 高度（high）0  (实时刷新)(change)
#define y1h1_c  ls1(adc_error)
#define y1h2_c  ls2(distance)
#define y1h3_c  ls3(Cam_Servo_add)
#define y1h4_c  ls4(yaw1)
#define y1h5_c  ls5(pitch)
#define y1h6_c  ls6(roll)
#define y1h7_c  ls7(yaw1_obstacle)

#define opr_y1h0_add //time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y1h1_add
#define opr_y1h2_add
#define opr_y1h3_add
#define opr_y1h4_add
#define opr_y1h5_add
#define opr_y1h6_add
#define opr_y1h7_add

#define opr_y1h0_cut //time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y1h1_cut
#define opr_y1h2_cut
#define opr_y1h3_cut
#define opr_y1h4_cut
#define opr_y1h5_cut
#define opr_y1h6_cut
#define opr_y1h7_cut


#define y2h0_nc  tft180_show_string(16, 0,"ad4");ls0(ad4);//页（ye）0 高度（high）0  不变(即只是按下按键刷新(no change)
#define y2h1_nc  tft180_show_string(16, 15,"ad3");ls1(ad3);
#define y2h2_nc  tft180_show_string(16, 31,"rightedge[45]");ls2(rightedge[45]);
#define y2h3_nc  tft180_show_string(16, 46, "leftedge[45]");ls3(leftedge[45]);
#define y2h4_nc  tft180_show_string(16, 61, "midline[45]");ls4(midline[45]);
#define y2h5_nc  tft180_show_string(16, 76, "ad2");ls5(ad2);
#define y2h6_nc  tft180_show_string(16, 92, "ad1");ls6(ad1);
#define y2h7_nc  tft180_show_string(16, 108, "ad0");ls7(ad0);

#define y2h0_c  ls0(ad4)//页(ye)-1 高度（high）0  (实时刷新)(no change)
#define y2h1_c  ls1(ad3)
#define y2h2_c  ls2(rightedge[45]);
#define y2h3_c  ls3(leftedge[45]);
#define y2h4_c  ls4(midline[45])
#define y2h5_c  ls5(ad2)
#define y2h6_c  ls6(ad1)
#define y2h7_c  ls7(ad0)

#define opr_y2h0_add time-=1000  //按下按键时执行的操作 (oprate ye0 high0)
#define opr_y2h1_add
#define opr_y2h2_add
#define opr_y2h3_add
#define opr_y2h4_add th+=1
#define opr_y2h5_add
#define opr_y2h6_add
#define opr_y2h7_add
#define opr_y2h8_add
#define opr_y2h9_add
#define opr_y2h0_cut
#define opr_y2h1_cut
#define opr_y2h2_cut
#define opr_y2h3_cut
#define opr_y2h4_cut th-=1
#define opr_y2h5_cut
#define opr_y2h6_cut
#define opr_y2h7_cut


#define read_key1 gpio_get_level(B12)//读取按键io电平
#define read_key2 gpio_get_level(D8)
#define read_key3 gpio_get_level(C6)
//#define read_key4 gpio_get_level(A8)
#define set_key1 gpio_set_level(C7,1)//设置按键io电平为高
#define set_key2 gpio_set_level(A8,1)
#define set_key3 gpio_set_level(B0,1)
//#define set_key4 gpio_set_level(B12,1)
#define reset_key1 gpio_set_level(C7,0)//设置按键io电平为低
#define reset_key2 gpio_set_level(A8,0)
#define reset_key3 gpio_set_level(B0,0)
//#define reset_key4 gpio_set_level(B12,0)
int key_scan1(void);
int key_scan2(void);
int key_scan3(int i);
extern int flag_test,flag_tc;
extern int a1;
extern float k1;
void lcd_show(void);
void key_init0(void);



#endif /* KEY_H_ */
