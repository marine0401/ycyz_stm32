#include "ph/ph.h"
#include "sensor_config.h"
#include "usart.h"
#include "serial_port.h"
//#ifdef SENSEO_SMOKE_ENABLED

//串口发送或接收完成标志，
ph_msg PHsensor;

//huart1字符串发送函数
void UART1_Sends(char *buf1)		  
{
	uint8_t i=0;
	uint8_t bufLen = 0;
	while(buf1[i] != 0)
	{
		i++;
	}
	bufLen = i;
	UartReady = RESET;//清标志
	if (HAL_UART_Transmit_IT(&huart1, (uint8_t *)buf1, bufLen) != HAL_OK)//把接收数组里的数据发送
	{
	}
	while (UartReady != SET)
	{
		
		osDelay(1);//等待1ms
	}
}


//int smoke_init()	
//{
//	HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,2);  
//	return 0;
//}

//int smoke_read()
//{
//	return ADC_ConvertedValue[0]&0xFFF;
//}
//#endif 