/*
 * Draw_Line.c
 *
 *  Created on: Apr 19, 2023
 *      Author: 86157
 */


#include "Draw_Line.h"

/*
 * @brief LCD屏幕上画十字交点
 * @param 点的横坐标
 * @param 点的纵坐标
 * @param 点的颜色
 * @notice一定要将图像的范围限制住,不然就会导致屏幕卡死
 * */
void LCD_Draw_Cross_Point(int point_x, int point_y, int color)
{
    if (point_x > 2 && point_x < 91 && point_y > 2 && point_y < 57)
    {
        for (int i = point_x-2; i <= point_x+2; i++)
        {
            tft180_draw_point(i,point_y,color);
        }
        for (int i = point_y-2; i <= point_y+2; i++)
        {
            tft180_draw_point(point_x,i,color);
        }
    }
}

/*
 * @brief 给输出图像画直线
 * @param 第一个点的横坐标
 * @param 第一个点的纵坐标
 * @param 第二个点的横坐标
 * @param 第二个点的纵坐标
 * @param 图像的宽度
 * @notice 第一个点和第二个点都会进行标黑
 * */
void Draw_Straight_Line(int *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x)
{
    int *ptd = imag_out;
    int dx = second_point_x - first_point_x;
    int dy = second_point_y - first_point_y;
    float K = (float)dx/dy;
    float b = first_point_x-K*first_point_y;
    int Y, supplementary_point, deviation;

    supplementary_point = first_point_x;
    *(ptd+first_point_x+Imag_x*first_point_y) = 0;
    for (int i = 1; i <= (-dy); i++)//根据Y的坐标去求x
    {
        Y = (int)((first_point_y-i)*K+b);

        //为了使得循边界的时候四邻域可以生长
        if (Y > supplementary_point)
        {
            deviation = Y - supplementary_point;
            for (int j = 0; j < deviation; j++)
            {
                *(ptd+(Y-j-1)+Imag_x*(first_point_y-i)) = 0;
            }
        }
        else
        {
            deviation = supplementary_point - Y;
            for (int j = 0; j < deviation; j++)
            {
                *(ptd+(Y+j+1)+Imag_x*(first_point_y-i)) = 0;
            }
        }

        *(ptd+Y+Imag_x*(first_point_y-i)) = 0;
        supplementary_point = Y;
    }
}

/*
 * @brief 给输出图像画射线
 * @param 输出图像地址
 * @param 第一个点的横坐标
 * @param 第一个点的纵坐标
 * @param 第二个点的横坐标
 * @param 第二个点的纵坐标
 * @param 图像的宽度
 * @notice 第一个点也会进行标黑
 * */
int Draw_Ray_Line(int *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x)
{
    int *ptd = imag_out;
    int temp_x, temp_y;
    int deviation;
    ARRAY start_point;
    float slope, intercept;

    start_point.x = first_point_x;
    start_point.y = first_point_y;
    *(ptd+first_point_x+first_point_y*Imag_x) = 0;
    Calculate_Boder_Line_Slope(first_point_x, first_point_y, second_point_x, second_point_y, start_point, &slope, &intercept);

    do{
        Fixed_Middle_Line_With_Slope(slope, intercept, start_point, &temp_x, &temp_y);
        if (temp_x < start_point.x)
        {
            deviation = start_point.x - temp_x;
            for (int i = 0; i < deviation; i++)
            {
                *(ptd+temp_x+i+1+temp_y*Imag_x) = 0;
            }
        }
        else
        {
            deviation = temp_x - start_point.x;
            for (int i = 0; i < deviation; i++)
            {
                *(ptd+temp_x-i-1+temp_y*Imag_x) = 0;
            }
        }
        *(ptd+temp_x+temp_y*Imag_x) = 0;
        start_point.x = temp_x;
        start_point.y = temp_y;
    }while(temp_y > 2);

    return temp_x;
}

/*
 * @brief 画出曲线
 * @param 输出图像地址
 * @param 第一个点的横坐标
 * @param 第一个点的纵坐标
 * @param 第二个点的横坐标
 * @param 第二个点的纵坐标
 * @param 整幅图像的横坐标
 * */
void Draw_Curve(uint8 *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x)
{
    float center_x, center_y;
    int dy = first_point_y - second_point_y;
    int temp_x, supplementary_point, deviation;
    int distance;

    //求出两点间的距离
    if (first_point_x < second_point_x)
    {
        distance = My_sqrt((first_point_y - second_point_y)*(first_point_y - second_point_y) + (second_point_x - first_point_x)*(second_point_x - first_point_x));
    }
    else
    {
        distance = My_sqrt((first_point_y - second_point_y)*(first_point_y - second_point_y) + (first_point_x - second_point_x)*(first_point_x - second_point_x));
    }


    //求出圆心坐标
    float c1 = (float)(second_point_x*second_point_x - first_point_x*first_point_x + second_point_y*second_point_y - first_point_y*first_point_y) / (2 *(second_point_x - first_point_x));
    float c2 = (float)(second_point_y - first_point_y) / (second_point_x - first_point_x);  //斜率
    float AA = (c2*c2 + 1);
    float BB = (2 * first_point_x*c2 - 2 * c1*c2 - 2 * first_point_y);
    float CC = first_point_x*first_point_x - 2 * first_point_x*c1 + c1*c1 + first_point_y*first_point_y - distance*distance;

    center_y = (-BB + My_sqrt(BB*BB - 4 * AA*CC)) /(float)(2 * AA);
    center_x = c1 - c2 * center_y;

    //带入圆的标准方程,求出每一个x
    *(imag_out+first_point_x+first_point_y*Imag_x) = 0;
    supplementary_point = first_point_x;
    for (int i = 1; i <= dy; i++)
    {
        temp_x = My_sqrt(distance*distance - (first_point_y-i-center_y)*(first_point_y-i-center_y))+center_x;
        if (temp_x < supplementary_point)
        {
            deviation = supplementary_point - temp_x;
            for (int j = 0; j <= deviation; j++)
            {
                *(imag_out+temp_x+j+(first_point_y-i)*Imag_x) = 0;
            }
        }
        else
        {
            deviation = temp_x - supplementary_point;
            for (int j = 0; j <= deviation; j++)
            {
                *(imag_out+temp_x-j+(first_point_y-i)*Imag_x) = 0;
            }
        }
        supplementary_point = temp_x;
    }
}

