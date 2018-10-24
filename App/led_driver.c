//头文件header file//
#include "app_main.h"
uint8_t  step;
uint8_t  Fire_Data_H[6][10]; 
uint8_t  Fire_Data_V[12][5]; 
uint8_t  Fire_Data_V_sub[12][5]; 
uint8_t  PwmDuty[LED_LENGH];//数据数组
/*******************************************************************************************/
/*******************************************************************************************/ 
void delay(uint8_t i)
{
 while(i--){}
}
uint8_t send_index;
uint8_t send_enable;
void MC96F6508A_driver(void )
{	
 if(send_enable)
 {			
  sclk(0);
  sda1(PwmDuty[send_index]&0x01);
  sda2(PwmDuty[send_index]&0x02);
  sda3(PwmDuty[send_index]&0x04);
  sda4(PwmDuty[send_index]&0x08);
  sda5(PwmDuty[send_index]&0x10);	 
  __NOP();__NOP(); 
  sclk(1);
  if(++send_index>=LED_LENGH)
  {send_index=0;send_enable=0;}	 
 }	
}
/*******************************************************************************************/ 
/*******************************************************************************************/ 
const uint8_t MC96F_Map_Addr_V[12][5] =
{                               
    17,   47,   11,   41,    5, 
 35,   59,   29,   53,   23,    
    16,   46,   10,   40,    4, 
 34,   58,   28,   52,   22,	
    15,   45,    9,   39,    3, 
 33,   57,   27,   51,   21,    
    14,   44,    8,   38,    2, 
 32,   56,   26,   50,   20,    
    13,   43,    7,   37,    1, 
 31,   55,   25,   49,   19,    
    12,   42,    6,   36,    0, 
 30,   54,   24,   48,   18,    
};                              
const uint8_t MC96F_Map_Addr_H[6][10] =
{
  35,17,59,47,29,11,53,41,23,5,	
  34,16,58,46,28,10,52,40,22,4,	
  33,15,57,45,27,9 ,51,39,21,3,
  32,14,56,44,26,8 ,50,38,20,2,
  31,13,55,43,25,7 ,49,37,19,1,
  30,12,54,42,24,6 ,48,36,18,0,
};
/*******************************************************************************************/
/*******************************************************************************************/ 
void LoadData_to_MC96F_V(void) 
{
 u8 i,j,addr;
 for(i=0;i<12;i++)
 {
  for(j=0;j<5;j++)
  {
   addr= MC96F_Map_Addr_V[i][j];
   PwmDuty[addr]=Fire_Data_V[i][j];
  }
 }
}
void LoadData_to_MC96F_H(void) 
{
 u8 i,j,addr;
 for(i=0;i<6;i++)
 {
  for(j=0;j<10;j++)
  {
   addr= MC96F_Map_Addr_H[i][j];
   PwmDuty[addr]=Fire_Data_H[i][j];
  }
 }
}
/*******************************************************************************************/
/*******************************************************************************************/ 
void Off_Fire_Mode(void)
{
 u8 i,j;
 for(i=0;i<12;i++)
 {
  for(j=0;j<5;j++)
  {
   Fire_Data_V[i][j]=0;
  }
 }
 LoadData_to_MC96F_V();	 
}

void FireMode_Handle(void)
{	
 if (FireMode == FIRE_SMALL)
 {	 
  h_Small_Fire_Mode();
 }
 else if (FireMode == FIRE_MIDDLE)
 {	 
  h_Middle_Fire_Mode();
 } 
 else if (FireMode == FIRE_BIG)
 {	 
  h_Big_Fire_Mode();
 }
 else if (FireMode == FIRE_WIND)
 {
  h_Wind_Fire_Mode();
 }
 else if (FireMode == FIRE_MUSIC)
 {
  Music_Fire_Mode(); 
 }
 else if (FireMode == FIRE_LEVEL)
 {
  Level_Fire_Mode(); 
 } 
 else 
 {
  Off_Fire_Mode(); 
 }
}
/*******************************************************************************************/
/*******************************************************************************************/ 











