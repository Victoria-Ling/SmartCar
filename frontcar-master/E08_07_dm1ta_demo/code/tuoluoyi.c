/*
 * tuoluoyi.c
 *
 *  Created on: Apr 9, 2023
 *      Author: 86157
 */


#include "tuoluoyi.h"
#include "math.h"
//四元素法陀螺仪姿态解算
extern int16 imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;                                // 三轴陀螺仪数据
extern int16 imu660ra_acc_x,  imu660ra_acc_y,  imu660ra_acc_z;
#define new_weight           0.35f
#define old_weight           0.65f

float X_Zero = 0.7 ;
float Y_Zero = 2.6 ;

double  Attitude_Angel_X = 0.0000;  //卡尔曼滤波，z轴积分值

float yaw_math[500];
int FLAG = 0;

//三轴零点X=-1.1 Y=4.6
#define mpu_acc_x imu_acc_x
#define mpu_acc_y imu_acc_y
#define mpu_acc_z imu_acc_z
#define mpu_gyro_x imu_gyro_x
#define mpu_gyro_y imu_gyro_y
#define mpu_gyro_z imu_gyro_z
#define M_PI 3.14159
float values[6];
float GyroOffset_Xgyro = 0;
float GyroOffset_Ygyro = 0;
float GyroOffset_Zgyro = 0;
float GyroOffset_Xacc = 0;
float GyroOffset_Yacc = 0;
float GyroOffset_Zacc = 0;
float yaw1;
int ring=0;
float yaw_last;
float yaw1_obstacle;//遇到障碍第一次显示的yaw值

float My_sqrt(float number)
{
    long i;
    float x, y;
    const float f = 1.5F;
    float my_sqrt_reciprocal;

    x = number * 0.5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - ( i >> 1 );

    y = * ( float * ) &i;
    y = y * ( f - ( x * y * y ) );
    y = y * ( f - ( x * y * y ) );

    my_sqrt_reciprocal = y;

    return number * my_sqrt_reciprocal;
}

//牛顿迭代法快速计算 1.0/sqrt(x)逆平方根
float InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = * (int* ) & x;  // get bits for floating VALUE
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    x = * (float* )&i;      // convert bits BACK to float
    x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
    return x;
}
void gyroOffsetInit(void)
{

    for (uint16_t i = 0; i < 100; ++i)
    {
        imu660ra_get_gyro();    // 获取陀螺仪角速度
        imu660ra_get_acc();     //获取陀螺仪加速度
        GyroOffset_Xgyro += imu660ra_gyro_x;
        GyroOffset_Ygyro += imu660ra_gyro_y;
        GyroOffset_Zgyro += imu660ra_gyro_z;
//        GyroOffset_Xacc += imu660ra_acc_x;
//        GyroOffset_Yacc += imu660ra_acc_y;
//        GyroOffset_Zacc += imu660ra_acc_z;
//        systick_delay_ms(5);    // 最大 1Khz
    }

    GyroOffset_Xgyro /= 100;
    GyroOffset_Ygyro /= 100;
    GyroOffset_Zgyro /= 100;
//    GyroOffset_Xacc /= 100;
//    GyroOffset_Yacc /= 100;
//    GyroOffset_Zacc /= 100;

}

