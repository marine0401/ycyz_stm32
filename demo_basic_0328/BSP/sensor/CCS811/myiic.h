#ifndef __MYIIC_H
#define __MYIIC_H

#include "main.h"

#define u8      uint8_t

#define SDA_H     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)
#define SDA_L     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)
#define SCL_H     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET)
#define SCL_L     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET)

#define SDA_read        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)

//IIC���в�������
void SDA_IN(void);  
void SDA_OUT(void);

void IIC_Init(void);                //��ʼ��IIC��IO��				 
u8 IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

u8 Single_WriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 data);
u8 Single_MWriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length);
u8 Single_ReadIIC(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length);
#endif
















