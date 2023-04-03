#ifndef __CCS811_H
#define __CCS811_H

#include "stm32l4xx_hal.h"
#include "myiic.h"
#include "gpio.h"
#include "usart.h"

#define CCS811_Add      		0x5A<<1

#define DRIVE_MODE_1SEC 		0x10  // 1��������
#define DRIVE_MODE_10SEC		0x20  // 10s�������
#define DRIVE_MODE_60SEC 		0x30  // ÿ���Ӳ���
#define INTERRUPT_DRIVEN 		0x8   // ǿ������250ms

extern unsigned short eco2,tvoc;
void CCS811_Init(void);
void CCS811GetData(void);

#endif