void IMU_getValues(void)
{


    imu660ra_get_gyro();    // 获取陀螺仪角速度
    imu660ra_get_acc();     //获取陀螺仪加速度
    static float lastaccel[3]= {0,0,0};
    int i;
//    values[0] = ((float)icm20602_acc_x/2048) * new_weight + lastaccel[0] * old_weight;       //量程16g
//    values[1] = ((float)icm20602_acc_y/2048) * new_weight + lastaccel[1] * old_weight;
//    values[2] = ((float)icm20602_acc_z/2048) * new_weight + lastaccel[2] * old_weight;
//    values[0] = ((float)icm20602_acc_x - GyroOffset_Xacc) * new_weight + lastaccel[0] * old_weight;
//    values[1] = ((float)icm20602_acc_y - GyroOffset_Yacc) * new_weight + lastaccel[1] * old_weight;
//    values[2] = ((float)icm20602_acc_z - GyroOffset_Zacc) * new_weight + lastaccel[2] * old_weight;
        values[0] = ((float)imu660ra_acc_x) * new_weight + lastaccel[0] * old_weight;
        values[1] = ((float)imu660ra_acc_y) * new_weight + lastaccel[1] * old_weight;
        values[2] = ((float)imu660ra_acc_z) * new_weight + lastaccel[2] * old_weight;
    for(i=0; i<3; i++)
    {
        lastaccel[i] = values[i];
    }

//    values[3] = ((float)icm20602_gyro_x - GyroOffset_Xdata) * M_PI / 180 / 16.4f;            //量程2000dps
//    values[4] = ((float)icm20602_gyro_y - GyroOffset_Ydata) * M_PI / 180 / 16.4f;
//    values[5] = ((float)icm20602_gyro_z - GyroOffset_Zdata) * M_PI / 180 / 16.4f;
    values[3] = ((float)imu660ra_gyro_x - GyroOffset_Xgyro) * M_PI / 180;
    values[4] = ((float)imu660ra_gyro_y - GyroOffset_Ygyro) * M_PI / 180;
    values[5] = ((float)imu660ra_gyro_z - GyroOffset_Zgyro) * M_PI / 180;

    //
}

#define delta_T      0.005f  //5ms计算一次

float I_ex, I_ey, I_ez;  // 误差积分
float Q_info_q0=1,Q_info_q1=0,Q_info_q2=0,Q_info_q3=0;  // 全局四元数
float yaw,pitch,roll; //欧拉角
float param_Kp = 50.0;//50.0;   // 加速度计(磁力计)的收敛速率比例增益50
float param_Ki = 0.20;   //陀螺仪收敛速率的积分增益 0.2
void my_get_gyro(void)
{
    imu660ra_get_gyro();
    roll=imu660ra_gyro_x;
    pitch=imu660ra_gyro_y ;
    yaw  =imu660ra_gyro_z ;
}

//利用四元数法对陀螺仪数据进行姿态解算
 void IMU_AHRSupdate_noMagnetic(float gx, float gy, float gz, float ax, float ay, float az)
{
    float halfT = 0.5 * delta_T;
    float vx, vy, vz;    //当前的机体坐标系上的重力单位向量
    float ex, ey, ez;    //四元数计算值与加速度计测量值的误差
    float q0 = Q_info_q0;
    float q1 = Q_info_q1;
    float q2 = Q_info_q2;
    float q3 = Q_info_q3;
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;

    float q1q1 = q1 * q1;

    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;


    //对加速度数据进行归一化 得到单位加速度
     float norm = InvSqrt(ax*ax + ay*ay + az*az);
     ax = ax * norm;
     ay = ay * norm;
     az = az * norm;
     vx = 2*(q1q3 - q0q2);
     vy = 2*(q0q1 + q2q3);
     vz = q0q0 - q1q1 - q2q2 + q3q3;
     ex = ay * vz - az * vy;
     ey = az * vx - ax * vz;
     ez = ax * vy - ay * vx;
     //用叉乘误差来做PI修正陀螺零偏，
     //通过调节 param_Kp，param_Ki 两个参数，
     //可以控制加速度计修正陀螺仪积分姿态的速度。
   I_ex += delta_T * ex;   // integral error scaled by Ki
   I_ey += delta_T * ey;
   I_ez += delta_T * ez;

   gx = gx+ param_Kp*ex + param_Ki*I_ex;
   gy = gy+ param_Kp*ey + param_Ki*I_ey;
   gz = gz+ param_Kp*ez + param_Ki*I_ez;
           //四元数微分方程，其中halfT为测量周期的1/2，gx gy gz为陀螺仪角速度，以下都是已知量，这里使用了一阶龙哥库塔求解四元数微分方程
               q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
               q1 = q1 + ( q0*gx + q2*gz - q3*gy)*halfT;
               q2 = q2 + ( q0*gy - q1*gz + q3*gx)*halfT;
               q3 = q3 + ( q0*gz + q1*gy - q2*gx)*halfT;
               float delta_2=(2*halfT*gx)*(2*halfT*gx)+(2*halfT*gy)*(2*halfT*gy)+(2*halfT*gz)*(2*halfT*gz);
//               // 整合四元数率    四元数微分方程  四元数更新算法，二阶毕卡法
               q0 = (1-delta_2/8)*q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
               q1 = (1-delta_2/8)*q1 + (q0*gx + q2*gz - q3*gy)*halfT;
               q2 = (1-delta_2/8)*q2 + (q0*gy - q1*gz + q3*gx)*halfT;
               q3 = (1-delta_2/8)*q3 + (q0*gz + q1*gy - q2*gx)*halfT;
               // normalise quaternion
               norm = InvSqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
               Q_info_q0 = q0 * norm;
               Q_info_q1 = q1 * norm;
               Q_info_q2 = q2 * norm;
               Q_info_q3 = q3 * norm;

}

               void IMU_quaterToEulerianAngles(void)
               {
                   IMU_getValues();
                   IMU_AHRSupdate_noMagnetic( values[3],  values[4],  values[5],  values[0], values[1],  values[2]);

                   float q0 = Q_info_q0;
                   float q1 = Q_info_q1;
                   float q2 = Q_info_q2;
                   float q3 = Q_info_q3;

                   //陀螺仪安装问题，将X轴与Y轴所读数据互换
                  roll = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1) * 180/M_PI; // 陀螺仪计算的roll值,X轴
                  pitch = asin(-2*q1*q3 + 2*q0*q2) * 180/M_PI; // 陀螺仪计算的pitch值，Y轴
                  yaw = atan2(2*q1*q2 + 2*q0*q3, -2*q2*q2 - 2*q3*q3 + 1) * 180/M_PI; // yaw，Z轴
