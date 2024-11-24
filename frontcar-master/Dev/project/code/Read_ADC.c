#include "Myfile.h"

uint16 ADD_valu[7][6] = {0}, ADDD_valu[7] = {0}, AD_valu[7] = {0};
uint16 Position_Transit[2] = {225, 225};

float GUI_AD[7] = {0};
float Range = 250.0f;
int8 Max_Front = 0 ,Position = 0, Position_last = 0;
int16 AD_Max = 630;

/*********************************************
*函数：电感采集与处理函数
*函数名：ADC_Read()
*备注：
*日期：
*修改日期：
*********************************************/
void ADC_Read(void)
{
    int8 i, j, k;
    uint16 temp;
    uint16  adc_valu[7][10], ad_sum[7];

    for (i = 0; i < 10; ++i)
    {
        adc_valu[0][i] = adc_convert(ADC1_IN15_C5);//左横
        adc_valu[1][i] = adc_convert(ADC1_IN14_C4);
        adc_valu[2][i] = adc_convert(ADC1_IN13_C3);
        adc_valu[3][i] = adc_convert(ADC1_IN12_C2);//中间
        adc_valu[4][i] = adc_convert(ADC1_IN9_B1);
        adc_valu[5][i] = adc_convert(ADC1_IN0_A0);
        adc_valu[6][i] = adc_convert(ADC1_IN7_A7);//右横
    }

    for (i = 0; i < 7; ++i)                                             //排序
    {
        for (j = 0; j < 9; ++j)
        {
            for (k = 0; k < 9 - j; ++k)
            {
                if (adc_valu[i][k] > adc_valu[i][k + 1])
                {
                    temp = adc_valu[i][k + 1];
                    adc_valu[i][k + 1] = adc_valu[i][k];
                    adc_valu[i][k] = temp;
                }
            }
        }
    }

    for (i = 0; i < 7; ++i)                                    //中间值平均
    {
        ad_sum[i] = adc_valu[i][3] + adc_valu[i][4] + adc_valu[i][5] + adc_valu[i][6];
        AD_valu[i] = ad_sum[i] >> 2;
    }

    for(i = 0; i < 7; ++i)                                      //滑动滤波
    {
        for(j = 0; j < 5; ++j)
                ADD_valu[i][j] = ADD_valu[i][j+1];

        ADD_valu[i][j] = AD_valu[i];
    }

    for(i = 0; i < 7; ++i)                                      //平均值
    {
        ADDD_valu[i] = (ADD_valu[i][0] + ADD_valu[i][1] + ADD_valu[i][2] + ADD_valu[i][3] + ADD_valu[i][4] + ADD_valu[i][5]) / 6;
    }

    for (i = 0; i < 7; ++i)                                     //归一
    {
        GUI_AD[i] = Range * (ADDD_valu[i] / AD_Max);

        if (GUI_AD[i] >= Range)
            GUI_AD[i] = Range;
        if (GUI_AD[i] < 1)
            GUI_AD[i] = 1;
    }
}

