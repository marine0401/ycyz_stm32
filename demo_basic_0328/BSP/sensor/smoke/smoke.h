#ifndef __SMOKE__H__
#define __SMOKE__H__

#include "adc.h"

extern uint32_t ADC_ConvertedValue[2];

int smoke_init();
int smoke_read();

#endif