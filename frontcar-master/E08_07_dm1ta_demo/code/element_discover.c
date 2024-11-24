/*
 * element_discover.c
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */


#include "element_discover.h"
int flag_hd = 0;  //环岛标志位
int flag_sc = 0, flag_sz=0, flag_sc1 = 0, flag_sz1 = 0;  //三岔 十字回环 三岔次数 十字路口
int flag_status = 0;  //start;//特殊元素标志位
int flag_go = 0;  //出库标志位 等于2时进入直道
int right_plus[60];
int flag_hd_time;  //环岛次数判断
int flag_buffer;  //蜂鸣器标志位
int flag_zebra = 0, flag_zebra_time = 0;  //斑马线标志位
int zebra_time[5] = {1, 2, 1, 1};  //斑马线顺序的数组   0表示左循迹不入库 1表示右循迹不入库 2表示左循迹入库 3表示右循迹入库0,3
int hd_time[10] = {0, 2, 0, 2, 0, 0, 0, 0, 0, 0};  //环岛与回环顺序的数组  0表示小环 1表示大环 2表示十字回环
int status_time[20] = {rightfok, right, right, left, rightfok, rightzebra, left, leftzebra}; //元素顺序的数组，实测会出问题，不建议用，建议还是好好搞好元素识别
int status_time1[20] = {right, right, left, rightfok, rightzebra, left, rightzebra};
int flag_status_time = 0;
int plus_th=580;
int up_point, down_point;  //上拐点，下拐点
int16 leftside1[MT9V03X_H], rightside1[MT9V03X_H];  //补线时用到的临时数组
int flag_lx = 0;  //防止回环与环岛相邻而判断错，因为当时线上比赛时，环岛与十字回环距离非常近，所以加了该变量，一般线下赛不会距离太近，所以一般用不到该变量

int flag_pd = 0;  //坡道标志位
int flag_stop = 0;  //停止标志位
long int speed_cut = 0;
int r_sum=0;
int cpH,cpW;//拐点定义

int l_down,r_down,l_up,r_up;
int l_downW,r_downW,l_upW,r_upW;
int l_down_flag=0,r_down_flag=0,l_up_flag=0,r_up_flag=0;

int judge_mid;


void main_check(void)
{
       if(flag_go==3)
       {
            obstacle_check();
            huandao_check();
            zebra_linedrawing();
       // shizi_check();
       }
}
void obstacle_check(void)
{
    if(distance<=800&&!obstacle_flag)//横断标志位
          {
             count_of_obstacle++;
//              if(count_of_obstacle>4)
//                  count_of_obstacle=1;
             if(count_of_obstacle==1)
              {
                 obstacle_flag=1;
                 pace_flag=1;
              }
          }
}
void black_check(void)
{
    int16 k=0;
    for(int16 i=0;i<60;i++)
    {
        for(int16 j=0;j<160;j+=4)
        {
            if(mt9v03x_image[i][j]<th)
            {
                k++;
            }
            if(k>30)
            {
            midline[i]=80;
            leftedge[i]=0;
            rightedge[i]=160;
            }

        }
        k=0;
    }
}
void zebra_check(void)//斑马线检测  内部包含斑马线中的补线
{
    int i,z,k;
    int j=0;
    if(flag_zebra==0)
    {              //第一步
         for(i=59;i>=54;i--)
             {
                    if(leftedge[i]>14&&rightedge[i]<146)
                {
                    j++;

                }
             }
            if(j>3) //flag_status=leftzebra;
                    // else flag_status=rightzebra;
            flag_zebra=ZEBRA1;

    }

    else if(flag_zebra==ZEBRA1)
    {
        if(colorchange_check_col(80)&&colorchange_check_col(85)&&colorchange_check_col(75)&&leftedge[3]<=7)
        {
            flag_zebra=ZEBRA2;
            flag_status=rightzebra;
        }
    }

    if(flag_status==leftzebra)
    {
        if(flag_zebra==ZEBRA2)
        {
            if(colorchange_check_row(56)||colorchange_check_row(51)||colorchange_check_row(47))
            {
                flag_zebra=ZEBRA3;
            }
            else
            {
                add_line_left1(20,47,55,leftedge[55]);
            }
        }
        else if(flag_zebra==ZEBRA3)
        {
            j=0;
            for(i=44;i<56;i+=4)
            {
                if(rightedge[i]-rightedge[i+4]<0) j++;
                if(j>=3)
                {
                    if(rightedge[30]>107)
                    {
                        flag_status=0;
                        flag_zebra=0;
                        flag_zebra_time++;
                        flag_status_time++;
                        return ;
                    }
                }
            }
            add_line_left1(20,leftedge[20],55,47);
        }
    }
    else if(flag_status==rightzebra)
    {
        if(flag_zebra==ZEBRA2)
        {
            z=0,k=0;
            for(i=45;i>=15;i-=3)
            {
                if (leftedge[i]-leftedge[i+3]>2)
                 k++;


                if(rightedge[i]>=155)
                    z++;
            }
            if(k>=5&&k>6&&!colorchange_check_col(80))
                flag_zebra=ZEBRA3;
        }
        else if (flag_zebra==ZEBRA3)
        {
                        {   z=0,k=0;
                                 for (i = 20; i <= 50; i += 5)
                                 {
                                    if (leftedge[i] - leftedge[i + 5] > 1)
                                    z++;

                                  }
                                 for(i=30;i<60;i+=5)
                                 {
                                     if(leftedge[i]<5)
                                         z=0;
                                 }
                                 for (i = 20; i <=50; i += 5)
                                 {
                                 if (rightedge[i] - rightedge[i + 5] < -1)
                                   {
                                       k++;
                                   }
                                 }

                              if(z>=3&&k>=3&&!colorchange_check_col(80))
                                  {flag_zebra=ZEBRA4;}

                           }

        }
        else if(flag_zebra==ZEBRA4)
        {
            if(colorchange_check_row(42)&&colorchange_check_row(45)&&(!colorchange_check_row(30)))
           flag_zebra=17;

        }
    }

}
int16 counter=0;//判断到底是跑两圈还是一圈
void zebra_linedrawing(void)//入库识别  在zebra_check()函数中调用
{
    if(colorchange_check_row(58)&&colorchange_check_row(55))
    {
        counter++;
        if(counter==1)//如果是两次
        {
        flag_status=stop;
//        distance=0;
//        flag1=1;
//        if(zebra_time[flag_zebra_time]==2)  out=750;         //第二次检测到斑马线就右拐入库并减速
//        else out=-750;
       // start1=2;
        flag_go=4;
        }
    }
}

