#ifndef  __APP_MAIN_H__
#define  __APP_MAIN_H__
#include "stm32f0xx_hal.h"
#include <string.h>
#include "Key.h"
#include "h_adc.h"
#include "bt_mode.h"
#include "led_driver.h"
#include "big_fire.h"
#include "middle_fire.h"
#include "small_fire.h"
#include "music_fire.h"
#include "wind_fire.h"
#include "level_fire.h"
typedef unsigned         char uint8_t;
typedef unsigned short   int  uint16_t;
typedef unsigned         int  uint32_t;

#define uchar uint8_t
#define uint  uint16_t
#define ulong uint32_t

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define FRAME_LENGH		96
#define VAL1			0x0A  //DEC:10
#define VAL2			0x1E  //DEC:30
#define VAL3			0x32  //DEC:50
#define VAL4			0x50  //DEC:80
#define VAL5			0x6E  //DEC:110
#define VAL6			0x96  //DEC:150

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;
extern UART_HandleTypeDef huart1;


typedef enum
{
	FIRE_OFF   =0,
	FIRE_SMALL   ,//Ð¡»ð
	FIRE_MIDDLE  ,//ÖÐ»ð
	FIRE_BIG     ,//´ó»ð
	FIRE_WIND  	 ,//Ëæ·ç°Ú¶¯ÐÎÌ¬
	FIRE_MUSIC   ,//»ðÑæËæÒôÀÖ
	FIRE_LEVEL   ,//ÏñÒôÀÖÆµÆ×
}FIRE_MODE;
#define FIRE_MODE_MAX  FIRE_LEVEL

typedef enum
{
	PLAY_OFF =0,
	PLAY_ON	 =1,//À¶ÑÀ¹Ø
	PLAY_BT  =2,//À¶ÑÀ¿ª
}PLAY_MODE;

#define BTPower() HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)

extern uint8_t   cntAppTick;
extern uint8_t   AppTick1ms;
extern uint8_t   AppTick0;
extern uint8_t   AppTick1;
extern uint8_t   AppTick2;
extern uint8_t   AppTick3;
extern uint8_t   AppTick4;
extern uint8_t   AppTick5;
extern PLAY_MODE PlayMode; 
extern FIRE_MODE FireMode;
extern FIRE_MODE FireMode_c;

extern void app_main(void);

#endif








