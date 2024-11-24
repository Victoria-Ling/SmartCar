/*
 * camera.c
 *
 *  Created on: Mar 24, 2023
 *      Author: 86157
 */


//注意：所有与图像相关的行下标i都是从远到近对应0~MT9V03X_H-1，因此循环一般从i=MT9V03X_H-1开始

#include "camera.h"
//#define         USED_ROW                60  //用于透视图的行列
//#define         USED_COL                160

//#define PER_IMG     mt9v03x_image//SimBinImage:用于透视变换的图像



#define border_min 2
#define border_max 158

int th=110;//二值化阈值
int16 SAR_TH=38;
int16 leftedge[MT9V03X_H];      //左边界j值数组，0表示左边界丢失
int16 rightedge[MT9V03X_H];     //右边界j值数组，MT9V03X_W-1表示右边界丢失
int16 midline[MT9V03X_H];    //中心线数组
int16 ima[60][160];
unsigned char leftside[IMAGE_H],rightside[IMAGE_H];
//uint8_t *PerImg_ip[RESULT_ROW][RESULT_COL];
uint8 mt9v03x_image_show[IMAGE_H][IMAGE_W];
//-------------------------------------------------------------------------------------------------------------------
//  函数功能：图像处理，用于计算图像边界
//  参数：void
//  返回值：void
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
#define  qianzan1  1
#define  qianzan2  1
#define  qianzan3  1
#define  qianzan4  1
#define  qianzan5  1
#define  qianzan6  5
#define  qianzan7  10
#define  qianzan8  10
#define  qianzan9  10
#define  qianzan10  5
uint8 weight1[60]={
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,//注意斜率的变化引起的跳变,要平滑
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    qianzan5, qianzan5, qianzan5, qianzan5, qianzan5,qianzan6, qianzan6, qianzan6, qianzan6, qianzan6,
                   qianzan7,qianzan7,qianzan7,qianzan7,qianzan7,qianzan8,qianzan8,qianzan8,qianzan8,qianzan8,
                   qianzan9,qianzan9,qianzan9,qianzan9,qianzan9,qianzan10,qianzan10,qianzan10,qianzan10,qianzan10,
                   };                            //基础  速度快时要增大前面的权重
uint8 weight3[60]={ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 3, 3, 3, 3, 3,
                   10,10,10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,10,10,
                   3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                  };                               //环岛内
uint8 weight5[60]={
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                   3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                   10,10,10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,10,10,
                   10,10,10,10,10,10,10,10,10,10,
                   };                            //坡道内
int32 error_average=0;//前1/3中线位置(用于加减速)

uint8 circle_offset=30;//调试档环岛偏移