//                  roll = atan2(2*q2*q3 + 2*q0*q1, q0*q0-q1*q1-q2*q2+q3*q3) * 180/M_PI; // 陀螺仪计算的roll值,X轴
//                  pitch = asin(-2*q1*q3 -4*q0*q2) * 180/M_PI; // 陀螺仪计算的pitch值，Y轴
//                  yaw = atan2(2*q1*q2 + 4*q0*q3, q0*q0+q1*q1-q2*q2-q3*q3) * 180/M_PI; // yaw，Z轴
//                  yaw_math[FLAG] = yaw;
//                  FLAG++;

                  if(roll > 0)
                  {
                      roll = 180-roll;
                  }
                  else if(roll <0)
                  {
                      roll = -(180+roll);
                  }
                   if(yaw > 0)
                   {
                       yaw = 180-yaw;
                   }
                   else if(yaw <0)
                   {
                       yaw = -(180+yaw);
                   }

                    if(yaw_last>=120&&yaw<=-120)ring++;
                    if(yaw_last<=-120&&yaw>=120)ring--;
                    yaw_last=yaw;
                    yaw1=(yaw+360*ring)/24.6; //zangle的范围为 -180 到180度   zangle1无范围限制

///                  printf("%f,%f,%f\n",roll,pitch,yaw1);
//                   tft180_show_int(0,78,roll,4);
//                   tft180_show_int(0,93,pitch,4);
//                   tft180_show_int(0,108,yaw,4);
//                   printf("%f,%f,%f,%f,%f,%f\n", values[0],values[1],values[2],values[3],values[4],values[5]);

               }

