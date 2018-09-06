//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//
#define  ADCKEY_NUM   1

//���Ͷ���byte definition//


//��������variable definition//
uint8_t   gbKeyPress;     //��������
uint8_t   gbKeyNone;      //û�а�������
uint8_t   KeyValue;       //����ֵ
uint8_t   cntKeyLong;     //��������ʱ������������ڳ�����������
uint16_t  AdcValue;       //����ɼ���ADֵ
uint8_t   KeyEvent;       //�����¼�
uint8_t   cntKeyLoop;     //��������ѭ�����̰����������������İ���ʱ��
uint8_t   KeyCurValueBK;  //��ǰ����ֵ����
uint8_t   keyNum;
uint8_t   volValueData;		  //�ɼ����ĳ�����ѹֵ

static    uint8_t   KeyCurValue; //������ѹ��ǰֵ��current��ǰ��
static    uint8_t   KeyLastValue;//������ѹ��һ�ε�ֵ

const uint16_t ADKEY_TAB1[ADCKEY_NUM]=  //����������ѹֵ���������ֵ
{
	0x0000,      //T_LIGHT  //����ֻ�ж̰�ģʽ�л�
};
const uint16_t ADKEY_TAB2[ADCKEY_NUM]=  //����������ѹֵ���������ֵ
{
	0x0000+0x50, //T_LIGHT  //����ֻ�ж̰�ģʽ�л�
};

uint8_t SPASongs_Num_Table[4][6]= 
{
	"B0050\n",
	"B0051\n",
	"B0052\n",
	"B0053\n",	
//	"A005+A00\r\n",
//	"B005+K01\r\n",
//	"B005+K02\r\n",
//	"B005+K03\r\n",
};

//��־λ����flags definetion//


//��������function definetion//
//��ȡ������ѹ����Ӧ��ͬ�������з���ֵ
uint8_t GetKeyValue(void)
{
//	uint8_t  i;
	uint8_t  KeyNum=0;
//	AdcValue=HAL_ADC_GetValue(&hadc);//PA0��ȡ��ǰ����IO pin��ѹֵ,��һ�λ�ȡʱ���ܲ��ԣ�ת��ʱ�䲻��
//	if(AdcValue<0x00A0)//�ɼ��������ⰴ����ѹֵҪС��0x00A0
//	{
////		cntIdle=0;
//		for(i=0;i<ADCKEY_NUM;i++)
//		{
//			if((AdcValue>=ADKEY_TAB1[i]) && (AdcValue<=ADKEY_TAB2[i]))//�жϲɼ����İ�����ѹֵΪ��һ������
//			{
//				KeyNum=i+1;//ȷ��Ϊĳ����������Ϊi��ʼ��Ϊ0�����Լ�1
//				break;
//			}
//		}
//	}
//	HAL_ADC_Start(&hadc);//��ȡADֵ
	if(!KEY_LIGHT())//�ƹⰴ��
		KeyNum=T_LIGHT;
//	if((!KEY_LIGHT()) && (BT_POWER()))
//		KeyNum=T_LIGHT;
//	else if(BT_POWER())
//		KeyNum=T_BT_POWER;
	return KeyNum;//���ذ���
}

