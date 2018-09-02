#ifndef  __RGB_H__
#define  __RGB_H__

//头文件header file//
#include "app_main.h"

//宏定义macro definition//


//类型定义byte definition//
typedef struct
{
	uint8_t  path;
	uint8_t  step;
	uint8_t  data[2][6];
}LED_CAMPFIRE_TYPEDEF;


//变量定义variable definition//


//标志位定义flags definetion//


//函数定义function definetion//
void RGBMode_Handle(void);
void FireMode_Handle(void);
void LED_Fire1(void);
void LED_Fire2(void);
void Array_CampFire(void);
void Array_CampFire2(void);
//外部调用_宏定义macro definition//


//外部调用_类型定义byte definition//


//外部调用_变量定义variable definition//


//外部调用_标志位定义flags definetion//
extern uint8_t  Flag_ADAverageZero;

//外部调用_函数定义function definetion//
extern uint8_t ADAverageValue(void);







#endif









