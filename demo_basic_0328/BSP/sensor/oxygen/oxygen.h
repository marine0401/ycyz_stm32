#include "usart.h"

//溶解氧传感器数据存放结构体
__packed typedef struct  
{										    
		uint16_t version;					//版本数*100  放大了100倍,实际除以100
		uint16_t Temperature;	  //
		uint16_t DissolvedOxygen;
		uint16_t DissolvedOxygenRate;
		uint16_t voltage;					//电压值*100
		uint16_t errUp;					//PH值报警上限*100
		uint16_t errDown;					//PH值报警下限*100		
	
		uint8_t status;					//传感器状态 0:idle  1：busy
}oxygen_msg;

extern oxygen_msg OxygenSensor;

extern uint8_t LPUART1_RX_BUF[24];
extern uint8_t LPUART1_RX_STATUS;
extern uint8_t LPUART1_RX_CNT;
extern uint8_t LPUART1_HEAD_BUF[3];
extern uint8_t RS485_FrameFlag;
extern uint8_t oxygen_res;
extern uint8_t is_oxygen_updated;
uint8_t oxygenSensor_init();	
void send_get_oxygenSensor_addr_msg();
void send_get_attribute(void);
void send_set_mode(void);