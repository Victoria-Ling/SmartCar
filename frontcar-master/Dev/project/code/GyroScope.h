#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

extern float GY, GZ;
extern int16 Pitch, Yaw;


void gyro_Offset_Init(void);
//float Complementary(float newAngle, float newRate);
void icm_open(void);

#endif /* GYROSCOPE_H_ */