int colorchange_check_row(int a)
{      //检测连续五行发现斑马线特征（黑白交替多次）
    int i;      //按列遍历
    int changecolor=0;      //单次检测到的交替次数
    for(i=130; i>30; i-=1)
    {
        if(changecolor%2==0 && mt9v03x_image[a][i]>th+5)
        {        //偶数找白点
            changecolor++;
        }
        else if(changecolor%2==1 && mt9v03x_image[a][i]<th-5)
        {    //奇数找黑点
            changecolor++;
        }
    }
    if(changecolor<8)   return 0; //交替次数不足则检测失败
    else    return 1;     //返回1说明检测到斑马线
}
int colorchange_check_col(int a)
{      //检测连续五列发现斑马线特征（黑白交替多次）
    int j;      //按行遍历
    int changecolor=0;      //单次检测到的交替次数
    for(j=60; j>=30; j-=1)
    {
        if(changecolor%2==0 && mt9v03x_image[j][a]>th+5)
        {        //偶数找白点
            changecolor++;
        }
        else if(changecolor%2==1 && mt9v03x_image[j][a]<th-5)
        {    //奇数找黑点
            changecolor++;
        }
    }
    if(changecolor<13)   return 0; //交替次数不足则检测失败
    else    return 1;     //返回1说明检测到斑马线
}