void Cam_error(void)//偏差加权计算
{
    uint8 i;//用于for
    int sum=0;//中线之和
    int add=0;//权重之和
    int sum_average=0;//平均中线之和
    int add_average=0;//点数累加
    int8 mid=80;//中线

    ////////////处理偏差////////////

    Cam_Servo_error_pre_pre=Cam_Servo_error_pre;
    Cam_Servo_error_pre=Cam_Servo_error;

    ////////////处理error////////////

    for(i=10;i<MT9V03X_H-1;i++)//前10行舍弃
    {

        if(flag_hd==left4)
        {
            add+=weight3[i];
            sum+=weight3[i]*midline[i];
        }
        else if(ramp_flag==1)
        {
            add+=weight5[i];
            sum+=weight5[i]*midline[i];
        }
        else
        {
            add+=weight1[i];
            sum+=weight1[i]*midline[i];
        }
        if(i>((MT9V03X_H*2)/3))
        {
            sum_average+=midline[i];
            add_average++;
        }
    }
    /*if(length>63)//(工大是这种算法，设定一行，然后找离这行最近的三行，比较切，可以优化尝试一下)
    {
        add=3;
        sum=mid_point[error_line].x+mid_point[error_line-1].x+mid_point[error_line-2].x;
    }
    else if(length<63)
    {
        add=3;
        sum=mid_point[length-3].x+mid_point[length-4].x+mid_point[length-5].x;
    }*/
    ////////////处理中线位置////////////
    if(flag_hd==left4||flag_hd==right4)//环岛中线偏移，减小kp,方便大环卡顿，大环也能内切了
    {
        if(flag_status==left)
            mid=80+circle_offset;
        else if(flag_status==right)
            mid=80-circle_offset;
    }
    else
        mid=80;
    Cam_Servo_error=(int)(mid-(sum/add));//基本元素的偏差计算
    error_average=(int)(mid-(sum_average/add_average));//中线位置
}
void search_side(int wide)
{
    int i;
    for(i=wide/2;i>0;i-=1)
    {
        if( (((mt9v03x_image[IMAGE_H-2][i]-mt9v03x_image[IMAGE_H-2][i-1])<<8) / (mt9v03x_image[IMAGE_H-2][i]+mt9v03x_image[IMAGE_H-2][i-1]) )>WHITE_TH)
        {
            leftside[IMAGE_H-2]=i-1;
            break;
        }
    }
    for(i=wide/2;i<wide;i+=1)
    {
        if( (((mt9v03x_image[IMAGE_H-2][i]-mt9v03x_image[IMAGE_H-2][i+1])<<8) / (mt9v03x_image[IMAGE_H-2][i]+mt9v03x_image[IMAGE_H-2][i+1]) )>WHITE_TH)
        {
            rightside[IMAGE_H-2]=i+1;
            break;
        }
    }
}

