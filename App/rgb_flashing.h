#ifndef  __RGB_FLASHING_H__
#define  __RGB_FLASHING_H__

//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//
#define ADC_DMA_SIZE 10
#define audio_01_max_index	100

//���Ͷ���byte definition//
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

//��������variable definition//


//��־λ����flags definetion//


//��������function definetion//


//�ⲿ����_�궨��macro definition//


//�ⲿ����_���Ͷ���byte definition//

//�ⲿ����_��������variable definition//
//extern  uint8_t  audio_01_index;
//extern  uint16_t audio_01_buf[audio_01_max_index];
//extern  uint32_t audio_01_data;
//extern  uint16_t audio_01_pj_data;
extern uint16_t AdcDma_Buf[ADC_DMA_SIZE];	   //�ɼ����ĳ�����ѹֵ
extern uint16_t AdcAudio_Buf[ADC_DMA_SIZE];   //�ɼ����ĳ�����ѹֵ

//�ⲿ����_��־λ����flags definetion//
//extern uint8_t Flag_Music_Tick;

//�ⲿ����_��������function definetion//
//extern uint16_t AD_ContinuousToAverage(void);
//extern uint8_t  Audio_Level_Deal(void);

#endif