/*
 * @brief 计算一段直线的斜率
 * @param 第一个点的横坐标
 * @param 第一个点的纵坐标
 * @param 第二个点的横坐标
 * @param 第二个点的纵坐标
 * @param 求出的直线斜率
 * @param 求出的直线截距
 * */
void Calculate_Boder_Line_Slope(int first_point_x, int first_point_y, int second_point_x, int second_point_y, ARRAY start_point, float *slope, float *intercept)
{
    int dx = second_point_x - first_point_x;
    int dy = second_point_y - first_point_y;
    *slope = (float)dx/(float)dy;
    *intercept = start_point.x - (*slope)*start_point.y;
}

/*
 * @brief 根据直线斜率求出下一个点的坐标
 * @param 已知直线的斜率
 * @param 已知直线的截距
 * @param 已知点的坐标
 * @param 要求的点的横坐标
 * @param 要求的点的纵坐标
 * */
void Fixed_Middle_Line_With_Slope(float slope, float intercept, ARRAY start_point, int *output_x, int *output_y)
{
    *output_y = (start_point.y-1);
    *output_x = (int)(slope*(*output_y)+intercept);
}



/*
 * @brief 画出前瞻的中线
 * @param 前瞻线的纵坐标
 * @param 线的颜色
 * */
void LCD_Draw_Propect_Line(int propect_y, int color)
{
    for (int i = 20; i < 64; i++)
    {
        tft180_draw_point(i, propect_y, color);
    }
}

/*
 * @brief 计算直线的斜率
 * @param 第一个点的坐标
 * @param 第二个点的坐标
 * @return 该直线的斜率
 * */
float Calculate_Slope(int16 first_point_x, int16 second_point_x,int16 first_point_y, int16 second_point_y)
{
    int dx = second_point_x - first_point_x;
    int dy = second_point_y - first_point_y;
    float K = (float)dx / (float)dy;

    return K;
}

/*
 * @brief 根据边线斜率来拟合中线
 * @param 存放中线的数组
 * @param 第一个点的坐标
 * @param 第二个点的坐标
 * @param 拟合中线的起始点坐标
 * */
void Fitting_Middle_Line_With_Border(int* middle_line, int first_x, int second_x, int first_y, int second_y, int start_x, int start_y, int *last_x, int *last_y)
{
    int dx = second_x - first_x;
    int dy = second_y - first_y;
    float K = (float)dx / (float)dy;
    float b = start_x-K*start_y;
    int Y;

    *middle_line = start_x;
    for (int i = 1; i <= (-dy); i++)
    {
        Y = (int)((start_y-i)*K+b);
        *(middle_line+i) = Y;
    }
    *last_x = Y;
    *last_y = start_y+dy;
}

/*线性回归求斜率
*****注意数据类型
*参数   count         数据个数 数组行(列)的个数 数组的行列数目相等
*参数   dataCol_X[]   数据的列数据
*参数   dataRow_Y[]   数据的行数据
*返回值 k             斜率 范围(-∞,∞)
*本算法定义斜率为 ∞ 的情况 k = 0;
*使用注意 需要重定义数据类型
*typedef unsigned char  uint8;
*typedef unsigned int   uint16;
*typedef unsigned long  uint32;
*/
float get_K(uint8 count , int16 dataCol_X[] , int16 dataRow_Y[])
{
    float k = 0;//斜率
    float aveCol_X = 0;//列的平均值x
    float aveRow_Y = 0;//行的平均值y
    uint16 sum_XY = 0;//行列的总和xy
    uint16 sumRow_Y = 0;//行的总和y
    uint16 sumCol_X = 0;//列的总和x
    uint32 sumCol_X2 = 0;//列的总和x^2

    for(uint16 i = 0 ; i < count ; i++)
    {
        sumCol_X += dataCol_X[i];//求列x的总和
        sumRow_Y += dataRow_Y[i];//求行y的总和
        sumCol_X2 += dataCol_X[i] * dataCol_X[i];//求x^2的总和
        sum_XY += (dataCol_X[i] * dataRow_Y[i]);//求xy的总和
    }

    aveCol_X = (float)sumCol_X / count;//求平均值
    aveRow_Y = (float)sumRow_Y / count;

    if(sumCol_X2 - aveCol_X * aveCol_X * count)
    {
        k = (sum_XY - aveCol_X * aveRow_Y * count) / //根据公式求斜率
            (sumCol_X2 - aveCol_X * aveCol_X * count);
    }
    //斜率为∞的情况 定义斜率等于0
    else
        k = 0;

    return k;
}


