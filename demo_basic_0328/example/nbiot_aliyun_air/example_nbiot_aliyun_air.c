#include "example_nbiot_aliyun_air.h"
#include "task_config.h"

#include "CCS811.h"
#include "myiic.h"
#include "drv_serial.h"
//#include "delay/delay.h"
#include "lcd_1_3/tftlcd.h"
#include "sensor.h"
#include "nbiot.h"
#include "string.h"
#include "power/power.h"
#include "ph/ph.h"
#include "gui/gui.h"
#include "serial_port.h"

#if EXAMPLE_NBIOT_ALIYUN_AIR_TASK

static void __task_before_nbiot_init();

static uint8_t ID=0,msgid=1,qos=1,retain=0;
static uint8_t message[256],QMTPUB[256];


 void send_data(float ph )
{
	memset(message,0,strlen((const char*)message));
  sprintf((char*)message,"{'id':'1','version':'1.0','method':'thing.event.property.post','params':{'ph':%.2f}}",ph);
	
	memset(QMTPUB,0,strlen((const char*)QMTPUB));
  sprintf((char*)QMTPUB,"AT+QMTPUB=%d,%d,%d,%d,\"/attribute/display\",\"%s\"\r\n",ID,msgid,qos,retain,message);
	
	uint8_t len = 0;
	Uart3Ready = RESET;
	while(QMTPUB[len] != 0)
	{
		len++;
	}
	
  if(HAL_UART_Transmit_IT(&drv_huart,QMTPUB,len)!= HAL_OK){
	
	}
	while(Uart3Ready != SET){
		osDelay(1);
	}
}


void example_nbiot_aliyun_air_task()
{
	
	static uint8_t tim_cnt=0;
	__task_before_nbiot_init();

	uint8_t buff[5]={0};
  

	


}

static void __task_before_nbiot_init()
{
	
	uint8_t buff[5]={0};
	POINT_COLOR = RED;
	
	show_smoke_gui();
	IIC_Init();
	//CCS811_Init();
	
	
	show_wifi_state(1);

	  		   

}

#endif
