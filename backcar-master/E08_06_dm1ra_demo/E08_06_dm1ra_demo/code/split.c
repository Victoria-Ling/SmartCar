/*
 * split.c
 *
 *  Created on: May 2, 2023
 *      Author: YJY
 */

#include "split.h"
#include "zf_device_dm1xa.h"

uint16 car_distance=0;
void get_cardistance(void)
{
    uint16 car_distance1[20]={0};
    uint16 temp,car_distance_sum=0;

    int i,j,k;
    for(i=0;i<20;i++)
    {
 //   取值
        car_distance1[i]=dm1xa_receiver_ranging();
//        car_distance_sum+=car_distance1[i];
    }
//    car_distance=car_distance_sum/20;
        for(j=0;j<20;j++)
            {
                for(k=0;k<20-j;k++)
                {
                    if(car_distance1[k] > car_distance1[k+1])   ///从小到大排序
                    {
                        temp = car_distance1[k];
                        car_distance1[k] = car_distance1[k+1];
                        car_distance1[k+1] = temp;
                    }
                }
            }

 //  取中间5个值平均

        car_distance_sum = car_distance1[10] + car_distance1[9] + car_distance1[11]+ car_distance1[12]+ car_distance1[8];
        car_distance=car_distance_sum/5;

}
