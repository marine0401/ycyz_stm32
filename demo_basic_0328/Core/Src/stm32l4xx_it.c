/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CCS811.h"
#include "ph/ph.h"
#include "oxygen/oxygen.h"
#include "FreeRTOS.h"	
#include "semphr.h"
#include "modbus/modbus.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t UART1_RX_BUF[24];
uint8_t UART1_RX_STATUS=0;
uint8_t UART1_RX_CNT=0;
uint8_t UART1_HEAD_BUF[3];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
extern SemaphoreHandle_t BinarySemaphore;	//二值信号量句柄
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM16 global interrupt.
  */
void TIM1_UP_TIM16_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM16_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM16_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint8_t res;
	if(__HAL_UART_GET_IT(&huart1,UART_IT_RXNE)!=RESET)  //接收中断
	{
		HAL_UART_Receive(&huart1,&res,1,1000);
		
		UART1_HEAD_BUF[0] = UART1_HEAD_BUF[1];
		UART1_HEAD_BUF[1] = res;	
		if(UART1_HEAD_BUF[0] == 0x0D &&UART1_HEAD_BUF[1] == 0x0A)		//检测到数据尾“\r\n”
		{		
			UART1_RX_BUF[UART1_RX_CNT]=res;
			UART1_RX_BUF[UART1_RX_CNT+1]=0;
			
			if(UART1_RX_CNT>=3)																				//接收数据有效
			{
				if(UART1_RX_BUF[0] == '+' &&UART1_RX_BUF[1] == 'V'&&UART1_RX_BUF[2] == 'E'&&UART1_RX_BUF[3] == 'R'
					&&UART1_RX_BUF[4] == 'S'&&UART1_RX_BUF[5] == 'I'&&UART1_RX_BUF[6] == 'O'&&UART1_RX_BUF[7] == 'N'&&UART1_RX_BUF[8] == '=')
				{
					PHsensor.version=(uint16_t)(UART1_RX_BUF[9]-'0')*100+(UART1_RX_BUF[11]-'0')*10;
				}	
				else if(UART1_RX_BUF[0]=='+' &&UART1_RX_BUF[1]=='V'&&UART1_RX_BUF[2]=='=')
				{
					PHsensor.voltage=(uint16_t)(UART1_RX_BUF[3]-'0')*100+(UART1_RX_BUF[5]-'0')*10+(UART1_RX_BUF[6]-'0');
				}
				else if(UART1_RX_BUF[0] == 'O' &&UART1_RX_BUF[1] == 'K')
				{
					
				}
				
				
			}
			UART1_RX_CNT=0;
			UART1_HEAD_BUF[0] = 0;
			UART1_HEAD_BUF[1] = 0;
			UART1_HEAD_BUF[2] = 0;
		}
		else
		{
			UART1_RX_BUF[UART1_RX_CNT]=res;
			UART1_RX_CNT=(UART1_RX_CNT+1)%24;
		}
	}
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	uint8_t res;
	if(__HAL_UART_GET_IT(&hlpuart1,UART_IT_RXNE)!=RESET)  //接收中断
	{
		HAL_UART_Receive(&hlpuart1,&res,1,1000);
		tvoc=res;
	}
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC channel1 and channel2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
	BaseType_t xHigherPriorityTaskWoken=pdTRUE;
	HAL_TIM_Base_Stop_IT(&htim7);
//	__HAL_TIM_CLEAR_IT(&htim7,TIM_IT_UPDATE);
//	__HAL_TIM_DISABLE(&htim7);
	
	
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); //发送状态
	RS485_FrameFlag=1;
	mb_buf_in_count = LPUART1_RX_CNT-1;
	
	printf("tim7 running\n");
	memcpy(mb_buf_in,LPUART1_RX_BUF,sizeof(LPUART1_RX_BUF));
	//释放二值信号量
	if(BinarySemaphore!=NULL)//接收到数据，并且二值信号量有效
	{
		xSemaphoreGiveFromISR(BinarySemaphore,&xHigherPriorityTaskWoken);	//释放二值信号量
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);//如果需要的话进行一次任务切换
	}	
	
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles LPUART1 global interrupt.
  */
void LPUART1_IRQHandler(void)
{
  /* USER CODE BEGIN LPUART1_IRQn 0 */
	uint8_t res;
//	
//	if(__HAL_UART_GET_IT(&hlpuart1,UART_IT_RXNE)!=RESET)  //接收中断
//	{
//		//HAL_UART_Receive(&hlpuart1,&res,1,1000);
//		//tvoc=res;
//			printf("cc\r\n");
//		
//		if(LPUART1_RX_CNT<24)
//		{
//			LPUART1_RX_BUF[LPUART1_RX_CNT] = res;
//			LPUART1_RX_CNT++;
//			

//			
////			__HAL_TIM_ENABLE_IT(&htim7,TIM_IT_UPDATE);
////			__HAL_TIM_SetCounter(&htim7,0);
////			__HAL_TIM_ENABLE(&htim7);
////			

//			
//		}
//	}
  /* USER CODE END LPUART1_IRQn 0 */
  HAL_UART_IRQHandler(&hlpuart1);
  /* USER CODE BEGIN LPUART1_IRQn 1 */

  /* USER CODE END LPUART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
