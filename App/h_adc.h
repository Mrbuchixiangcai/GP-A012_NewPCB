#ifndef  __H_ADC_H__
#define  __H_ADC_H__
#include "app_main.h"
extern uint8_t  Adc_Dma_Irq_f;
#define AUDIO_SIZE 10
#define MEAN_SIZE  10
#define ADC_DMA_SIZE  1
#define ADC_DATA_SIZE 100
extern uint8_t   Adc_Dma_Irq_f;
extern uint16_t  AdcDma_Buf[ADC_DMA_SIZE];
extern uint16_t  AdcDma_Data[ADC_DATA_SIZE];		
extern uint16_t  Audio_Mean[MEAN_SIZE];
extern uint16_t  AdcAudio_Data[AUDIO_SIZE]; 
extern void ADC_GetBuffer(void); 
extern void Audio_Average(void); 
#endif











