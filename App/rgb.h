#ifndef  __RGB_H__
#define  __RGB_H__

//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//


//���Ͷ���byte definition//
typedef struct
{
	uint8_t  path;
	uint8_t  step;
	uint8_t  data[2][6];
}LED_CAMPFIRE_TYPEDEF;


//��������variable definition//


//��־λ����flags definetion//


//��������function definetion//
void RGBMode_Handle(void);
void FireMode_Handle(void);
void LED_Fire1(void);
void LED_Fire2(void);
void Array_CampFire(void);
void Array_CampFire2(void);
//�ⲿ����_�궨��macro definition//


//�ⲿ����_���Ͷ���byte definition//


//�ⲿ����_��������variable definition//


//�ⲿ����_��־λ����flags definetion//
extern uint8_t  Flag_ADAverageZero;

//�ⲿ����_��������function definetion//
extern uint8_t ADAverageValue(void);







#endif