void image_boundry_rec(int image_h,int image_w)
{
    search_side(image_w);
    int i;
    int last_x=leftside[image_h-2],last_y=image_h-2;
    int cha,he,sar;
    int totle_point=image_h-2;
    int new_x1,new_y1,new_x2,new_y2;
//    char seeds_l[12][2]={{0,-2},{1,-2},{2,-2},{2,-1},{2,0},{2,1},{1,2},{0,2},{-1,2},{-2,1},{-2,0},{-2,-1},{-1,-2}};
    char seeds_l[8][2]= { { 0,  1}, {  1, 1 }  , {  1, 0}, {  1, -1 },{ 0, -1},{ -1, -1}, { -1,  0},{ -1, 1}, };
    char seeds_r[8][2]= { { 0,  1}, { -1, 1 }  , { -1, 0}, { -1, -1 },{ 0, -1},{  1, -1}, {  1,  0},{  1, 1}, };

    while(totle_point--)
    {
        for (i=0;i<8;i++)
        {
            new_x1=last_x+seeds_l[i][0];
            new_y1=last_y+seeds_l[i][1];
            new_x2=last_x+seeds_l[i+1][0];
            new_y2=last_y+seeds_l[i+1][1];
            if(new_x2<0)
            {
                last_x=0;
                last_y=new_y2;
                leftside[last_x]=last_y;
                break;
            }
            if(new_y2>image_h)break;
            cha= mt9v03x_image[ new_y1 ]  [ new_x1 ] -  mt9v03x_image[new_y2] [ new_x2 ];
            he=  mt9v03x_image[ new_y1 ]  [ new_x1 ] +  mt9v03x_image[new_y2] [ new_x2 ];
            sar=(cha<<8)/he;
            if(sar>WHITE_TH)
            {
                last_x=last_x+seeds_l[i+1][0];
                last_y=last_y+seeds_l[i+1][1];
                leftside[last_y]=last_x;
                break;
            }
        }
    }
    totle_point=image_h-2;
    last_x=rightside[image_h-2],last_y=image_h-2;
    while(totle_point--)
    {
        for (i=0;i<8;i++)
        {
            new_x1=last_x+seeds_r[i][0];
            new_y1=last_y+seeds_r[i][1];
            new_x2=last_x+seeds_r[i+1][0];
            new_y2=last_y+seeds_r[i+1][1];
            if(new_x2>=image_w)
            {
                last_x=image_w-1;
                last_y=new_y2;
                rightside[last_x]=last_y;
                break;
            }
            if(new_y2>image_h)break;
            cha= mt9v03x_image[ new_y1 ]  [ new_x1 ] -  mt9v03x_image[new_y2] [ new_x2 ];
            he=  mt9v03x_image[ new_y1 ]  [ new_x1 ] +  mt9v03x_image[new_y2] [ new_x2 ];
            sar=(cha<<8)/he;
            if(sar>WHITE_TH)
            {
                last_x=last_x+seeds_r[i+1][0];
                last_y=last_y+seeds_r[i+1][1];
                rightside[last_y]=last_x;
                break;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
void image_boundary_process(void)
{
    int16 i;                          //循环变量
    int16 init_y = MT9V03X_W/2;            //搜索边界的起始点

    //计算左右边界
    for(i = MT9V03X_H-1; i >= 1; i -= 1)
    {
        //边界搜索起点设置，选用上一行的中点作为下一行的起始点
        if(i != MT9V03X_H-1)
            init_y = midline[i+1];
        else
        {
            init_y = MT9V03X_W/2;
        }

        //计算此行左右边界
        row_boundary_process(i, init_y);
        midline[i] = (leftedge[i]+rightedge[i])/2;
    }

}
//-------------------------------------------------------------------------------------------------------------------
//  函数功能：给定第i行和初始j值，计算该行的左右边界
//  参数：pos_x（第pos_x行），pos_y（初始边界pos_y值)
//  返回值：void
//-------------------------------------------------------------------------------------------------------------------
void row_boundary_process(int pos_x, int pos_y)
{
    int j;                    //列循环变量

    float cha, he, sar;            //sar为差和比值

    //计算第pos_x行左边界
    leftedge[pos_x] = 0;                                //当左边界找不到时默认为0
    for(j = pos_y; j >= 3; j -= 2)    //此处终止值选用SAR_DW+1是因为要保证j-SAR_DW要大于0，因为我们摄像头采集到的数据最左边一列全为0，数据是错的，各种宏见h文件注释
    {
        //此处选用这种方法是因为可以不用浮点数乘法，加快运算速度
        cha = (float)((mt9v03x_image[pos_x][j] - mt9v03x_image[pos_x][j-3])<<8);
        he  = (float)(mt9v03x_image[pos_x][j] + mt9v03x_image[pos_x][j-3]+1);
        sar = abs_f(cha/he);
        if(sar > SAR_TH)
        {
            leftedge[pos_x] = j-2;
            break;
        }
    }

    //计算第pos_x行的右边界
    rightedge[pos_x] = MT9V03X_W-1;                     //当右边界找不到时默认为MT9V03X_W-1
    for(j = pos_y; j <= MT9V03X_W-3; j +=2)
    {
        cha = (float)((mt9v03x_image[pos_x][j]-mt9v03x_image[pos_x][j+3])<<8);
        he = (float)(mt9v03x_image[pos_x][j]+mt9v03x_image[pos_x][j+3]+1);
        sar = abs_f(cha/he);
        if(sar > SAR_TH)
        {
            rightedge[pos_x] = j+2;
            break;
        }
    }
}
void show_line(void)//将中线与边界线在显示的图像中描黑
{
    int i,j;
    if(flag_tc==3||flag_tc==4)
    {

        for(i = MT9V03X_H; i >= 0; i -= 1)
          {
              //画赛道中线
            for(j=MT9V03X_W;j>=0;j--)
            {
                mt9v03x_image_show[i][j]=mt9v03x_image[i][j];
            }
            mt9v03x_image_show[i][leftedge[i]] = 0;
            mt9v03x_image_show[i][rightedge[i]] = 0;
            mt9v03x_image_show[i][midline[i]] = 0;

          }

    }

}
//-------------------------------------------------------------------------------------------------------------------
//  函数功能：计算浮点数绝对值
//  参数：float
//  返回值：float
//-------------------------------------------------------------------------------------------------------------------
float abs_f(float x)
{
    if(x < 0)
        return -x;
    else
        return x;
}
void erzhihua (void)//二值化函数
{
    int i,j;

    //th=GetOSTU();//GetOSTU();

    for (i=0;i<MT9V03X_H;i++)//行数遍历
    {
        for (j=0;j<MT9V03X_W;j++)//列数遍历
        {
            //如果灰度值大于阈值(WHITE_TH),那么将该点灰度值转换成255，小于则转化//成0
            if(mt9v03x_image[i][j]<th)mt9v03x_image[i][j]=0;//该点变黑
            else mt9v03x_image[i][j]=255;//该点变白
        }
    }
}
short GetOSTU ()
{
signed short i, j;
unsigned long Amount = 0;
unsigned long PixelBack = 0;
unsigned long PixelshortegralBack = 0;
unsigned long Pixelshortegral = 0;
signed long PixelshortegralFore = 0;
signed long PixelFore = 0;
float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
signed short MinValue, MaxValue;
signed short Threshold = 0;
unsigned char HistoGram[256]; //

for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

for (j = 0; j < MT9V03X_H; j++)
    {
        for (i = 0; i < MT9V03X_W; i++)
        {
        HistoGram[mt9v03x_image[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++); //获取最小灰度的值

for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

if (MaxValue == MinValue)
return MaxValue; // 图像中只有一个颜色
if (MinValue + 1 == MaxValue)
return MinValue; // 图像中只有二个颜色

for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        // 像素总数

Pixelshortegral = 0;
for (j = MinValue;j <= MaxValue; j++)
{
Pixelshortegral += HistoGram[j] * j; //灰度值总数
}
SigmaB = -1;
for (j = MinValue; j < MaxValue; j++)
{
    PixelBack = PixelBack + HistoGram[j]; //前景像素点数
    PixelFore = Amount - PixelBack; //背景像素点数
    OmegaBack = (float) PixelBack / Amount; //前景像素百分比
    OmegaFore = (float) PixelFore / Amount; //背景像素百分比
    PixelshortegralBack += HistoGram[j] * j; //前景灰度值
    PixelshortegralFore = Pixelshortegral - PixelshortegralBack; //背景灰度值
    MicroBack = (float) PixelshortegralBack / PixelBack; //前景灰度百分比
    MicroFore = (float) PixelshortegralFore / PixelFore; //背景灰度百分比
    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore); //计算类间方差
    if (Sigma > SigmaB) //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
    {
        SigmaB = Sigma;
        Threshold = j;
    }
    if(Sigma < SigmaB)
    {
        break;
    }
}
return Threshold; //返回最佳阈值;
}
void getmidline()
{int16 i,j,L,R;//高度
int16 x,y;

 //   mt9v03x_image[i][j]


    for(i=MT9V03X_H;i>0;i--)
        for(j=0;j<MT9V03X_W;j++)
        {   if(mt9v03x_image[i][j]>1)
            ima[i][j]=1;
            else
            ima[i][j]=0;
        }


   for(y=MT9V03X_H;y>0;y--)
   {
       for(x=MT9V03X_W;x>94;x--)
       {
           if(ima[y][x-1]==0&&ima[y][x-2]==1&&ima[y][x]==0)
           {
                rightedge[y]=x;

                R=rightedge[y]; break;

           }
       }

       for(x=0;x<94;x++)
          {
                  if(ima[y][x-1]==0&&ima[y][x+1]==1&&ima[y][x]==0)
               {
                     leftedge[y]=x;

                     L=leftedge[y]; break;

                }
           }
       midline[y]=(L+R)/2;
   }

}





////--------------------------------------------------------------------------------------------------------------用于八邻域找点
int my_abs(int value)
{
if(value>=0) return value;
else return -value;
}

int16 limit_a_b(int16 x, int a, int b)
{
    if(x<a) x = a;
    if(x>b) x = b;
    return x;
}


int16 limit1(int16 x, int16 y)
{
    if (x > y)             return y;
    else if (x < -y)       return -y;
    else                return x;
}
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
#define GrayScale 256
    uint16 Image_Width  = col;
    uint16 Image_Height = row;
    int X; uint16 Y;
    uint8* data = image;
    int HistGram[GrayScale] = {0};

    uint32 Amount = 0;
    uint32 PixelBack = 0;
    uint32 PixelIntegralBack = 0;
    uint32 PixelIntegral = 0;
    int32 PixelIntegralFore = 0;
    int32 PixelFore = 0;
    double OmegaBack=0, OmegaFore=0, MicroBack=0, MicroFore=0, SigmaB=0, Sigma=0; // 类间方差;
    uint8 MinValue=0, MaxValue=0;
    uint8 Threshold = 0;


    for (Y = 0; Y <Image_Height; Y++) //Y<Image_Height改为Y =Image_Height；以便进行 行二值化
    {
        //Y=Image_Height;
        for (X = 0; X < Image_Width; X++)
        {
        HistGram[(int)data[Y*Image_Width + X]]++; //统计每个灰度值的个数信息
        }
    }
    for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值

    if (MaxValue == MinValue)
    {
        return MaxValue;          // 图像中只有一个颜色
    }
    if (MinValue + 1 == MaxValue)
    {
        return MinValue;      // 图像中只有二个颜色
    }

    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        Amount += HistGram[Y];        //  像素总数
    }

    PixelIntegral = 0;
    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        PixelIntegral += HistGram[Y] * Y;//灰度值总数
    }
    SigmaB = -1;
    for (Y = MinValue; Y < MaxValue; Y++)
    {
          PixelBack = PixelBack + HistGram[Y];    //前景像素点数
          PixelFore = Amount - PixelBack;         //背景像素点数
          OmegaBack = (double)PixelBack / Amount;//前景像素百分比
          OmegaFore = (double)PixelFore / Amount;//背景像素百分比
          PixelIntegralBack += HistGram[Y] * Y;  //前景灰度值
          PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
          MicroBack = (double)PixelIntegralBack / PixelBack;//前景灰度百分比
          MicroFore = (double)PixelIntegralFore / PixelFore;//背景灰度百分比
          Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
          if (Sigma > SigmaB)//遍历最大的类间方差g
          {
              SigmaB = Sigma;
              Threshold = (uint8)Y;
          }
    }
   return Threshold;
}


uint8 original_image[MT9V03X_H][MT9V03X_W];
uint8 image_thereshold;//图像分割阈值

void Get_image(uint8(*mt9v03x_image)[MT9V03X_W])//将图像的值用另一个数组保存起来
{
#define use_num     1
    uint8 i = 0, j = 0, row = 0, line = 0;
    for (i = 0; i < MT9V03X_H; i += use_num)          //
    {
        for (j = 0; j <MT9V03X_W; j += use_num)     //
        {
            original_image[row][line] = mt9v03x_image[i][j];
            line++;
        }
        line = 0;
        row++;
    }
}

uint8 bin_image[MT9V03X_H][MT9V03X_W];//图像数组
void turn_to_bin(void)
{
  uint8 i,j;
 image_thereshold = otsuThreshold(original_image[0], MT9V03X_W, MT9V03X_H);//GetOSTU();th;
  for(i = 0;i<MT9V03X_H;i++)
  {
      for(j = 0;j<MT9V03X_W;j++)
      {
          if(original_image[i][j]>image_thereshold)bin_image[i][j] = 0;
          else bin_image[i][j] = 255;
      }
  }
}

uint8 start_point_l[2] = { 0 };//左边起点的x，y值
uint8 start_point_r[2] = { 0 };//右边起点的x，y值
uint8 get_start_point(uint8 start_row)
{
    uint8 i = 0,l_found = 0,r_found = 0;
    //清零
    start_point_l[0] = 0;//x
    start_point_l[1] = 0;//y

    start_point_r[0] = 0;//x
    start_point_r[1] = 0;//y

        //从中间往左边，先找起点
    for (i = MT9V03X_W / 2; i > border_min; i--)
    {
        start_point_l[0] = i;//x
        start_point_l[1] = start_row;//y
        if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
        {
            //printf("找到左边起点image[%d][%d]\n", start_row,i);
            l_found = 1;
            break;
        }
    }

    for (i = MT9V03X_W / 2; i < border_max; i++)
    {
        start_point_r[0] = i;//x
        start_point_r[1] = start_row;//y
        if (bin_image[start_row][i] == 255 && bin_image[start_row][i + 1] == 0)
        {
            //printf("找到右边起点image[%d][%d]\n",start_row, i);
            r_found = 1;
            break;
        }
    }

    if(l_found&&r_found)return 1;
    else {
        //printf("未找到起点\n");
        return 0;
    }
}
#define USE_num 300 //定义找点的数组成员个数按理说300个点能放下，但是有些特殊情况确实难顶，多定义了一点

 //存放点的x，y坐标
uint16 points_l[(uint16)USE_num][2] = { {  0 } };
uint16 points_r[(uint16)USE_num][2] = { {  0 } };
uint16 dir_r[(uint16)USE_num] = { 0 };
uint16 dir_l[(uint16)USE_num] = { 0 };
uint16 data_stastics_l = 0;
uint16 data_stastics_r = 0;
uint8 hightest = 0;
void search_l_r(uint16 break_flag, uint8(*image)[MT9V03X_W], uint16 *l_stastic, uint16 *r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8*hightest)
{

    uint8 i = 0, j = 0;

    uint8 search_filds_l[8][2] = { {  0 } };
    uint8 index_l = 0;
    uint8 temp_l[8][2] = { {  0 } };
    uint8 center_point_l[2] = {  0 };
    uint16 l_data_statics;
    static int8 seeds_l[8][2] = { {0,  1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,  0},{1, 1}, };
    uint8 search_filds_r[8][2] = { {  0 } };
    uint8 center_point_r[2] = { 0 };
    uint8 index_r = 0;
    uint8 temp_r[8][2] = { {  0 } };
    uint16 r_data_statics;
    static int8 seeds_r[8][2] = { {0,  1},{1,1},{1,0}, {1,-1},{0,-1},{-1,-1}, {-1,  0},{-1, 1}, };
    l_data_statics = *l_stastic;
    r_data_statics = *r_stastic;
    center_point_l[0] = l_start_x;//x
    center_point_l[1] = l_start_y;//y
    center_point_r[0] = r_start_x;//x
    center_point_r[1] = r_start_y;//y
    while (break_flag--)
    {
        for (i = 0; i < 8; i++)
        {
            search_filds_l[i][0] = center_point_l[0] + seeds_l[i][0];//x
            search_filds_l[i][1] = center_point_l[1] + seeds_l[i][1];//y
        }
        points_l[l_data_statics][0] = center_point_l[0];//x
        points_l[l_data_statics][1] = center_point_l[1];//y
        l_data_statics++;//
        for (i = 0; i < 8; i++)
        {
            search_filds_r[i][0] = center_point_r[0] + seeds_r[i][0];//x
            search_filds_r[i][1] = center_point_r[1] + seeds_r[i][1];//y
        }
        points_r[r_data_statics][0] = center_point_r[0];//x
        points_r[r_data_statics][1] = center_point_r[1];//y

        index_l = 0;
        for (i = 0; i < 8; i++)
        {
            temp_l[i][0] = 0;
            temp_l[i][1] = 0;
        }

        for (i = 0; i < 8; i++)
        {
            if (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0
                && image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] == 255)
            {
                temp_l[index_l][0] = search_filds_l[(i)][0];
                temp_l[index_l][1] = search_filds_l[(i)][1];
                index_l++;
                dir_l[l_data_statics - 1] = (i);
            }

            if (index_l)
            {

                center_point_l[0] = temp_l[0][0];//x
                center_point_l[1] = temp_l[0][1];//y
                for (j = 0; j < index_l; j++)
                {
                    if (center_point_l[1] > temp_l[j][1])
                    {
                        center_point_l[0] = temp_l[j][0];//x
                        center_point_l[1] = temp_l[j][1];//y
                    }
                }
            }

        }
        if ((points_r[r_data_statics][0]== points_r[r_data_statics-1][0]&& points_r[r_data_statics][0] == points_r[r_data_statics - 2][0]
            && points_r[r_data_statics][1] == points_r[r_data_statics - 1][1] && points_r[r_data_statics][1] == points_r[r_data_statics - 2][1])
            ||(points_l[l_data_statics-1][0] == points_l[l_data_statics - 2][0] && points_l[l_data_statics-1][0] == points_l[l_data_statics - 3][0]
                && points_l[l_data_statics-1][1] == points_l[l_data_statics - 2][1] && points_l[l_data_statics-1][1] == points_l[l_data_statics - 3][1]))
        {
            break;
        }
        if (my_abs(points_r[r_data_statics][0] - points_l[l_data_statics - 1][0]) < 2
            && my_abs(points_r[r_data_statics][1] - points_l[l_data_statics - 1][1] < 2)
            )
        {

            *hightest = (points_r[r_data_statics][1] + points_l[l_data_statics - 1][1]) >> 1;

            break;
        }
        if ((points_r[r_data_statics][1] < points_l[l_data_statics - 1][1]))
        {
            continue;
        }
        if (dir_l[l_data_statics - 1] == 7
            && (points_r[r_data_statics][1] > points_l[l_data_statics - 1][1]))
        {
            center_point_l[0] = points_l[l_data_statics - 1][0];//x
            center_point_l[1] = points_l[l_data_statics - 1][1];//y
            l_data_statics--;
        }
        r_data_statics++;

        index_r = 0;
        for (i = 0; i < 8; i++)
        {
            temp_r[i][0] = 0;
            temp_r[i][1] = 0;
        }
        for (i = 0; i < 8; i++)
        {
            if (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0
                && image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] == 255)
            {
                temp_r[index_r][0] = search_filds_r[(i)][0];
                temp_r[index_r][1] = search_filds_r[(i)][1];
                index_r++;
                dir_r[r_data_statics - 1] = (i);
                //printf("dir[%d]:%d\n", r_data_statics - 1, dir_r[r_data_statics - 1]);
            }
            if (index_r)
            {
                center_point_r[0] = temp_r[0][0];//x
                center_point_r[1] = temp_r[0][1];//y
                for (j = 0; j < index_r; j++)
                {
                    if (center_point_r[1] > temp_r[j][1])
                    {
                        center_point_r[0] = temp_r[j][0];//x
                        center_point_r[1] = temp_r[j][1];//y
                    }
                }

            }
        }


    }
    *l_stastic = l_data_statics;
    *r_stastic = r_data_statics;

}
void image_draw_rectan(uint8(*image)[MT9V03X_W])
{

    uint8 i = 0;
    for (i = 0; i < MT9V03X_H; i++)
    {
        mt9v03x_image[i][0] = 0;
        mt9v03x_image[i][1] = 0;
        mt9v03x_image[i][MT9V03X_W - 1] = 0;
        mt9v03x_image[i][MT9V03X_W - 2] = 0;

    }
    for (i = 0; i < MT9V03X_W; i++)
    {
        mt9v03x_image[0][i] = 0;
        mt9v03x_image[1][i] = 0;
        //image[image_h-1][i] = 0;

    }
}
void image_process(void)
{
uint16 i;
uint8 hightest = 0;
/*这是离线调试用的*/
Get_image(mt9v03x_image);
turn_to_bin();
/*提取赛道边界*/
image_draw_rectan(bin_image);
//清零
data_stastics_l = 0;
data_stastics_r = 0;
if (get_start_point(MT9V03X_H - 2))
{

    search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);



}

    for (i = 0; i < data_stastics_l; i++)
    {

        tft180_draw_point(points_l[i][0], points_l[i][1], RGB565_RED);
    }
    for (i = 0; i < data_stastics_r; i++)
    {

        tft180_draw_point(points_r[i][0], points_r[i][1], RGB565_BLUE);
    }



}

