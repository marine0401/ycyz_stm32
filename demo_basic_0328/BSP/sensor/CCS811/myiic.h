#ifndef __MYIIC_H
#define __MYIIC_H

#include "main.h"

#define u8      uint8_t

#define SDA_H     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET)
#define SDA_L     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET)
#define SCL_H     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET)
#define SCL_L     HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET)

#define SDA_read        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)

//IIC所有操作函数
void SDA_IN(void);  
void SDA_OUT(void);

void IIC_Init(void);                //初始化IIC的IO口				 
u8 IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

u8 Single_WriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 data);
u8 Single_MWriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length);
u8 Single_ReadIIC(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length);
#endif
















