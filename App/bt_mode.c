#include "app_main.h"

uint8_t  enUart_Send =0;
uint8_t  mPtr_Receive=0;
uint8_t  sPtr_Receive=0;
uint8_t  Uart1_RX_Timeout;
uint8_t  BT_ReceiveBuffer[RECEIVELEN];
uint8_t  Uart1_ReceiveBuffer[RECEIVELEN];
uint8_t  Uart1_TransmitBuffer[RECEIVELEN];

uint8_t page;		
HAL_StatusTypeDef User_UART_Receive_IT(uint8_t rx_data)
{
  Uart1_ReceiveBuffer[mPtr_Receive]=rx_data;
  if(++mPtr_Receive>=(RECEIVELEN))
   mPtr_Receive=0;
  Uart1_RX_Timeout=10;
  return HAL_OK;
		 
//  if(rx_data>=0x20)
//  {
//   page=rx_data-0x20;
//   Wind_index_max=page+1;  
//   mPtr_Receive=0;    
//  }
//  else
//  {
////   Small_Fire_tab_array1[page][mPtr_Receive/5][mPtr_Receive%5]=rx_data; 
//   mPtr_Receive++;  
//  }		
//  return HAL_OK;	
}
void Usart1SendData(uint8_t *pdata) 
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

void BlueMode_Receive(void)
{
 static uint8_t ptrReceive=0;	
 while(mPtr_Receive!=sPtr_Receive)
 {
  Uart1_RX_Timeout=10;
  BT_ReceiveBuffer[ptrReceive++]=Uart1_ReceiveBuffer[sPtr_Receive];
  Uart1_ReceiveBuffer[sPtr_Receive]=0x00;
  if(++sPtr_Receive>=(RECEIVELEN))
   sPtr_Receive=0;
 }	
 if(Uart1_RX_Timeout != 0)
 {
  if(--Uart1_RX_Timeout==0)
  {
   if((BT_ReceiveBuffer[0]=='B')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&(BT_ReceiveBuffer[3]=='5'))
   {//按键传过来B005x //enUart_Send=0;
	if(BT_ReceiveBuffer[4]=='0')
	{
	 FireMode=FIRE_OFF;
	 if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))==1)
	  PlayMode=PLAY_BT;
	 else
	  PlayMode=PLAY_OFF;
	}
	else if(BT_ReceiveBuffer[4]=='1')
	 FireMode=FIRE_SMALL;
	else if(BT_ReceiveBuffer[4]=='2')
	 FireMode=FIRE_MIDDLE;
	else if(BT_ReceiveBuffer[4]=='3')
	 FireMode=FIRE_BIG;
	else if(BT_ReceiveBuffer[4]=='4')
	 FireMode=FIRE_WIND;
	else if(BT_ReceiveBuffer[4]=='5')
	 FireMode=FIRE_MUSIC;
	else if(BT_ReceiveBuffer[4]=='6')
	 FireMode=FIRE_LEVEL;
	return;
   }
   if ((BT_ReceiveBuffer[0] == 'I') && (BT_ReceiveBuffer[1] == 'I'))
   {
	PlayMode=PLAY_BT;
   }
   else if ((BT_ReceiveBuffer[0] == 'I') && (BT_ReceiveBuffer[1] == 'A'))
   {
	PlayMode=PLAY_BT;
   }
   else if ((BT_ReceiveBuffer[0] == 'O') && (BT_ReceiveBuffer[1] == 'F'))
   {
	PlayMode=PLAY_OFF;
   }
   else if ((BT_ReceiveBuffer[0] == 'O') && (BT_ReceiveBuffer[1] == 'N'))
   {
	PlayMode=PLAY_BT;
   }
   ptrReceive=0;
   memset(BT_ReceiveBuffer,0,sizeof(BT_ReceiveBuffer));
  }
 }
 else ptrReceive=0;
   
}
void BlueMode_Handle(void)
{
	BlueMode_Receive();
}	






