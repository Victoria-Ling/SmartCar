#include "Myfile.h"

int8 numm = 1;
int8 num = 1;
int8 nummm = 1;
int8 nux;

void menu(void)
{
  tft180_show_string(0, num * 16, "#");
  tft180_show_string(48, 0, "MENU");
  tft180_show_string(16, 16, "ADC_SHOW()");
  tft180_show_string(16, 32, "xunjiflag()");
  tft180_show_string(16, 48, "MOTRO_PID()");
  tft180_show_string(16, 64, "MOTRO_Ctro()");
  tft180_show_string(16, 80, "DUOJI_Ctro()");
  tft180_show_string(16, 96, "yuanshi_ADC()");
  tft180_show_string(16, 112, "duanlu_Ctro()");
}

void xunjiflag(void)
{
  while (Key_Switch == 1)
  {
    tft180_show_int(120, 0, space_flag, 1);
    tft180_show_string(16, 0, "spaceflag");

    tft180_show_int(120, 16, Island_Left, 1);
    tft180_show_string(16, 16, "Island_Left");

    tft180_show_int(120, 32, Island_Right, 1);
    tft180_show_string(16, 32, "Island_Right");

    tft180_show_int(120, 48, hengduan, 1);
    tft180_show_string(16, 48, "hengduan");

    tft180_show_int(120, 64, out_ku, 1);
    tft180_show_string(16, 64, "out_ku");

    tft180_show_int(120, 80, inku, 1);
    tft180_show_string(16, 80, "in_ku");

    tft180_show_float(16, 96, road_sum, 3, 3);

    tft180_show_int(120, 96, Yaw, 5);

    tft180_show_uint(120, 112, distance_pingjun, 4);
    tft180_show_string(16, 112, "dis_pingjun");

    Key_Scan();
    if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void ADC_SHOW(void)
{
  while (Key_Switch == 1)
  {
    ADC_Read();
    tft180_show_uint(10, 16, GUI_AD[3], 4);

    tft180_show_uint(10, 32, GUI_AD[0], 4);     tft180_show_uint(80, 32, GUI_AD[6], 4);
    tft180_show_uint(10, 48, GUI_AD[1], 4);     tft180_show_uint(80, 48, GUI_AD[5], 4);
    tft180_show_uint(10, 64, GUI_AD[2], 4);     tft180_show_uint(80, 64, GUI_AD[4], 4);

    Key_Scan();
    if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}
void DUOJI_Ctro(void)
{
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "E_speed()");
    tft180_show_string(16, 32, "huandao_pd()");
    tft180_show_string(16, 48, "ZW_Ctrl()");
    tft180_show_string(16, 64, "zhidao_pd()");
    tft180_show_string(16, 80, "huan_xishu()");
    tft180_show_string(16, 96, "mid +- 1");
    tft180_show_string(16, 112, "mid +- 5");
    tft180_show_uint(120, 96, S3010_mid, 4);
    tft180_show_uint(120, 112, S3010_mid, 4);
    tft180_show_string(0, numm * 16, "#");

    Key_Scan();
    if (Key_Number == 8)
    {
        ++numm;
        if (numm > 7)
        {
          numm = 1;
          tft180_show_string(0, 7 * 16, " ");
        }
        nux = numm - 1;
        tft180_show_string(0, numm * 16, "#");
        if(nux <= 7 && nux >= 0)    tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 2)
    {
      --numm;
      if (numm < 1)
      {
          numm = 7;
        tft180_show_string(0, 1 * 16, " ");
      }
      nux = numm + 1;
      tft180_show_string(0, numm * 16, "#");
      if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 5)
    {
        tft180_clear();
        nummm = 1;
        switch (numm)
        {
        case 1:
          E_speed();
          break;
        case 2:
          annulus_PD();
          break;
        case 3:
          ZW_Ctrl();
          break;
        case 4:
          zhidao_pd();
          break;
        case 5:
          huan_xishu();
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 4)
    {
        switch (numm)
        {
            case 6:
              S3010_mid -= 1;
              pwm_set_duty(TIM2_PWM_MAP3_CH1_A15, S3010_mid);
              break;
            case 7:
              S3010_mid -= 5;
              pwm_set_duty(TIM2_PWM_MAP3_CH1_A15, S3010_mid);
              break;
            default:
              break;
        }
    }
    else if(Key_Number == 6)
    {
        switch (numm)
        {
        case 6:
          S3010_mid += 1;
          pwm_set_duty(TIM2_PWM_MAP3_CH1_A15, S3010_mid);
          break;
        case 7:
          S3010_mid += 5;
          pwm_set_duty(TIM2_PWM_MAP3_CH1_A15, S3010_mid);
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void huan_xishu(void)
{
  tft180_clear();
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "SL_in:");
    tft180_show_uint(120, 16, SL_In_xishu, 4);
    tft180_show_string(16, 32, "SL_out:");
    tft180_show_uint(120, 32, SL_Out_xishu, 4);
    tft180_show_string(16, 48, "SR_in:");
    tft180_show_uint(120, 48, SR_In_xishu, 4);
    tft180_show_string(16, 64, "SR_out:");
    tft180_show_uint(120, 64, SR_Out_xishu, 4);
    tft180_show_string(0, nummm * 16, "#");

    Key_Scan();
    if (Key_Number == 8)
    {
        ++nummm;
        if (nummm > 4)
        {
          nummm = 1;
          tft180_show_string(0, 4 * 16, " ");
        }
        nux = nummm - 1;
        tft180_show_string(0, nummm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 2)
    {
      --nummm;
      if (nummm < 1)
      {
          nummm = 4;
        tft180_show_string(0, 1 * 16, " ");
      }
      nux = nummm + 1;
      tft180_show_string(0, nummm * 16, "#");
      if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 6)
    {
        switch (nummm)
        {
        case 1:
          SL_In_xishu += 2;
          break;
        case 2:
          SL_Out_xishu += 2;
          break;
        case 3:
          SR_In_xishu += 2;
          break;
        case 4:
          SR_Out_xishu += 2;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 4)
    {
        switch (nummm)
        {
        case 1:
          SL_In_xishu -= 2;
          break;
        case 2:
          SL_Out_xishu -= 2;
          break;
        case 3:
          SR_In_xishu -= 2;
          break;
        case 4:
          SR_Out_xishu -= 2;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void zhidao_pd(void)
{
  tft180_clear();
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "zhidao_p:");
    tft180_show_float(120, 16, zhidao_p, 2, 2);
    tft180_show_string(16, 32, "zhidao_d:");
    tft180_show_float(120, 32, zhidao_d, 2, 2);
    tft180_show_string(0, nummm * 16, "#");

    Key_Scan();
    if (Key_Number == 8)
    {
        ++nummm;
        if (nummm > 2)
        {
          nummm = 1;
          tft180_show_string(0, 2 * 16, " ");
        }
        nux = nummm - 1;
        tft180_show_string(0, nummm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    if (Key_Number == 6)
    {
        switch (nummm)
        {
        case 1:
          zhidao_p += 0.1;
          break;
        case 2:
          zhidao_d += 0.1;
          break;
        default:
          break;
        }
    }

    if (Key_Number == 4)
    {
        switch (nummm)
        {
        case 1:
          zhidao_p -= 0.1;
          break;
        case 2:
          zhidao_d -= 0.1;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}
void E_speed(void)
{
  tft180_clear();
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "base_bend:");
    tft180_show_int(120, 16, base_bend, 4);
    tft180_show_string(16, 32, "base_loop:");
    tft180_show_int(120, 32, base_loop, 4);
    tft180_show_string(16, 48, "base_ramp:");
    tft180_show_int(120, 48, base_ramp, 4);
    tft180_show_string(16, 64, "base_stra:");
    tft180_show_int(120, 64, base_straight, 4);
    tft180_show_string(16, 80, "base_duan:");
    tft180_show_int(120, 80, base_hengduan, 4);
    tft180_show_string(16, 96, "base_ku:");
    tft180_show_int(120, 96, base_ku, 4);
    tft180_show_string(0, nummm * 16, "#");

    Key_Scan();
    if (Key_Number == 8)
    {
        ++nummm;
        if (nummm > 6)
        {
          nummm = 1;
          tft180_show_string(0, 6 * 16, " ");
        }
        nux = nummm - 1;
        tft180_show_string(0, nummm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 2)
    {
        --nummm;
        if (nummm < 1)
        {
          nummm = 6;
          tft180_show_string(0, 16, " ");
        }
        nux = nummm + 1;
        tft180_show_string(0, nummm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 6)
    {
        switch (nummm)
        {
        case 1:
          base_bend += 5;
          break;
        case 2:
          base_loop += 5;
          break;
        case 3:
          base_ramp += 5;
          break;
        case 4:
          base_straight += 5;
          break;
        case 5:
          base_hengduan += 5;
          break;
        case 6:
          base_ku += 5;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 4)
    {
        switch (nummm)
        {
        case 1:
          base_bend -= 5;
          break;
        case 2:
          base_loop -= 5;
          break;
        case 3:
          base_ramp -= 5;
          break;
        case 4:
          base_straight -= 5;
          break;
        case 5:
          base_hengduan -= 5;
          break;
        case 6:
          base_ku -= 5;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void annulus_PD(void)
{
  tft180_clear();
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "ruh_p:");
    tft180_show_string(16, 32, "ruh_d:");
    tft180_show_float(120, 16, ruhuan_p, 2, 2);
    tft180_show_float(120, 32, ruhuan_d, 2, 2);
    tft180_show_string(16, 48, "huz_p");
    tft180_show_float(120, 48, huanz_p, 2, 2);
    tft180_show_string(16, 64, "huz_d");
    tft180_show_float(120, 64, huanz_d, 2, 2);
    tft180_show_string(16, 80, "cuh_p");
    tft180_show_float(120, 80, chuhuan_p, 2, 2);
    tft180_show_string(16, 96, "cuh_d");
    tft180_show_float(120, 96, chuhuan_d, 2, 2);
    tft180_show_string(0, nummm * 16, "#");

    Key_Scan();
    if (Key_Number == 8)
    {
        ++nummm;
        if (nummm > 6)
        {
          nummm = 1;
          tft180_show_string(0, 6 * 16, " ");
        }
        nux = nummm - 1;
        tft180_show_string(0, nummm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 2)
    {
        --nummm;
        if (nummm < 1)
        {
          nummm = 6;
          tft180_show_string(0, 16, " ");
        }
        nux = nummm + 1;
        tft180_show_string(0, nummm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 6)
    {
        switch (nummm)
        {
        case 1:
          ruhuan_p += 0.1;
          break;
        case 2:
          ruhuan_d += 0.1;
          break;
        case 3:
          huanz_p += 0.1;
          break;
        case 4:
          huanz_d += 0.1;
          break;
        case 5:
          chuhuan_p += 0.1;
          break;
        case 6:
          chuhuan_d += 0.1;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 4)
    {
        switch (nummm)
        {
        case 1:
          ruhuan_p -= 0.1;
          break;
        case 2:
          ruhuan_d -= 0.1;
          break;
        case 3:
          huanz_p -= 0.1;
          break;
        case 4:
          huanz_d -= 0.1;
          break;
        case 5:
          chuhuan_p -= 0.1;
          break;
        case 6:
          chuhuan_d -= 0.1;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void yuanshi_ADC(void)
{
  while (Key_Switch == 1)
  {
    ADC_Read();

    tft180_show_uint(10, 16, ADDD_valu[3], 4);

    tft180_show_uint(10, 32, ADDD_valu[0], 4);      tft180_show_uint(80, 32, ADDD_valu[6], 4);
    tft180_show_uint(10, 48, ADDD_valu[1], 4);      tft180_show_uint(80, 48, ADDD_valu[5], 4);
    tft180_show_uint(10, 64, ADDD_valu[2], 4);      tft180_show_uint(80, 64, ADDD_valu[4], 4);

    Key_Scan();
    if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void MOTRO_PID(void)
{
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "KP_L:");
    tft180_show_float(120, 16, KP_L, 3, 1);
    tft180_show_string(16, 32, "KD_L:");
    tft180_show_float(120, 32, KD_L, 3, 1);
    tft180_show_string(16, 48, "KI_L:");
    tft180_show_float(120, 48, KI_L, 3, 1);
    tft180_show_string(16, 64, "KP_R:");
    tft180_show_float(120, 64, KP_R, 3, 1);
    tft180_show_string(16, 80, "KD_R:");
    tft180_show_float(120, 80, KD_R, 3, 1);
    tft180_show_string(16, 96, "KI_R:");
    tft180_show_float(120, 96, KI_R, 3, 1);
    tft180_show_string(0, numm * 16, "#");

    Key_Scan();
    if (Key_Number == 8)
    {
        ++numm;
        if (numm > 6)
        {
          numm = 1;
          tft180_show_string(0, 6 * 16, " ");
        }
        nux = numm - 1;
        tft180_show_string(0, numm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 2)
    {
        --numm;
        if (numm < 1)
        {
          numm = 6;
          tft180_show_string(0, 16, " ");
        }
        nux = numm + 1;
        tft180_show_string(0, numm * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 6)
    {
        switch (numm)
        {
        case 1:
          KP_L += 0.5;
          break;
        case 2:
          KD_L += 0.5;
          break;
        case 3:
          KI_L += 0.5;
          break;
        case 4:
          KP_R += 0.5;
          break;
        case 5:
          KD_R += 0.5;
          break;
        case 6:
          KI_R += 0.5;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 4)
    {
        switch (numm)
        {
        case 1:
          KP_L -= 0.5;
          break;
        case 2:
          KD_L -= 0.5;
          break;
        case 3:
          KI_L -= 0.5;
          break;
        case 4:
          KP_R -= 0.5;
          break;
        case 5:
          KD_R -= 0.5;
          break;
        case 6:
          KI_R -= 0.5;
          break;
        default:
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}

void MOTRO_Ctro(void)
{
  while (Key_Switch == 1)
  {
    tft180_show_string(16, 16, "base:");
    tft180_show_int(120, 16, base, 4);
    numm = 1;
    if (numm == 1)
    {
      tft180_show_string(0, numm * 16, "#");
    }

    Key_Scan();
    if (Key_Number == 6)
    {
        switch (numm)
        {
        case 1:
          base += 1;
          break;
        }
    }
    else if (Key_Number == 4)
    {
        switch (numm)
        {
        case 1:
          base -= 1;
          break;
        }
    }
    else if (Key_Number == 9)
    {
        tft180_clear();
        Key_Number = 0;
        break;
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Number = 0;
       Key_Switch = !Key_Switch;
    }
  }
}


void oled_menu(void)
{
  while (Key_Switch == 1)
  {
    menu();
    Key_Scan();
    if (Key_Number == 8)
    {
        num += 1;
        if (num > 7)
        {
          num = 1;
          tft180_show_string(0, 112, " ");
        }
        nux = num - 1;
        tft180_show_string(0, num * 16, "#");
        if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }
    else if (Key_Number == 2)
    {
      num -= 1;
      if (num < 1)
      {
        num = 7;
        tft180_show_string(0, 16, " ");
      }
      nux = num + 1;
      tft180_show_string(0, num * 16, "#");
      if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
    }

    else if (Key_Number == 5)
    {
        tft180_clear();
        numm = 1;
        switch (num)
        {
        case 1:
          ADC_SHOW();
          break;
        case 2:
          xunjiflag();
          break;
        case 3:
          MOTRO_PID();
          break;
        case 4:
          MOTRO_Ctro();
          break;
        case 5:
          DUOJI_Ctro();
          break;
        case 6:
          yuanshi_ADC();
          break;
        case 7:
          DUANLU();
          break;
        default:
          break;
        }
    }
    else if(Key_Number == 1)
    {
       tft180_clear();
       gpio_set_level(C7, 0);
       gpio_set_level(A8, 0);
       gpio_set_level(B0, 1);
       Key_Switch = !Key_Switch;
    }
    if(Key_Switch == 0)
        tft180_clear();
  }
}

void DUANLU(void)
{
    tft180_clear();
    while(Key_Switch == 1)
    {
        tft180_show_string(16, 16, "c_finish:");
        tft180_show_string(16, 32, "barrier[0]:");
        tft180_show_string(16, 48, "barrier[1]:");
        tft180_show_string(16, 64, "barrier[2]:");
        tft180_show_string(16, 80, "barrier[3]:");
        tft180_show_string(16, 96, "barrier[4]:");
        tft180_show_string(16, 112, "barrier[5]:");

        tft180_show_uint(120, 16, cout_finish, 1);
        tft180_show_uint(120, 32, barrier_type[0], 1);
        tft180_show_uint(120, 48, barrier_type[1], 1);
        tft180_show_uint(120, 64, barrier_type[2], 1);
        tft180_show_uint(120, 80, barrier_type[3], 1);
        tft180_show_uint(120, 96, barrier_type[4], 1);
        tft180_show_uint(120, 112, barrier_type[5], 1);
        tft180_show_string(0, nummm * 16, "#");

        Key_Scan();
        if (Key_Number == 8)
        {
            ++nummm;
            if (nummm > 7)
            {
                nummm = 1;
                tft180_show_string(0, 112, " ");
            }
            nux = nummm - 1;
            tft180_show_string(0, nummm * 16, "#");
            if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
        }
        else if (Key_Number == 2)
        {
            --nummm;
            if (nummm < 1)
            {
                nummm = 7;
                tft180_show_string(0, 16, " ");
            }
            nux = nummm + 1;
            tft180_show_string(0, nummm * 16, "#");
            if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
        }
        else if (Key_Number == 6)
        {
            switch (nummm)
            {
                case 1:
                    ++ cout_finish;
                    break;
                case 2:
                    ++ barrier_type[0];
                    break;
                case 3:
                    ++ barrier_type[1];
                    break;
                case 4:
                    ++ barrier_type[2];
                    break;
                case 5:
                    ++ barrier_type[3];
                    break;
                case 6:
                    ++ barrier_type[4];
                    break;
                case 7:
                    ++ barrier_type[5];
                    break;
                default:
                    break;
            }
        }
        else if (Key_Number == 4)
        {
            switch (nummm)
            {
                case 1:
                    -- cout_finish;
                    break;
                case 2:
                    -- barrier_type[0];
                    break;
                case 3:
                    -- barrier_type[1];
                    break;
                case 4:
                    -- barrier_type[2];
                    break;
                case 5:
                    -- barrier_type[3];
                    break;
                case 6:
                    -- barrier_type[4];
                    break;
                case 7:
                    -- barrier_type[5];
                    break;
                default:
                    break;
            }
        }
        else if (Key_Number == 9)
        {
            tft180_clear();
            Key_Number = 0;
            break;
        }
        else if(Key_Number == 1)
        {
           tft180_clear();
           gpio_set_level(C7, 0);
           gpio_set_level(A8, 0);
           gpio_set_level(B0, 1);
           Key_Number = 0;
           Key_Switch = !Key_Switch;
        }
    }

}


void ZW_Ctrl(void)
{
    tft180_clear();
    while(Key_Switch == 1)
    {
        tft180_show_string(16, 16, "a:");
        tft180_show_string(16, 32, "b:");
        tft180_show_string(16, 48, "ad_referens:");
        tft180_show_string(16, 64, "spaceflag:");
        tft180_show_string(16, 80, "AD_MAX:");

        tft180_show_int(120, 16, a, 4);
        tft180_show_int(120, 32, b, 4);
        tft180_show_int(120, 48, ad_referens, 4);
        tft180_show_int(120, 64, spaceflag, 4);
        tft180_show_int(120, 80, AD_Max, 4);
        tft180_show_string(0, nummm * 16, "#");

        Key_Scan();
        if (Key_Number == 8)
        {
            ++nummm;
            if (nummm > 5)
            {
                nummm = 1;
                tft180_show_string(0, 80, " ");
            }
            nux = nummm - 1;
            tft180_show_string(0, nummm * 16, "#");
            if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
        }
        else if (Key_Number == 2)
        {
            --nummm;
            if (nummm < 1)
            {
                nummm = 5;
                tft180_show_string(0, 16, " ");
            }
            nux = nummm + 1;
            tft180_show_string(0, nummm * 16, "#");
            if(nux <= 7 && nux >= 0)  tft180_show_string(0, nux * 16, " ");
        }
        else if (Key_Number == 6)
        {
            switch (nummm)
            {
                case 1:
                    ++ a;
                    break;
                case 2:
                    ++ b;
                    break;
                case 3:
                    ++ ad_referens;
                    break;
                case 4:
                    ++ spaceflag;
                    break;
                case 5:
                    AD_Max += 2;
                    break;
                default:
                    break;
            }
        }
        else if (Key_Number == 4)
        {
            switch (nummm)
            {
                case 1:
                    -- a;
                    break;
                case 2:
                    -- b;
                    break;
                case 3:
                    -- ad_referens;
                    break;
                case 4:
                    -- spaceflag;
                    break;
                case 5:
                    AD_Max -= 2;
                    break;
                default:
                    break;
            }
        }
        else if (Key_Number == 9)
        {
            tft180_clear();
            break;
        }
        else if(Key_Number == 1)
        {
           tft180_clear();
           gpio_set_level(C7, 0);
           gpio_set_level(A8, 0);
           gpio_set_level(B0, 1);
           Key_Number = 0;
           Key_Switch = !Key_Switch;
        }
    }
}
