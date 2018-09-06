//头文件header file//
#include "app_main.h"

//宏定义macro definition//
#define  ADCKEY_NUM   1

//类型定义byte definition//


//变量定义variable definition//
uint8_t   gbKeyPress;     //按键按下
uint8_t   gbKeyNone;      //没有按键按下
uint8_t   KeyValue;       //按键值
uint8_t   cntKeyLong;     //按键按下时间计数，可用于长按键和其他
uint16_t  AdcValue;       //最初采集的AD值
uint8_t   KeyEvent;       //按键事件
uint8_t   cntKeyLoop;     //计数按键循环，短按，长按，超长按的按下时间
uint8_t   KeyCurValueBK;  //当前按键值备份
uint8_t   keyNum;
uint8_t   volValueData;		  //采集到的初步电压值

static    uint8_t   KeyCurValue; //按键电压当前值，current当前的
static    uint8_t   KeyLastValue;//按键电压上一次的值

const uint16_t ADKEY_TAB1[ADCKEY_NUM]=  //按键正常电压值与允许误差值
{
	0x0000,      //T_LIGHT  //按键只有短按模式切换
};
const uint16_t ADKEY_TAB2[ADCKEY_NUM]=  //按键正常电压值与允许误差值
{
	0x0000+0x50, //T_LIGHT  //按键只有短按模式切换
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

//标志位定义flags definetion//


//函数定义function definetion//
//获取按键电压，对应不同按键，有返回值
uint8_t GetKeyValue(void)
{
//	uint8_t  i;
	uint8_t  KeyNum=0;
//	AdcValue=HAL_ADC_GetValue(&hadc);//PA0获取当前按键IO pin电压值,第一次获取时可能不对，转换时间不够
//	if(AdcValue<0x00A0)//采集到的任意按键电压值要小于0x00A0
//	{
////		cntIdle=0;
//		for(i=0;i<ADCKEY_NUM;i++)
//		{
//			if((AdcValue>=ADKEY_TAB1[i]) && (AdcValue<=ADKEY_TAB2[i]))//判断采集到的按键电压值为哪一个按键
//			{
//				KeyNum=i+1;//确定为某个按键，因为i初始化为0，所以加1
//				break;
//			}
//		}
//	}
//	HAL_ADC_Start(&hadc);//获取AD值
	if(!KEY_LIGHT())//灯光按键
		KeyNum=T_LIGHT;
//	if((!KEY_LIGHT()) && (BT_POWER()))
//		KeyNum=T_LIGHT;
//	else if(BT_POWER())
//		KeyNum=T_BT_POWER;
	return KeyNum;//返回按键
}

//被调用时接收的是GetKeyValue()的返回值  一般固定，不更改
void KeyEventPorc(uint8_t KeyTmp)
{
	gbKeyPress=0;
	if(KeyCurValue != KeyTmp)//这个if语句是去抖，会被执行两次，第三次进来时直接跳过
	{//KeyTmp为临时值
		if(KeyCurValueBK != KeyTmp)
			KeyCurValueBK=KeyTmp;
		else //第二次进来时执行这一条
			KeyCurValue=KeyTmp;
		return;
	}
	if(KeyCurValue == KeyLastValue)
	{
		if((KeyLastValue==0) || (cntKeyLoop==0))
			return;
		if(--cntKeyLoop==0)//这个在第二次进KeyEventPorc()函数（第一次进“if(KeyCurValue==KeyLastValue)”之前）时被下面赋值为5
		{//cntKeyLoop为5就是50ms时间
			KeyValue=KeyLastValue;//防抖之后把确定的按键赋值给KeyValue
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

//被主函数调用
void KeyScan(void)
{
	KeyEventPorc(GetKeyValue());
	
}

//按键处理
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
				else if(PlayMode==PLAY_ON)//蓝牙关机情况打开lihgt，只有小火和关闭两种情况
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






