void add_line_left1(int up_line1,int up_point1,int down_line1,int down_point1)//根据左边界补中线，并改变右边界
{
    int i,j=0;
    float slop;
    slop=(up_point1-down_point1)/(float)(down_line1-up_line1);
    for(i=down_line1;i>=up_line1;i--)
    {
        j++;
        leftedge[i]=down_point1+slop*j;
        midline[i]=(rightside1[i]+leftedge[i])/2;
    }
}
void add_line_right1(int up_line2,int up_point2,int down_line2,int down_point2)//根据右边界补中线，并改变左边界
{
    int i,j=0;
    float slop;
    slop=(up_point2-down_point2)/(float)(down_line2-up_line2);
    for(i=down_line2;i>=up_line2;i--)
    {
        j++;
        rightedge[i]=down_point2+slop*j;
        midline[i]=(rightside1[i]+leftedge[i])/2;
    }
}
//void huandao_check (void)
//{
//    int i, j=0, k=0, z=0;
//    if (flag_status == 0)  //标志位为
//    {
//        if (flag_hd == 0)  //环岛的初步判断
//        {
//            j = 0, k = 0, z = 0;
//            for (i = 12; i <= 32; i++)
//            {
//                if (leftedge[i] < 10)
//                    j++;
//            }
//            for (i = 35; i < 55; i +=2)
//            {
//                if (leftedge[i] - leftedge[i + 3] >1.8)
//                    z++;
//            }
//            for (i = 2; i <= 30; i += 2)
//            {
//                if (rightedge[i] - rightedge[i + 3] < -0.8)
//                {
//                    k++;
//                }
//                else if(rightedge[i]>154&&rightedge[i+1]>154&&rightedge[i+2]>154&&rightedge[i+3]>154&&rightedge[i+4]>154)
//                {
//                    k=0;break;
//                }
//            }
//            if (j >7 && z >6 && k >8&&leftedge[3]>=25&&leftedge[4]>=23&&leftedge[5]>=21)
//            {
//                flag_hd = left1;
//                gpio_set_level(C13,1);
//            }
//
//        }
//        if(flag_hd==left1)
//        {
//             k=0,z=0;
//             if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-40&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=0)
//             {
//                    for(i=59;i>=29;i-=3)
//                    {
//                        if(leftedge[i]<=7&&leftedge[57]<=7&&leftedge[56]<=7)
//                            k++;
//                    }
//                    for(j=1;j<=11;j++)
//                    {
//                        if(leftedge[j]-leftedge[j+25]>=30)
//                            z++;
//                    }
//             }
//             if(k>=5&&z>=5)
//                 flag_hd =left2;
//        }
//        if (flag_hd == left2)
//            {
//             j=0,k=0,z=0;
//             if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-40&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=0)
//          {
//                for (i = 3; i < 10; i ++)
//                {
//                    if (leftedge[i]<5 )
//                        j++;
//                }
//                for (i = 51; i < 59; i ++)
//                               {
//                                   if (leftedge[i]<5 )
//                                       k++;
//                               }
//
//                for (i = 23; i <48; i +=2)
//                                   {
//                                       if (leftedge[i] - leftedge[i + 3] >0.8 )
//                                           z++;
//                                   }
//
//        }
//                if (j >=4&&k>=5&&z>7&&midline[30]>=60)//
//                {
//                    flag_hd = left3;gpio_toggle_level(C13);
//                }
//
//            }
//
//
//      if(flag_hd==left3)
//      {
//          j = 0,  z = 0;
//          if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-40&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=0)
//       {
//          for (i = 59; i >39; i-=2)
//          {
//              if (leftedge[i] < 7&&leftedge[58]<7&&leftedge[57]<7&&leftedge[40]<7)
//                  j++;
//          }
//
////           for(i=0;i<=16;i+=2)
////          {
////               if (rightedge[i] - rightedge[i + 5] < -1.8)
////                           {
////                               z++;
////                           }
////          }
//      }
//           if (j >6&&leftedge[17]>=40)//
//                       {
//                           flag_hd = left4;gpio_toggle_level(C13);
//                       }
//
//          }
//      if(flag_hd==left4)
//      {
//          pace_flag=1;
//          if(erage_path>=12)
//        {
//              pace_flag=0;
//        }
//              if(!pace_flag&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-110&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=-30)
//
//          {
//              int mid_sum=0;
//              k=0;
//              for(i=30;i<50;i++)
//                  {mid_sum=midline[i];}
//              if((mid_sum/20)<65)
//                  z=1;
//               for (j = 10; j <150 ; j+=10)
//               {
//                      if(mt9v03x_image[10][j]<th+10)
//                          k++;
//                }
//          }
//
//          if(z&&k>11)
//              flag_hd=left5;
//
//      }
//      if(flag_hd==left5)
//         {
//          if((rightedge[7]+rightedge[8]+rightedge[9]-rightedge[18]-rightedge[19]-rightedge[20])>=40&&(rightedge[7]+rightedge[8]+rightedge[9]-rightedge[18]-rightedge[19]-rightedge[20])<=135)
//          {    j=0;z=0;
//             for(i=28;i<52;i+=2)
//             {
//                 if(rightedge[i]-rightedge[i-3]>=2)
//                  {j=1;continue;}
//                 else if(j)
//                 {
//                     if(rightedge[i+3]-rightedge[i]<=0)
//                         {j=0;break;}
//                 }
//             }
//             cpH=i+1;
//             cpW=rightedge[i];
//             for(i=30;i<=50;i+=2)
//                  {
//                      if(leftedge[i]<5)
//                      {
//                         z++;
//                      }
//                  }
//          }
//             if(j&&rightedge[3]>=140&&z>=5&&leftedge[4]>=50)
//             {   flag_hd=left6;
//             gpio_toggle_level(C13);}
//         }
//       if(flag_hd==left6)//左右皆丢线
//       {   j=0,k=0;
//           for(i=20;i<50;i+=2)
//           {
//               if(leftedge[i]<7)
//                 j++;
//           }
//           for(i=20;i<50;i+=2)
//             {
//                if(rightedge[i]>150)
//                 k++;
//             }
//           if(j>9&&k>9)
//           { flag_hd=left7;gpio_toggle_level(C13);}
//       }
//       if(flag_hd==left7)
//       {   j=0;
//           for(i=20;i<50;i+=2)
//           {
//               if(rightedge[i+3]-rightedge[i]<=5&&rightedge[i+3]-rightedge[i]>=3)
//                   j++;//斜率恢复正常
//           }
//           for(i=10;i<50;i+=2)
//           {
//               if(leftedge[i]<5)k++;
//           }
//           if(j>=10&&k>8)//
//              flag_hd=left8;
//       }
//       if(flag_hd==left8)
//       {   z=0,k=0;
//           for (i = 20; i <= 50; i += 5)
//           {
//              if (leftedge[i] - leftedge[i + 5] > 1)
//              z++;
//
//            }
//           for(i=30;i<60;i+=5)
//           {
//               if(leftedge[i]<5)
//                   z=0;
//           }
//           for (i = 20; i <=50; i += 5)
//           {
//           if (rightedge[i] - rightedge[i + 5] < -1)
//             {
//                 k++;
//             }
//           }
//
//        if(z>=3&&k>=3)
//            {flag_hd=left9;gpio_toggle_level(C13);
//            flag_status=1;
//            }
//       }
//     }
//
//
//}

