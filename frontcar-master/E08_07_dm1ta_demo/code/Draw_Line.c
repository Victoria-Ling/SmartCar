/*
 * Draw_Line.c
 *
 *  Created on: Apr 19, 2023
 *      Author: 86157
 */


#include "Draw_Line.h"

/*
 * @brief LCD��Ļ�ϻ�ʮ�ֽ���
 * @param ��ĺ�����
 * @param ���������
 * @param �����ɫ
 * @noticeһ��Ҫ��ͼ��ķ�Χ����ס,��Ȼ�ͻᵼ����Ļ����
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
 * @brief �����ͼ��ֱ��
 * @param ��һ����ĺ�����
 * @param ��һ�����������
 * @param �ڶ�����ĺ�����
 * @param �ڶ������������
 * @param ͼ��Ŀ��
 * @notice ��һ����͵ڶ����㶼����б��
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
    for (int i = 1; i <= (-dy); i++)//����Y������ȥ��x
    {
        Y = (int)((first_point_y-i)*K+b);

        //Ϊ��ʹ��ѭ�߽��ʱ���������������
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
 * @brief �����ͼ������
 * @param ���ͼ���ַ
 * @param ��һ����ĺ�����
 * @param ��һ�����������
 * @param �ڶ�����ĺ�����
 * @param �ڶ������������
 * @param ͼ��Ŀ��
 * @notice ��һ����Ҳ����б��
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
 * @brief ��������
 * @param ���ͼ���ַ
 * @param ��һ����ĺ�����
 * @param ��һ�����������
 * @param �ڶ�����ĺ�����
 * @param �ڶ������������
 * @param ����ͼ��ĺ�����
 * */
void Draw_Curve(uint8 *imag_out, int first_point_x, int first_point_y, int second_point_x, int second_point_y, int Imag_x)
{
    float center_x, center_y;
    int dy = first_point_y - second_point_y;
    int temp_x, supplementary_point, deviation;
    int distance;

    //��������ľ���
    if (first_point_x < second_point_x)
    {
        distance = My_sqrt((first_point_y - second_point_y)*(first_point_y - second_point_y) + (second_point_x - first_point_x)*(second_point_x - first_point_x));
    }
    else
    {
        distance = My_sqrt((first_point_y - second_point_y)*(first_point_y - second_point_y) + (first_point_x - second_point_x)*(first_point_x - second_point_x));
    }


    //���Բ������
    float c1 = (float)(second_point_x*second_point_x - first_point_x*first_point_x + second_point_y*second_point_y - first_point_y*first_point_y) / (2 *(second_point_x - first_point_x));
    float c2 = (float)(second_point_y - first_point_y) / (second_point_x - first_point_x);  //б��
    float AA = (c2*c2 + 1);
    float BB = (2 * first_point_x*c2 - 2 * c1*c2 - 2 * first_point_y);
    float CC = first_point_x*first_point_x - 2 * first_point_x*c1 + c1*c1 + first_point_y*first_point_y - distance*distance;

    center_y = (-BB + My_sqrt(BB*BB - 4 * AA*CC)) /(float)(2 * AA);
    center_x = c1 - c2 * center_y;

    //����Բ�ı�׼����,���ÿһ��x
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
 * @brief ����һ��ֱ�ߵ�б��
 * @param ��һ����ĺ�����
 * @param ��һ�����������
 * @param �ڶ�����ĺ�����
 * @param �ڶ������������
 * @param �����ֱ��б��
 * @param �����ֱ�߽ؾ�
 * */
void Calculate_Boder_Line_Slope(int first_point_x, int first_point_y, int second_point_x, int second_point_y, ARRAY start_point, float *slope, float *intercept)
{
    int dx = second_point_x - first_point_x;
    int dy = second_point_y - first_point_y;
    *slope = (float)dx/(float)dy;
    *intercept = start_point.x - (*slope)*start_point.y;
}

/*
 * @brief ����ֱ��б�������һ���������
 * @param ��ֱ֪�ߵ�б��
 * @param ��ֱ֪�ߵĽؾ�
 * @param ��֪�������
 * @param Ҫ��ĵ�ĺ�����
 * @param Ҫ��ĵ��������
 * */
void Fixed_Middle_Line_With_Slope(float slope, float intercept, ARRAY start_point, int *output_x, int *output_y)
{
    *output_y = (start_point.y-1);
    *output_x = (int)(slope*(*output_y)+intercept);
}



/*
 * @brief ����ǰհ������
 * @param ǰհ�ߵ�������
 * @param �ߵ���ɫ
 * */
void LCD_Draw_Propect_Line(int propect_y, int color)
{
    for (int i = 20; i < 64; i++)
    {
        tft180_draw_point(i, propect_y, color);
    }
}

/*
 * @brief ����ֱ�ߵ�б��
 * @param ��һ���������
 * @param �ڶ����������
 * @return ��ֱ�ߵ�б��
 * */
float Calculate_Slope(int16 first_point_x, int16 second_point_x,int16 first_point_y, int16 second_point_y)
{
    int dx = second_point_x - first_point_x;
    int dy = second_point_y - first_point_y;
    float K = (float)dx / (float)dy;

    return K;
}

/*
 * @brief ���ݱ���б�����������
 * @param ������ߵ�����
 * @param ��һ���������
 * @param �ڶ����������
 * @param ������ߵ���ʼ������
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

/*���Իع���б��
*****ע����������
*����   count         ���ݸ��� ������(��)�ĸ��� �����������Ŀ���
*����   dataCol_X[]   ���ݵ�������
*����   dataRow_Y[]   ���ݵ�������
*����ֵ k             б�� ��Χ(-��,��)
*���㷨����б��Ϊ �� ����� k = 0;
*ʹ��ע�� ��Ҫ�ض�����������
*typedef unsigned char  uint8;
*typedef unsigned int   uint16;
*typedef unsigned long  uint32;
*/
float get_K(uint8 count , int16 dataCol_X[] , int16 dataRow_Y[])
{
    float k = 0;//б��
    float aveCol_X = 0;//�е�ƽ��ֵx
    float aveRow_Y = 0;//�е�ƽ��ֵy
    uint16 sum_XY = 0;//���е��ܺ�xy
    uint16 sumRow_Y = 0;//�е��ܺ�y
    uint16 sumCol_X = 0;//�е��ܺ�x
    uint32 sumCol_X2 = 0;//�е��ܺ�x^2

    for(uint16 i = 0 ; i < count ; i++)
    {
        sumCol_X += dataCol_X[i];//����x���ܺ�
        sumRow_Y += dataRow_Y[i];//����y���ܺ�
        sumCol_X2 += dataCol_X[i] * dataCol_X[i];//��x^2���ܺ�
        sum_XY += (dataCol_X[i] * dataRow_Y[i]);//��xy���ܺ�
    }

    aveCol_X = (float)sumCol_X / count;//��ƽ��ֵ
    aveRow_Y = (float)sumRow_Y / count;

    if(sumCol_X2 - aveCol_X * aveCol_X * count)
    {
        k = (sum_XY - aveCol_X * aveRow_Y * count) / //���ݹ�ʽ��б��
            (sumCol_X2 - aveCol_X * aveCol_X * count);
    }
    //б��Ϊ�޵���� ����б�ʵ���0
    else
        k = 0;

    return k;
}


