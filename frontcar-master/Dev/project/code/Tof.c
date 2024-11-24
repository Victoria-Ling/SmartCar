#include "Myfile.h"

//障碍类型变量
int8 barrier_type[6] = {0, 1, 0, 0, 0, 0};//菜单修改
int8 cout_finish = 2;   //路障和坡道总个数
int8 cout = 0;      //第几个

//横断变量
int8 hengduan = 0;
int8 i = 0;
uint16 distance_mm[4] = {0}, distance_pingjun = 0;
float obstacle_p = 0.5f, obstacle_d = 0.65f;
int8 obstacle_error[2] = {0};
int8 angle_want = 0;

//坡道变量
int ramp_time = 0;
int8 finish = 0;         //上下坡


/*********************************************
 *函数:障碍类型判断
 *函数名:duan_or_po()
 *备注:
 *修改日期:
 *********************************************/
void duan_or_po(void)
{
        if(distance_pingjun <= 650 && barrier_type[cout] == 0 && space_flag != 3)
        {
            base = base_hengduan;
            hengduan = 1;
            space_flag = 3;
            yaw_angle = Yaw;
            angle_want = -35;
            BEEP_ON;
        }
        else if(distance_pingjun <= 350 && barrier_type[cout] == 1 && space_flag != 5)
        {
            space_flag = 5;
            ++ finish;
            BEEP_ON;
        }


//        if(hengduan == 1 && abs(Yaw - yaw_angle) >= 35)
//        {
//            yaw_angle = Yaw;
//            hengduan = 2;
//        }
//        if(hengduan == 2 && abs(Yaw - yaw_angle) >= 87)
//        {
//            hengduan = 3;
//            yaw_angle = Yaw;
//        }
//        if(hengduan == 3 && (abs(Yaw - yaw_angle) >= 52 || MAD >= 240))
//        {
//            hengduan = 4;
//            yaw_angle = 0;
//        }
//        if(hengduan == 4)
//        {
//            BEEP_OFF;
//            hengduan = 0;
//            distance_mm[3] = 0;
//            distance_pingjun = 0;
//
//
//            ++ cout;
//            if(cout == cout_finish)
//                cout = 0;
//
//            if (MAD >= spaceflag)
//            {
//                space_flag = 1;
//            }
//            if (MAD < spaceflag)
//            {
//                space_flag = 2;
//            }
//        }

        if(hengduan == 1 && abs(Yaw - yaw_angle) >= 35)
        {
            yaw_angle = Yaw;
            hengduan = 2;
            angle_want = 85;
        }
        if(hengduan == 2 && abs(Yaw - yaw_angle) >= 85)
        {
            hengduan = 3;
            yaw_angle = Yaw;
            angle_want = -55;
        }
        if(hengduan == 3 && (abs(Yaw - yaw_angle) >= 55 || MAD >= 240))
        {
            hengduan = 4;
            yaw_angle = 0;
            angle_want = 0;
        }
        if(hengduan == 4)
        {
            BEEP_OFF;
            hengduan = 0;
            distance_mm[3] = 0;
            distance_pingjun = 0;
            obstacle_error[0] = 0;


            ++ cout;
            if(cout == cout_finish)
                cout = 0;

            if (MAD >= spaceflag)
            {
                space_flag = 1;
            }
            if (MAD < spaceflag)
            {
                space_flag = 2;
            }
        }

        if(space_flag == 5 && ramp_time >= 55)
        {
            BEEP_OFF;
            distance_mm[3] = 0;
            distance_pingjun = 0;

            if(finish % 2 != 1)
                ++ cout;
            if(cout == cout_finish)
                cout = 0;

            if (MAD >= spaceflag)
            {
                space_flag = 1;
            }
            if (MAD < spaceflag)
            {
                space_flag = 2;
            }
        }
}


/*********************************************
 *函数:障碍检测
 *函数名:barrier()
 *备注:
 *修改日期:
 *********************************************/
void barrier(void)
{
    if(space_flag != 4 && MAD >= 210 && space_flag != 3 && space_flag != 5)
    {
        dl1a_get_distance();

        if(dl1a_distance_mm <= 670 && dl1a_distance_mm >= 50)
        {
            for(i = 0; i < 3; ++i)
            {
                 distance_mm[i] = distance_mm[i+1];
            }
            distance_mm[i] = dl1a_distance_mm;
        }
        else if(dl1a_distance_mm > 670)
            distance_mm[3] = 0;

        if(distance_mm[0] != 0 && distance_mm[1] != 0 && distance_mm[2] != 0 && distance_mm[3] != 0)
            distance_pingjun = distance_mm[2] * 0.1f + distance_mm[3] * 0.9f;
        else
            distance_pingjun = 0;
     }
}

