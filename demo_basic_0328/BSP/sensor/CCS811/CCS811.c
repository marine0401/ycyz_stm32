#include "CCS811.h"

#define INT_Pin GPIO_PIN_6
#define INT_GPIO_Port GPIOC
#define RST_Pin GPIO_PIN_0
#define RST_GPIO_Port GPIOC
#define nWAKE_Pin GPIO_PIN_4
#define nWAKE_GPIO_Port GPIOA

u8 BUF[12];
unsigned short eco2=0,tvoc=0;
u8 IID,Boot_Version,App_Version,Status,MeasureMode;
u8 temp=0x5a;

void ccs_gpio_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(nWAKE_GPIO_Port, nWAKE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = nWAKE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(nWAKE_GPIO_Port, &GPIO_InitStruct);

}


void CCS811_Init(void)
{
	ccs_gpio_init();
	HAL_Delay(500);
    HAL_GPIO_WritePin(nWAKE_GPIO_Port,nWAKE_Pin,GPIO_PIN_RESET);
    HAL_Delay(100);
    while(1)
    {
      Single_ReadIIC(CCS811_Add,0x20,&IID,1);
      if(IID == 0x81)
      {
        printf("get ID SUCCESS\r\n");
        break;
      }
      else
      {
        printf("get ID¡­¡­\r\n");
      }
      HAL_Delay(1000);
    }
    HAL_Delay(100);
		Single_ReadIIC(CCS811_Add,0x23,&Boot_Version,2);
		HAL_Delay(10);
		printf("Boot_Version:%d\r\n",Boot_Version);
		HAL_Delay(10);
		Single_ReadIIC(CCS811_Add,0x24,&App_Version,2);
		HAL_Delay(10);
		printf("App_Version:%d\r\n",App_Version);
		HAL_Delay(10);
		Single_ReadIIC(CCS811_Add,0x00,&Status,1);
		HAL_Delay(10);
		printf("Status:%x\r\n",Status);
		HAL_Delay(10);
		if(Status & 0x10)
		{
			while(!(Status & 0x80))
			{
				Single_WriteIIC_byte(CCS811_Add,0xF3,0xF0);
				HAL_Delay(20);
				printf("transition the CCS811 state from to app mode...\r\n");
				Single_MWriteIIC_byte(CCS811_Add,0xF4,&temp,0);
				HAL_Delay(100);
				Single_ReadIIC(CCS811_Add,0x00,&Status,1);
				HAL_Delay(100);
			}
				printf("CCS811 in app mode...\r\n");
		}
		HAL_Delay(100);
		Single_ReadIIC(CCS811_Add,0x01,&MeasureMode,1);
		HAL_Delay(100);
		printf("MeasureMode:%d\r\n",MeasureMode);
		
		MeasureMode &= 0x70;
		while(MeasureMode != DRIVE_MODE_1SEC)
		{
			Single_WriteIIC_byte(CCS811_Add,0x01,DRIVE_MODE_1SEC);
			HAL_Delay(100);
			Single_ReadIIC(CCS811_Add,0x01,&MeasureMode,1);
			HAL_Delay(100);
			MeasureMode &= 0x70;
			printf("try to set measure mode...\r\n");
			HAL_Delay(100);
		}
		printf("set measure mode success !\r\n");
		HAL_Delay(100);
    HAL_GPIO_WritePin(nWAKE_GPIO_Port,nWAKE_Pin,GPIO_PIN_SET);
		HAL_Delay(100);

}

void CCS811GetData()
{
	HAL_GPIO_WritePin(nWAKE_GPIO_Port,nWAKE_Pin,GPIO_PIN_RESET);
  HAL_Delay(100);
	Single_ReadIIC(CCS811_Add,0x02,BUF,8);
	HAL_Delay(100);
	Single_ReadIIC(CCS811_Add,0x20,&IID,1);
	HAL_Delay(100);
	HAL_GPIO_WritePin(nWAKE_GPIO_Port,nWAKE_Pin,GPIO_PIN_SET);
	HAL_Delay(100);
	eco2 = (unsigned short)BUF[0]*256 + BUF[1];
	tvoc = (unsigned short)BUF[2]*256 + BUF[3];
}
