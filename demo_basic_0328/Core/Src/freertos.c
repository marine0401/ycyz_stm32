/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "lcd_1_3/tftlcd.h"
#include "sensor.h"
#include "drv_serial.h"
#include "comm_config.h"
#include "task_config.h"
#include "power/power.h"
#include "bsp_change.h"
#include "ph/ph.h"
#include "example_nbiot_aliyun_air.h"
#include "oxygen/oxygen.h"
#include "serial_port.h"
#include "modbus/modbus.h"
#include "string.h"


//#include "ph/ph.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
SemaphoreHandle_t BinarySemaphore;
/* USER CODE END Variables */
osThreadId iotTaskHandle;
osThreadId readPHValTaskHandle;
osThreadId readOxygenTaskHandle;
osThreadId initTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */


/* USER CODE END FunctionPrototypes */

void iotThread(void const * argument);
void readPHValThread(void const * argument);
void readOxygenThread(void const * argument);
void initThread(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of iotTask */
  osThreadDef(iotTask, iotThread, osPriorityNormal, 0, 128);
  iotTaskHandle = osThreadCreate(osThread(iotTask), NULL);

  /* definition and creation of readPHValTask */
  osThreadDef(readPHValTask, readPHValThread, osPriorityIdle, 0, 128);
  readPHValTaskHandle = osThreadCreate(osThread(readPHValTask), NULL);

  /* definition and creation of readOxygenTask */
  osThreadDef(readOxygenTask, readOxygenThread, osPriorityLow, 0, 128);
  readOxygenTaskHandle = osThreadCreate(osThread(readOxygenTask), NULL);

  /* definition and creation of initTask */
  osThreadDef(initTask, initThread, osPriorityIdle, 0, 128);
  initTaskHandle = osThreadCreate(osThread(initTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	
	vTaskSuspend(iotTaskHandle);
	vTaskSuspend(readPHValTaskHandle);
	vTaskSuspend(readOxygenTaskHandle);
	
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_iotThread */
/**
  * @brief  Function implementing the iotTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_iotThread */
void iotThread(void const * argument)
{
  /* USER CODE BEGIN iotThread */
	//printf("Runnung...\r\n");
		//delay_init(80);
	//drv_serial_init();
//	power_init();
//	new_hard_init();
//	LCD_Init();	
	//HAL_Delay(2000);
  /* Infinite loop */
	example_nbiot_aliyun_air_task();
  for(;;)
  {
		
		//printf("iot Runnung...\r\n");
		
		
		osDelay(10000);
    
  }
  /* USER CODE END iotThread */
}

/* USER CODE BEGIN Header_readPHValThread */
/**
* @brief Function implementing the readPHValTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_readPHValThread */
void readPHValThread(void const * argument)
{
  /* USER CODE BEGIN readPHValThread */
	//定义一个字符串数组
	char Atstr[100];
  /* Infinite loop */
	uint8_t RX_buf[100];
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&(res), 1);
  for(;;)
  {
		printf("readPH Runnung...\r\n");
		//sprintf(Atstr, "page0.t17.txt=\"%2.1f\"\xff\xff\xff", showSpeed);				
		//UART1_Sends(tjcstr);   //把字符串发送出去
		
		//UART1_Sends("AT+PH\r\n");   //把字符串发送出去	
		
    osDelay(1000);
		printf("PH=%.2f",PHsensor.PHvalue);
		//send_data(PHsensor.PHvalue);
  }
  /* USER CODE END readPHValThread */
}

/* USER CODE BEGIN Header_readOxygenThread */
/**
* @brief Function implementing the readOxygenTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_readOxygenThread */
void readOxygenThread(void const * argument)
{
  /* USER CODE BEGIN readOxygenThread */
  /* Infinite loop */
	
	BaseType_t err=pdFALSE;

	//LPUART1_Send_Data(buf1,buflen1);
	printf("readOxygen Runnung 1\r\n");
	
	//send_get_oxygenSensor_addr_msg();
	//send_cmd(buf1);
	LPUART1_RX_CNT=0;
	
	//HAL_UART_Receive_IT(&hlpuart1,LPUART1_RX_BUF,8);
	//TIM_ClearITPendingBit();

//		send_get_attribute();
	//HAL_UART_Receive_IT(&hlpuart1,(uint8_t*)&oxygen_res,1);
	
//	__HAL_TIM_ENABLE_IT(&htim7,TIM_IT_UPDATE);
//	__HAL_TIM_SetCounter(&htim7,0);
//	__HAL_TIM_ENABLE(&htim7);
	//BinarySemaphore=(SemaphoreHandle_t)1;
	//HAL_TIM_Base_Start_IT(&htim7);

	//send_get_attribute();
	send_set_mode();
	osDelay(10000);
	printf("readOxygen Runnung 2\r\n");
  for(;;)
  {
		
	
//		if(BinarySemaphore!=NULL)
//		{
//			err=xSemaphoreTake(BinarySemaphore,portMAX_DELAY);	//获取信号量
//			if(err==pdTRUE)	
//			{
//				
//				printf("x %s\n",mb_buf_in);
//				
//				
//			}
		
		//send digital
		
		memset(LPUART1_RX_BUF, 0, sizeof(LPUART1_RX_BUF));

		send_get_attribute();

		while(1){
			if(LPUART1_RX_STATUS == 1)
			{
				for(uint8_t i=0;i < 21;i++){
					printf("%x ",LPUART1_RX_BUF[i]);
				}
				  printf("temper = %d \r\n",OxygenSensor.Temperature);
				printf("rate = %d \r\n",OxygenSensor.DissolvedOxygenRate);
				printf("oxygen = %d \r\n",OxygenSensor.DissolvedOxygen);
			     printf("\r\nrec done\r\n");
					 LPUART1_RX_STATUS = 0;
					break;
			}
			osDelay(1);//等待1ms
		}
    osDelay(30000);
//		}
	}
  /* USER CODE END readOxygenThread */
}

/* USER CODE BEGIN Header_initThread */
/**
* @brief Function implementing the initTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_initThread */
void initThread(void const * argument)
{
  /* USER CODE BEGIN initThread */
	printf("init started!...\r\n");
	LCD_Init();
	taskENTER_CRITICAL();           //进入临界区
	vTaskResume(iotTaskHandle);
	vTaskResume(readPHValTaskHandle);
	vTaskResume(readOxygenTaskHandle);
  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
    vTaskDelete(initTaskHandle); //删除开始任务
		printf("init deleted!...\r\n");
    taskEXIT_CRITICAL();            //退出临界区
  /* USER CODE END initThread */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
