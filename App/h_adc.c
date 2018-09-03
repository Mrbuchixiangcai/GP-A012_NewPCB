#include "app_main.h"
#include "h_adc.h"

Audio_ad_TypeDef	audio_ad;//----------------------------音频AD结构体

uint8_t						DMA_interrupt_flag;//------------------DMA产生中断标志

uint16_t 					dma_ad[AD_LENGH];//-------------------DMA存放转换AD完成后的数组
uint16_t 					temp_ad[CHAN_NUM][CHAN_LENGH];//-------临时AD值数组


//uint16_t					current_T_AD;//------------------------当前内部温度AD值
//float							current_temperature;//-----------------当前温度
//uint16_t					current_REF_AD;//----------------------当前内部参考电压AD值
//float							current_RER_voltage;//-----------------当前参考电压


//计算平均值（数组,长度）
uint16_t calculate_average_value(uint16_t data[],uint16_t lengh)
{
	
	//C89规定局部变量的声明必须在开头
	uint16_t i;
	
	//求和临时变量
	uint32_t sum_temp=0;
	
	//复位最大值
	audio_ad.max=0;

	//复位最小值
	audio_ad.min=0XFFF;

	//遍历数组
	for(i=0;i<lengh ;i++)
	{
		
		//查找最小值
		if(data[i]<audio_ad.min)
		{
			//更新最小值
			audio_ad.min=data[i];
		}
		//
		
		//查找最大值
		if(data[i]>audio_ad.max)
		{
			//更新最大值
			audio_ad.max=data[i];
		}
		//
		
		//累加求和
		sum_temp=sum_temp+data[i];
	}
	//
	
	//减去最大值和最小值
	//sum_temp=sum_temp-audio_ad.min-audio_ad.max;
	
	//长度减2
	//lengh-=2;
	
	//返回平均值
	return  (sum_temp /lengh);
}
//


////获取内部温度和参考电压
//void get_temperature_and_refvoltage(void)
//{
//	
//	//当前读取到的温度AD平均值
//	current_T_AD=calculate_average_value (temp_ad[TEMPERATURE_CHAN],CHAN_LENGH);
//	
//	//当前读取到的内部参考电压平均值
//	current_REF_AD=calculate_average_value (temp_ad[VREFINT_CHAN],CHAN_LENGH);
//	
//	//当前温度
//	current_temperature=(current_T_AD*1.0)*25/T25_VALUE;
//	
//	//当前参考电压
//	current_RER_voltage=(current_REF_AD*1.0)*1.2/REF_VALUE;
//}
////

//初始化ADC
void init_adc(void)
{
	
	//启动之前校准ADC
	if (HAL_ADCEx_Calibration_Start (&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	//
	
	//启动DMA，并把DMA接收到的数据存放到指定长度的数组中
	if (HAL_ADC_Start_DMA(&hadc ,(uint32_t*)dma_ad,AD_LENGH) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	//
}
//


//复制数据
void cope_data(void)
{
	
	//C89规定局部变量的声明必须在开头
	uint8_t i;
	
	//C89规定局部变量的声明必须在开头
	uint16_t j;

	//遍历通道个数(通道个数不可能超过uint8_t)
	for(i=0;i<CHAN_NUM;i++)
	{

		//遍历通道长度(通道长度上限为uint16_t)
		for(j=0;j<CHAN_LENGH;j++)
		{
			
			//按通道分类数组
			temp_ad[i][j]=dma_ad[i+CHAN_NUM*j];
		}
		//
	}
	//
}
//


////DMA中断处理
//void DMA_interrupt_handle(DMA_HandleTypeDef *hdma)
//{

//	//复制数据
//	cope_data();
//	
//	//标记传输完成
//	DMA_interrupt_flag=1;

//	//复制AD前禁用中断
//	//__disable_irq();
//	
//	//复制之前暂停DMA;
//	//HAL_ADC_Stop_DMA(&hadc);
//	
//	//传输完成
//	//if(DMA_interrupt_flag==1)
//	//{
//		//cope_data();
//	//}
//	//
//	
//	//启动DMA，并把DMA接收到的数据存放到指定长度的数组中
//	//HAL_ADC_Start_DMA(&hadc ,(uint32_t*)dma_ad,AD_LENGH);

//	//复制完后重新启用中断
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
//ADC扫描
void adc_scan(void)
{
	
	//传输完成
	if(DMA_interrupt_flag==1)
	{
		
		//复位标记位
		DMA_interrupt_flag=0;
		
		//停止DMA
		if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
		//
		
		//复制数据
		cope_data();
		
		//启动DMA，并把DMA接收到的数据存放到指定长度的数组中
		if (HAL_ADC_Start_DMA(&hadc ,(uint32_t*)dma_ad,AD_LENGH) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
		//

		//获取内部温度和参考电压
		//get_temperature_and_refvoltage();

		//获取当前AD平均值(音频通道数组，长度)
		audio_ad.current_average=calculate_average_value (temp_ad [AUDIO_CHAN] ,CHAN_LENGH);

		//直接获取一个AD值
		//audio_ad.current_average=dma_ad[0];

		//计算AD值变化率，正数变大，负数变小，0没有变化
		audio_ad.slope =audio_ad.current_average -audio_ad.previous_average ;
		
		//更新前一个AD值
		audio_ad.previous_average=audio_ad.current_average;

	}
	ADAverageValue();
}
//








