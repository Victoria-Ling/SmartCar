#ifndef READ_ADC_H_
#define READ_ADC_H_

//******************����Ų�ͼ*******************//

//��һ��     ����      |    ����     |       ����      //



//�ڶ���            ����           ����              //

//******************����Ų�ͼ******************//

#define ZLAD  GUI_AD[0]     //���һ�����
#define QLAD  GUI_AD[1]     //��ǰһ�����
#define XLAD  GUI_AD[2]     //��ǰһ������
#define MAD   GUI_AD[3]     //��ǰһ���м�
#define XRAD  GUI_AD[4]     //��ǰһ������
#define QRAD  GUI_AD[5]     //��ǰһ���Һ�
#define ZRAD  GUI_AD[6]     //���һ���Һ�

extern float GUI_AD[7];
extern uint16 ADDD_valu[7];
extern int16 AD_Max;
extern int8 Max_Front, Position, Position_last;
extern uint16 Position_Transit[2];

void ADC_Read(void);

#endif
