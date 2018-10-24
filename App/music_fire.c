//ͷ�ļ�header file//
#include "app_main.h"
uint16_t mMusic_Map_Tab[6][10];
uint16_t sMusic_Map_Tab[6][10];
uint16_t cntMusic_none;		
void MusicMode_AudioDeal(void)
{
 //uint8_t i,j;	
 uint32_t _sum;		
 uint16_t x,tmp_data;	
 static uint8_t  y[10];	
 for(_sum=0,x=0;x<10;x++)
 {
  _sum+=AdcAudio_Data[x];
 }
 _sum=_sum/10; 
 if(_sum<=5) 
 {
  if(cntMusic_none<100)  
   cntMusic_none++;
 }
 else if(_sum>=40) 
 {
  cntMusic_none=0;	
 } 	
 for(x=0;x<10;x++) 	
 {	
  tmp_data=AdcAudio_Data[x];	
  if(tmp_data>mMusic_Map_Tab[y[x]][x])
  {
	sMusic_Map_Tab[y[x]][x]=tmp_data/3;///2;
    if(y[x]>0)
     y[x]--;
    mMusic_Map_Tab[y[x]][x]=tmp_data;
  }
  else
  {
	sMusic_Map_Tab[y[x]][x]=0;  
    if(y[x]<5)
     y[x]++;
    mMusic_Map_Tab[y[x]][x]=tmp_data;  
	sMusic_Map_Tab[y[x]][x]=tmp_data;
    if(((y[x]==5)||(y[x]==4))&&(sMusic_Map_Tab[y[x]][x]==0))
	{
	 if(y[x]==4)	
	 sMusic_Map_Tab[y[x]][x]=1;	
	 else
	 sMusic_Map_Tab[y[x]][x]=2; 
    }
  } 	  
 } 
 
// for(x=0;x<10;x++)
// {	
//  for(i=0;i<(6-1);i++)
//  {
//   for(j=0;j<(6-i-1);j++)          
//   {
//    if(sMusic_Map_Tab[j][x]>sMusic_Map_Tab[j+1][x])   
//    {
//     tmp_data=sMusic_Map_Tab[j+1][x];
//     sMusic_Map_Tab[j+1][x]=sMusic_Map_Tab[j][x];
//     sMusic_Map_Tab[j][x]=tmp_data;      
//    }                                
//   }
//  } 
// }   
}
uint8_t  Fire_Data_H_temp[6][10]; 
void Music_Fire_Mode(void)
{
 uint8_t x,j;	
 static uint8_t cntWrite;	
 if(FireMode_c!=FireMode)
 {
  cntWrite=0;
  cntMusic_none=100;	 
  FireMode_c=FireMode;
  for(x=0;x<10;x++)	
  {
   for(j=0;j<6;j++)
   {
	Fire_Data_H[j][x]=0;   
	mMusic_Map_Tab[j][x]=0;    
	sMusic_Map_Tab[j][x]=0;  
	Fire_Data_H_temp[j][x]=0;  
   }
  }	 
 }	 
 MusicMode_AudioDeal();	
 for(x=0;x<10;x++)	
 {
  for(j=0;j<6;j++)
  {
    if(Fire_Data_H_temp[j][x]<sMusic_Map_Tab[j][x])  
     Fire_Data_H_temp[j][x]++;
    if(Fire_Data_H_temp[j][x]>sMusic_Map_Tab[j][x])  
     Fire_Data_H_temp[j][x]--;		
    if(Fire_Data_H_temp[j][x]>=31)	
     Fire_Data_H_temp[j][x]=31;	
  }
 }	
 if(++cntWrite>5)
 {
  cntWrite=0;	 
  for(x=0;x<10;x++)	
  {
   for(j=0;j<6;j++)
   {
    Fire_Data_H[j][x]=Fire_Data_H_temp[j][x];
   }
  }
 }
 if(cntMusic_none>=100) 
 {
  s_Music_Fire_Mode();
  LoadData_to_MC96F_V();	 
 }
 else
 {
  LoadData_to_MC96F_H();	 
 }	 
}

