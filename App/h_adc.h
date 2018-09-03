#ifndef __h_adc_h__
#define __h_adc_h__

#include "stm32f0xx_hal.h"

//#define TS_CAL1						(__IO uint16_t *)(0X1FFFF7B8)//内部温度AD值地址
//#define VREFINT_CAL				(__IO uint16_t *)(0X1FFFF7BA)//内部1.2V基准参考电压地址
//#define T25_VALUE					(*TS_CAL1)//-------------------内部温度25摄氏度AD值0X6CA,0X6C9(1737),25摄氏度
//#define REF_VALUE					(*VREFINT_CAL)//---------------内部参考电压AD值0X05F7,OX5FB(1531),1.233V

#define	CHAN_NUM					(1)//------------------------通道个数
#define	CHAN_LENGH				(10)//-----------------------通道长度1000us/((239.5+12.5)/14MHz)=1000/18us=56个理论值
#define AD_LENGH					(CHAN_NUM*CHAN_LENGH)//------AD值数组总长度

#define	AUDIO_CHAN					(0)//----------------------音频通道
//#define TEMPERATURE_CHAN	(1)//----------------------内部温度通道
//#define VREFINT_CHAN			(2)//----------------------内部参考电压通道

#define	NOISE_AD_AVERAGE	0X050//----------------------实测噪音AD平均值
#define	NOISE_AD_PEAK			0X100//----------------------实测噪音AD峰值
#define	AD_MAX						0X380//----------------------AD最大值


typedef struct audio_ad_struct
{
	uint16_t 		current_average;//---------当前AD值
	uint16_t 		previous_average;//--------前一个AD值
	int16_t 		slope;//-------------------AD值变化率
	uint16_t		max;//---------------------AD最大值
	uint16_t 		min;//---------------------AD最小值
	
}Audio_ad_TypeDef;
//

extern ADC_HandleTypeDef 	hadc;
extern DMA_HandleTypeDef 	hdma_adc;

extern Audio_ad_TypeDef		audio_ad;


//标记传输完成
extern uint8_t			DMA_interrupt_flag;//------------------DMA产生中断标志

extern void					init_adc(void);
extern void		 			adc_scan(void);
//extern void 				DMA_interrupt_handle(DMA_HandleTypeDef *hdma);

#endif