void huandao_check (void)
{
    int16 i, j=0, k=0, z=0,counter;
    int mid_sum=0;
    float slope;
    if (flag_status == 0)  //标志位为
    {
        if (flag_hd == 0)  //环岛的初步判断,判断是右环岛还是左环岛
        {
            j = 0, k = 0, z = 0,mid_sum=0;
          if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-40&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=0)
          {
              if(!colorchange_check_row(20)&&!colorchange_check_row(25)&&!colorchange_check_row(15)&&!colorchange_check_row(10)&&!colorchange_check_row(30)&&!colorchange_check_row(55)&&!colorchange_check_row(40)&&!colorchange_check_row(50))
               //防止与入库误判
              {
                  counter=0,z=0;
                  for (i = 12; i <= 32; i++)

                    {
                        if (leftedge[i] < 7)
                            j++;
                    }
                  for(i=3;i<18;i++)
                  {
                      mid_sum+=midline[i];
                  }
                  mid_sum=mid_sum/15;
                  slope=Calculate_Slope(midline[8],midline[16],8,16);
                  for (i = 55; i > 35; i -=2)
                  {
                      if (leftedge[i] - leftedge[i + 3] >=0)
                          z++;
                      if(leftedge[i]<7)
                          {z=0;break;}
                  }
                  for (i = 3; i < 57; i+=3)
                                {
                                     if(rightedge[i]>153||(rightedge[i+3]-rightedge[i]>9))
                                         {j=0;break;}
                                }
                  if(z>6&&j>=12&&mid_sum<75&&slope<0)
                  {
                      flag_status=left;//判断为左
                  }
                  j=0;
              }
          }
          else if((leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])<=40&&(leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])>=0)
          {
              if(!colorchange_check_row(20)&&!colorchange_check_row(25)&&!colorchange_check_row(15)&&!colorchange_check_row(10)&&!colorchange_check_row(30)&&!colorchange_check_row(55)&&!colorchange_check_row(40)&&!colorchange_check_row(50))
            //防止与入库误判
              {
                  counter=0,z=0;
              for (i = 12; i <= 32; i++)
                            {
                                if (rightedge[i] > 153)
                                    j++;

                            }
              for(i=3;i<18;i++)
              {
                  mid_sum+=midline[i];
              }
              mid_sum=mid_sum/15;
              slope=Calculate_Slope(midline[8],midline[16],8,16);
              for (i = 55; i > 35; i -=2)
              {
                  if (rightedge[i+3] - rightedge[i] >=0)
                      z++;
                  if(rightedge[i]>153)
                       {z=0;break;}
              }
              for (i = 3; i < 57; i+=3)
                            {
                                 if(leftedge[i]<7||(leftedge[i]-leftedge[i+3]>9))
                                 { j=0;break;}
                            }
                          if(j>=12&&z>=6&&mid_sum>85&&slope>0)
                          {
                              flag_status=right;//判断为右
                          }
                          j=0;
             }
          }
        }
    }
        else if(flag_status==left)//在判断为左的条件下继续判断是不是左环岛
          {
            if(flag_hd==0)
            {
                    for (i = 35; i < 55; i +=2)
                    {
                        if (leftedge[i] - leftedge[i + 3] >=0)
                            z++;
                    }
                    for (i = 2; i <= 30; i += 2)
                    {
                        if (rightedge[i] - rightedge[i + 3] < -0.8)
                        {
                            k++;
                        }
                        else if(rightedge[i]>154&&rightedge[i+1]>154&&rightedge[i+2]>154&&rightedge[i+3]>154)
                        {
                            k=0;break;
                        }
                    }

                    if ( z >6&&k>8&&leftedge[3]>=25&&leftedge[4]>=23&&leftedge[5]>=21)//
                    {
                        flag_hd = left1;
                        gpio_set_level(C13,1);

                    }
            }
            else if(flag_hd==left1)
                         {
                            k=0,z=0;

                                       if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-40&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=0)
                                               {

                                                 for(i=59;i>=29;i-=3)
                                                     {
                                                               if(leftedge[57]<=10)//leftedge[i]<=10&&leftedge[56]<=7
                                                                     { k++;flag_test=2;}
                                                       }
                                                 for(j=1;j<=11;j++)
                                                     {
                                                          if(leftedge[j]-leftedge[j+25]>=30)
                                                                         z++;
                                                     }

                                                          if(z>=5&&k>=5)//
                                                                    flag_hd =left2;

                                                    }
                         }
            else if (flag_hd == left2)
                          {
                                                     j=0,k=0,z=0;
                                                     if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-50&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=10)
                                                  {
                                                        for (i = 1; i < 8; i ++)
                                                        {
                                                            if (leftedge[i]<10 )
                                                                j++;
                                                        }
                                                        for (i = 51; i < 59; i ++)
                                                                       {
                                                                           if (leftedge[i]<10)
                                                                               k++;
                                                                       }

                                                        for (i = 23; i <48; i +=2)
                                                                           {
                                                                               if (leftedge[i] - leftedge[i + 3] >0.8 )
                                                                                   z++;
                                                                           }

                                                }
                                                        if (j >=4&&k>=4&&z>7)//&&midline[30]>=45
                                                        {
                                                            flag_hd = left3;gpio_toggle_level(C13);
                                                        }
                              }
            else  if(flag_hd==left3)
                              {
                                                  j = 0,  z = 0;
                                                  if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-40&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=0)
                                               {
                                                  for (i = 59; i >39; i-=2)
                                                  {
                                                      if (leftedge[i] < 7&&leftedge[58]<7&&leftedge[57]<7&&leftedge[40]<7)
                                                          j++;
                                                  }

                                                  for(i=0;i<16;i++)
                                                       {mid_sum+=midline[i];}
                                                  flag_test=mid_sum/16;
                                                       if((mid_sum/16)<92&&(mid_sum/16)>68)
                                                             z=1;
                                              }
                                                   if (j >6&&z&&leftedge[19]>=40)//
                                                               {
                                                                   flag_hd = left4;gpio_toggle_level(C13);
                                                                   mid_sum=0;
                                                               }
                                  }
            else   if(flag_hd==left4)
                                  {


                                                      if((rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])>=-100&&(rightedge[20]+rightedge[21]+rightedge[22]-rightedge[33]-rightedge[34]-rightedge[35])<=-45)

                                                  {

                                                      k=0,z=0;
                                                      for(i=30;i<50;i++)
                                                          {
                                                          mid_sum+=midline[i];
                                                          if(leftedge[i]<7)
                                                          {
                                                              counter++;
                                                          }
                                                          }
                                                      if((mid_sum/20)<55)
                                                          z=1;
                                                       for (j = 10; j <150 ; j+=10)
                                                       {
                                                              if(mt9v03x_image[8][j]<th+10)
                                                                  k++;
                                                        }
                                                  }

                                                  if(z&&k>=10&&counter>13&&rightedge[57]<150)
                                                      flag_hd=left5;

                                   }
            else if(flag_hd==left5)
                                    {
                                                  if((rightedge[17]+rightedge[18]+rightedge[19]-rightedge[27]-rightedge[26]-rightedge[25])>=60&&(rightedge[17]+rightedge[18]+rightedge[19]-rightedge[27]-rightedge[26]-rightedge[25])<=140)
                                                  {
                                                      j=0;z=0;k=0;
                                                      for(i=1;i<11;i++)
                                                      {
                                                          if(leftedge[i]-leftedge[i+2]>0)
                                                          {
                                                              k++;
                                                          }
                                                      }
                                                     for(i=28;i<52;i+=2)
                                                     {
                                                         if(rightedge[i]-rightedge[i-3]>=2)
                                                          {j=1;continue;}
                                                         else if(j)
                                                         {
                                                             if(rightedge[i+3]-rightedge[i]<=0)
                                                                 {j=0;break;}
                                                         }
                                                     }

                                                     for(i=30;i<=50;i+=2)
                                                          {
                                                              if(leftedge[i]<5)
                                                              {
                                                                 z++;
                                                              }
                                                          }
                                                  }
                                                     if(j&&k>=4&&rightedge[10]>=90&&z>=5&&leftedge[10]>35)
                                                     {   flag_hd=left6;
                                                     gpio_toggle_level(C13);}
                                      }
            else   if(flag_hd==left6)//左右皆丢线
                                               {   j=0,k=0;
                                                   for(i=20;i<50;i+=2)
                                                   {
                                                       if(leftedge[i]<7)
                                                         j++;
                                                   }
                                                   for(i=20;i<50;i+=2)
                                                     {
                                                        if(rightedge[i]>150)
                                                         k++;
                                                     }
                                                   if(j>9&&k>9)
                                                   { flag_hd=left7;gpio_toggle_level(C13);}
                                               }
                                                else   if(flag_hd==left7)
                                               {   j=0;
                                                   for(i=20;i<50;i+=2)
                                                   {
                                                       if(rightedge[i+3]-rightedge[i]<=5&&rightedge[i+3]-rightedge[i]>=3)
                                                           j++;//斜率恢复正常
                                                   }
                                                   for(i=10;i<50;i+=2)
                                                   {
                                                       if(leftedge[i]<5)k++;
                                                   }
                                                   if(j>=10&&k>8)//
                                                      flag_hd=left8;
                                               }
                 else  if(flag_hd==left8)
                                               {   z=0,k=0;
                                                   for (i = 20; i <= 50; i += 5)
                                                   {
                                                      if (leftedge[i] - leftedge[i + 5] > 1)
                                                      z++;

                                                    }
                                                   for(i=30;i<60;i+=5)
                                                   {
                                                       if(leftedge[i]<5)
                                                           z=0;
                                                   }
                                                   for (i = 20; i <=50; i += 5)
                                                   {
                                                       if (rightedge[i] - rightedge[i + 5] < -1)
                                                         {
                                                             k++;
                                                         }
                                                   }

                                                if(z>=3&&k>=3)
                                                    {
                                                        flag_hd=0;gpio_toggle_level(C13);
                                                        flag_status=0;
                                                    }
                                               }
                          }
                    else if(flag_status==right)//在判断为右的条件下，继续判断是不是为右环岛
          {
                      if(flag_hd==0)
                   {
                          for (i = 35; i < 55; i +=2)
                          {
                              if (rightedge[i+3] - rightedge[i] >=0)
                                  z++;
                          }
                          for (i = 2; i <= 30; i += 2)
                          {
                              if (leftedge[i+3] - leftedge[i] < -0.8)
                              {
                                  k++;
                              }
                              else if(leftedge[i]<6&&leftedge[i+1]<6&&leftedge[i+2]<6&&leftedge[i+3]<6)
                              {
                                  k=0;break;
                              }
                          }
                          if (z >6 &&k>8&&rightedge[3]<=115&&rightedge[4]<=115&&rightedge[5]<=115 )//z >6&&
                          {
                              flag_hd = right1;
                              gpio_set_level(C13,1);

                          }
                   }
                     else if(flag_hd==right1)
                       {
                            k=0,z=0;
                            if((leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])<=40&&(leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])>=0)
                            {
                                   for(i=59;i>=29;i-=3)
                                   {
                                       if(rightedge[i]>=152&&rightedge[57]>=152&&rightedge[56]>=152)
                                           k++;
                                   }
                                   for(j=1;j<=11;j++)
                                   {
                                       if(rightedge[j+25]-rightedge[j]>=30)
                                           z++;
                                   }
                            }
                                  if(k>=5&&z>=5)
                                      flag_hd =right2;
                       }
                     else if (flag_hd == right2)
                     {
                                     j=0,k=0,z=0;
                             if((leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])<=40&&(leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])>=0)
                           {
                                  for (i = 3; i < 10; i ++)
                                 {
                                       if (rightedge[i]>150 )
                                        j++;
                                  }
                                  for (i = 51; i < 59; i ++)
                                  {
                                        if (rightedge[i]>155 )
                                         k++;
                                  }

                                    for (i = 23; i <48; i +=2)
                                 {
                                          if (rightedge[i+3] - rightedge[i ] >0.8 )
                                            z++;
                                 }

                              }
                              if (j >=4&&k>=5&&z>7&&midline[30]>=60)//
                                {
                                   flag_hd=right3;gpio_toggle_level(C13);
                                }
                       }

                     else  if(flag_hd==right3)
                       {
                                          j = 0,  z = 0;
                                if((leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])<=40&&(leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])>=0)
                              {
                                for (i = 59; i >39; i-=2)
                                     {
                                        if (rightedge[i] >153&&rightedge[58] >153&&rightedge[57] >153&&rightedge[40] >153)
                                          j++;
                                     }
                                for(i=0;i<16;i++)
                                     {mid_sum+=midline[i];}
                                      flag_test=mid_sum/16;
                                     if((mid_sum/16)<92&&(mid_sum/16)>68)
                                           z=1;
                             }

                          if (j >6&&z&&leftedge[25]<=120)//
                                 {
                                     flag_hd = right4;gpio_toggle_level(C13);
                                  }

                       }
                     else if(flag_hd==right4)
                      {
                              if((leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])<=110&&(leftedge[20]+leftedge[21]+leftedge[22]-leftedge[33]-leftedge[34]-leftedge[35])>=40)
                          {

                              k=0,z=0;
                              for(i=30;i<50;i++)
                                  {
                                  mid_sum+=midline[i];
                                  if(rightedge[i]>150)
                                    {
                                      counter++;
                                     }
                                  }
                              if((mid_sum/20)>87)
                                  z=1;
                               for (j = 10; j <150 ; j+=10)
                               {
                                      if(mt9v03x_image[10][j]<th+10)
                                          k++;
                                }
                          }

                          if(z&&k>=10&&counter>10)//
                              flag_hd=right5;

                      }
                     else if(flag_hd==right5)
                     {
                         if((leftedge[17]+leftedge[18]+leftedge[19]-leftedge[27]-leftedge[26]-leftedge[25])<=-60&&(leftedge[17]+leftedge[18]+leftedge[19]-leftedge[27]-leftedge[26]-leftedge[25])>=-140)
                          {        j=0;z=0;k=0;
                                   for(i=1;i<11;i++)
                                        {
                                            if(rightedge[i+2]-rightedge[i]>0)
                                            {
                                                k++;
                                            }
                                        }
                                   for(i=28;i<52;i+=2)
                                   {
                                       if(leftedge[i-3]-leftedge[i]>=2)
                                        {j=1;continue;}
                                       else if(j)
                                       {
                                           if(leftedge[i]-leftedge[i+3]<=0)
                                               {j=0;break;}
                                       }
                                   }
                                   for(i=30;i<=50;i+=2)
                                        {
                                            if(rightedge[i]>155)
                                            {
                                               z++;
                                            }
                                        }
                                }
                                   if(j&&z>=5&&k>=4&&leftedge[10]<=70&&rightedge[10]<125)
                                   {   flag_hd=right6;
                                   gpio_toggle_level(C13);}
                       }
                     else if(flag_hd==right6)//左右皆丢线
                      {   j=0,k=0;
                          for(i=20;i<50;i+=2)
                          {
                              if(leftedge[i]<7)
                                j++;
                          }
                          for(i=20;i<50;i+=2)
                            {
                               if(rightedge[i]>150)
                                k++;
                            }
                          if(j>9&&k>9)
                          { flag_hd=right7;gpio_toggle_level(C13);}
                      }
                     else  if(flag_hd==right7)
                     {   j=0;
                         for(i=20;i<50;i+=2)
                         {
                             if(leftedge[i]-leftedge[i+3]<=5&&leftedge[i]-leftedge[i+3]>=3)
                                 j++;//斜率恢复正常
                         }
                         for(i=10;i<50;i+=2)
                         {
                             if(rightedge[i]>153)
                                 k++;
                         }
                         if(j>=10&&k>8)//
                            flag_hd=right8;
                     }
                     else if(flag_hd==right8)
                     {   z=0,k=0;
                         for (i = 20; i <= 50; i += 5)
                         {
                            if (leftedge[i] - leftedge[i + 5] > 1)
                            z++;

                          }
                         for(i=60;i>=30;i-=5)
                         {
                             if(rightedge[i]>155)
                                 z=0;
                         }
                         for (i = 20; i <=50; i += 5)
                         {
                         if (rightedge[i] - rightedge[i + 5] < -1)
                           {
                               k++;
                           }
                         }

                      if(z>=3&&k>=3)
                          {flag_hd=0;gpio_toggle_level(C13);
                          flag_status=0;
                          }
                     }

          }
 }



