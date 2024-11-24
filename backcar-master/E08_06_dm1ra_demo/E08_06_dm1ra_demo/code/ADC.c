/*
 * ADC.c
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */


/*
 * adc.c
 *
 *  Created on: 2023年3月22日
 *      Author: YJY
 */
#include "ADC.h"

#define ADC_CHANNEL1            ADC1_IN15_C5
#define ADC_CHANNEL2            ADC1_IN14_C4
#define ADC_CHANNEL3            ADC1_IN12_C2
#define ADC_CHANNEL4             ADC1_IN13_C3 //C2
#define ADC_CHANNEL5            ADC1_IN9_B1  //b1
#define ADC_CHANNEL6            ADC1_IN2_A2

#define AD_Val_max 4095
#define N 10
#define NUM 5

//对于电感值的滤波处理，我们第一步是每个电感采 3 次数据取中间值，目的是为了降低电感值中的偶然干扰。
//或者对每个传感器采集五次数据，将5次数据取均值
//电感值的归一化 为了使小车在不同的赛道上采集到的电感值在一定范围内，也使得在程序中识别等代码中关于利用电感值判断的部分能够适用于不同的赛道，我们在数据采
//集之后对电感值进行了归一化处理。经测试通过采最值和归一化后，
//通过对电感进行归一化之后，我们得到了一组可以解算出小车位置的电感值。在通过差比和可以得到关于小车位置的数据。
//将采集到的电压信号通过归一化、差比和、限幅等处理
//数据处理：由于噪声的存在，采集到的电磁信号不可以直接使用，需要先进行取平均操作和归一化处理。将多次采集的电感值去除最大值和最小值后求取平均值，然后进行归一化处理。
//归一化是使用电感数值的最大值和最小值对采集到的电感值进行处理，使处理后的值处于0到200之间。对电感采集的值进行处理后可以消除部分噪声。
//循迹处理：对电感数值进行处理后，需要使用电感数值获取小车偏离赛道的程度和方向。我们使用了6个电感对赛道电磁信息进行采集，使用通过加权差比和计算得到的数值标识小车偏离赛道的程度和方向。
float AD_sum[NUM]={0};
float AD_value[NUM][5]={{0},{0},{0},{0},{0}} , adtemp , ad_sum[NUM] , ad_ave[NUM] , AD_sum[NUM] ;
float AD_V[NUM];
float ad0,ad1,ad2,ad3,ad4 ;
float adc_error;
int KA=10,KB=10,Limit=6.5;

void Adc_init(void)
{
    adc_init(ADC_CHANNEL1,ADC_12BIT);
    adc_init(ADC_CHANNEL2,ADC_12BIT);
    adc_init(ADC_CHANNEL3,ADC_12BIT);
    adc_init(ADC_CHANNEL4,ADC_12BIT);
    adc_init(ADC_CHANNEL5,ADC_12BIT);
    adc_init(ADC_CHANNEL6,ADC_12BIT);
}
float Adinductance_getval(int GroupIndex) //获取adc转换值
{
  int adc_result;

  switch(GroupIndex)
   {
    case 0: {
       adc_result = adc_mean_filter_convert(ADC_CHANNEL1, 10);//采集10次求平均  分辨率12位
       break ;
    }
    case 1: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL2,  10);//采集10次求平均  分辨率12位
       break ;
    }
    case 2: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL3,  10);//采集10次求平均  分辨率12位
       break ;
    }
    case 3: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL4, 10);//采集10次求平均  分辨率12位
       break ;
    }
  case 4: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL5,  10);//采集10次求平均  分辨率12位
      break ;
   }
  }

  return adc_result;
}

