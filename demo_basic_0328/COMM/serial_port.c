#include "serial_port.h"
#include "drv_serial.h"
#include "modbus/modbus.h"
#include "ph.h"
#include "stm32l4xx_it.h"
#include "oxygen/oxygen.h"
#include <string.h>
uint8_t _UART1_RX_BUF[24]={0};
uint8_t _UART1_RX_STATUS=0;
uint8_t _UART1_RX_CNT=0;
uint8_t _UART1_HEAD_BUF[3]={0};
uint8_t res=111;

__IO ITStatus Uart3Ready = RESET;
__IO ITStatus UartLPReady = RESET;
__IO ITStatus UartReady = RESET;






//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//	
//	if (htim == (&htim7)){
//	
//	}

//}

//发送完成回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
	if(UartHandle->Instance == USART1){
		UartReady = SET;
		
	}else if(UartHandle->Instance == USART3){
		Uart3Ready = SET;
	}else if(UartHandle->Instance == LPUART1){
		UartLPReady = SET;
		printf("UartLPReady\r\n");
	}
	

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{

	
	drv_serial_usart_irhandle(UartHandle);
	
	if(UartHandle == &hlpuart1){
//		HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)&oxygen_res,1);
//		
//		if(LPUART1_RX_CNT<24)
//		{
//			LPUART1_RX_BUF[LPUART1_RX_CNT] = oxygen_res;
//			LPUART1_RX_CNT++;
			
			LPUART1_RX_STATUS = 1;
			if(LPUART1_RX_BUF[2] == 0x10 && LPUART1_RX_BUF[1] == 0X03){
				memcpy(mb_buf_in,LPUART1_RX_BUF,21);
				mb_buf_in_count = 21;
				ModBus_SetAddress(0x01);
				ModBusParse();
				
			}
//			
//			__HAL_TIM_ENABLE_IT(&htim7,TIM_IT_UPDATE);
//			__HAL_TIM_SetCounter(&htim7,0);
//			__HAL_TIM_ENABLE(&htim7);
//		HAL_TIM_Base_Start_IT(&htim7);	

//			
		}
		
		
		
//		HAL_UART_Receive_IT(&hlpuart1,oxygen_res,1);
//		printf("lphuart\n");
//		uint8_t i = 0;
//		while(LPUART1_RX_BUF[i] !=0){
//			i++;
//		}
//		LPUART1_RX_CNT = i;
////		HAL_TIM_Base_Start_IT(&htim7);
//				
//			
//			__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
//			__HAL_TIM_SetCounter(&htim7,0);
//			__HAL_TIM_ENABLE(&htim7);
//			

		
		
//	}
	
	if(UartHandle->Instance==USART1)
	{
		HAL_UART_Receive_IT(&huart1,(uint8_t *)&(res),1);
		_UART1_HEAD_BUF[0] = _UART1_HEAD_BUF[1];
		_UART1_HEAD_BUF[1] = res;	
		if(_UART1_HEAD_BUF[0] == 0x0D &&_UART1_HEAD_BUF[1] == 0x0A)		//检测到数据尾“\r\n”
		{		
			_UART1_RX_BUF[_UART1_RX_CNT]=res;
			_UART1_RX_BUF[_UART1_RX_CNT+1]=0;
			
			if(_UART1_RX_CNT>=3)																				//接收数据有效
			{
				if(_UART1_RX_BUF[0] == '+' &&_UART1_RX_BUF[1] == 'V'&&_UART1_RX_BUF[2] == 'E'&&_UART1_RX_BUF[3] == 'R'
					&&_UART1_RX_BUF[4] == 'S'&&_UART1_RX_BUF[5] == 'I'&&_UART1_RX_BUF[6] == 'O'&&_UART1_RX_BUF[7] == 'N'&&_UART1_RX_BUF[8] == '=')
				{
					PHsensor.version=(uint16_t)(_UART1_RX_BUF[9]-'0')*100+(_UART1_RX_BUF[11]-'0')*10;
				}	
				else if(_UART1_RX_BUF[0]=='+' &&_UART1_RX_BUF[1]=='V'&&_UART1_RX_BUF[2]=='=')
				{
					PHsensor.voltage=(uint16_t)(_UART1_RX_BUF[3]-'0')*100+(_UART1_RX_BUF[5]-'0')*10+(_UART1_RX_BUF[6]-'0');
				}
				else if(_UART1_RX_BUF[0] == 'O' &&_UART1_RX_BUF[1] == 'K')
				{
					
				}
				else if(_UART1_RX_BUF[0] == '+' &&_UART1_RX_BUF[1] == 'P' &&_UART1_RX_BUF[2] == 'H' && _UART1_RX_BUF[3] == '='){
					
						uint16_t temp = 0;
						for(uint8_t i = 4;_UART1_RX_BUF[i-1]!=0x0D &&_UART1_RX_BUF[i] !=0x0A;i++){
							
								if(_UART1_RX_BUF[i] == 0x2E || _UART1_RX_BUF[i] == 0x0D){
										continue;
								}
								
								temp = temp*10 + (uint16_t)(_UART1_RX_BUF[i]-'0');
								
						}
						PHsensor.PHvalue = temp;
						
				}
				
			}
			_UART1_RX_CNT=0;
			_UART1_HEAD_BUF[0] = 0;
			_UART1_HEAD_BUF[1] = 0;
			_UART1_HEAD_BUF[2] = 0;
		}
		else
		{
			_UART1_RX_BUF[_UART1_RX_CNT]=res;
			_UART1_RX_CNT=(_UART1_RX_CNT+1)%24;
		}
		
		
		//printf("version %d",PHsensor.version);
	}
	
}
	
	

