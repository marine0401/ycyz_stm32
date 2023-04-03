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
 
//��ʼ��IIC
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

//����IIC��ʼ�ź�
u8 IIC_Start(void)
{
	SDA_OUT();     //sda�����
	SDA_H;	  	  
	SCL_H;
	if(!SDA_read) return 0;
	delay_us(5);
 	SDA_L;//START:when CLK is high,DATA change form high to low 
	if(SDA_read) return 0;
	delay_us(5);
	SCL_L;//ǯסIIC���ߣ�׼�����ͻ�������� 
	return 1;
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	SCL_L;
	SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(5);
	SCL_H; 
	SDA_H;//����IIC���߽����ź�
	delay_us(5);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	SCL_L;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
    SDA_OUT(); 	    
    SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			SDA_H;
		else
			SDA_L;
		txd<<=1; 	  
		delay_us(50);   //��TEA5767��������ʱ���Ǳ����
		SCL_H;
		delay_us(50); 
		SCL_L;	
		delay_us(50); 
		
    }	 

} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  SDA_IN();//SDA����Ϊ����
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
      IIC_NAck();//����nACK
   else
      IIC_Ack(); //����ACK   
   return receive;
}

u8 Single_WriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 data)
{
  if(IIC_Start()==0)  //��ʼ�ź�
  {
    IIC_Start();
    return RESET;
  }           

  IIC_Send_Byte(Slave_Address);   //�����豸��ַ+д�ź�
  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
  IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
  IIC_Send_Byte(data);       //�ڲ��Ĵ������ݣ�
  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
  
  IIC_Stop();   //����ֹͣ�ź�
  
  return SET;
}

u8 Single_MWriteIIC_byte(u8 Slave_Address,u8 REG_Address,u8 const *data,u8 length)
{
	  IIC_Start();         

	IIC_Send_Byte(Slave_Address);   //�����豸��ַ+д�ź�
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
   
		IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ��
 	  if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	 
	while(length)
	{
		IIC_Send_Byte(*data++);       //�ڲ��Ĵ������ݣ�
	   if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}           //Ӧ��
		length--;
	}
		IIC_Stop();   //����ֹͣ�ź�		
		return SET;
}

u8 Single_ReadIIC(u8 Slave_Address,u8 REG_Address,u8 *REG_data,u8 length)
{
	
	if(IIC_Start()==0)  //��ʼ�ź�
		{IIC_Stop(); return RESET;}          
	 
	IIC_Send_Byte(Slave_Address);    //�����豸��ַ+д�ź�
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;} 
	
	IIC_Send_Byte(REG_Address);     //���ʹ洢��Ԫ��ַ
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;} 
	
	if(IIC_Start()==0)  //��ʼ�ź�
			{IIC_Stop(); return RESET;}            

	IIC_Send_Byte(Slave_Address+1);  //�����豸��ַ+���ź�
 	if(IIC_Wait_Ack()){IIC_Stop(); return RESET;}
	
	while(length-1)
	{
		*REG_data++=IIC_Read_Byte(1);       //�����Ĵ�������
		length--;
	}
	*REG_data=IIC_Read_Byte(0);  

	IIC_Stop();                    //ֹͣ�ź�
	return SET;
}























