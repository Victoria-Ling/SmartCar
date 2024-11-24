#include "Myfile.h"

//�������ֵ
int16 S3010_mid = 735;       //��������ֵ
int16 S3010_Left_Max = 815;  //��߼���ֵ������������ﲻ���ٴ���
int16 S3010_Right_Max = 655; //�ұߵ���ͬ���
float Error_angle_out = 0, Steer_duty = 0; //[Error-���� angle_out-�Ƕ� Steer_duty-���ն�����ռ�ձ�]
float Kp = 1.2, Kd = 2;                          //��Ⱥ��õ�kp,kd;

float error_value = 0, error_value_old = 0, reduce = 0, plus = 0, spaceflag = 235, ratio = 0, ad_referens = 250, abserror = 0, rp = 0;
float Difference_error = 0; //�������

//������־λ       1_ֱ��          2_���            3_·��            4_����            5_�µ�
uint8 space_flag = 0;

//Բ����־λ
int8 Island_Left = 0;
int8 Island_Right = 0;
int Island_time = 0;

//ֱ��pd
float zhidao_p = 1.2, zhidao_d = 4.0;

//Բ��PD
float ruhuan_p = 3.2, ruhuan_d = 2.8;
float chuhuan_p = 3.8, chuhuan_d = 2.3;
float huanz_p = 2.0, huanz_d = 8;

int SL_In_xishu = 470, SL_Out_xishu = 15; //��С���뻷ϵ��������ϵ��������뻷ϵ��������ƫ��ֵ
int SR_In_xishu = 470, SR_Out_xishu = 15; //��С���뻷ϵ��������ϵ�����Ҵ��뻷ϵ��������ƫ��ֵ

//����������·���õ��ı���
float road_temp = 0;

//��Ⱥ��õ�ϵ��
short a = 85;
int16 b = 540;
float error_heng = 0, error_xie = 0, error_shu = 0;

//������־λ
int8 library = 0;      //���Ƴ����ǣ�Ҳ���ò����
uint8 out_garage = 0, out_ku = 0;
int16 yaw_ruku = 0;
float ruku_lucheng = 0;
int16 yaw_chuku = 0;
uint8 inku = 0;

//ƫ��������
int16 yaw_angle = 0;

//���ʱ��
int16 charge_time = 0;

/*********************************************
 *������ִ�к���
 *��������caculation()
 *��ע��
 *�޸����ڣ�
 *********************************************/
void caculation()
{
    ADC_Read();
    error_heng = (QLAD - QRAD) / (QLAD + QRAD);
    error_xie = (XLAD - XRAD) / (XLAD + XRAD);

    Position_Jud();
    ZW_judge();
    barrier();

    Circular_zuo();
    Circular_syou();
    duan_or_po();
}


/*********************************************
 *������������㺯�����ɣ�
 *��������Position_Jud()
 *��ע��
 *���ڣ�
 *�޸����ڣ�
 *********************************************/
void Position_Jud(void)
{
//    ADC_Read();
    for (int8 i = 0; i < 7; i += 3)
        if (GUI_AD[Max_Front] < GUI_AD[i] - 5)
            Max_Front = i;

    if (Max_Front == 0 && MAD <= Position_Transit[0])
        Position = 0;
    else if ((Max_Front == 0 && MAD >= Position_Transit[0]) || (Max_Front == 3 && ZLAD > ZRAD))
        Position = 1;
    else if ((Max_Front == 6 && MAD >= Position_Transit[1]) || (Max_Front == 3 && ZRAD > ZLAD))
        Position = 2;
    else if (Max_Front == 6 && MAD <= Position_Transit[1])
        Position = 3;

    if (abs(Position - Position_last) == 3) //ǰ��λ�÷�����   ��ֹ�ٽ���������
        Position = Position_last;
    else
        Position_last = Position;
}

/*********************************************
 *�������������㷨����
 *��������position_new()
 *��ע��
 *�޸����ڣ�
 *********************************************/
