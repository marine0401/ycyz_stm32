#ifndef __DRV_SERIAL__H__
#define __DRV_SERIAL__H__

#include "stm32l4xx_hal.h"
#include "tim.h"
#include "usart.h"

#define BUFF_MAX_LEN 200


#define DEBUG_CMD_INFO 1


void drv_serial_init();
uint16_t drv_serial_read(uint8_t* buff,uint16_t* len);
uint8_t send_cmd_check(UART_HandleTypeDef* huart,uint8_t *cmd,uint8_t *ack,uint16_t waittime,uint8_t max_cnt);
void USARTx_SendString(UART_HandleTypeDef huartx,uint8_t *str);


void drv_serial_tim_irhandle(TIM_HandleTypeDef *htim );
void drv_serial_usart_irhandle(UART_HandleTypeDef *UartHandle);


#define drv_huart huart3
#define drv_htim  htim6

extern uint8_t rx_data;
extern uint8_t rx_flag;
extern 	uint16_t rx_cnt;
extern 	uint8_t rx_buff[BUFF_MAX_LEN];
extern 	uint8_t tx_buff[BUFF_MAX_LEN];

#endif