/*
 * ADC.c
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */


/*
 * adc.c
 *
 *  Created on: 2023��3��22��
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

//���ڵ��ֵ���˲��������ǵ�һ����ÿ����в� 3 ������ȡ�м�ֵ��Ŀ����Ϊ�˽��͵��ֵ�е�żȻ���š�
//���߶�ÿ���������ɼ�������ݣ���5������ȡ��ֵ
//���ֵ�Ĺ�һ�� Ϊ��ʹС���ڲ�ͬ�������ϲɼ����ĵ��ֵ��һ����Χ�ڣ�Ҳʹ���ڳ�����ʶ��ȴ����й������õ��ֵ�жϵĲ����ܹ������ڲ�ͬ�����������������ݲ�
//��֮��Ե��ֵ�����˹�һ������������ͨ������ֵ�͹�һ����
//ͨ���Ե�н��й�һ��֮�����ǵõ���һ����Խ����С��λ�õĵ��ֵ����ͨ����ȺͿ��Եõ�����С��λ�õ����ݡ�
//���ɼ����ĵ�ѹ�ź�ͨ����һ������Ⱥ͡��޷��ȴ���
//���ݴ������������Ĵ��ڣ��ɼ����ĵ���źŲ�����ֱ��ʹ�ã���Ҫ�Ƚ���ȡƽ�������͹�һ����������βɼ��ĵ��ֵȥ�����ֵ����Сֵ����ȡƽ��ֵ��Ȼ����й�һ������
//��һ����ʹ�õ����ֵ�����ֵ����Сֵ�Բɼ����ĵ��ֵ���д���ʹ������ֵ����0��200֮�䡣�Ե�вɼ���ֵ���д���������������������
//ѭ�������Ե����ֵ���д������Ҫʹ�õ����ֵ��ȡС��ƫ�������ĳ̶Ⱥͷ�������ʹ����6����ж����������Ϣ���вɼ���ʹ��ͨ����Ȩ��Ⱥͼ���õ�����ֵ��ʶС��ƫ�������ĳ̶Ⱥͷ���
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
float Adinductance_getval(int GroupIndex) //��ȡadcת��ֵ
{
  int adc_result;

  switch(GroupIndex)
   {
    case 0: {
       adc_result = adc_mean_filter_convert(ADC_CHANNEL1, 10);//�ɼ�10����ƽ��  �ֱ���12λ
       break ;
    }
    case 1: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL2,  10);//�ɼ�10����ƽ��  �ֱ���12λ
       break ;
    }
    case 2: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL3,  10);//�ɼ�10����ƽ��  �ֱ���12λ
       break ;
    }
    case 3: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL4, 10);//�ɼ�10����ƽ��  �ֱ���12λ
       break ;
    }
  case 4: {
        adc_result = adc_mean_filter_convert(ADC_CHANNEL5,  10);//�ɼ�10����ƽ��  �ֱ���12λ
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
    a[i]=Adinductance_getval(k);   //��ȡ���ֵ
    adsum=adsum+a[i];               //���
   }
   for(i=0;i<N;i++)
   {
    if(a[i]>2*(adsum-a[i])/(j-1))       //ȥ��ƫ��ֵ�ϴ�ֵ
                                                                //ʾ��  100  10 11  12 10  10  ȥ��100
    {
           adsum = adsum-a[i];
           j--;
        }
    if(a[i]<(adsum-a[i])/(j-1)/2)   //ȥ��ƫ��ֵ�ϴ�ֵ
                                                                //ʾ��  10  100 110  120 100  100  ȥ��10
    {
           adsum = adsum-a[i];
       j--;
        }
   }

    return (adsum/j);          //����ƽ��ֵ��ÿ����д��صĹ�10��ֵ��ƽ��ֵ��-->ʮ��
 }

void read_AD(void)
{

   int i,j,k;
   for(i=0;i<5;i++)
   {
//   ȡֵ
       AD_value[0][i] = Adaverage(0);
       AD_value[1][i] = Adaverage(1);
       AD_value[2][i] = Adaverage(2);
       AD_value[3][i] = Adaverage(3);
       AD_value[4][i] = Adaverage(4);      //ȡ�����У���ƽ����

   }

   for(i=0;i<NUM;i++)
   {
       for(j=0;j<4;j++)
           {
               for(k=0;k<4-j;k++)
               {
                   if(AD_value[i][k] > AD_value[i][k+1])   ///��С��������
                   {
                       adtemp = AD_value[i][k];
                       AD_value[i][k] = AD_value[i][k+1];
                       AD_value[i][k+1] = adtemp;
                   }
               }
           }
   }
//  ȡ�м�����ֵƽ��
   for(i=0;i<NUM;i++)
   {
       ad_sum[i] = AD_value[i][1] + AD_value[i][2] + AD_value[i][3];
       ad_ave[i] = ad_sum[i]/3;
   }
//   ��������
   for(i=0;i<4;i++)
   {
       AD_value[0][i] = AD_value[0][i+1];
       AD_value[1][i] = AD_value[1][i+1];
       AD_value[2][i] = AD_value[2][i+1];
       AD_value[3][i] = AD_value[3][i+1];
       AD_value[4][i] = AD_value[4][i+1];
//     AD_value[5][i] = AD_value[5][i+1];
   }
//��ƽ��ֵ�������һ��
   for(i=0;i<NUM;i++)
   {
       AD_value[i][4] = ad_ave[i];
   }
//�������ٴ����
   for(i=0;i<5;i++)
   {
       AD_sum[0] += AD_value[0][i];
       AD_sum[1] += AD_value[1][i];
       AD_sum[2] += AD_value[2][i];
       AD_sum[3] += AD_value[3][i];
       AD_sum[4] += AD_value[4][i];
//     AD_sum[5] += AD_value[5][i];
   }
//ȡƽ��
   for(i=0;i<NUM;i++)
   {
       AD_V[i] =  AD_sum[i]/NUM;
       AD_sum[i] = 0;
   }

   float MAX[NUM]={3360,3380,3400,3380,3300};//ʵ�������ֵ��ʵ�ʲɼ������ֵ
   float AD_ONE[5]={0,0,0,0,0};
   for(int i=0;i<NUM;i++)
   {   /*************��һ��****************/
     AD_ONE[i]=(100*AD_V[i]/MAX[i]);    ///AD_V[i]��ж���ֵ���ٷֱȣ�
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



//target Ϊ��ȡ�ĵ���ֵ




