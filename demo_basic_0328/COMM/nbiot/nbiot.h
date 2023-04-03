#ifndef __NBIOT__H__
#define __NBIOT__H__
#include "comm_config.h"
#include "stm32l4xx_hal.h"
#include "task_config.h"

#ifdef NBIOT_ENABLED



#define ProductKey      "a1jIbsxgdEt"
#define DeviceName      "YmC3Aot1sxjkKvHF2opN"
#define DeviceSecret    "39cac05cb8370900da4e0af25eabe5ef"


#endif


uint8_t nbiot_init();
uint8_t __check_nbiot();
#endif