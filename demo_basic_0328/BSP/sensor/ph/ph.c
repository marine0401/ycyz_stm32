#include "ph/ph.h"
#include "sensor_config.h"
#include "usart.h"
#include "serial_port.h"
//#ifdef SENSEO_SMOKE_ENABLED

//���ڷ��ͻ������ɱ�־��
ph_msg PHsensor;

//huart1�ַ������ͺ���
void UART1_Sends(char *buf1)		  
{
	uint8_t i=0;
	uint8_t bufLen = 0;
	while(buf1[i] != 0)
	{
		i++;
	}
	bufLen = i;
	UartReady = RESET;//���־
	if (HAL_UART_Transmit_IT(&huart1, (uint8_t *)buf1, bufLen) != HAL_OK)//�ѽ�������������ݷ���
	{
	}
	while (UartReady != SET)
	{
		
		osDelay(1);//�ȴ�1ms
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