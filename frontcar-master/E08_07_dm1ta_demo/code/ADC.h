/*
 * ADC.h
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */

#ifndef ADC_H_
#define ADC_H_
#include "zf_common_headfile.h"
void Adc_init(void);
void read_AD(void);
void self_read_AD(void);
float Adaverage(int k);
extern float ad0,ad1,ad2,ad3,ad4;
extern int KA,KB,Limit;
extern float adc_error;
#endif /* ADC_H_ */
