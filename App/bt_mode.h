#ifndef  __BT_MODE_H__
#define  __BT_MODE_H__

//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//


//���Ͷ���byte definition//


//��������variable definition//


//��־λ����flags definetion//


//��������function definetion//


//�ⲿ����_�궨��macro definition//


//�ⲿ����_���Ͷ���byte definition//

#define  RECEIVELEN  30
//�ⲿ����_��������variable definition//
extern uint8_t  Uart1_ReceiveBuffer[RECEIVELEN];
extern uint8_t  Uart1_TransmitBuffer[RECEIVELEN];
extern uint8_t  BT_ReceiveBuffer[RECEIVELEN];
extern uint8_t  BT_TransmitBuffer[RECEIVELEN];

//�ⲿ����_��־λ����flags definetion//

extern void Usart1SendData_DMA(uint8_t *pdata); 
//�ⲿ����_��������function definetion//
extern void BlueMode_Handle(void);



#endif








