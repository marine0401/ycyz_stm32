#include "sensor.h"
#include "sensor_config.h"



#ifdef SENSOR_DHT11_ENABLED
#include "dht11/dht11.h"

/**
  * @brief  DHT11初始化
  * @param  无            
  * @retval 0：成功
						1：失败
  */
uint8_t sensor_dht11_init()
{
	return DHT11_Init();
}
 
/**
  * @brief  DHT11温湿度读取
  * @param  temp ->pointer to temp   
  * @param  humi ->pointer to humi       
  * @retval 0：成功
						1：失败
  */
uint8_t sensor_dht11_read(uint8_t *temp,uint8_t *humi)
{
	return DHT11_Read_Data(temp,humi);
}





#endif