////--------------------------------------------------------------------------------------------------------------用于八邻域找点
//#define a11 (2.33145776e+00)
//#define a12 (3.07998761e+00)
//#define a13 (-7.70240636e+01)
//#define a21 (1.38992993e-01)
//#define a22 (5.29631665e+00)
//#define a23 (-8.33813133e+01)
//#define a31 (1.47320530e-03)
//#define a32 (3.89122946e-02)
//#define a33 (1.00000000e+00)
////#define a11 (1.90028008e+00)
////#define a12 (3.04694624e+00)
////#define a13 (-5.98790267e+01)
////#define a21 (-3.73152807e-02)
////#define a22 (4.71172875e+00)
////#define a23 (-6.27237607e+01)
////#define a31 (-1.53876708e-03)
////#define a32 (3.91528504e-02)
////#define a33 (1.00000000e+00)
//#define getx(u,v) (a11*(u)+a12*(v)+a13)
//#define gety(u,v) (a21*(u)+a22*(v)+a23)
//#define getw(u,v) (a31*(u)+a32*(v)+a33)
//
////[[ 2.33145776e+00  3.07998761e+00 -7.70240636e+01]
//// [ 1.38992993e-01  5.29631665e+00 -8.33813133e+01]
//// [ 1.47320530e-03  3.89122946e-02  1.00000000e+00]]
//
////[[ 1.90028008e+00  3.04694624e+00 -5.98790267e+01]
//// [-3.73152807e-02  4.71172875e+00 -6.27237607e+01]
//// [-1.53876708e-03  3.91528504e-02  1.00000000e+00]]
//
//
//
////带入提取出来的两条边线，得到透视变换后的两条边线
//void Pespective(int pts_in[][2], int num, int pts_out[][2])
//{
//    float x, y, w;
//    for (int16_t i = 0; i < num; i++)
//    {
//        x = getx(pts_in[i][0], pts_in[i][1]);
//        y = gety(pts_in[i][0], pts_in[i][1]);
//        w = getw(pts_in[i][0], pts_in[i][1]);
//        pts_out[i][0] = x / w;
//        pts_out[i][1] = y / w;
//    }
//}
//void Pespective_left(int a, int num, int pts_out[][2])
//{
//    float x, y, w;
//    for (int16_t i = 0; i < num; i++)
//    {
//        x = getx(leftedge[a], a);
//        y = gety(leftedge[a], a);
//        w = getw(leftedge[a], a);
//        pts_out[i][0] = x / w;
//        pts_out[i][1] = y / w;
//    }
//}
//


