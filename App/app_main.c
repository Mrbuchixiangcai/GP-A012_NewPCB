//头文件header file//
#include "app_main.h"

//宏定义macro definition//


//类型定义byte definition//
PLAY_MODE PlayMode; //关机，开机，开机&蓝牙开启
FIRE_SIZE FireSize1;//火焰的大小
FIRE_SIZE  FireSize1_bk;

//变量定义variable definition//
uint8_t  idle_f;
uint16_t  cntIdle;
uint8_t  cntAppTick;
uint8_t  electricityBrightness;//电流亮度，改变3232芯片26H-49H寄存器的bit1和bit2可以改变电流，进而改变亮度
uint8_t  PWMBrightness;//PWM亮度，改变PWM亮度改变
uint8_t  keyBT;
uint8_t  keyBT_bk;

uint8_t Adc_Dma_Irq_f;
void ADC_GetBuffer(void) //在中断里面调用，然后中断处理结束进入这里出具求平均
{
  uint16_t i;
  if((Adc_Dma_Irq_f))// && (FireSize1 == MODE4_FLASHING))
  {
	Adc_Dma_Irq_f = 0;
	if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	for (i = 0; i < ADC_DMA_SIZE; i++)
		AdcAudio_Buf[i] = AdcDma_Buf[i] - 0x0400;//减0x0400是因为最低音量时仍有0x0420左右
	//AD_ContinuousToAverage();//连续采集的ad值累加求平均值
	if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)AdcDma_Buf, ADC_DMA_SIZE) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
  }
}

//标志位定义flags definetion//
uint8_t  AppTick1ms;
uint8_t  AppTick0;
uint8_t  AppTick1;
uint8_t  AppTick2;
uint8_t  AppTick3;
uint8_t  AppTick4;
uint8_t  AppTick5;
uint8_t  brightness1;
uint8_t  fireSpeed;
uint8_t  bt_fire;
         


void PowerON_Reset(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
	brightness1=1;//与electricityBrightness(电流控制亮度)共同控制
	electricityBrightness=0x07;//brightness1(PWM控制亮度)共同控制
	SDA5_OUT();
	SDA6_OUT();
	SDA7_OUT();
	SDA8_OUT();
	SDA9_OUT();
	SDA10_OUT();
	SDA11_OUT();
	SDA12_OUT();
	FireSize1=MODE0_OFF_FIRE;
	PlayMode=PLAY_ON;


}

//函数定义function definetion//
void app_main(void)
{
	PowerON_Reset();
	while(1)
	{
		if(AppTick1ms)
		{
			AppTick1ms=0;
			ADC_GetBuffer();
			keyBT=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
			if(keyBT_bk!=keyBT)
			{
				keyBT_bk=keyBT;
				if(keyBT==1)
					PlayMode=PLAY_BT;
				else 
				{
					PlayMode=PLAY_OFF;
					FireSize1=MODE0_OFF_FIRE;
				}
			}
		}
		if(AppTick0)
		{
			AppTick0=0;
			KeyScan();
			KeyComMsg();
		}
		if(AppTick1)
		{
			AppTick1=0;
			BlueMode_Handle();
			
		}
		if(AppTick2)
		{
			AppTick2=0;
			
			//Array_CampFire();
//			Array_CampFire2();
			FireMode_Handle();
		}
		if(AppTick3)
		{
			AppTick3=0;
			RGBMode_Handle();
		}
//		if(AppTick5)
//		{
//			AppTick5=0;
//			
//		}
	}
}