float Adaverage(int k)
{
   int i = 0;
   int j = 10;
   float a[N]={0};
   float adsum = 0;
   for(i=0;i<N;i++)
   {
    a[i]=Adinductance_getval(k);   //获取电感值
    adsum=adsum+a[i];               //求和
   }
   for(i=0;i<N;i++)
   {
    if(a[i]>2*(adsum-a[i])/(j-1))       //去掉偏差值较大值
                                                                //示例  100  10 11  12 10  10  去掉100
    {
           adsum = adsum-a[i];
           j--;
        }
    if(a[i]<(adsum-a[i])/(j-1)/2)   //去掉偏差值较大值
                                                                //示例  10  100 110  120 100  100  去掉10
    {
           adsum = adsum-a[i];
       j--;
        }
   }

    return (adsum/j);          //返回平均值，每个电感传回的共10个值的平均值，-->十倍
 }

void read_AD(void)
{

   int i,j,k;
   for(i=0;i<5;i++)
   {
//   取值
       AD_value[0][i] = Adaverage(0);
       AD_value[1][i] = Adaverage(1);
       AD_value[2][i] = Adaverage(2);
       AD_value[3][i] = Adaverage(3);
       AD_value[4][i] = Adaverage(4);      //取五个电感（已平均）

   }

   for(i=0;i<NUM;i++)
   {
       for(j=0;j<4;j++)
           {
               for(k=0;k<4-j;k++)
               {
                   if(AD_value[i][k] > AD_value[i][k+1])   ///从小到大排序
                   {
                       adtemp = AD_value[i][k];
                       AD_value[i][k] = AD_value[i][k+1];
                       AD_value[i][k+1] = adtemp;
                   }
               }
           }
   }
//  取中间三个值平均
   for(i=0;i<NUM;i++)
   {
       ad_sum[i] = AD_value[i][1] + AD_value[i][2] + AD_value[i][3];
       ad_ave[i] = ad_sum[i]/3;
   }
//   滑动覆盖
   for(i=0;i<4;i++)
   {
       AD_value[0][i] = AD_value[0][i+1];
       AD_value[1][i] = AD_value[1][i+1];
       AD_value[2][i] = AD_value[2][i+1];
       AD_value[3][i] = AD_value[3][i+1];
       AD_value[4][i] = AD_value[4][i+1];
//     AD_value[5][i] = AD_value[5][i+1];
   }
//把平均值赋给最后一个
   for(i=0;i<NUM;i++)
   {
       AD_value[i][4] = ad_ave[i];
   }
//五个电感再次求和
   for(i=0;i<5;i++)
   {
       AD_sum[0] += AD_value[0][i];
       AD_sum[1] += AD_value[1][i];
       AD_sum[2] += AD_value[2][i];
       AD_sum[3] += AD_value[3][i];
       AD_sum[4] += AD_value[4][i];
//     AD_sum[5] += AD_value[5][i];
   }
//取平均
   for(i=0;i<NUM;i++)
   {
       AD_V[i] =  AD_sum[i]/NUM;
       AD_sum[i] = 0;
   }

   float MAX[NUM]={3360,3380,3400,3380,3300};//实际情况改值，实际采集的最大值
   float AD_ONE[5]={0,0,0,0,0};
   for(int i=0;i<NUM;i++)
   {   /*************归一化****************/
     AD_ONE[i]=(100*AD_V[i]/MAX[i]);    ///AD_V[i]电感读回值（百分比）
   }

   ad0=AD_ONE[0];
   ad1=AD_ONE[1];
   ad2=AD_ONE[2];
   ad3=AD_ONE[3];
   ad4=AD_ONE[4];

}
void self_read_AD(void)
{
    ad0=adc_mean_filter_convert(ADC1_IN15_C5, 10);
    ad1=adc_mean_filter_convert(ADC1_IN14_C4, 10);
    ad2=adc_mean_filter_convert(ADC1_IN12_C2, 10);
    ad3=adc_mean_filter_convert(ADC1_IN13_C3, 10);
    ad4=adc_mean_filter_convert(ADC1_IN9_B1, 10);
}



//target 为读取的电流值




