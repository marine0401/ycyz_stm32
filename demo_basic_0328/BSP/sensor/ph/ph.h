#include "usart.h"

//PH值传感器数据存放结构体
__packed typedef struct  
{										    
		uint16_t version;					//版本数*100  放大了100倍,实际除以100
		float PHvalue;					//PH值*100
		uint16_t voltage;					//电压值*100
		uint16_t errUp;					//PH值报警上限*100
		uint16_t errDown;					//PH值报警下限*100		
}ph_msg;

extern ph_msg PHsensor;
void UART1_Sends(char *buf1);

