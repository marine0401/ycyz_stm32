#include <stdbool.h>

#include "usart.h"
#include "oxygen/oxygen.h"
#include "sensor_config.h"
#include "serial_port.h"
#include "cmsis_os.h"
//#ifdef SENSEO_SMOKE_ENABLED

oxygen_msg OxygenSensor;

uint8_t LPUART1_RX_BUF[24]={0};
uint8_t LPUART1_RX_STATUS=0;
uint8_t LPUART1_RX_CNT=0;
uint8_t LPUART1_HEAD_BUF[3]={0};
uint8_t RS485_FrameFlag=0;
uint8_t oxygen_res=0;
uint8_t oxygenSensor_init()	
{
	OxygenSensor.status=0;
	
	//HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,2);  
	
	return 0;
}

uint8_t rx_buf[10];
void send_get_attribute(void){

	uint8_t buf1[]={0x01,0x03,0x00,0x10,0x00,0x08,0x45,0xC9};
	oxygen_res++;
	
	if(oxygen_res == 1){
		HAL_UART_Receive_IT(&hlpuart1,LPUART1_RX_BUF,22);
	}else{
		HAL_UART_Receive_IT(&hlpuart1,LPUART1_RX_BUF,21);
		oxygen_res = 2;
	}
	
	UartLPReady = RESET;//清标志
	LPUART1_RX_STATUS = 0;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	osDelay(10);
	HAL_UART_Transmit_IT(&hlpuart1, (uint8_t *)buf1, sizeof(buf1)/sizeof(uint8_t));
	while(true)
	{
		if(UartLPReady == SET)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
			printf("send done\r\n");
			break;
		}
		osDelay(1);//等待1ms
	}
	
		

}

void send_get_oxygenSensor_addr_msg()
{
	if(OxygenSensor.status==0)  //PH传感器处于空闲状态
	{
		//LPUART1_Send_Data("AT+VERSION\r\n");   //把字符串发送出去	
		LPUART1_RX_CNT=0;
		OxygenSensor.status=1;  //设置PH传感器处于busy状态
	}	
}
//int smoke_read()
//{
//	return ADC_ConvertedValue[0]&0xFFF;
//}
//#endif 