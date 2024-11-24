/*
 * camera.h
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */

#ifndef CAMERA_H_
#define CAMERA_H_



#include "zf_common_headfile.h"
#define ImageUsed   *PerImg_ip//*PerImg_ip定义使用的图像，ImageUsed为用于巡线和识别的图像

#define SAR_TH 60
typedef unsigned char       uint8_t;                                              // 无符号  8 bits

//extern uint8_t *PerImg_ip[RESULT_ROW][RESULT_COL];

extern int th;
extern int16 leftedge[MT9V03X_H];      //左边界j值数组，0表示左边界丢失
extern int16 rightedge[MT9V03X_H];     //右边界j值数组，MT9V03X_W-1表示右边界丢失
extern int16 midline[MT9V03X_H];    //中心线数组
extern int16 Light_X;
extern int16 Light_Y;
extern int16 reverse_perspective_switch;
void seek_light_error(void);
//void ImagePerspective_Init(void);
float abs_f(float x);
void row_boundary_process(int pos_x, int pos_y);
void image_boundary_process(void);
void endline_judge(void);
void getmidline(void);
void erzhihua (void);
void show_line(void);//将中线与边界线在显示的图像中描黑
void Cam_error(void);//偏差加权计算

void Pespective(int pts_in[][2], int num, int pts_out[][2], int num_out);

uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);
void Get_image(uint8(*mt9v03x_image)[MT9V03X_W]);
void turn_to_bin(void);
void image_process(void);
void image_draw_rectan(uint8(*image)[MT9V03X_W]);
void search_l_r(uint16 break_flag, uint8(*image)[MT9V03X_W], uint16 *l_stastic, uint16 *r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8*hightest);
short GetOSTU ();
int my_abs(int value);
int16 limit_a_b(int16 x, int a, int b);
int16 limit1(int16 x, int16 y);

#endif /* CAMERA_H_ */
