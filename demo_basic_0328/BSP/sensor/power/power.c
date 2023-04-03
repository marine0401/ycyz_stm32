#include "power/power.h"

#include "smoke/smoke.h"
#include "lcd_1_3/tftlcd.h"
#include "stdio.h"

int power_init()	
{
	HAL_ADC_Start_DMA(&hadc1,ADC_ConvertedValue,2);  
	return 0;
}

int power_read()
{
	return (ADC_ConvertedValue[1]&0x0FFF)*2 ;
}



void display_battery_voltage()
{
	char buff[10];
	//LCD_ShowString(0,72+24,200,24,24,"current power: ");	
	sprintf(buff,"%.3f v",(power_read()*3.3)/4096);
//	LCD_ShowString(12*14,72+24,200,24,24,buff);
	
	LCD_ShowString(40+32,134,200,32,32,buff);

}