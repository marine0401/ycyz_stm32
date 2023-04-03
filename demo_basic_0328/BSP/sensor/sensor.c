#include "sensor.h"
#include "sensor_config.h"



#ifdef SENSOR_DHT11_ENABLED
#include "dht11/dht11.h"

/**
  * @brief  DHT11��ʼ��
  * @param  ��            
  * @retval 0���ɹ�
						1��ʧ��
  */
uint8_t sensor_dht11_init()
{
	return DHT11_Init();
}
 
/**
  * @brief  DHT11��ʪ�ȶ�ȡ
  * @param  temp ->pointer to temp   
  * @param  humi ->pointer to humi       
  * @retval 0���ɹ�
						1��ʧ��
  */
uint8_t sensor_dht11_read(uint8_t *temp,uint8_t *humi)
{
	return DHT11_Read_Data(temp,humi);
}





#endif