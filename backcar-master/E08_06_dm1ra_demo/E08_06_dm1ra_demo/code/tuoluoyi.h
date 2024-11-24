/*
 * tuoluoyi.h
 *
 *  Created on: Apr 9, 2023
 *      Author: 86157
 */

#ifndef TUOLUOYI_H_
#define TUOLUOYI_H_

#include "zf_common_headfile.h"
extern float X_Zero;
extern float Y_Zero;
extern uint16 car_distance;
extern float yaw,pitch,roll,yaw1; //ŷ����
extern float yaw1_obstacle;//�����ϰ���һ����ʾ��yawֵ
void IMU_quaterToEulerianAngles(void);
void IMU_AHRSupdate_noMagnetic(float gx, float gy, float gz, float ax, float ay, float az);
void IMU_getValues(void);
void gyroOffsetInit(void);
void my_get_gyro(void);
float My_sqrt(float number);
float InvSqrt(float x);


//void KalmanFilter(float ACC_Angle,float Gyro_y);
//void Get_Attitude_Kalman(void);



#endif /* TUOLUOYI_H_ */
