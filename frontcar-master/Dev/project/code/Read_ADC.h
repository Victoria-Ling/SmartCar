#ifndef READ_ADC_H_
#define READ_ADC_H_

//******************电感排布图*******************//

//第一排     ——      |    ——     |       ——      //



//第二排            ——           ——              //

//******************电感排布图******************//

#define ZLAD  GUI_AD[0]     //最后一排左横
#define QLAD  GUI_AD[1]     //最前一排左横
#define XLAD  GUI_AD[2]     //最前一排左竖
#define MAD   GUI_AD[3]     //最前一排中间
#define XRAD  GUI_AD[4]     //最前一排右竖
#define QRAD  GUI_AD[5]     //最前一排右横
#define ZRAD  GUI_AD[6]     //最后一排右横

extern float GUI_AD[7];
extern uint16 ADDD_valu[7];
extern int16 AD_Max;
extern int8 Max_Front, Position, Position_last;
extern uint16 Position_Transit[2];

void ADC_Read(void);

#endif
