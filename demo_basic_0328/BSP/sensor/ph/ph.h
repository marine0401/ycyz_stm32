#include "usart.h"

//PHֵ���������ݴ�Žṹ��
__packed typedef struct  
{										    
		uint16_t version;					//�汾��*100  �Ŵ���100��,ʵ�ʳ���100
		float PHvalue;					//PHֵ*100
		uint16_t voltage;					//��ѹֵ*100
		uint16_t errUp;					//PHֵ��������*100
		uint16_t errDown;					//PHֵ��������*100		
}ph_msg;

extern ph_msg PHsensor;
void UART1_Sends(char *buf1);