void position_new()
{
    ADC_Read();
//    abserror = abs(ad_referens - MAD);
//    ratio = (abserror / ad_referens) * a;
//    Difference_error = error_value - error_value_old;

    //ֱ�����µ�
    if ((space_flag == 1 && (Position == 1 || Position == 2)) || finish % 2 == 1 || space_flag == 5)
    {
        base = base_straight;
        reduce = sqrt(ZLAD) - sqrt(ZRAD);
        plus = QLAD + QRAD + MAD;
        rp = (reduce / plus) * b;
        error_value_old = error_value;
        error_value = rp;
        Kp = zhidao_p;
        Kd = zhidao_d;
        Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
    }

    //���
    else if (space_flag == 2)                                   //�е��ѭ��
    {
        base = base_bend;
        if (error_xie < -0.27 && error_heng < -0.23)     //����
        {
            abserror = abs(ad_referens - MAD);
            error_value_old = error_value;
            error_value = -(abserror / ad_referens) * a;
            Difference_error = error_value - error_value_old;
            Kp = Fuzzy_P(error_value, Difference_error);
            Kd = Fuzzy_D(error_value, Difference_error);
            Error_angle_out = Kp * error_value + Kd * Difference_error;
        }
        else if (error_xie > 0.27 && error_heng > 0.23)      //����
        {
            abserror = abs(ad_referens - MAD);
            error_value_old = error_value;
            error_value = (abserror / ad_referens) * a;
            Difference_error = error_value - error_value_old;
            Kp = Fuzzy_P(error_value, Difference_error);
            Kd = Fuzzy_D(error_value, Difference_error);
            Error_angle_out = Kp * error_value + Kd * Difference_error;
        }
    }

    //Բ��
    else if (space_flag == 4)
    {
        base = base_loop;
        /**********************��*********************/
        if (Island_Left == 2)    //�뻷
        {
            error_value_old = error_value;
            error_value = ((sqrt(ZLAD) * 1.55 - sqrt(ZRAD) * 0.45) * SL_In_xishu) / (ZLAD + ZRAD); // 500
            Kp = ruhuan_p + 0.3;
            Kd = ruhuan_d + 0.3;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        else if (Island_Left == 3)   //�ڻ���ʹ�����ѭ��
        {
            abserror = abs(ad_referens - MAD);
            error_value_old = error_value;
            error_value = (abserror / ad_referens) * a;
            Kp = huanz_p;
            Kd = huanz_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        else if (Island_Left == 4)    //����
        {
            abserror = abs(ad_referens - MAD);
            error_value_old = error_value;
            error_value = (abserror / ad_referens) * a + SL_Out_xishu;
            Kp = chuhuan_p;
            Kd = chuhuan_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }

        //***************�һ�*****************//
        if (Island_Right == 2)     //�뻷
        {
            error_value_old = error_value;
            error_value = ((sqrt(ZLAD) * 0.45 - sqrt(ZRAD) * 1.55) * SR_In_xishu) / (ZLAD + ZRAD);
            Kp = ruhuan_p;
            Kd = ruhuan_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        else if (Island_Right == 3)
        {
            abserror = abs(ad_referens - MAD);
            error_value_old = error_value;
            error_value = -(abserror / ad_referens) * a;
            Kp = huanz_p;
            Kd = huanz_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        else if (Island_Right == 4)   //����
        {
            abserror = abs(ad_referens - MAD);
            error_value_old = error_value;
            error_value = -((abserror / ad_referens) * a + SR_Out_xishu);
            Kp = chuhuan_p;
            Kd = chuhuan_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
      }

      //���
      else if(space_flag == 3)
      {
          base = base_hengduan;
          obstacle_error[1] = obstacle_error[0];
          if(hengduan == 1 || hengduan == 3)    obstacle_error[0] = angle_want + abs(yaw_angle - Yaw);
          else if(hengduan == 2)                obstacle_error[0] = angle_want - abs(yaw_angle - Yaw);
          Kp = obstacle_p;
          Kd = obstacle_d;
          Error_angle_out = Kp * obstacle_error[0] + Kd * (obstacle_error[0] - obstacle_error[1]);
      }

      //��Ԫ��
      else
      {

      }

}

/*********************************************
 *������ģ��pid����
 *��������mohu_pid()
 *��ע��Ҫ���� ���ֵ ���Ĳ�ֵ
 *���ڣ�
 *�޸����ڣ�
 *********************************************/
float Fuzzy_P(float E, float EC)
{
    /*������P����ֵ������*/
    float EFF[7] = {-56, -20, -10, 0, 10, 20, 56};    //Error��Χ

    /*������D����ֵ������*/
    float DFF[7] = {-2.5, -1.5, -0.5, 0, 0.5, 1.5, 2.5};  // ���仯�ʷ�Χ

    /*�����U����ֵ������(������������ѡ��ͬ�����ֵ)*/
    float UFF[7] = {1.7, 1.8, 1.9, 2.0, 2.1, 2.8, 3}; // 1.15 2  2.2 2.4 2.6 2.8 3 4}
//    float UFF[7] = {2.0, 2.1, 2.2, 2.4, 2.8, 2.8, 3};

    int rule[7][7] = {
        {6, 5, 4, 3, 2, 1, 0},                           //������������޸�
        {5, 4, 3, 2, 1, 0, 1},
        {4, 3, 2, 1, 0, 1, 2},
        {3, 2, 1, 0, 1, 2, 3},
        {2, 1, 0, 1, 2, 3, 4},
        {1, 0, 1, 2, 3, 4, 5},
        {0, 1, 2, 3, 4, 5, 6},
    };

    float U = 0;                                 /*ƫ��,ƫ��΢���Լ����ֵ�ľ�ȷ��*/
    float PF[2] = {0}, DF[2] = {0}, UF[4] = {0}; //ƫ��,ƫ��΢���Լ����ֵ��������

    int Pn = 0, Dn = 0, Un[4] = {0};
    float t1 = 0, t2 = 0, t3 = 0, t4 = 0, temp1 = 0, temp2 = 0;
    /*�����ȵ�ȷ��*/
    /*����PD��ָ������ֵ�����Ч������*/
    if (E > EFF[0] && E < EFF[6])
    {
        if (E <= EFF[1])
        {
            Pn = -2;
            PF[0] = (EFF[1] - E) / (EFF[1] - EFF[0]);
        }
        else if (E <= EFF[2])
        {
            Pn = -1;
            PF[0] = (EFF[2] - E) / (EFF[2] - EFF[1]);
        }
        else if (E <= EFF[3])
        {
            Pn = 0;
            PF[0] = (EFF[3] - E) / (EFF[3] - EFF[2]);
        }
        else if (E <= EFF[4])
        {
            Pn = 1;
            PF[0] = (EFF[4] - E) / (EFF[4] - EFF[3]);
        }
        else if (E <= EFF[5])
        {
            Pn = 2;
            PF[0] = (EFF[5] - E) / (EFF[5] - EFF[4]);
        }
        else if (E <= EFF[6])
        {
            Pn = 3;
            PF[0] = (EFF[6] - E) / (EFF[6] - EFF[5]);
        }
    }

    else if (E <= EFF[0])
    {
        Pn = -2;
        PF[0] = 1;
    }
    else if (E >= EFF[6])
    {
        Pn = 3;
        PF[0] = 0;
    }

    PF[1] = 1 - PF[0];

    //�ж�D��������
    if (EC > DFF[0] && EC < DFF[6])
    {
        if (EC <= DFF[1])
        {
            Dn = -2;
            DF[0] = (DFF[1] - EC) / (DFF[1] - DFF[0]);
        }
        else if (EC <= DFF[2])
        {
            Dn = -1;
            DF[0] = (DFF[2] - EC) / (DFF[2] - DFF[1]);
        }
        else if (EC <= DFF[3])
        {
            Dn = 0;
            DF[0] = (DFF[3] - EC) / (DFF[3] - DFF[2]);
        }
        else if (EC <= DFF[4])
        {
            Dn = 1;
            DF[0] = (DFF[4] - EC) / (DFF[4] - DFF[3]);
        }
        else if (EC <= DFF[5])
        {
            Dn = 2;
            DF[0] = (DFF[5] - EC) / (DFF[5] - DFF[4]);
        }
        else if (EC <= DFF[6])
        {
            Dn = 3;
            DF[0] = (DFF[6] - EC) / (DFF[6] - DFF[5]);
        }
    }
    //���ڸ�����������
    else if (EC <= DFF[0])
    {
        Dn = -2;
        DF[0] = 1;
    }
    else if (EC >= DFF[6])
    {
        Dn = 3;
        DF[0] = 0;
    }

    DF[1] = 1 - DF[0];

    /*ʹ����Χ�Ż���Ĺ����rule[7][7]*/
    /*���ֵʹ��13����������,����ֵ��UFF[7]ָ��*/
    /*һ�㶼���ĸ�������Ч*/
    Un[0] = rule[Pn + 2][Dn + 2];
    Un[1] = rule[Pn + 3][Dn + 2];
    Un[2] = rule[Pn + 2][Dn + 3];
    Un[3] = rule[Pn + 3][Dn + 3];

    if (PF[0] <= DF[0]) //��С
        UF[0] = PF[0];
    else
        UF[0] = DF[0];
    if (PF[1] <= DF[0])
        UF[1] = PF[1];
    else
        UF[1] = DF[0];
    if (PF[0] <= DF[1])
        UF[2] = PF[0];
    else
        UF[2] = DF[1];
    if (PF[1] <= DF[1])
        UF[3] = PF[1];
    else
        UF[3] = DF[1];
    /*ͬ���������������ֵ���*/
    if (Un[0] == Un[1])
    {
        if (UF[0] > UF[1])
            UF[1] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[2])
    {
        if (UF[0] > UF[2])
            UF[2] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[3])
    {
        if (UF[0] > UF[3])
            UF[3] = 0;
        else
            UF[0] = 0;
    }
    if (Un[1] == Un[2])
    {
        if (UF[1] > UF[2])
            UF[2] = 0;
        else
            UF[1] = 0;
    }
    if (Un[1] == Un[3])
    {
        if (UF[1] > UF[3])
            UF[3] = 0;
        else
            UF[1] = 0;
    }
    if (Un[2] == Un[3])
    {
        if (UF[2] > UF[3])
            UF[3] = 0;
        else
            UF[2] = 0;
    }
    t1 = UF[0] * UFF[Un[0]];
    t2 = UF[1] * UFF[Un[1]];
    t3 = UF[2] * UFF[Un[2]];
    t4 = UF[3] * UFF[Un[3]];
    temp1 = t1 + t2 + t3 + t4;
    temp2 = UF[0] + UF[1] + UF[2] + UF[3]; //ģ�������
    U = temp1 / temp2;
    return U;
}
float Fuzzy_D(float E, float EC)
{
    /*������P����ֵ������*/
    float EFF[7] = {-56, -20, -10, 0, 10, 25, 56};
    /*������D����ֵ������*/
    float DFF[7] = {-2.5, -1.5, -0.5, 0, 0.5, 1.5, 2};
    /*�����U����ֵ������(������������ѡ��ͬ�����ֵ)*/
    float UFF[7] = {2.3, 4.2, 8.2, 7, 6, 5, 4};
    // float UFF[7] = {0.6, 0.9, 1.2, 8, 7, 6, 5};

    int rule[7][7] = {
        {0, 1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6, 5},
        {2, 3, 4, 5, 6, 5, 4},
        {3, 4, 5, 6, 5, 4, 3},
        {4, 5, 6, 5, 4, 3, 2},
        {5, 6, 5, 4, 3, 2, 1},
        {6, 5, 4, 3, 2, 1, 0},
    };

    float U = 0; /*ƫ��,ƫ��΢���Լ����ֵ�ľ�ȷ��*/
    float PF[2] = {0}, DF[2] = {0}, UF[4] = {0};
    /*ƫ��,ƫ��΢���Լ����ֵ��������*/
    int Pn = 0, Dn = 0, Un[4] = {0};
    float t1 = 0, t2 = 0, t3 = 0, t4 = 0, temp1 = 0, temp2 = 0;
    /*�����ȵ�ȷ��*/
    /*����PD��ָ������ֵ�����Ч������*/
    if (E > EFF[0] && E < EFF[6])
    {
        if (E <= EFF[1])
        {
            Pn = -2;
            PF[0] = (EFF[1] - E) / (EFF[1] - EFF[0]);
        }
        else if (E <= EFF[2])
        {
            Pn = -1;
            PF[0] = (EFF[2] - E) / (EFF[2] - EFF[1]);
        }
        else if (E <= EFF[3])
        {
            Pn = 0;
            PF[0] = (EFF[3] - E) / (EFF[3] - EFF[2]);
        }
        else if (E <= EFF[4])
        {
            Pn = 1;
            PF[0] = (EFF[4] - E) / (EFF[4] - EFF[3]);
        }
        else if (E <= EFF[5])
        {
            Pn = 2;
            PF[0] = (EFF[5] - E) / (EFF[5] - EFF[4]);
        }
        else if (E <= EFF[6])
        {
            Pn = 3;
            PF[0] = (EFF[6] - E) / (EFF[6] - EFF[5]);
        }
    }

    else if (E <= EFF[0])
    {
        Pn = -2;
        PF[0] = 1;
    }
    else if (E >= EFF[6])
    {
        Pn = 3;
        PF[0] = 0;
    }

    PF[1] = 1 - PF[0];

    //�ж�D��������
    if (EC > DFF[0] && EC < DFF[6])
    {
        if (EC <= DFF[1])
        {
            Dn = -2;
            DF[0] = (DFF[1] - EC) / (DFF[1] - DFF[0]);
        }
        else if (EC <= DFF[2])
        {
            Dn = -1;
            DF[0] = (DFF[2] - EC) / (DFF[2] - DFF[1]);
        }
        else if (EC <= DFF[3])
        {
            Dn = 0;
            DF[0] = (DFF[3] - EC) / (DFF[3] - DFF[2]);
        }
        else if (EC <= DFF[4])
        {
            Dn = 1;
            DF[0] = (DFF[4] - EC) / (DFF[4] - DFF[3]);
        }
        else if (EC <= DFF[5])
        {
            Dn = 2;
            DF[0] = (DFF[5] - EC) / (DFF[5] - DFF[4]);
        }
        else if (EC <= DFF[6])
        {
            Dn = 3;
            DF[0] = (DFF[6] - EC) / (DFF[6] - DFF[5]);
        }
    }
    //���ڸ�����������
    else if (EC <= DFF[0])
    {
        Dn = -2;
        DF[0] = 1;
    }
    else if (EC >= DFF[6])
    {
        Dn = 3;
        DF[0] = 0;
    }

    DF[1] = 1 - DF[0];

    /*ʹ����Χ�Ż���Ĺ����rule[7][7]*/
    /*���ֵʹ��13����������,����ֵ��UFF[7]ָ��*/
    /*һ�㶼���ĸ�������Ч*/
    Un[0] = rule[Pn + 2][Dn + 2];
    Un[1] = rule[Pn + 3][Dn + 2];
    Un[2] = rule[Pn + 2][Dn + 3];
    Un[3] = rule[Pn + 3][Dn + 3];

    if (PF[0] <= DF[0]) //��С
        UF[0] = PF[0];
    else
        UF[0] = DF[0];
    if (PF[1] <= DF[0])
        UF[1] = PF[1];
    else
        UF[1] = DF[0];
    if (PF[0] <= DF[1])
        UF[2] = PF[0];
    else
        UF[2] = DF[1];
    if (PF[1] <= DF[1])
        UF[3] = PF[1];
    else
        UF[3] = DF[1];
    /*ͬ���������������ֵ���*/
    if (Un[0] == Un[1])
    {
        if (UF[0] > UF[1])
            UF[1] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[2])
    {
        if (UF[0] > UF[2])
            UF[2] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[3])
    {
        if (UF[0] > UF[3])
            UF[3] = 0;
        else
            UF[0] = 0;
    }
    if (Un[1] == Un[2])
    {
        if (UF[1] > UF[2])
            UF[2] = 0;
        else
            UF[1] = 0;
    }
    if (Un[1] == Un[3])
    {
        if (UF[1] > UF[3])
            UF[3] = 0;
        else
            UF[1] = 0;
    }
    if (Un[2] == Un[3])
    {
        if (UF[2] > UF[3])
            UF[3] = 0;
        else
            UF[2] = 0;
    }
    t1 = UF[0] * UFF[Un[0]];
    t2 = UF[1] * UFF[Un[1]];
    t3 = UF[2] * UFF[Un[2]];
    t4 = UF[3] * UFF[Un[3]];
    temp1 = t1 + t2 + t3 + t4;
    temp2 = UF[0] + UF[1] + UF[2] + UF[3]; //ģ�������
    U = temp1 / temp2;
    return U;
}

/*********************************************
 *������ֱ���ʶ����
 *��������ZW_judge()
 *��ע���������Ǹ�������
 *���ڣ�
 *�޸����ڣ�
 *********************************************/
void ZW_judge()
{
    if (space_flag != 3 && space_flag != 4 && space_flag != 5 && (((error_heng <= 0.23 || error_heng >= -0.23) && (error_xie <= 0.27 || error_xie >= -0.27)) || MAD > spaceflag))
    {
        space_flag = 1;
        BEEP_OFF;
    }
    if (space_flag != 3 && space_flag != 4 && space_flag != 5 && MAD <= spaceflag && (error_heng > 0.23 || error_heng < -0.23) && (error_xie >= 0.27 || error_xie <= -0.27))
    {
        space_flag = 2;
        BEEP_ON;
    }
}

/*********************************************
 *��������С����־λʶ��������
 *��������Circular_zuo()
 *��ע���������Ǹ�������
 *���ڣ�
 *�޸����ڣ�
 *********************************************/
void Circular_zuo()
{
    if (MAD >= 240 && QLAD > 190 && Island_Left == 0 && Island_Right == 0 && (finish % 2 == 0))
    {
        Island_Left = 1;
        BEEP_ON;
    }
    if (XLAD > 120 && Island_Left == 1)
    {
        Island_Left = 2;
        space_flag = 4;
        yaw_angle = Yaw;
        BEEP_OFF;
    }
    if (abs(Yaw - yaw_angle) > 25 && Island_Left == 2)
    {

        yaw_angle = Yaw;
        Island_Left = 3;
    }
    if (Island_Left == 3 && abs(Yaw - yaw_angle) >= 255)
    {
        yaw_angle = Yaw;
        Island_Left = 4;
        BEEP_ON;

    }
    if (Island_Left == 4 && abs(Yaw - yaw_angle) >= 40)
    {
        Island_Left = 5;
        yaw_angle = 0;
        BEEP_OFF;

        if (MAD >= spaceflag)
        {
            space_flag = 1;
        }
        if (MAD < spaceflag)
        {
            space_flag = 2;
        }
    }
    if (Island_Left == 5 && Island_time > 150)
    {
        Island_Left = 0;
    }
}

void Circular_syou()
{
    if (MAD > 240 && QRAD > 190 && Island_Right == 0 && Island_Left == 0 && (finish % 2 == 0))
    {
        Island_Right = 1;
        BEEP_ON;
    }
    if (XRAD > 130 && Island_Right == 1)
    {
        Island_Right = 2;
        yaw_angle = Yaw;
        space_flag = 4;
        BEEP_OFF;
    }
    if (abs(Yaw - yaw_angle) > 30 && Island_Right == 2)
    {
        Island_Right = 3;
        yaw_angle = Yaw;
    }
    if (Island_Right == 3 && abs(Yaw - yaw_angle) >= 255)
    {
        Island_Right = 4;
        yaw_angle = Yaw;
        BEEP_ON;
    }
    if (Island_Right == 4 && abs(Yaw - yaw_angle) >= 35)
    {
        Island_Right = 5;
        yaw_angle = 0;
        BEEP_OFF;

        if (MAD >= spaceflag) //��һ��
        {
            space_flag = 1;
        }
        if (MAD < spaceflag)
        {
            space_flag = 2;
        }
    }

    //��ʱ����
    if (Island_Right == 5 && Island_time > 150)
    {
        Island_Right = 0;
    }
}

/*********************************************
 *������������մ�Ǻ���
 *��������S3010_Direation_Control()
 *��ע��
 *���ڣ�
 *�޸����ڣ�
 *********************************************/
void S3010_Direation_Control() //���
{
    if(out_ku == 1)
    {
        caculation();
        position_new();
        if (Error_angle_out > 80)
            Error_angle_out = 80;
        else if (Error_angle_out < -80)
            Error_angle_out = -80;
        Steer_duty = (Error_angle_out + S3010_mid);
        if (Steer_duty > S3010_Left_Max)
            Steer_duty = S3010_Left_Max;
        else if (Steer_duty < S3010_Right_Max)
            Steer_duty = S3010_Right_Max;
        pwm_set_duty(TIM2_PWM_MAP3_CH1_A15, Steer_duty);
    }
}

/*********************************************
 *����������⺯��
 *��������Out_storage()/In_ku()
 *��ע��
 *���ڣ�
 *�޸����ڣ�
 *********************************************/
void Out_storage(void)
{
    if(out_ku == 0 && charge_time >= 600)
    {
        out_ku = 1;
    }
}
void In_ku(void)
{

}

