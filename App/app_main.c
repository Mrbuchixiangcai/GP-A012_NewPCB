//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//


//���Ͷ���byte definition//
PLAY_MODE PlayMode; //�ػ�������������&��������
FIRE_SIZE FireSize1;//����Ĵ�С
FIRE_SIZE  FireSize1_bk;

//��������variable definition//
uint8_t  idle_f;
uint16_t  cntIdle;
uint8_t  cntAppTick;
uint8_t  electricityBrightness;//�������ȣ��ı�3232оƬ26H-49H�Ĵ�����bit1��bit2���Ըı�����������ı�����
uint8_t  PWMBrightness;//PWM���ȣ��ı�PWM���ȸı�
uint8_t  keyBT;
uint8_t  keyBT_bk;

uint8_t Adc_Dma_Irq_f;
void ADC_GetBuffer(void) //���ж�������ã�Ȼ���жϴ��������������������ƽ��
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
		AdcAudio_Buf[i] = AdcDma_Buf[i] - 0x0400;//��0x0400����Ϊ�������ʱ����0x0420����
	//AD_ContinuousToAverage();//�����ɼ���adֵ�ۼ���ƽ��ֵ
	if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)AdcDma_Buf, ADC_DMA_SIZE) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
  }
}

//��־λ����flags definetion//
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
	brightness1=1;//��electricityBrightness(������������)��ͬ����
	electricityBrightness=0x07;//brightness1(PWM��������)��ͬ����
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

//��������function definetion//
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