//
//void ImagePerspective_Init(void) {
//
//    static uint8_t BlackColor = 0;
//    double change_un_Mat[3][3] =  {{0.855406,-0.538805,-11.464220},{-0.006272,0.216456,6.619284},{-0.000523,-0.007117,0.778003}};
//            //  {{1.591057,-1.057444,44.733423},{-0.000000,0.660101,2.103082},{-0.000000,-0.012143,0.961313}};        //114w*100h
//    //{{1.084812,-0.720985,43.695344},{-0.000000,0.450069,1.803036},{0.000000,-0.008279,0.966832}};
//// {{0.945854,-0.676801,-6.586641},{0.000000,0.376130,4.977759},{0.000000,-0.007565,0.899880}};
//
//    for (int i = 0; i < RESULT_COL ;i++) {
//        for (int j = 0; j < RESULT_ROW ;j++) {
//            int local_x = (int) ((change_un_Mat[0][0] * i
//                    + change_un_Mat[0][1] * j + change_un_Mat[0][2])
//                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
//                            + change_un_Mat[2][2]));
//            int local_y = (int) ((change_un_Mat[1][0] * i
//                    + change_un_Mat[1][1] * j + change_un_Mat[1][2])
//                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j
//                            + change_un_Mat[2][2]));
//            if (local_x >= 0&& local_y >= 0 && local_y < USED_ROW && local_x < USED_COL)
//            {
//                PerImg_ip[j][i] = &PER_IMG[local_y][local_x];
//            }
//            else {
//                PerImg_ip[j][i] = &BlackColor;          //&PER_IMG[0][0];
//            }
//
//        }
//    }
//
//}
