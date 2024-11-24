/*
 * element_discover.h
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */

#ifndef ELEMENT_DISCOVER_H_
#define ELEMENT_DISCOVER_H_

#include "zf_common_headfile.h"
extern int flag_status;
extern int flag_go;
extern int flag_zebra,flag_zebra_time;
extern int zebra_time[5];
extern int hd_time[10];
extern int flag_hd_time;
extern int up_point,down_point;
extern int flag_lx;
extern int flag_status_time;
extern int flag_sc;
extern int flag_sz;
extern int flag_sz1;
extern int status_time[20],status_time1[20],status_time2[20];
//extern int yaw1,roll1;
extern int flag_pd;
extern int flag_stop;
extern long int speed_cut;
extern int flag_hd;
extern int r_sum;
extern int plus_th;
extern int cpH,cpW;


//#define update_yaw yaw1=yaw
//#define dif_yaw (int)(yaw-yaw1)
//#define update_roll roll1=roll
//#define dif_roll (int)(roll-roll1)

#define right 1
#define left 2
#define rightfok 3
#define leftfok 4
#define leftzebra 5
#define start 6
#define stop 7
#define rightzebra 8
#define shizi 9
#define poudao 10

#define right1 1
#define right2 2
#define right3 3
#define right4 4
#define right5 5
#define right6 6
#define right7 7
#define right8 8
#define right9 9
#define right10 10

#define left1 11
#define left2 12
#define left3 13
#define left4 14
#define left5 15
#define left6 16
#define left7 17
#define left8 18
#define left9 19
#define left10 20
#define rightfok1 1
#define rightfok2 2
#define rightfok3 3
#define rightfok4 4
#define rightfok5 5
#define leftfok1 11
#define leftfok2 12
#define leftfok3 13
#define leftfok4 14
#define leftfok5 15

#define shizi1 1
#define shizi2 2
#define shizi3 3
#define shizi4 4

#define ZEBRA1 1    //预识别斑马线
#define ZEBRA2 2 //第一次识别并进入斑马线状态
#define ZEBRA3 3    //第一次离开斑马线，第一圈完成6
#define ZEBRA4 4
#define szhh_speed_cut      speed_define-=0
#define szhh_speed_up       speed_define+=0

#define leftshizi1 101
#define rightshizi1 102



int cl_average(int a);
int rs_average(int a);
int ls_average(int a);
int ls_lost(int a);
int rs_lost(int a);
void huandao_check(void);
void sancha_check(void);
void garage_out(void);
void shizi_check(void);
void zebra_linedrawing(void);
int colorchange_check_row(int a);
int colorchange_check_col(int a);
void zebra_check(void);
void status_reset(void);
void add_line_left(int up_line1,int up_point1,int down_line1,int down_point1);
void add_line_right(int up_line2,int up_point2,int down_line2,int down_point2);
void add_line_left1(int up_line1,int up_point1,int down_line1,int down_point1);
void add_line_right1(int up_line2,int up_point2,int down_line2,int down_point2);
void poudao_check(void);
void main_check(void);
int get_line_min(int t);
int get_line_max(int t);
int colorchange_check_row(int a);
int colorchange_check_col(int a);
void zebra_linedrawing(void);
void obstacle_check(void);
void black_check(void);
#endif /* ELEMENT_DISCOVER_H_ */