//float Accel_x;       //X轴加速度值暂存
//float Accel_y;       //Y轴加速度值暂存
//float Accel_z;       //Z轴加速度值暂存
//
//float Gyro_x;        //X轴陀螺仪数据暂存
//float Gyro_y;        //Y轴陀螺仪数据暂存
//float Gyro_z;        //Z轴陀螺仪数据暂存
//
//float Angle_gx;    //由角速度计算的倾斜角度
//float Angle_gy;    //由角速度计算的倾斜角度
//float Angle_gz;    //由角速度计算的倾斜角度
//
//float Angle_x_temp;  //由加速度计算的x倾斜角度
//float Angle_y_temp;  //由加速度计算的y倾斜角度
//float Angle_z_temp;  //由加速度计算的z倾斜角度
//
//float Angle_X_Final; //X最终倾斜角度
//float Angle_Y_Final; //Y最终倾斜角度
//float Angle_Z_Final; //Z最终倾斜角度
//
//
////角度计算
//void Angle_Calcu(void)
//{
//    //范围为2g时，换算关系：16384 LSB/g
//    float rad;
//    float deg = rad*180/3.14;
//    float x,y,z;
//    icm20602_get_gyro();    // 获取陀螺仪角速度
//    icm20602_get_acc();     //获取陀螺仪加速度
//
//    Accel_x = icm20602_acc_x;    //x轴加速度值暂存
//    Accel_y = icm20602_acc_y;    //y轴加速度值暂存
//    Accel_z = icm20602_acc_z;    //z轴加速度值暂存
//    Gyro_x  = icm20602_gyro_x;  //x轴陀螺仪值暂存
//    Gyro_y  = icm20602_gyro_y;  //y轴陀螺仪值暂存
//    Gyro_z  = icm20602_gyro_z;  //z轴陀螺仪值暂存
//
//    //处理x轴加速度
//    if(Accel_x<32764) x=Accel_x/16384;
//    else              x=1-(Accel_x-49152)/16384;
//
//    //处理y轴加速度
//    if(Accel_y<32764) y=Accel_y/16384;
//    else              y=1-(Accel_y-49152)/16384;
//
//    //处理z轴加速度
//    if(Accel_z<32764) z=Accel_z/16384;
//    else              z=(Accel_z-49152)/16384;
//
//    //用加速度计算三个轴和水平面坐标系之间的夹角
//    Angle_x_temp=(atan(y/z))*180/3.1415926;
//    Angle_y_temp=(atan(x/z))*180/3.1415926;
//    Angle_z_temp=(atan(x/y))*180/3.1415926;
//
//    //角度的正负号
//    if(Accel_x<32764) Angle_y_temp = +Angle_y_temp;
//    if(Accel_x>32764) Angle_y_temp = -Angle_y_temp;
//    if(Accel_y<32764) Angle_x_temp = +Angle_x_temp;
//    if(Accel_y>32764) Angle_x_temp = -Angle_x_temp;
//    if(Accel_z<32764) Angle_z_temp = +Angle_z_temp;
//    if(Accel_z>32764) Angle_z_temp = -Angle_z_temp;
//
//    //角速度
//    //向前运动
//    if(Gyro_x<32768) Gyro_x=-(Gyro_x/16.4);//范围为1000deg/s时，换算关系：16.4 LSB/(deg/s)
//    //向后运动
//    if(Gyro_x>32768) Gyro_x=+(65535-Gyro_x)/16.4;
//    //向前运动
//    if(Gyro_y<32768) Gyro_y=-(Gyro_y/16.4);//范围为1000deg/s时，换算关系：16.4 LSB/(deg/s)
//    //向后运动
//    if(Gyro_y>32768) Gyro_y=+(65535-Gyro_y)/16.4;
//    //向前运动
//    if(Gyro_z<32768) Gyro_z=-(Gyro_z/16.4);//范围为1000deg/s时，换算关系：16.4 LSB/(deg/s)
//    //向后运动
//    if(Gyro_z>32768) Gyro_z=+(65535-Gyro_z)/16.4;
//
//    Angle_gx = Angle_gx + Gyro_x*0.025;  //角速度积分得到倾斜角度.越大积分出来的角度越大
//    Angle_gy = Angle_gy + Gyro_y*0.005;  //角速度积分得到倾斜角度.越大积分出来的角度越大
//    Angle_gz = Angle_gz + Gyro_z*0.001;  //角速度积分得到倾斜角度.越大积分出来的角度越大
//
//    Kalman_Filter_X(Angle_x_temp,Gyro_x);  //卡尔曼滤波计算X倾角
//    Kalman_Filter_Y(Angle_y_temp,Gyro_y);  //卡尔曼滤波计算Y倾角
//    Kalman_Filter_Z(Angle_z_temp,Gyro_z);  //卡尔曼滤波计算Z倾角
//}
//
//
////卡尔曼参数
//float Q_angle = 0.001;
//float Q_gyro  = 0.003;
//float R_angle = 0.5;
//float dt      = 0.01;//dt为kalman滤波器采样时间;
//char  C_0     = 1;
//float Q_bias, Angle_err;
//float PCt_0, PCt_1, E;
//float K_0, K_1, t_0, t_1;
//float Pdot[4] ={0,0,0,0};
//float PP[2][2] = { { 1, 0 },{ 0, 1 } };
//
//void Kalman_Filter_X(float Accel,float Gyro) //卡尔曼函数
//{
//    Angle_X_Final += (Gyro_x - Q_bias) * dt; //先验估计
//
//    Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
//
//    Pdot[1]= -PP[1][1];
//    Pdot[2]= -PP[1][1];
//    Pdot[3]= Q_gyro;
//
//    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
//    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
//    PP[1][0] += Pdot[2] * dt;
//    PP[1][1] += Pdot[3] * dt;
//
//    Angle_err = Accel - Angle_X_Final;  //zk-先验估计
//
//    PCt_0 = C_0 * PP[0][0];
//    PCt_1 = C_0 * PP[1][0];
//
//    E = R_angle + C_0 * PCt_0;
//
//    K_0 = PCt_0 / E;
//    K_1 = PCt_1 / E;
//
//    t_0 = PCt_0;
//    t_1 = C_0 * PP[0][1];
//
//    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
//    PP[0][1] -= K_0 * t_1;
//    PP[1][0] -= K_1 * t_0;
//    PP[1][1] -= K_1 * t_1;
//
//    Angle_X_Final += K_0 * Angle_err;    //后验估计
//    Q_bias        += K_1 * Angle_err;    //后验估计
//    Gyro_x         = Gyro_x - Q_bias;  //输出值(后验估计)的微分=角速度
//}
//
//void Kalman_Filter_Y(float Accel,float Gyro) //卡尔曼函数
//{
//    Angle_Y_Final += (Gyro - Q_bias) * dt; //先验估计
//
//    Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
//
//    Pdot[1]=- PP[1][1];
//    Pdot[2]=- PP[1][1];
//    Pdot[3]=Q_gyro;
//
//    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
//    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
//    PP[1][0] += Pdot[2] * dt;
//    PP[1][1] += Pdot[3] * dt;
//
//    Angle_err = Accel - Angle_Y_Final;  //zk-先验估计
//
//    PCt_0 = C_0 * PP[0][0];
//    PCt_1 = C_0 * PP[1][0];
//
//    E = R_angle + C_0 * PCt_0;
//
//    K_0 = PCt_0 / E;
//    K_1 = PCt_1 / E;
//
//    t_0 = PCt_0;
//    t_1 = C_0 * PP[0][1];
//
//    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
//    PP[0][1] -= K_0 * t_1;
//    PP[1][0] -= K_1 * t_0;
//    PP[1][1] -= K_1 * t_1;
//
//    Angle_Y_Final   += K_0 * Angle_err;  //后验估计
//    Q_bias  += K_1 * Angle_err;  //后验估计
//    Gyro_y   = Gyro - Q_bias;    //输出值(后验估计)的微分=角速度
//}
//
//void Kalman_Filter_Z(float Accel,float Gyro) //卡尔曼函数
//{
//    Angle_Z_Final += (Gyro - Q_bias) * dt; //先验估计
//
//    Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-先验估计误差协方差的微分
//
//    Pdot[1]=- PP[1][1];
//    Pdot[2]=- PP[1][1];
//    Pdot[3]=Q_gyro;
//
//    PP[0][0] += Pdot[0] * dt;   // Pk-先验估计误差协方差微分的积分
//    PP[0][1] += Pdot[1] * dt;   // =先验估计误差协方差
//    PP[1][0] += Pdot[2] * dt;
//    PP[1][1] += Pdot[3] * dt;
//
//    Angle_err = Accel - Angle_Z_Final;  //zk-先验估计
//
//    PCt_0 = C_0 * PP[0][0];
//    PCt_1 = C_0 * PP[1][0];
//
//    E = R_angle + C_0 * PCt_0;
//
//    K_0 = PCt_0 / E;
//    K_1 = PCt_1 / E;
//
//    t_0 = PCt_0;
//    t_1 = C_0 * PP[0][1];
//
//    PP[0][0] -= K_0 * t_0;       //后验估计误差协方差
//    PP[0][1] -= K_0 * t_1;
//    PP[1][0] -= K_1 * t_0;
//    PP[1][1] -= K_1 * t_1;
//
//    Angle_Z_Final   += K_0 * Angle_err;  //后验估计
//    Q_bias  += K_1 * Angle_err;  //后验估计
//    Gyro_z   = Gyro - Q_bias;    //输出值(后验估计)的微分=角速度
//}
