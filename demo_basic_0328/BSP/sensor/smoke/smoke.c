#include "smoke/smoke.h"
#include "sensor_config.h"

#ifdef SENSEO_SMOKE_ENABLED

uint32_t ADC_ConvertedValue[2]={0};

int smoke_init()	
{
	HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,2);  
	return 0;
}

int smoke_read()
{
	return ADC_ConvertedValue[0]&0xFFF;
}
#endif 