//������ʱ���յ���GetKeyValue()�ķ���ֵ  һ��̶���������
void KeyEventPorc(uint8_t KeyTmp)
{
	gbKeyPress=0;
	if(KeyCurValue != KeyTmp)//���if�����ȥ�����ᱻִ�����Σ������ν���ʱֱ������
	{//KeyTmpΪ��ʱֵ
		if(KeyCurValueBK != KeyTmp)
			KeyCurValueBK=KeyTmp;
		else //�ڶ��ν���ʱִ����һ��
			KeyCurValue=KeyTmp;
		return;
	}
	if(KeyCurValue == KeyLastValue)
	{
		if((KeyLastValue==0) || (cntKeyLoop==0))
			return;
		if(--cntKeyLoop==0)//����ڵڶ��ν�KeyEventPorc()��������һ�ν���if(KeyCurValue==KeyLastValue)��֮ǰ��ʱ�����渳ֵΪ5
		{//cntKeyLoopΪ5����50msʱ��
			KeyValue=KeyLastValue;//����֮���ȷ���İ�����ֵ��KeyValue
			if(gbKeyNone==0)
				gbKeyPress=1;
			switch(KeyEvent)
			{
				case 0:
					KeyEvent=1;
					KeyValue |= K_D;
					cntKeyLoop=cKEY_HOLD;
					break;
				case 1:
					KeyEvent=2;
					KeyValue |= K_H;
					cntKeyLoop=cKEY_RATE_VOL;
					break;
				case 2:
				case 3:
					KeyEvent=3;
					KeyValue |= K_R;
					cntKeyLoop=cKEY_RATE_VOL;
					if(cntKeyLong<250)
						cntKeyLong++;
					break;
			}
		}
	}
	else
	{
		if(KeyLastValue)
		{
			KeyValue=KeyLastValue;
			if(gbKeyNone==0)
				gbKeyPress=1;
			switch(KeyEvent)
			{
				case 1:KeyValue |= K_U; break;
				case 2:KeyValue |= K_LU;break;
				case 3:KeyValue |= K_LU;break;
			}
			KeyEvent=0;
		}
		else
		{
			gbKeyNone=0;
			cntKeyLong=0;
		}
		cntKeyLoop=cKEY_CLICK;
		KeyLastValue=KeyCurValue;
	}
}

//������������
void KeyScan(void)
{
	KeyEventPorc(GetKeyValue());
	
}

//��������
void KeyComMsg(void)
{
	static uint16_t  cntUart_Send=0;
	if(gbKeyPress)
	{
		if(PlayMode==PLAY_OFF)
			PlayMode=PLAY_ON;
		switch(KeyValue)
		{
//			case KU(T_BT_POWER):
//			{}
//			case KLU(T_BT_POWER):
//			{
//				if(cntKeyLong>=10)
//					break;
//				PlayMode=PLAY_BT;
//				break;
//			}
			case KU(T_LIGHT): 
			{
				if(PlayMode==PLAY_BT)
				{
					
					if(FireSize1==MODE0_OFF_FIRE)
					{	
						FireSize1=MODE1_SMALL_FIRE1;
						keyNum=1;
					}
					else if(FireSize1==MODE1_SMALL_FIRE1)
					{	
						FireSize1=MODE3_BIG_FIRE1;
						keyNum=2;
					}
					else if(FireSize1==MODE3_BIG_FIRE1)
					{	
						FireSize1=MODE4_FLASHING;
						keyNum=3;
					}
					else //if(keyNum==3)
					{	
						FireSize1=MODE0_OFF_FIRE;
						if(keyBT==1)
							PlayMode=PLAY_BT;
						else
							PlayMode=PLAY_OFF;
						keyNum=0;
					}
				}
				else if(PlayMode==PLAY_ON)//�����ػ������lihgt��ֻ��С��͹ر��������
				{
					//PlayMode=PLAY_ON;
					if(FireSize1==MODE0_OFF_FIRE)
					{	
						FireSize1=MODE1_SMALL_FIRE1;
						keyNum=1;
						
					}
					else
					{	
						FireSize1=MODE0_OFF_FIRE;
						PlayMode=PLAY_OFF;
						keyNum=0;
					}
				}
				enUart_Send=1;
				if(cntUart_Send==600)
				{
					enUart_Send=0;	
					cntUart_Send=0;	
					Usart1SendData_DMA(&SPASongs_Num_Table[FireSize1][0]);
				}					
				break;
			}
			case KLU(T_LIGHT):
			{
				if (cntKeyLong >= 50) 
					break;
				if(brightness1==1)
					brightness1=3;
				else
					brightness1=1;
				break;
			}
		}
	}
	if(enUart_Send)
	{	
		if(++cntUart_Send>600)
		{	 
			enUart_Send=0;  
			cntUart_Send=0;	  
			Usart1SendData_DMA(&SPASongs_Num_Table[FireSize1][0]);
		}	  
	}
	else if(cntUart_Send<600)
		cntUart_Send++;	 
}






























