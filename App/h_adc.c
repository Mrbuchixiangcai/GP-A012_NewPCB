//Í·ÎÄ¼þheader file//
#include "app_main.h"
uint8_t   Adc_Dma_Irq_f;
uint16_t  AdcDma_Buf[ADC_DMA_SIZE];
uint16_t  AdcDma_Data[ADC_DATA_SIZE];		
uint16_t  Audio_Mean[MEAN_SIZE];
uint16_t  AdcAudio_Data[AUDIO_SIZE];
void ADC_GetBuffer(void) 
{
 static uint8_t  dac_i; 	
 if((Adc_Dma_Irq_f))
 {
	Adc_Dma_Irq_f=0;
	if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK)
	{
	 _Error_Handler(__FILE__, __LINE__);
	}
	AdcDma_Data[dac_i]=AdcDma_Buf[0];
	if(++dac_i>=ADC_DATA_SIZE)
	 dac_i=0;	
	if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)AdcDma_Buf,ADC_DMA_SIZE) != HAL_OK)
	{
	 _Error_Handler(__FILE__, __LINE__);
	}
 }
}
void Audio_Average(void) 
{
 uint8_t   i,j;
 uint32_t  sum=0;	
 uint16_t  AdcDma_Temp[ADC_DATA_SIZE];		
 static uint16_t Audio_Mean_Tab[10][MEAN_SIZE]; 	
 for(i=0;i<ADC_DATA_SIZE;i++)
  AdcDma_Temp[i]=AdcDma_Data[i];
 for(j=0;j<10;j++)
 {	
  sum=0;
  for(i=0;i<10;i++)
   sum += AdcDma_Temp[(j*10)+i];
  sum=sum/10;  	 
  AdcAudio_Data[j]=sum;  	 
  for(i=0;i<(MEAN_SIZE-1);i++)	 
   Audio_Mean_Tab[j][i]=Audio_Mean_Tab[j][i+1];	 
  Audio_Mean_Tab[j][MEAN_SIZE-1]=sum;  
  for(i=0;i<MEAN_SIZE;i++)
   sum += Audio_Mean_Tab[j][i];
  Audio_Mean[j]=(sum/MEAN_SIZE); 
 }
 for(j=0;j<MEAN_SIZE;j++)
 {
  if(Audio_Mean[j]>256)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/11;  
  else if(Audio_Mean[j]>224)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/10;  
  else if(Audio_Mean[j]>192)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/9; 	 
  else if(Audio_Mean[j]>160)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/8;
  else if(Audio_Mean[j]>128)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/7;  
  else if(Audio_Mean[j]>96)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/6;  
  else if(Audio_Mean[j]>64)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/5;  
  else if(Audio_Mean[j]>48)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/4;  
  else if(Audio_Mean[j]>40)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/3;    
  else if(Audio_Mean[j]>32)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/2;  
  else if(Audio_Mean[i]>16)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]/1;     
  else if(Audio_Mean[j]>8)	 
   AdcAudio_Data[j]=AdcAudio_Data[j]*2;    
  else if(Audio_Mean[j]>3)	  
   AdcAudio_Data[j]=AdcAudio_Data[j]*4;    
  else 
   AdcAudio_Data[j]=0;    
 }		
}

//void Audio_Average(void) 
//{
// uint8_t   i,j;
// uint32_t  sum=0;	
// uint16_t  AdcDma_Temp[ADC_DATA_SIZE];		
// static uint16_t Audio_Mean_Tab[10][MEAN_SIZE]; 	
// for(i=0;i<ADC_DATA_SIZE;i++)
//  AdcDma_Temp[i]=AdcDma_Data[i];
// for(j=0;j<10;j++)
// {	
//  sum=0;
//  for(i=0;i<10;i++)
//   sum += AdcDma_Temp[(j*10)+i];
//  sum=sum/10;  	 
//  AdcAudio_Data[j]=sum;  	 
//  for(i=0;i<(MEAN_SIZE-1);i++)	 
//   Audio_Mean_Tab[j][i]=Audio_Mean_Tab[j][i+1];	 
//  Audio_Mean_Tab[j][MEAN_SIZE-1]=sum;  
//  for(i=0;i<MEAN_SIZE;i++)
//   sum += Audio_Mean_Tab[j][i];
//  Audio_Mean[j]=(sum/MEAN_SIZE); 
// }
// for(j=0;j<MEAN_SIZE;j++)
// {
//  if(Audio_Mean[j]>256)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/14;  
//  else if(Audio_Mean[j]>224)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/13;  
//  else if(Audio_Mean[j]>192)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/12; 	 
//  if(Audio_Mean[j]>160)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/11;
//  else if(Audio_Mean[j]>128)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/10;  
//  else if(Audio_Mean[j]>96)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/9;  
//  else if(Audio_Mean[j]>64)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/8;  
//  else if(Audio_Mean[j]>48)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/7;  
//  else if(Audio_Mean[j]>40)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/6;    
//  else if(Audio_Mean[j]>32)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/5;  
//  else if(Audio_Mean[i]>16)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/4;     
//  else if(Audio_Mean[j]>8)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/3;    
//  else if(Audio_Mean[j]>3)	  
//   AdcAudio_Data[j]=AdcAudio_Data[j]/2;    
//  else 
//   AdcAudio_Data[j]=0;    
// }		
//}
//void Audio_Average(void) 
//{
// uint8_t   i,j;
// uint32_t  sum=0;	
// uint16_t  AdcDma_Temp[ADC_DATA_SIZE];		
// static uint16_t Audio_Mean_Tab[10][MEAN_SIZE]; 	
// for(i=0;i<ADC_DATA_SIZE;i++)
//  AdcDma_Temp[i]=AdcDma_Data[i];
// for(j=0;j<10;j++)
// {	
//  sum=0;
//  for(i=0;i<10;i++)
//   sum += AdcDma_Temp[(j*10)+i];
//  sum=sum/10;  	 
//  AdcAudio_Data[j]=sum;  	 
//  for(i=0;i<(MEAN_SIZE-1);i++)	 
//   Audio_Mean_Tab[j][i]=Audio_Mean_Tab[j][i+1];	 
//  Audio_Mean_Tab[j][MEAN_SIZE-1]=sum;  
//  for(i=0;i<MEAN_SIZE;i++)
//   sum += Audio_Mean_Tab[j][i];
//  Audio_Mean[j]=(sum/MEAN_SIZE); 
// }
// for(j=0;j<MEAN_SIZE;j++)
// {
//  if(Audio_Mean[j]>256)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/13;  
//  else if(Audio_Mean[j]>224)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/12;  
//  else if(Audio_Mean[j]>192)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/11; 	 
//  if(Audio_Mean[j]>160)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/10;
//  else if(Audio_Mean[j]>128)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/9;  
//  else if(Audio_Mean[j]>96)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/8;  
//  else if(Audio_Mean[j]>64)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/7;  
//  else if(Audio_Mean[j]>48)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/6;  
//  else if(Audio_Mean[j]>40)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/5;    
//  else if(Audio_Mean[j]>32)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/4;  
//  else if(Audio_Mean[i]>16)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/3;     
//  else if(Audio_Mean[j]>8)	 
//   AdcAudio_Data[j]=AdcAudio_Data[j]/2;    
//  else if(Audio_Mean[j]>3)	  
//   AdcAudio_Data[j]=AdcAudio_Data[j]/1;    
//  else 
//   AdcAudio_Data[j]=0;    
// }		
//}


