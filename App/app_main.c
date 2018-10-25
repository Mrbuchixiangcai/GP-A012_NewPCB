//Í·ÎÄ¼þheader file//
#include "app_main.h"
uint8_t   cntAppTick;
uint8_t   AppTick1ms;
uint8_t   AppTick0;
uint8_t   AppTick1;
uint8_t   AppTick2;
uint8_t   AppTick3;
uint8_t   AppTick4;
uint8_t   AppTick5;
PLAY_MODE PlayMode;
FIRE_MODE FireMode;
FIRE_MODE FireMode_c;
void PowerON_Reset(void)
{
	PlayMode = PLAY_ON;
	FireMode = FIRE_OFF;
	HAL_UART_Receive_IT(&huart1, Uart1_ReceiveBuffer, RECEIVELEN);
	if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)AdcDma_Buf, ADC_DMA_SIZE) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
}

void Scan_ONOFF(void)
{
	static uint8_t  BTPower_c;
	GPIO_InitTypeDef GPIO_InitStruct;
	if (BTPower() != BTPower_c)
	{
		BTPower_c = BTPower();
		if (BTPower())
		{
			PlayMode = PLAY_BT;
			GPIO_InitStruct.Pin = GPIO_PIN_15;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
		else
		{
			PlayMode = PLAY_OFF;
			FireMode = FIRE_OFF;
			GPIO_InitStruct.Pin = GPIO_PIN_15;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		}
	}
	if (FireMode == FIRE_OFF)
	{
		POWER_LED(0);
	}
	else
	{
		POWER_LED(1);
	}
}


void app_main(void)
{
	PowerON_Reset();
	while (1)
	{
		if (AppTick1ms)
		{
			AppTick1ms = 0;
			BlueMode_Handle();
		}
		if (AppTick0)
		{
			AppTick0 = 0;
			KeyScan();
			KeyComMsg();
			Scan_ONOFF();
		}
		if (AppTick1)
		{
			AppTick1 = 0;
			Audio_Average();
		}
		if (AppTick2)
		{
			AppTick2 = 0;
		}
		if (AppTick3)
		{
			AppTick3 = 0;
			send_index = 0;
			send_enable = 1;
			FireMode_Handle();
			//GPIOA->BSRR = GPIO_PIN_7;   			 
			//GPIOA->BRR  = GPIO_PIN_7;//40us			
		}
	}
}


