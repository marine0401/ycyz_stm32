#include "nbiot.h"
#include "drv_serial.h"
#include "string.h"
#include "comm_config.h"



#ifdef NBIOT_ENABLED
uint8_t ID=0,msgid=1,qos=1,retain=0;
uint8_t QMTCFG[256],QMTOPEN[256],QMTCONN[256],QMTSUB[256],message[256];
//1:²»´æÔÚ

uint8_t __check_nbiot()
{
		
		
			
		if(send_cmd_check(&drv_huart,(uint8_t*)"AT\r\n",(uint8_t*)"OK",10,5))//
		{

			return 1;
		}
		
		else
		{

			printf("¼ì²âµ½NBIOT\r\n");
			return 0;
		}
		
	
}

uint8_t nbiot_init()
{
	if(__check_nbiot())return 1;

	if(send_cmd_check(&drv_huart,(uint8_t *)"AT+CFUN=1,0\r\n",(uint8_t*)"OK",200,5))return 2;
	if(send_cmd_check(&drv_huart,(uint8_t *)"AT+CPIN?\r\n",(uint8_t*)"OK",200,5)){printf("¼ì²âSIM¿¨Ê§°Ü\r\n"); return 3;}
	if(send_cmd_check(&drv_huart,(uint8_t *)"AT+CEREG?\r\n",(uint8_t*)"+CEREG: 0,1",700,5)){printf("ÍøÂç×¢²áÊ§°Ü\r\n"); return 4;}
	if(send_cmd_check(&drv_huart,(uint8_t *)"AT+CGATT?\r\n",(uint8_t*)"+CGATT: 1",1000,5)){printf("ÁªÍøÊ§°Ü\r\n"); return 5;}
	if(send_cmd_check(&drv_huart,(uint8_t *)"AT+QMTDISC=0\r\n",(uint8_t*)"OK",100,1)){}
	
	memset(QMTOPEN,0,sizeof(QMTOPEN));
  sprintf((char*)QMTOPEN,"AT+QMTOPEN=%d,\"47.100.200.181\",1883\r\n",ID);
	if(send_cmd_check(&drv_huart,(uint8_t *)QMTOPEN,(uint8_t*)"+QMTOPEN: 0,0",8000,5)){ printf("´ò¿ªÍøÂçÊ§°Ü£¡\r\n"); return 7;}
	
	memset(QMTCONN,0,sizeof(QMTCONN));
	sprintf((char*)QMTCONN,"AT+QMTCONN=%d,\"%s\",\"%s\",\"%s\"\r\n",ID,DeviceName,"device","sl707_");
	if(send_cmd_check(&drv_huart,(uint8_t *)QMTCONN,(uint8_t*)"+QMTCONN: 0,0,0",1000,2)){ printf("ÉÏÏßÊ§°Ü£¡\r\n"); return 8;}
	
	return 0;
		
}
#endif