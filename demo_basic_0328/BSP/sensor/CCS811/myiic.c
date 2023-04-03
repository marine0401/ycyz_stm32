#include "myiic.h"
#include "delay/delay.h"
//void delay_us(uint32_t udelay)
//{
//  uint32_t startval,tickn,delays,wait;
// 
//  startval = SysTick->VAL;
//  tickn = HAL_GetTick();
//  //sysc = 80000;  //SystemCoreClock / (1000U / uwTickFreq);
//  delays =udelay * 80; //sysc / 1000 * udelay;
//  if(delays > startval)
//    {
//      while(HAL_GetTick() == tickn)
//        {
// 
//        }
//      wait = 80000 + startval - delays;
//      while(wait < SysTick->VAL)
//        {
// 
//        }
//    }
//  else
//    {
//      wait = startval - delays;
//      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
//        {
// 
//        }
//    }
//}
 
//初始化IIC
void IIC_Init(void)
{					     
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_SET);
  
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void SDA_IN()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SDA_OUT()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

//产生IIC起始信号
u8 IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	SDA_H;	  	  
	SCL_H;
	if(!SDA_read) return 0;
	delay_us(5);
 	SDA_L;//START:when CLK is high,DATA change form high to low 
	if(SDA_read) return 0;
	delay_us(5);
	SCL_L;//钳住IIC总线，准备发送或接收数据 
	return 1;
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	SCL_H; 
	SDA_H;//发送IIC总线结束信号
	delay_us(5);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	SDA_H;delay_us(1);	   
	SCL_H;delay_us(1);	 
	while(SDA_read)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL_L;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	SCL_L;
	SDA_OUT();
	SDA_L;
	delay_us(5);
	SCL_H;
	delay_us(5);
	SCL_L;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	SCL_L;
	SDA_OUT();
	SDA_H;
	delay_us(5);
	SCL_H;
	delay_us(5);
	SCL_L;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    SDA_OUT(); 	    
    SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			SDA_H;
		else
			SDA_L;
		txd<<=1; 	  
		delay_us(50);   //对TEA5767这三个延时都是必须的
		SCL_H;
		delay_us(50); 
		SCL_L;	
		delay_us(50); 
		
    }	 

} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  SDA_IN();//SDA设置为输入
  for(i=0;i<8;i++ )
  {
    SCL_L; 
    delay_us(50);
    SCL_H;
    receive<<=1;
    if(SDA_read)receive++;   
    delay_us(50); 
   }					 
   if (!ack)
      IIC_NAck();//发送nACK
   else
      IIC_Ack(); //发送ACK   
   return receive;
}

u8 Single_WriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 data)
{
  if(IIC_Start()==0)  //起始信号
  {
    IIC_Start();
    return RESET;
  }           

  IIC_Send_Byte(Slave_Address);   //发送设备地址+写信号
  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
  IIC_Send_Byte(REG_Address);    //内部寄存器地址，
  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
  IIC_Send_Byte(data);       //内部寄存器数据，
  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
  
  IIC_Stop();   //发送停止信号
  
  return SET;
}

u8 Single_MWriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length)
{
	  IIC_Start();         

	IIC_Send_Byte(Slave_Address);   //发送设备地址+写信号
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
		IIC_Send_Byte(REG_Address);    //内部寄存器地址，
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	 
	while(length)
	{
		IIC_Send_Byte(*data++);       //内部寄存器数据，
	   if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}           //应答
		length--;
	}
		IIC_Stop();   //发送停止信号		
		return SET;
}

u8 Single_ReadIIC(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length)
{
	
	if(IIC_Start()==0)  //起始信号
		{IIC_Stop(); return RESET;}          
	 
	IIC_Send_Byte(Slave_Address);    //发送设备地址+写信号
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;} 
	
	IIC_Send_Byte(REG_Address);     //发送存储单元地址
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;} 
	
	if(IIC_Start()==0)  //起始信号
			{IIC_Stop(); return RESET;}            

	IIC_Send_Byte(Slave_Address+1);  //发送设备地址+读信号
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	while(length-1)
	{
		*REG_data++=IIC_Read_Byte(1);       //读出寄存器数据
		length--;
	}
	*REG_data=IIC_Read_Byte(0);  

	IIC_Stop();                    //停止信号
	return SET;
}























