#include "app_main.h"
#include "h_adc.h"

Audio_ad_TypeDef	audio_ad;//----------------------------��ƵAD�ṹ��

uint8_t						DMA_interrupt_flag;//------------------DMA�����жϱ�־

uint16_t 					dma_ad[AD_LENGH];//-------------------DMA���ת��AD��ɺ������
uint16_t 					temp_ad[CHAN_NUM][CHAN_LENGH];//-------��ʱADֵ����


//uint16_t					current_T_AD;//------------------------��ǰ�ڲ��¶�ADֵ
//float							current_temperature;//-----------------��ǰ�¶�
//uint16_t					current_REF_AD;//----------------------��ǰ�ڲ��ο���ѹADֵ
//float							current_RER_voltage;//-----------------��ǰ�ο���ѹ


//����ƽ��ֵ������,���ȣ�
uint16_t calculate_average_value(uint16_t data[],uint16_t lengh)
{
	
	//C89�涨�ֲ����������������ڿ�ͷ
	uint16_t i;
	
	//�����ʱ����
	uint32_t sum_temp=0;
	
	//��λ���ֵ
	audio_ad.max=0;

	//��λ��Сֵ
	audio_ad.min=0XFFF;

	//��������
	for(i=0;i<lengh ;i++)
	{
		
		//������Сֵ
		if(data[i]<audio_ad.min)
		{
			//������Сֵ
			audio_ad.min=data[i];
		}
		//
		
		//�������ֵ
		if(data[i]>audio_ad.max)
		{
			//�������ֵ
			audio_ad.max=data[i];
		}
		//
		
		//�ۼ����
		sum_temp=sum_temp+data[i];
	}
	//
	
	//��ȥ���ֵ����Сֵ
	//sum_temp=sum_temp-audio_ad.min-audio_ad.max;
	
	//���ȼ�2
	//lengh-=2;
	
	//����ƽ��ֵ
	return  (sum_temp /lengh);
}
//


////��ȡ�ڲ��¶ȺͲο���ѹ
//void get_temperature_and_refvoltage(void)
//{
//	
//	//��ǰ��ȡ�����¶�ADƽ��ֵ
//	current_T_AD=calculate_average_value (temp_ad[TEMPERATURE_CHAN],CHAN_LENGH);
//	
//	//��ǰ��ȡ�����ڲ��ο���ѹƽ��ֵ
//	current_REF_AD=calculate_average_value (temp_ad[VREFINT_CHAN],CHAN_LENGH);
//	
//	//��ǰ�¶�
//	current_temperature=(current_T_AD*1.0)*25/T25_VALUE;
//	
//	//��ǰ�ο���ѹ
//	current_RER_voltage=(current_REF_AD*1.0)*1.2/REF_VALUE;
//}
////

//��ʼ��ADC
void init_adc(void)
{
	
	//����֮ǰУ׼ADC
	if (HAL_ADCEx_Calibration_Start (&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	//
	
	//����DMA������DMA���յ������ݴ�ŵ�ָ�����ȵ�������
	if (HAL_ADC_Start_DMA(&hadc ,(uint32_t*)dma_ad,AD_LENGH) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	//
}
//


//��������
void cope_data(void)
{
	
	//C89�涨�ֲ����������������ڿ�ͷ
	uint8_t i;
	
	//C89�涨�ֲ����������������ڿ�ͷ
	uint16_t j;

	//����ͨ������(ͨ�����������ܳ���uint8_t)
	for(i=0;i<CHAN_NUM;i++)
	{

		//����ͨ������(ͨ����������Ϊuint16_t)
		for(j=0;j<CHAN_LENGH;j++)
		{
			
			//��ͨ����������
			temp_ad[i][j]=dma_ad[i+CHAN_NUM*j];
		}
		//
	}
	//
}
//


////DMA�жϴ���
//void DMA_interrupt_handle(DMA_HandleTypeDef *hdma)
//{

//	//��������
//	cope_data();
//	
//	//��Ǵ������
//	DMA_interrupt_flag=1;

//	//����ADǰ�����ж�
//	//__disable_irq();
//	
//	//����֮ǰ��ͣDMA;
//	//HAL_ADC_Stop_DMA(&hadc);
//	
//	//�������
//	//if(DMA_interrupt_flag==1)
//	//{
//		//cope_data();
//	//}
//	//
//	
//	//����DMA������DMA���յ������ݴ�ŵ�ָ�����ȵ�������
//	//HAL_ADC_Start_DMA(&hadc ,(uint32_t*)dma_ad,AD_LENGH);

//	//����������������ж�
//	//__enable_irq();
//}
////

uint16_t adAverageValue;
void ADAverageValue(void)
{
	adAverageValue = audio_ad.current_average;
	if ((adAverageValue >= 0x0030) && (adAverageValue <= 0x01F7))
		ADGrade = 1;
	else if ((adAverageValue >= 0x01F7) && (adAverageValue <= 0x03EE))
		ADGrade = 2;
	else if ((adAverageValue >= 0x03EE) && (adAverageValue <= 0x05E5))
		ADGrade = 3;
	else if ((adAverageValue >= 0x05E5) && (adAverageValue <= 0x07DC))
		ADGrade = 4;
	else if ((adAverageValue >= 0x07DC) && (adAverageValue <= 0x09D3))
		ADGrade = 5;
	else if (adAverageValue >= 0x09D3)
		ADGrade = 6;

	if (adAverageValue < 0x0030)
	{	
		adAverZero = 0;
		ADGrade = 0;
	}
	else 
		adAverZero = 1;
	Flag_ADAverageZero = adAverZero;
}
//ADCɨ��
void adc_scan(void)
{
	
	//�������
	if(DMA_interrupt_flag==1)
	{
		
		//��λ���λ
		DMA_interrupt_flag=0;
		
		//ֹͣDMA
		if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
		//
		
		//��������
		cope_data();
		
		//����DMA������DMA���յ������ݴ�ŵ�ָ�����ȵ�������
		if (HAL_ADC_Start_DMA(&hadc ,(uint32_t*)dma_ad,AD_LENGH) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
		//

		//��ȡ�ڲ��¶ȺͲο���ѹ
		//get_temperature_and_refvoltage();

		//��ȡ��ǰADƽ��ֵ(��Ƶͨ�����飬����)
		audio_ad.current_average=calculate_average_value (temp_ad [AUDIO_CHAN] ,CHAN_LENGH);

		//ֱ�ӻ�ȡһ��ADֵ
		//audio_ad.current_average=dma_ad[0];

		//����ADֵ�仯�ʣ�������󣬸�����С��0û�б仯
		audio_ad.slope =audio_ad.current_average -audio_ad.previous_average ;
		
		//����ǰһ��ADֵ
		audio_ad.previous_average=audio_ad.current_average;

	}
	ADAverageValue();
}
//