//void sancha_check ()  //三岔识别
//{
//    int i, j, y, k, z;
//    static int flag_sc_time = 1;  //进入三岔次数
//    if (flag_sc == 0)  //未进入三岔时flag_sc都等于0
//    {
//        j = 0;
//        for (i = 10; i <= 30; i += 5)  //三岔的预判断
//        {
//            if (j == 0)
//            {
//                if (leftedge[i] - leftedge[i + 5] < -1)
//                    j++;
//            }
//            if (j != 0)  //这时前面那个点真的被发现的话，j就不等于0，然后在进行一次判断，若还是有一个特殊的点使远处的边界点小于近处的边界点
//                         //则j再++，相当于+2，但如果发现是误判则退出循环，接下来j都是大于0的，所以只执行下面的判断语句，直到发现了一个不满足这个条件的点
//            {
//                if (leftedge[i] - leftedge[i + 5] < -1)
//                    j++;
//                else
//                    break;
//            }
//        }
//        i += 5;                    //为了防止提前跳出循环的情况，所以直接从最远的点开始操作
////         for(;i<=60;i+=5)//该循环用来判定是否下面的线也是上小下大，如果是，则判定为不是三岔，是利用y和k来判定的
////      {
////            if(leftedge[i]-leftedge[i+5]<-1) y=0;//左边界特别小也不可以
////      }
//        k = 0;
//        for (i = 0; i <= 30; i += 5)
//        {
//            if (k == 0)
//            {
//                if (rightedge[i] - rightedge[i + 5] > 1)
//                    k++;
//            }
//            if (j != 0)
//            {
//                if (rightedge[i] - rightedge[i + 5] > 1)                    //可以通过改变数值来改变灵敏度
//                    k++;
//                else
//                    break;
//            }
////         i+=5;
////         for(;i<=60;i+=5)
////         {
////            if(rightedge[i]-rightedge[i+5]>3)k=0;
////         }
//
//            if (j >= 3 && k >= 3)
//            {
//                if (flag_sc1 == 1)
//                {
//                    flag_status = leftfok;
//                    flag_sc = leftfok1;
//                    flag_sc1 = 0;                    //下一次从右边进去
//                }
//                if (flag_sc1 == 0)
//                {
//                    flag_status = rightfok;
//                    flag_sc = rightfok1;
//                    flag_sc1 = 1;                    //下一次从左边进去
//                }
//            }
//        }
//    }
//    else if (flag_status == rightfok)                    //三岔的内部判断
//    {
//        if (flag_sc == rightfok1)
//        {
//            j = 0;
//            for (i = 0; i < 20; i++)                    //这东西要看扫中线从哪里开始
//            {
//                for (z = 84; z < 104; z++)
//                {
//                    if (mt9v03x_image[i][z] == 0)
//                        j++;
//                }
//            }
//            if (j >= 50)
//            {
//                flag_sc = rightfok2;
//            }
//        }
//        else if (flag_sc == rightfok2)
//        {
//            j = 0, k = 0;
//            for (i = 40; i < 60; i++)
//            {
//                if (leftedge[i] < 3)
//                    j++;
//            }
//            for (i = 0; i < 30; i += 3)
//            {
//                if (rightedge[i] - rightedge[i - 3] < 0)
//                    k++;
//            }
//            if (j >= 4 && k >= 3)
//            {
//                flag_sc = rightfok3;
//            }
//
//        }
//        else if (flag_sc == rightfok3)                    //状态4的判断，已经在直道内的情况
//        {
//            k = 0;
//            j = 0;
//            for (i = 30; i < 57; i++)
//            {
//                if (leftedge[i] - leftedge[i + 3] > 1)
//                    j++;
//            }
//            for (i = 30; i < 57; i++)
//            {
//                if (rightedge[i] - rightedge[i + 3] < -1)
//                    k++;
//            }
//            if (j >= 7 && k >= 7)
//            {
//                flag_sc = rightfok4;
//            }
//            else if (flag_sc == rightfok4)                    //出三岔的情况
//            {
//                j = 0, k = 0;
//                for (i = 10; i <= 40; i++)
//                {
//                    if (leftedge[i] - leftedge[i + 5] < -10)
//                        j = 1;
//
//                }
//                for (i = 40; i <= 55; i++)
//                {
//                    if (rightedge[i] - rightedge[i + 5] < -1)
//                        j++;
//                }
//                if (j = 1 && k > 5)
//                {
//                    flag_sc = rightfok5;
//                }
//            }
//        }
//
//    }
//    else if (flag_status == leftfok)
//    {
//        if (flag_sc == leftfok1)
//        {
//            j = 0;
//            {
//                for (z = 84; z < 104; z++)
//                    if (mt9v03x_image[i][z] == 0)
//                        j++;
//            }
//            if (j >= 7)
//            {
//                flag_sc = leftfok2;
//            }
//        }
//        else if (flag_sc == rightfok2)                    //状态3的判断
//        {
//            j = 0, k = 0;
//            for (i = 20; i < 50; i++)
//            {
//                if (leftedge[i] - leftedge[i + 3] > 3)
//                    j++;
//            }
//            for (i = 20; i < 50; i++)
//            {
//                if (rightedge[i] - rightedge[i + 8] < -1)
//                    k++;
//            }
//            if (j >= 15 && k >= 8)
//            {
//                flag_sc = rightfok3;
//            }
//
//        }
//        else if (flag_sc == leftfok3)                    //状态4的判断，已经在直道内的情况
//        {
//            j = 0;
//            for (i = 70; i < 100; i++)
//            {
//                if (leftedge[i] - leftedge[i + 3] > 5)
//                    j++;
//            }
//            if (j >= 15)
//            {
//                flag_sc = leftfok4;
//            }
//            else if (flag_sc == leftfok4)                    //,状态5的判断，出三岔的情况
//            {
//                j = 0;
//                for (i = 0; i <= 30; i++)
//                {
//                    if (leftedge[i] - leftedge[i + 5] < -3)
//                        j++;
//                }
//                for (i = 0; i <= 30; i++)
//                {
//                    if (rightedge[i] - rightedge[i + 5] < -3)
//                        j++;
//                }
//                if (j > 5 && k > 5)
//                {
//                    flag_sc = rightfok5;
//                }
//
//            }
//        }
//
//    }
//
//}
//void shizi_check()不好用
//{
//   int i,j;
//   int y,k;
//    if(flag_status==1)
//    {
//        if(flag_sz==0)
//        {
//            for(i=10;i<=50;i+=2)
//            {
//                if(leftedge[i+2]-leftedge[i]>8&&leftedge[i+3]-leftedge[i]>8&&leftedge[i+3]-leftedge[i]>8)
//                    {y=1;break;}
//            }
//            for(i=0;i<=50;i++)
//             {
//                if(rightedge[i]>=175)
//                      k++;
//             }
//            if(y==1&&k>7)
//            {flag_sz=shizi1;}
//        }
//
//
//
//    }
//
//}
void shizi_check(void)
{
        int i,j,k,m;
     if(flag_status==1)
     {  if(flag_sz==0)
        {
            j=0;
            for(i=0;i<=10;i++)
            {
                if(rightedge[i]-leftedge[i]<=70)
                    j++;
            }
            k=0;
            for(i=11;i<=40;i++)
            {
                if(rightedge[i]-leftedge[i]>=140)
                    k++;
            }
            m=0;
            for(i=40;i<=60;i++)
            {
                if(rightedge[i]-leftedge[i]>=70 && rightedge[i]-leftedge[i]<=110)
                    m++;
            }

            if(k>=5 && k>=20 && m>=15)
            {
                flag_sz=1;
            }
        }

        if(flag_sz==1)
        {


            j=0;
            k=0;
            for(i=0;i<=40;i++)
            {
                if(rightedge[i]-rightedge[i+1]<0)
                {
                    j++;
                }
                if(leftedge[i]-leftedge[i+1]>0)
                {
                    k++;
                }
            }
            if(j>=20 && k>=20 && rightedge[55]>145)
            {
                flag_sz=2;
            }




        }
         if(flag_sz==2)
         {


               j=0;
             if((rightedge[59]<=140 &&leftedge[59]>=20 ) &&(rightedge[40]<=135 &&leftedge[40]>=25 ) )
               {
                  j=1;
                }
                 if( j==1 && leftedge[20]-leftedge[30]<=-30 )
                    {
                       flag_sz=3; //切换电磁循迹
                    }



         }




          if(flag_sz==3)
          {
              if((midline[60]>=120||midline[60]<=60)&&(midline[30]>=120||midline[30]<=60))
                  flag_sz=4; //摄像头拍不到白色赛道
          }

          if(flag_sz==4)
           {
              j=0;
                 for(i=0;i>=50;i++)
                 {
                     if(rightedge[i]-leftedge[i]>=145)
                      j++;
                            }
                 if(j>=40)
                     flag_sz=4;
                   flag_sz=5;
           }

          //直到找到标志位6之前一直用电磁循迹
          if(flag_sz==5)
          {
              j=0;
              for(i=60;i>=30;i--)
              {
                  if(rightedge[i]-leftedge[i]>=90)
                      j++;
              }
              k=0;
              if(rightedge[15]-leftedge[15]>140)
              {
                  k=1;
              }
              if(j>=20 && k==1)
                  flag_sz=6;
          }


            if(flag_sz==6)
            {
                j=0;
                for(i=5;i<=60;i++)
                {
                    if(rightedge[i]-leftedge[i]>=150)
                        j++;
                }
                if(j>=40)
                           flag_sz=7;


            }
            if(flag_sz==7)
            {

                j=0;
                for(i=0;i<=60;i++)
                {
                    if(leftedge[i]-leftedge[i+3]>=3)
                        j++;
                }
                if(j>=35 && rightedge[55]<=140)
                    flag_sz=8;
            }

     }
}


