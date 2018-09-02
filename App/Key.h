#ifndef  __KEY_H__
#define  __KEY_H__

//头文件header file//
#include "app_main.h"

//宏定义macro definition//
#define  K_D     (1<<5)//第一位向左移动5位
#define  K_U     (2<<5)
#define  K_H     (3<<5)
#define  K_R     (4<<5)
#define  K_L     (5<<5)
#define  K_LU    (6<<5)
#define  KD(x)   (x|K_D)
#define  KU(x)   (x|K_U)
#define  KH(x)   (x|K_H)
#define  KR(x)   (x|K_R)
#define  KL(x)   (x|K_L)
#define  KLU(x)  (x|K_LU)

#define  cKEY_CLICK    5  //单击时间常数
#define  cKEY_HOLD     50 //按住时间常数
#define  cKEY_RATE_VOL 20 //连击时间常数

#define  KEY_LIGHT()   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)
#define  BT_POWER()    HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)

//类型定义byte definition//
enum
{
	T_NC     =0,
	T_BT_POWER ,
	T_LIGHT    ,
};

//变量定义variable definition//


//标志位定义flags definetion//


//函数定义function definetion//

//外部调用_宏定义macro definition//


//外部调用_类型定义byte definition//


//外部调用_变量定义variable definition//


//外部调用_标志位定义flags definetion//


//外部调用_函数定义function definetion//
extern void    KeyScan(void);
extern void    KeyComMsg(void);
extern uint8_t GetVoltageValue(void);




#endif









