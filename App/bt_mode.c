#include "app_main.h"

//宏定义macro definition//


//类型定义byte definition//


//变量定义variable definition//
uint8_t  BT_Work;
uint8_t  Uart1_ReceiveBuffer[RECEIVELEN];
uint8_t  Uart1_TransmitBuffer[RECEIVELEN];
uint8_t  BT_ReceiveBuffer[RECEIVELEN];
uint8_t  BT_TransmitBuffer[RECEIVELEN];
uint8_t  Uart1_RX_Timeout;
uint8_t   enUart_Send=0;
//标志位定义flags definetion//

void Usart1SendData_DMA(uint8_t *pdata) 
{
  uint8_t size = 0;
  HAL_UART_DMAStop(&huart1);	
  while ((*pdata !='\n')&&(*pdata !='\0'))  
  {           
    Uart1_TransmitBuffer[size] = *pdata;
    size++;
    pdata++;
  }
  HAL_UART_Transmit_DMA(&huart1, Uart1_TransmitBuffer, size);
}
//函数定义function definetion//
void hex_to_char(uint8_t *p,uint8_t indata)
{
	uint8_t tmp;
	tmp=indata>>4;
	if(tmp>=0x0A)
	 *p=((tmp-0x0A)+'A'); 
	else
	 *p=(tmp+'0');
	p++;
	tmp=indata&0x0F;
	if(tmp>=0x0A)
		*p=((tmp-0x0A)+'A'); 
	else
		*p=(tmp+'0');
}
char char_to_bcd(char indata1,char indata2)
{
	if(indata1>='A')
		indata1=((indata1-'A')+0x0A);
	else
		indata1=(indata1-'0');
	if(indata2>='A')
		indata2=((indata2-'A')+0x0A);
	else
		indata2=(indata2-'0');
	return (indata1*10+indata2);
}

///start void BlueMode_Receive(void)
///....................(功能说明)
///....................
void BT_Send_Command(uint8_t cmd)
{
//	switch(cmd)
//	{
//		
//	}
}	
///end void BlueMode_Receive(void)

///start void BlueMode_Receive(void)
///....................(功能说明)
///....................
void BlueMode_Receive(void)
{
	uint8_t Uart1_RX_LEN;
	if(Uart1_RX_Timeout != 0)
	{//在中断里面置为3，并且前提是有空闲中断发生，空闲中断发生的原因是接收数据结束，
	 //IT从busy进入空闲，出发了IDLE(空闲中断))	
		if(--Uart1_RX_Timeout==0)
		{
    		HAL_UART_DMAStop(&huart1);
			Uart1_RX_LEN=RECEIVELEN - huart1.hdmarx->Instance->CNDTR;
			memset(BT_ReceiveBuffer,0,sizeof(BT_ReceiveBuffer));
			for(uint8_t i=0;i<Uart1_RX_LEN;i++)
				BT_ReceiveBuffer[i]=Uart1_ReceiveBuffer[i];
			memset(Uart1_ReceiveBuffer,0,sizeof(Uart1_ReceiveBuffer));
	        if (HAL_UART_Receive_DMA(&huart1,(uint8_t *)Uart1_ReceiveBuffer, RECEIVELEN) != HAL_OK)
	        {
		     _Error_Handler(__FILE__, __LINE__);
	        }
			if((BT_ReceiveBuffer[0]=='B')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&(BT_ReceiveBuffer[3]=='5'))
			{//按键传过来B005x
				//enUart_Send=0;
				if(BT_ReceiveBuffer[4]=='0')
				{
					FireSize1=MODE0_OFF_FIRE;
					if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))==1)
						PlayMode=PLAY_BT;
					else
						PlayMode=PLAY_OFF;
				}
				else if(BT_ReceiveBuffer[4]=='1')
					FireSize1=MODE1_SMALL_FIRE1;
				else if(BT_ReceiveBuffer[4]=='2')
					FireSize1=MODE3_BIG_FIRE1;
				else if(BT_ReceiveBuffer[4]=='3')
					FireSize1=MODE4_FLASHING;
				return;
			}
		}
	}
}
///end void BlueMode_Receive(void)

///start BlueMode_Handle(void)
///....................(功能说明)
///....................
void BlueMode_Handle(void)
{
	if(BT_Work==0)
	{
//		MX_USART1_UART_Init();
	}
	BT_Work=1;
	BlueMode_Receive();
}	
///end BlueMode_Handle(void)





