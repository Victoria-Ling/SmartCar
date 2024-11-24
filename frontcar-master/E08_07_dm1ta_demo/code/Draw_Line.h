/*
 * Draw_Line.h
 *
 *  Created on: Apr 19, 2023
 *      Author: 86157
 */

#ifndef DRAW_LINE_H_
#define DRAW_LINE_H_
#include "zf_common_headfile.h"
typedef struct _array_
{
    int x;
    int y;
}ARRAY;
void LCD_Draw_Cross_Point(int point_x, int point_y, int color);
void Draw_Straight_Line(int *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x);
int Draw_Ray_Line(int *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x);
void Calculate_Boder_Line_Slope(int first_point_x, int first_point_y, int second_point_x, int second_point_y, ARRAY start_point, float *slope, float *intercept);
void Fixed_Middle_Line_With_Slope(float slope, float intercept, ARRAY start_point, int *output_x, int *output_y);
void LCD_Draw_Middle_Line(int stack_length, int color);
void LCD_Draw_Propect_Line(int propect_y, int color);
float Calculate_Slope(int16 first_point_x, int16 second_point_x,int16 first_point_y, int16 second_point_y);
void Fitting_Middle_Line_With_Border(int* middle_line, int first_x, int second_x, int first_y, int second_y, int start_x, int start_y, int *last_x, int *last_y);
float get_K(uint8 count , int16 dataCol_X[] , int16 dataRow_Y[]);
void Draw_Curve(uint8 *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x);
#endif /* DRAW_LINE_H_ */
