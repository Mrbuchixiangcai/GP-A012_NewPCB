#ifndef  __APP_MAIN_H__
#define  __APP_MAIN_H__

//ͷ�ļ�header file//
#include "main.h"
#include "stm32f0xx_hal.h"
#include <string.h>
//#include "dma.h"
//#include "usart.h"
//#include "gpio.h"
#include "h_adc.h"
#include "bt_mode.h"
#include "rgb.h"
#include "user_uart_dma.h"
#include "IO_IIC.h"
#include "SN3236.h"
#include "Key.h"
#include "rgb_flashing.h"

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
//�궨��macro definition//


//���Ͷ���byte definition//
typedef enum
{
	MODE0_OFF_FIRE   =0,
	MODE1_SMALL_FIRE1  ,
	MODE3_BIG_FIRE1    ,
	MODE4_FLASHING     ,//����������
}FIRE_SIZE;

typedef enum
{
	PLAY_OFF =0,
	PLAY_ON	 =1,//������
	PLAY_BT  =2,//������
}PLAY_MODE;

//��������variable definition//


//��־λ����flags definetion//


//��������function definetion//


//�ⲿ����_�궨��macro definition//


//�ⲿ����_���Ͷ���byte definition//
extern PLAY_MODE  PlayMode; //�ػ�������������&��������
extern FIRE_SIZE  FireSize1;//����Ĵ�С
extern FIRE_SIZE  FireSize1_bk;

//�ⲿ����_��������variable definition//
extern uint16_t  cntIdle;
extern uint8_t   cntAppTick;
extern uint8_t   Uart1_RX_Timeout;
extern uint8_t   brightness1;
extern uint8_t   fireSpeed;
extern uint8_t   electricityBrightness;
extern uint8_t   PWMBrightness;
extern uint8_t   keyBT;
extern uint8_t   enUart_Send;
//
//�ⲿ����_��־λ����flags definetion//
extern uint8_t   AppTick1ms;
extern uint8_t   AppTick0;
extern uint8_t   AppTick1;
extern uint8_t   AppTick2;
extern uint8_t   AppTick3;
extern uint8_t   AppTick4;
extern uint8_t   AppTick5;
extern uint8_t   bt_fire;


//�ⲿ����_��������function definetion//
extern void app_main(void);
extern void SystemClock_Config(void);

extern void ADC_GetBuffer(void);
#endif







