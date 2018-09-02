#ifndef  __RGB_FLASHING_H__
#define  __RGB_FLASHING_H__

//头文件header file//
#include "app_main.h"

//宏定义macro definition//
#define ADC_DMA_SIZE 10
#define audio_01_max_index	100

//类型定义byte definition//
typedef struct 
{
	uint16_t max;
	uint16_t mean;
	uint16_t mini;
	uint16_t index;
	uint16_t Data[ADC_DMA_SIZE];
} ADC_VAL_TypeDef;

typedef enum 
{
	LOWEST = 0,
	LOW		  ,
	MID		  ,
	HIGH	  ,
	HIGHEST	  ,
} TYPE_LEVEL;

typedef struct 
{
	uint16_t cntHighest;
	uint16_t cntHigh;
	uint16_t cntMid;
	uint16_t cntLow;
	uint16_t cntLowest;
	TYPE_LEVEL Level;
} AUDIO_LEVEL_TypeDef;

//变量定义variable definition//


//标志位定义flags definetion//


//函数定义function definetion//


//外部调用_宏定义macro definition//


//外部调用_类型定义byte definition//

//外部调用_变量定义variable definition//
//extern  uint8_t  audio_01_index;
//extern  uint16_t audio_01_buf[audio_01_max_index];
//extern  uint32_t audio_01_data;
//extern  uint16_t audio_01_pj_data;
extern uint16_t AdcDma_Buf[ADC_DMA_SIZE];	   //采集到的初步电压值
extern uint16_t AdcAudio_Buf[ADC_DMA_SIZE];   //采集到的初步电压值

//外部调用_标志位定义flags definetion//
//extern uint8_t Flag_Music_Tick;

//外部调用_函数定义function definetion//
//extern uint16_t AD_ContinuousToAverage(void);
//extern uint8_t  Audio_Level_Deal(void);

#endif




