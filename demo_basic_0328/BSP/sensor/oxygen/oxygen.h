#include "usart.h"

//�ܽ������������ݴ�Žṹ��
__packed typedef struct  
{										    
		uint16_t version;					//�汾��*100  �Ŵ���100��,ʵ�ʳ���100
		uint16_t Temperature;	  //
		uint16_t DissolvedOxygen;
		uint16_t DissolvedOxygenRate;
		uint16_t voltage;					//��ѹֵ*100
		uint16_t errUp;					//PHֵ��������*100
		uint16_t errDown;					//PHֵ��������*100		
	
		uint8_t status;					//������״̬ 0:idle  1��busy
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