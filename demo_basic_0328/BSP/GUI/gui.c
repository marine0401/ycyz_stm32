#include "gui/gui.h"

#include "delay/delay.h"
#include "lcd_1_3/tftlcd.h"


#include "gui/temp.h"
#include "gui/battery.h"
#include "gui/wifi_on.h"
#include "gui/wifi_off.h"
#include "gui/smoke.h"


void __show_title(char *title)
{
	//LCD_ShowString(5,10,240,32,32,title);	 
	LCD_ShowString(30,10,240,32,32,title);	 
}
void show_temp_gui()
{

	BACK_COLOR=GRAY;
	LCD_Fill(0,0,240,60,GRAY);
	POINT_COLOR=WHITE;
//	show_title("WIFI TO ALIYUN");
		__show_title("WIFI NODE_1");

	BACK_COLOR=WHITE;
	POINT_COLOR=LIGHTBLUE;
	LCD_DrawLine(0,60,240,60);
	LCD_DrawLine(0,120,240,120);
	LCD_DrawLine(0,180,240,180);

	POINT_COLOR=RED;
	
//	LCD_Show_Image(10,70,40,40,gImage_wifi_on);
//	LCD_ShowString(40+32,74,240,32,32,"CONNECT");	
	//断网
//	LCD_Show_Image(10,70,40,40,gImage_wifi_off);
//	LCD_ShowString(40+32,74,240,32,32,"DISCONNECT");	
	
	LCD_Show_Image(10,130,40,40,gImage_battery);
	
	LCD_Show_Image(10,190,40,40,gImage_temp);
	
		LCD_ShowString(100+12*3,182,24,24,24,"C");	 
 	LCD_ShowString(100+12*3,210,24,24,24,"%");


}

void show_temp_gui_nbiot()
{

	BACK_COLOR=GRAY;
	LCD_Fill(0,0,240,60,GRAY);
	POINT_COLOR=WHITE;
//	show_title("WIFI TO ALIYUN");
	__show_title("NBIOT NODE");

	BACK_COLOR=WHITE;
	POINT_COLOR=LIGHTBLUE;
	LCD_DrawLine(0,60,240,60);
	LCD_DrawLine(0,120,240,120);
	LCD_DrawLine(0,180,240,180);

	POINT_COLOR=RED;
	
	LCD_Show_Image(10,130,40,40,gImage_battery);
	
	LCD_Show_Image(10,190,40,40,gImage_temp);
	
		LCD_ShowString(100+12*3,182,24,24,24,"C");	 
 	LCD_ShowString(100+12*3,210,24,24,24,"%");


}


void show_smoke_gui()
{

	BACK_COLOR=GRAY;
	LCD_Fill(0,0,240,60,GRAY);
	POINT_COLOR=WHITE;
//	show_title("WIFI TO ALIYUN");
		__show_title("NBIOT NODE");

	BACK_COLOR=WHITE;
	POINT_COLOR=LIGHTBLUE;
	LCD_DrawLine(0,60,240,60);
	LCD_DrawLine(0,120,240,120);
	LCD_DrawLine(0,180,240,180);

	POINT_COLOR=RED;

	LCD_Show_Image(10,130,40,40,gImage_battery);
	
	LCD_Show_Image(10,190,40,40,gImage_smoke);


}

void show_smoke_gui_wifi()
{

	BACK_COLOR=GRAY;
	LCD_Fill(0,0,240,60,GRAY);
	POINT_COLOR=WHITE;
//	show_title("WIFI TO ALIYUN");
		__show_title("WIFI NODE_1");

	BACK_COLOR=WHITE;
	POINT_COLOR=LIGHTBLUE;
	LCD_DrawLine(0,60,240,60);
	LCD_DrawLine(0,120,240,120);
	LCD_DrawLine(0,180,240,180);

	POINT_COLOR=RED;

	LCD_Show_Image(10,130,40,40,gImage_battery);
	
	LCD_Show_Image(10,190,40,40,gImage_smoke);


}

void show_acc_gui()   //加速度传感器
{

	BACK_COLOR=GRAY;
	LCD_Fill(0,0,240,60,GRAY);
	POINT_COLOR=WHITE;
//	show_title("WIFI TO ALIYUN");
		__show_title("WIFI NODE_1");

	BACK_COLOR=WHITE;
	POINT_COLOR=LIGHTBLUE;
	LCD_DrawLine(0,60,240,60);
	LCD_DrawLine(0,120,240,120);
	LCD_DrawLine(0,180,240,180);

	POINT_COLOR=RED;

	LCD_Show_Image(10,130,40,40,gImage_battery);
	
	//LCD_Show_Image(10,190,40,40,gImage_smoke);


}


void show_wifi_state(uint8_t wifi_sta)
{
	if(wifi_sta)
	{
		LCD_Show_Image(10,70,40,40,gImage_wifi_on);
		LCD_ShowString(40+32,74,240,32,32,"CONNECT");	
	}
	else{
		LCD_Show_Image(10,70,40,40,gImage_wifi_off);
	  LCD_ShowString(40+32,74,240,32,32,"DISCONNECT");	
	}
}

//显示wifi标题及划线
void show_Wifi_title()
{
		BACK_COLOR=GRAY;
	LCD_Fill(0,0,240,60,GRAY);
	POINT_COLOR=WHITE;
//	show_title("WIFI TO ALIYUN");
		__show_title("WIFI NODE_1");

	BACK_COLOR=WHITE;
	POINT_COLOR=LIGHTBLUE;
	LCD_DrawLine(0,60,240,60);
	LCD_DrawLine(0,120,240,120);
	LCD_DrawLine(0,180,240,180);

	POINT_COLOR=RED;
}

void show_wifi_connect()
{
	LCD_Show_Image(10,70,40,40,gImage_wifi_on);
	LCD_ShowString(40+32,74,240,32,32,"CONNECT");	
}

void show_wifi_disconnect()
{
	LCD_Show_Image(10,70,40,40,gImage_wifi_off);
	LCD_ShowString(40+32,74,240,32,32,"DISCONNECT");	
}

void show_battery()
{
		LCD_Show_Image(10,130,40,40,gImage_battery);
}