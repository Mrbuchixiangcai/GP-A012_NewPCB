#ifndef __h_adc_h__
#define __h_adc_h__

#include "stm32f0xx_hal.h"

//#define TS_CAL1						(__IO uint16_t *)(0X1FFFF7B8)//�ڲ��¶�ADֵ��ַ
//#define VREFINT_CAL				(__IO uint16_t *)(0X1FFFF7BA)//�ڲ�1.2V��׼�ο���ѹ��ַ
//#define T25_VALUE					(*TS_CAL1)//-------------------�ڲ��¶�25���϶�ADֵ0X6CA,0X6C9(1737),25���϶�
//#define REF_VALUE					(*VREFINT_CAL)//---------------�ڲ��ο���ѹADֵ0X05F7,OX5FB(1531),1.233V

#define	CHAN_NUM					(1)//------------------------ͨ������
#define	CHAN_LENGH				(10)//-----------------------ͨ������1000us/((239.5+12.5)/14MHz)=1000/18us=56������ֵ
#define AD_LENGH					(CHAN_NUM*CHAN_LENGH)//------ADֵ�����ܳ���

#define	AUDIO_CHAN					(0)//----------------------��Ƶͨ��
//#define TEMPERATURE_CHAN	(1)//----------------------�ڲ��¶�ͨ��
//#define VREFINT_CHAN			(2)//----------------------�ڲ��ο���ѹͨ��

#define	NOISE_AD_AVERAGE	0X050//----------------------ʵ������ADƽ��ֵ
#define	NOISE_AD_PEAK			0X100//----------------------ʵ������AD��ֵ
#define	AD_MAX						0X380//----------------------AD���ֵ


typedef struct audio_ad_struct
{
	uint16_t 		current_average;//---------��ǰADֵ
	uint16_t 		previous_average;//--------ǰһ��ADֵ
	int16_t 		slope;//-------------------ADֵ�仯��
	uint16_t		max;//---------------------AD���ֵ
	uint16_t 		min;//---------------------AD��Сֵ
	
}Audio_ad_TypeDef;
//

extern ADC_HandleTypeDef 	hadc;
extern DMA_HandleTypeDef 	hdma_adc;

extern Audio_ad_TypeDef		audio_ad;


//��Ǵ������
extern uint8_t			DMA_interrupt_flag;//------------------DMA�����жϱ�־

extern void					init_adc(void);
extern void		 			adc_scan(void);
//extern void 				DMA_interrupt_handle(DMA_HandleTypeDef *hdma);

#endif
