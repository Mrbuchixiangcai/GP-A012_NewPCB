#include "app_main.h"

//�궨��macro definition//


//���Ͷ���byte definition//


//��������variable definition//
uint8_t  BT_Work;
uint8_t  Uart1_ReceiveBuffer[RECEIVELEN];
uint8_t  Uart1_TransmitBuffer[RECEIVELEN];
uint8_t  BT_ReceiveBuffer[RECEIVELEN];
uint8_t  BT_TransmitBuffer[RECEIVELEN];
uint8_t  Uart1_RX_Timeout;
uint8_t   enUart_Send=0;
//��־λ����flags definetion//
uint8_t mPtr_Receive=0;
uint8_t sPtr_Receive=0;
HAL_StatusTypeDef User_UART_Receive_IT(UART_HandleTypeDef *huart)
{
  uint16_t uhMask = huart->Mask;
	Uart1_ReceiveBuffer[mPtr_Receive]=(uint8_t)(huart->Instance->RDR & (uint8_t)uhMask);
	if(++mPtr_Receive>=(RECEIVELEN))
		mPtr_Receive=0;
	Uart1_RX_Timeout=10;
  return HAL_OK;
}
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
  HAL_UART_Transmit_IT(&huart1, Uart1_TransmitBuffer, size);
}
//��������function definetion//
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
///....................(����˵��)
///....................
void BT_Send_Command(uint8_t cmd)
{
}	

uint8_t Uart1_RX_Count=0;
void BlueMode_Receive(void)
{
	 while(mPtr_Receive!=sPtr_Receive)
	 {
	  Uart1_RX_Timeout=10;
	  BT_ReceiveBuffer[Uart1_RX_Count++]=Uart1_ReceiveBuffer[sPtr_Receive];
	  //Uart1_ReceiveBuffer[sPtr_Receive]=0x00;
	  if(++sPtr_Receive>=(RECEIVELEN))
	   sPtr_Receive=0;
     }	
	if(Uart1_RX_Timeout != 0)
	{
		if(--Uart1_RX_Timeout==0)
		{
			if((BT_ReceiveBuffer[0]=='B')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&(BT_ReceiveBuffer[3]=='5'))
			{//����������B005x
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
			Uart1_RX_Count=0;
			//memset(BT_ReceiveBuffer,0,sizeof(BT_ReceiveBuffer));
		}
	}
	else Uart1_RX_Count=0;
   
}
///end void BlueMode_Receive(void)

///start BlueMode_Handle(void)
///....................(����˵��)
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





