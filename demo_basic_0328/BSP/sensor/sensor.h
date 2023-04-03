#ifndef __SENSOR_H__
#define __SENSOR_H__


#include "smoke/smoke.h"

#ifdef SENSOR_DHT11_ENABLED
#include "dht11/dht11.h"
uint8_t sensor_dht11_init();
uint8_t sensor_dht11_read(uint8_t *temp,uint8_t *humi);
#endif

uint8_t sensor_smoke_init();
uint8_t sensor_smoke_read(uint16_t *smoke);

#endif