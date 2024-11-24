/*
 * key.c
 *
 *  Created on: Mar 25, 2023
 *      Author: 86157
 */


#include "key.h"

int flag_test=0;
int a1=-30;
float k1=0.70;
int flag_tc=5,point=3;
int time=0;
int key_scan1(void)
{
    if(read_key1)return 1;
    if(read_key2)return 2;
    if(read_key3)return 3;
    //if(read_key4)return 4;
    return 0;
}
void key_init0(void)
{
    y0h0_nc;
    y0h1_nc;
    y0h2_nc;
    y0h3_nc;
    y0h4_nc;
    y0h5_nc;
    y0h6_nc;
    y0h7_nc;
}
int key_scan2(void)
{
    int i=0;
    set_key1;
    reset_key2;
    reset_key3;
    //reset_key4;
    i=key_scan1();
    switch(i)
    {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        default:break;
    }
    reset_key1;
    set_key2;
    i=key_scan1();
    switch(i)
    {
        case 1: return 4;
        case 2: return 5;
        case 3: return 6;

        default:break;
    }
    reset_key2;
    set_key3;
    i=key_scan1();
    switch(i)
    {
        case 1: return 7;
        case 2: return 8;
        case 3: return 9;

        default:break;
    }
    reset_key3;

return 0;
}
int key_scan3(int i)
{
    switch(i)
    {
        case 0:return 0;
        case 9:{flag_tc--;break;}//上一页
        case 8:{point-=15;break;}//上
        case 7:{flag_tc++;break;}//下一页
        case 5:{flag_go=1;break;}//初始化成功后的开启标志位
        case 2:{point+=15;break;}//下

        case 3://帧率显示
        {

            break;
        }
        default://左右进行变量增减
        {

            switch (flag_tc)
            {
                case 0://第0页
                {
                    if(i==6)     //左
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_y0h0_cut;break;}
                            case 18:{opr_y0h1_cut;break;}
                            case 33:{opr_y0h2_cut;break;}
                            case 48:{opr_y0h3_cut;break;}
                            case 63:{opr_y0h4_cut;break;}
                            case 78:{opr_y0h5_cut;break;}
                            case 93:{opr_y0h6_cut;break;}
                            case 108:{opr_y0h7_cut;break;}
                        }
                    }

                    if(i==4)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_y0h0_add;break;}
                            case 18:{opr_y0h1_add;break;}
                            case 33:{opr_y0h2_add;break;}
                            case 48:{opr_y0h3_add;break;}
                            case 63:{opr_y0h4_add;break;}
                            case 78:{opr_y0h5_add;break;}
                            case 93:{opr_y0h6_add;break;}
                            case 108:{opr_y0h7_add;break;}
                        }
                    }
                    break;
                }
                case -1://-1页
                {
                     if(i==6)     //左
                     {
                         switch (point)//第point行
                         {
                           case 3:{opr_yf1h0_cut;break;}
                           case 18:{opr_yf1h1_cut;break;}
                           case 33:{opr_yf1h2_cut;break;}
                           case 48:{opr_yf1h3_cut;break;}
                           case 63:{opr_yf1h4_cut;break;}
                           case 78:{opr_yf1h5_cut;break;}
                           case 93:{opr_yf1h6_cut;break;}
                           case 108:{opr_yf1h7_cut;break;}
                         }
                     }

                     if(i==4)  // 右
                     {
                         switch (point)//第point行
                         {
                             case 3:{opr_yf1h0_add;break;}
                             case 18:{opr_yf1h1_add;break;}
                             case 33:{opr_yf1h2_add;break;}
                             case 48:{opr_yf1h3_add;break;}
                             case 63:{opr_yf1h4_add;break;}
                             case 78:{opr_yf1h5_add;break;}
                             case 93:{opr_yf1h6_add;break;}
                             case 108:{opr_yf1h7_add;break;}
                         }
                     }
                     break;
                }
                case -2://-2页
                {
                    if(i==6)     //左
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_yf2h0_cut;break;}
                            case 18:{opr_yf2h1_cut;break;}
                            case 33:{opr_yf2h2_cut;break;}
                            case 48:{opr_yf2h3_cut;break;}
                            case 63:{opr_yf2h4_cut;break;}
                            case 78:{opr_yf2h5_cut;break;}
                            case 93:{opr_yf2h6_cut;break;}
                            case 108:{opr_yf2h7_cut;break;}
                        }
                    }

                    if(i==4)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_yf2h0_add;break;}
                            case 18:{opr_yf2h1_add;break;}
                            case 33:{opr_yf2h2_add;break;}
                            case 48:{opr_yf2h3_add;break;}
                            case 63:{opr_yf2h4_add;break;}
                            case 78:{opr_yf2h5_add;break;}
                            case 93:{opr_yf2h6_add;break;}
                            case 108:{opr_yf2h7_add;break;}
                        }
                    }
                    break;
                }
                case 1://-2页
                {
                    if(i==6)     //左
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_y1h0_cut;break;}
                            case 18:{opr_y1h1_cut;break;}
                            case 33:{opr_y1h2_cut;break;}
                            case 48:{opr_y1h3_cut;break;}
                            case 63:{opr_y1h4_cut;break;}
                            case 78:{opr_y1h5_cut;break;}
                            case 93:{opr_y1h6_cut;break;}
                            case 108:{opr_y1h7_cut;break;}
                        }
                    }

                    if(i==4)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_y1h0_add;break;}
                            case 18:{opr_y1h1_add;break;}
                            case 33:{opr_y1h2_add;break;}
                            case 48:{opr_y1h3_add;break;}
                            case 63:{opr_y1h4_add;break;}
                            case 78:{opr_y1h5_add;break;}
                            case 93:{opr_y1h6_add;break;}
                            case 108:{opr_y1h7_add;break;}
                        }
                    }
                    break;
                }
                case 2://2页
                {
                    if(i==6)     //左
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_y2h0_cut;break;}
                            case 18:{opr_y2h1_cut;break;}
                            case 33:{opr_y2h2_cut;break;}
                            case 48:{opr_y2h3_cut;break;}
                            case 63:{opr_y2h4_cut;break;}
                            case 78:{opr_y2h5_cut;break;}
                            case 93:{opr_y2h6_cut;break;}
                            case 108:{opr_y2h7_cut;break;}
                        }
                    }

                    if(i==4)  // 右
                    {
                        switch (point)//第point行
                        {
                            case 3:{opr_y2h0_add;break;}
                            case 18:{opr_y2h1_add;break;}
                            case 33:{opr_y2h2_add;break;}
                            case 48:{opr_y2h3_add;break;}
                            case 63:{opr_y2h4_add;break;}
                            case 78:{opr_y2h5_add;break;}
                            case 93:{opr_y2h6_add;break;}
                            case 108:{opr_y2h7_add;break;}
                        }
                    }
                    break;
                }
            }
        }
    }
    if(i!=13)
    {
        switch(flag_tc)
        {
            case -2://-2页
            {
                tft180_clear();
                tft180_show_string(0, point, "-");
                yf2h0_nc;
                yf2h1_nc;
                yf2h2_nc;
                yf2h3_nc;
                yf2h4_nc;
                yf2h5_nc;
                yf2h6_nc;
                yf2h7_nc;
                break;
            }
            case -1://-1页
            {
                tft180_clear();
                tft180_show_string(0, point, "-");
                yf1h0_nc;
                yf1h1_nc;
                yf1h2_nc;
                yf1h3_nc;
                yf1h4_nc;
                yf1h5_nc;
                yf1h6_nc;
                yf1h7_nc;
                break;
            }
            case 0://0页
            {
                tft180_clear();
                tft180_show_string(0, point, "-");
                y0h0_nc;
                y0h1_nc;
                y0h2_nc;
                y0h3_nc;
                y0h4_nc;
                y0h5_nc;
                y0h6_nc;
                y0h7_nc;
                break;
            }
            case 1://1页
            {
                tft180_clear();
                tft180_show_string(0, point, "-");
                y1h0_nc;
                y1h1_nc;
                y1h2_nc;
                y1h3_nc;
                y1h4_nc;
                y1h5_nc;
                y1h6_nc;
                y1h7_nc;
                break;
            }
            case 2://2页
            {
                tft180_clear();
                tft180_show_string(0, point, "-");
                y2h0_nc;
                y2h1_nc;
                y2h2_nc;
                y2h3_nc;
                y2h4_nc;
                y2h5_nc;
                y2h6_nc;
                y2h7_nc;
                break;
            }
            default:
            {
                tft180_clear();
            }
        }
    }
    return 1;
}
void lcd_show(void)
{

    static int flag1=0;
    static int j;
    int i=key_scan2();
    int black_flag;
    j++;
    if((flag1==0)&&i)
    {
        flag1=1;
        key_scan3(i);
    }
    else flag1=i;
    //以上为按键扫描部分

    //以下为lcd显示变量部分
    if(flag_tc==-2)
    {
        yf2h0_c;
        yf2h1_c;
        yf2h2_c;
        yf2h3_c;
        yf2h4_c;
        yf2h5_c;
        yf2h6_c;
        yf2h7_c;

    }
    else if(flag_tc==-1)
    {
        yf1h0_c;
        yf1h1_c;
        yf1h2_c;
        yf1h3_c;
        yf1h4_c;
        yf1h5_c;
        yf1h6_c;
        yf1h7_c;

    }
    else if(flag_tc==0)
    {
        y0h0_c;
        y0h1_c;
        y0h2_c;
        y0h3_c;
        y0h4_c;
        y0h5_c;
        y0h6_c;
        y0h7_c;

    }
    else if(flag_tc==1)
    {
        y1h0_c;
        y1h1_c;
        y1h2_c;
        y1h3_c;
        y1h4_c;
        y1h5_c;
        y1h6_c;
        y1h7_c;

    }
    else if(flag_tc==2)
    {
        y2h0_c;
        y2h1_c;
        y2h2_c;
        y2h3_c;
        y2h4_c;
        y2h5_c;
        y2h6_c;
        y2h7_c;

    }
    else if(flag_tc==3||flag_tc==4)
    {   black_flag=0;
        if(flag_tc==4)black_flag=th;//erzhihua();
        tft180_show_gray_image(0,0,mt9v03x_image_show[0], MT9V03X_W,MT9V03X_H ,MT9V03X_W,MT9V03X_H,black_flag);
        tft180_show_int(0, 108, flag_hd,2);
        tft180_show_int(32, 108, flag_zebra,2);
        tft180_show_int(64,108,flag_sz,2);

        tft180_show_float(0, 76, erage_path,5,2);
        tft180_show_int(32,92,flag_go,2);
        tft180_show_int(64,92,flag_status,2);
        tft180_show_int(96,92,fullcharge_flag,2);
        tft180_show_int(0,92,rightside[IMAGE_H-2],2);
        tft180_show_int(32,76,rightside[IMAGE_H-4],2);

//        tft180_show_int(32,92,guaidian_min,2);
//         lcd_showint8(0,6,guaidian_max);
//        lcd_showint8(64,7,flag_sz1);
//        lcd_showint8(96,7,flag_zebra);
//        lcd_showint16(96,6,out);
//        lcd_showint8(0,6,frame1);
//        lcd_showint16(96,5,dif_yaw);
//        lcd_showint16(0,5,yaw);
//        lcd_showint16(0,4,roll);
//        lcd_showint16(96,4,dif_roll);
    }
 //   IMU_quaterToEulerianAngles();
    //lcd_showint16(0,0,(int)(100*pitch));
   //lcd_showint16(0,1,(int)(yaw));
   // lcd_showint16(0,2,(int)(100*roll));

}