int get_line_max(int t)
{
    int i,j;
    int x;
    int right_black=50,ima[60][188];

    for(i=60;i>0;i--)
        for(j=0;j<188;j++)
        {   if(mt9v03x_image[i][j]>1)
            ima[i][j]=1;
            else
            ima[i][j]=0;
        }
      i=0;
     for(x=183;x>=5;x--)
     {
         if(ima[t][x]==0&&ima[t][x+1]==0)
         {

             right_black=x;
             break;
         }

     }

//     for(j=i+1;j<=50;j++)
//        {
//            black[j]=1;
//        }
//     for(x=0;x>=50;x++)
//     {
//        if(black[x]>=max)
//        {
//            max=black[x];
//        }
//     }
     return right_black;
}
int get_line_min(int t)
{
    int i,j;
    int x;
    int left_black,ima[60][188];
    for(i=60;i>0;i--)
        for(j=0;j<188;j++)
        {   if(mt9v03x_image[i][j]>1)
            ima[i][j]=1;
            else
            ima[i][j]=0;
        }
      i=0;
     for(x=5;x<=183;x++)
     {
         if(ima[t][x]==0&&ima[t][x+1]==0)
         {

             left_black=x;
             break;

         }
     }
//     for(j=i+1;j<=50;j++)
//        {
//            black[j]=1;
//        }
//     for(x=1;x<=50;x++)
//     {
//        if(black[x]<=min)
//       {
//            min=black[x];
//        }
//     }
     return left_black;
}
void elements_reset ()                    //
{
    flag_sc = 0;
    flag_hd = 0;

}

