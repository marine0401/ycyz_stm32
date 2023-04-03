#ifndef __GUI_H__
#define __GUI_H__
#include "sys.h"



void show_temp_gui();
void show_Wifi_title();
void show_wifi_connect();
void show_wifi_disconnect();
void show_battery();

void show_smoke_gui();
void show_wifi_state(uint8_t wifi_sta);

void show_acc_gui();   //加速度传感器
void show_smoke_gui_wifi();

void show_temp_gui_nbiot();  //nb传温度
#endif