#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__
#include "app_main.h"

#include "stm32f0xx_hal.h"
#include "big_fire.h"

#define sda1(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_5;\
												 else GPIOA->BRR = GPIO_PIN_5;}while(0)

#define sda2(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_6;\
												 else GPIOA->BRR = GPIO_PIN_6;}while(0)

#define sda3(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_7;\
												 else GPIOA->BRR = GPIO_PIN_7;}while(0)

#define sda4(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_8;\
												 else GPIOA->BRR = GPIO_PIN_8;}while(0)

#define sda5(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_9;\
												 else GPIOA->BRR = GPIO_PIN_9;}while(0)												 

#define sclk(x)				do{if(x) GPIOB->BSRR = GPIO_PIN_0;\
												 else GPIOB->BRR = GPIO_PIN_0;}while(0)

//#define sda1(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_5;\
//												 else GPIOA->BRR = GPIO_PIN_5;}while(0)

//#define sda2(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_6;\
//												 else GPIOA->BRR = GPIO_PIN_6;}while(0)

//#define sda3(x)				do{if(x) GPIOB->BSRR = GPIO_PIN_0;\
//												 else GPIOB->BRR = GPIO_PIN_0;}while(0)

//#define sda4(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_8;\
//												 else GPIOA->BRR = GPIO_PIN_8;}while(0)

//#define sda5(x)				do{if(x) GPIOA->BSRR = GPIO_PIN_7;\
//												 else GPIOA->BRR = GPIO_PIN_7;}while(0)												 

//#define sclk(x)				do{if(x) GPIOB->BSRR = GPIO_PIN_1;\
//												 else GPIOB->BRR = GPIO_PIN_1;}while(0)

#define _N_NOP()				__NOP();__NOP();__NOP();__NOP();__NOP();
												 
#define	LED_LENGH		60  //60ธ๖ตฦึ้
												 
typedef struct
{
	uint8_t  path;
	uint8_t  step;
	uint8_t  data[12][5];
}LED_CAMPFIRE_TYPEDEF;
extern uint8_t  send_index;
extern uint8_t  send_enable;
extern uint8_t  Fire_Data_H[6][10]; 
extern uint8_t  Fire_Data_V[12][5]; 
extern uint8_t  Fire_Data_V_sub[12][5]; 
extern uint8_t  PwmDuty[LED_LENGH];	
extern void LoadData_to_MC96F_V(void); 
extern void LoadData_to_MC96F_H(void); 
extern void MC96F6508A_driver(void);
extern void FireMode_Handle(void);

#endif









