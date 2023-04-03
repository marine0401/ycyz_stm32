#ifndef __LCD_CONFIG__H__
#define __LCD_CONFIG__H__
#include "spi.h"


#define LCD_1_3_ENABLE 
//#define LCD_LOGO_ENABLE





#ifdef LCD_1_3_ENABLE


/*
	LCD_PWR:	PC7	
	LCD_RST:	PC8		
	LCD_WR:		PC11	
	LCD_CS:		PC9	
*/


#define LCD_PWR_PORT   GPIOC
#define LCD_PWR_PIN    GPIO_PIN_7
#define LCD_RST_PORT   GPIOC
#define LCD_RST_PIN    GPIO_PIN_8
#define LCD_WR_PORT    GPIOC
#define LCD_WR_PIN		 GPIO_PIN_11
#define LCD_CS_PORT    GPIOC
#define LCD_CS_PIN     GPIO_PIN_9


#define LCD_1_3_SPI  hspi3


#endif  



#endif
