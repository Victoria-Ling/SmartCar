#include "Myfile.h"

#define PI 3.1416

float Filter_Weight = 0.0035f;

float gyro_x = 0, gyro_y = 0, gyro_z = 0, gyro_z_last = 0;
float acc_x = 0, acc_y = 0, acc_z = 0, acc_x_last = 0, acc_y_last = 0, acc_z_last = 0;
float Angle_gz = 0;
float Angle_pitch = 0, pit = 0, pittch = 0;
int16 Pitch = 0, Yaw = 0;
float GY = 0, GZ = 0;


void gyro_Offset_Init(void)
{
    for (int8 i = 0; i < 100; ++i)
    {
        imu660ra_get_gyro();
        GY += imu660ra_gyro_y;
        GZ += imu660ra_gyro_z;
    }

    GY /= 100;
    GZ /= 100;
}

//float Complementary(float newAngle, float newRate)   //¶þ½×»¥²¹ÂË²¨
//{
//    float x1, y1, x2, pitch_angle;
//    float k = 0.8;
//    float dt2 = 0.005f;
//    x1 = (newAngle - pitch_angle) * k * k;
//    y1 = dt2 * x1 + y1;
//    x2 = y1 + (newAngle - pitch_angle) * 2 * k + newRate;
//    pitch_angle = dt2 * x2 + pitch_angle;
//    return pitch_angle;
//}

void icm_open(void)
{
    imu660ra_get_gyro();
//    imu660ra_get_acc();

    gyro_z_last = gyro_z;
    gyro_z = (float)(imu660ra_gyro_transition(imu660ra_gyro_z) - GZ);

    gyro_z = 0.95f * gyro_z + 0.05f * gyro_z_last;


    Angle_gz += gyro_z * 0.005f;
    Yaw = (int16)Angle_gz;

//    acc_x = imu660ra_acc_transition(imu660ra_acc_x);
//    acc_z = imu660ra_acc_transition(imu660ra_acc_z);
//    Angle_pitch = (float)(((atan2((acc_x), (acc_z)) * 57.296)));
//
//    pit = (1 - Filter_Weight) * (pit - (gyro_y * dt)) + Angle_pitch * Filter_Weight; //Ò»½×»¥²¹ÂË²¨¹«Ê½
////    pittch = Complementary(Angle_pitch, gyro_y);
//    Pitch = (int16)(pit);
}
