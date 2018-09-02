//ͷ�ļ�header file//
#include "app_main.h"
#include "IO_IIC.h"

void Delay_1us(u8 t_data)
{
	for(;t_data>0;t_data--);
	for(;t_data>0;t_data--);
	for(;t_data>0;t_data--);
	for(;t_data>0;t_data--);	
}

void IIC_Init1(void)  
{
	SDA5_OUT(); __NOP(); __NOP(); __NOP(); __NOP();
	SDA6_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	SDA7_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	SDA8_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	SDA9_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	SDA10_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	SDA11_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	SDA12_OUT();__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA5(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA6(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA7(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA8(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA9(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA10(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA11(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA12(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SCL(1);__NOP(); __NOP(); __NOP(); __NOP();
}

void IIC_Start1(void) 
{
//	IIC_SDA5(1);
//	IIC_SDA6(1);
//	IIC_SDA7(1);
//	IIC_SCL(1);
//	Delay_1us(0);
	IIC_SDA5(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA6(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA7(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA8(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA9(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA10(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA11(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA12(0);__NOP(); __NOP(); __NOP(); __NOP();
	Delay_1us(0);
	IIC_SCL(0);__NOP(); __NOP(); __NOP(); __NOP();
}
void IIC_Stop1(void) 
{
	IIC_SDA5(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA6(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA7(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA8(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA9(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA10(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA11(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA12(0);__NOP(); __NOP(); __NOP(); __NOP();
	Delay_1us(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SCL(1);__NOP(); __NOP(); __NOP(); __NOP();
	Delay_1us(0);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA5(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA6(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA7(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA8(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA9(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA10(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA11(1);__NOP(); __NOP(); __NOP(); __NOP();
	IIC_SDA12(1);__NOP(); __NOP(); __NOP(); __NOP();
}
u8 IIC_Wait_Ack(void)
{
	IIC_SCL(1);__NOP(); __NOP(); __NOP(); __NOP();
	Delay_1us(0);__NOP(); __NOP(); __NOP(); __NOP(); 
	IIC_SCL(0);__NOP(); __NOP(); __NOP(); __NOP();
	return 0;
}


void IIC_Send_Byte1(u8 txd)//ר��д�Ĵ�����ַ�ķ���IIC����
{
	for(uint8_t t=0;t<8;t++)
	{
		if(txd & 0x80){IIC_SDA5(1);}
		else{IIC_SDA5(0);}
		if(txd & 0x80){IIC_SDA6(1);}
		else{IIC_SDA6(0);}
		if(txd & 0x80){IIC_SDA7(1);}
		else{IIC_SDA7(0);}
		if(txd & 0x80){IIC_SDA8(1);}
		else{IIC_SDA8(0);}
		if(txd & 0x80){IIC_SDA8(1);}
		else{IIC_SDA9(0);}
		if(txd & 0x80){IIC_SDA10(1);}
		else{IIC_SDA10(0);}
		if(txd & 0x80){IIC_SDA11(1);}
		else{IIC_SDA11(0);}
		if(txd & 0x80){IIC_SDA12(1);}
		else{IIC_SDA12(0);}
		Delay_1us(0);
		IIC_SCL(1);
		Delay_1us(0);
		txd<<=1;
		IIC_SCL(0);
	}
}

void IIC_Send_Byte_Mix(u8 p)
{
	for(uint8_t t=0;t<8;t++)
	{
		if(SN3236_Pwm1_1[p-1] & 0x80)
    	{IIC_SDA5(1);}
		else {IIC_SDA5(0);}
		if(SN3236_Pwm1_2[p-1] & 0x80)
     	{IIC_SDA6(1);}
		else {IIC_SDA6(0);}
		if(SN3236_Pwm2_1[p-1] & 0x80)
     	{IIC_SDA7(1);}
		else {IIC_SDA7(0);}
		if(SN3236_Pwm2_2[p-1] & 0x80)
    	{IIC_SDA8(1);}
		else {IIC_SDA8(0);}
		if(SN3236_Pwm3_1[p-1] & 0x80)
     	{IIC_SDA9(1);}
		else {IIC_SDA9(0);}
		if(SN3236_Pwm3_2[p-1] & 0x80)
     	{IIC_SDA10(1);}
		else {IIC_SDA10(0);}
		if(SN3236_Pwm4_1[p-1] & 0x80)
    	{IIC_SDA11(1);}
		else {IIC_SDA11(0);}
		if(SN3236_Pwm4_2[p-1] & 0x80)
     	{IIC_SDA12(1);}
		else {IIC_SDA12(0);}
		Delay_1us(0);__NOP(); __NOP(); __NOP(); __NOP();
		IIC_SCL(1);__NOP(); __NOP(); __NOP(); __NOP();
		SN3236_Pwm1_1[p-1] <<= 1;
		SN3236_Pwm1_2[p-1] <<= 1;
		SN3236_Pwm2_1[p-1] <<= 1;
		SN3236_Pwm2_2[p-1] <<= 1;
		SN3236_Pwm3_1[p-1] <<= 1;
		SN3236_Pwm3_2[p-1] <<= 1;
		SN3236_Pwm4_1[p-1] <<= 1;
		SN3236_Pwm4_2[p-1] <<= 1;
		IIC_SCL(0);__NOP(); __NOP(); __NOP(); __NOP();
	}
}




