uint8_t const Music_Fire_tab_array[12][12][5] = 
{
{                  
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x02,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x02,  0x00,
  0x00,  0x04,  0x00,  0x00,  0x00,
0x00,  0x08,  0x06,  0x06,  0x00,  
  0x00,  0x0A,  0x07,  0x08,  0x00,
0x00,  0x04,  0x08,  0x08,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x02,  0x02,  0x00,  0x00,
0x00,  0x02,  0x02,  0x02,  0x00,
  0x00,  0x02,  0x03,  0x00,  0x00,
0x00,  0x06,  0x06,  0x04,  0x00,  
  0x00,  0x05,  0x06,  0x06,  0x00,
0x00,  0x07,  0x05,  0x08,  0x00, 
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x02,  0x00,  0x00,
0x00,  0x02,  0x02,  0x02,  0x00,
  0x00,  0x03,  0x02,  0x00,  0x00,
0x00,  0x04,  0x07,  0x05,  0x00,  
  0x00,  0x07,  0x08,  0x07,  0x00,
0x00,  0x04,  0x08,  0x06,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x02,  0x02,  0x02,  0x00,
  0x00,  0x04,  0x02,  0x00,  0x00,
0x00,  0x08,  0x05,  0x08,  0x00,  
  0x00,  0x08,  0x06,  0x06,  0x00,
0x00,  0x09,  0x07,  0x08,  0x00,  
},
{
  0x00,  0x00,  0x02,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x02,  0x00,
0x00,  0x02,  0x02,  0x02,  0x00,
  0x00,  0x02,  0x02,  0x02,  0x00,
0x00,  0x04,  0x06,  0x05,  0x00,  
  0x00,  0x06,  0x07,  0x06,  0x00,
0x00,  0x08,  0x08,  0x08,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x02,  0x04,  0x02,  0x00,
0x00,  0x06,  0x06,  0x05,  0x00,  
  0x00,  0x06,  0x08,  0x06,  0x00,
0x00,  0x09,  0x07,  0x09,  0x00,  
},	
{                  
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x03,  0x00,  0x00,
  0x00,  0x00,  0x04,  0x00,  0x00,
0x00,  0x02,  0x02,  0x00,  0x00,
  0x00,  0x02,  0x06,  0x00,  0x00,
0x00,  0x06,  0x06,  0x06,  0x00,  
  0x00,  0x08,  0x07,  0x08,  0x00,
0x00,  0x04,  0x09,  0x08,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x02,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x04,  0x02,  0x02,  0x00,
0x00,  0x07,  0x04,  0x04,  0x00,  
  0x00,  0x05,  0x08,  0x06,  0x00,
0x00,  0x07,  0x05,  0x08,  0x00, 
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x01,  0x00,  0x00,  0x00,
0x00,  0x02,  0x00,  0x00,  0x00,
  0x00,  0x02,  0x00,  0x00,  0x00,
0x00,  0x02,  0x02,  0x00,  0x00,
  0x00,  0x03,  0x03,  0x00,  0x00,
0x00,  0x04,  0x06,  0x05,  0x00,  
  0x00,  0x07,  0x07,  0x07,  0x00,
0x00,  0x04,  0x08,  0x06,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x01,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x02,  0x00,  0x00,
0x00,  0x02,  0x02,  0x02,  0x00,
  0x00,  0x02,  0x03,  0x00,  0x00,
0x00,  0x08,  0x06,  0x04,  0x00,  
  0x00,  0x06,  0x06,  0x06,  0x00,
0x00,  0x09,  0x07,  0x06,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x02,  0x00,
  0x00,  0x00,  0x02,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x02,  0x03,  0x02,  0x00,
0x00,  0x06,  0x06,  0x04,  0x00,  
  0x00,  0x06,  0x07,  0x06,  0x00,
0x00,  0x08,  0x08,  0x08,  0x00,  
},
{
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x00,  0x00,  0x00,
  0x00,  0x00,  0x00,  0x00,  0x00,
0x00,  0x00,  0x02,  0x00,  0x00,
  0x00,  0x02,  0x02,  0x02,  0x00,
0x00,  0x05,  0x05,  0x05,  0x00,  
  0x00,  0x06,  0x08,  0x06,  0x00,
0x00,  0x09,  0x07,  0x07,  0x00,  
},
};	

/*******************************************************************************************/
/*******************************************************************************************/ 
uint8_t mMusic_Mirror;	 
uint8_t mMusic_speed_cnt;
uint8_t mMusic_index_run;
void s_Music_Fire_Mode(void)
{
 uint8_t i,j;//,k;	
 //static uint8_t flash_f;
 if(++mMusic_speed_cnt>12)
 {		
  mMusic_speed_cnt=0;
  if(++mMusic_index_run>=12)
  {
   mMusic_index_run=0; 
   mMusic_Mirror=~mMusic_Mirror;	  
  }
  for(i=0;i<12;i++)
  {
    for(j=0;j<5;j++)
	{
     Fire_Data_V[i][j]=0;		 
    } 
    for(j=1;j<4;j++)
	{
	 if(mMusic_Mirror)	
      Fire_Data_V[i][j]=Music_Fire_tab_array[mMusic_index_run][i][j]/2;	 
	 else
      Fire_Data_V[i][j]=Music_Fire_tab_array[mMusic_index_run][i][4-j]/2;	 		 
    }   
  }
//  flash_f=~flash_f;
//  if(flash_f)
//  {
//   for(k=0;k<1;k++) 
//   {
//    for(i=0;i<12;i++)
//    {
//     for(j=0;j<5;j++)
//     { 
//      if(Fire_Data_V_sub[i][j])	 
//       Fire_Data_V_sub[i][j]--;   
//     }   
//    } 
//   }  
//  }  
 }

// for(k=0;k<1;k++) 
// {
//  for(i=0;i<12;i++)
//  {
//   for(j=0;j<5;j++)
//   {
//    if(Fire_Data_V[i][j]<Fire_Data_V_sub[i][j])
//     Fire_Data_V[i][j]++;  
//    if(Fire_Data_V[i][j]>Fire_Data_V_sub[i][j])	 
//     Fire_Data_V[i][j]--;   
//   }   
//  } 
// } 
}
