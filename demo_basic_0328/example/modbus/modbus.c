/**
Modbus slave implementation for STM32 HAL under FreeRTOS.
(c) 2017 Viacheslav Kaloshin, multik@multik.org
Licensed under LGPL. 
**/

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "modbus.h"
#include "oxygen/oxygen.h"
// If you want directly send to usb-cdc
// #include "usbd_cdc_if.h"

//osMessageQId ModBusInHandle;
//osMessageQId ModBusOutHandle;
//osThreadId ModBusTaskHandle;

uint16_t mb_reg[ModBusRegisters];

// Here is actual modbus data stores
uint8_t mb_buf_in[256];
uint8_t mb_buf_in_count;
uint8_t mb_addr;
uint8_t mb_buf_out[256];
uint8_t mb_buf_out_count;

void ModBus_Init(void)
{
  mb_buf_in_count=0;
  mb_addr=247; // by default maximum possible adrress
  mb_buf_out_count=0;
  for(int i=0;i<ModBusRegisters;i++) 
  {
    mb_reg[i]=0;
  }
}

void ModBus_SetAddress(uint8_t addr)
{
  mb_addr = addr;
}



// parse something in incoming buffer 
void ModBusParse(void)
{
    if(mb_buf_in_count==0) // call as by mistake on empty buffer?
    {
      return;
    }
    
    if(mb_buf_in[0] != mb_addr) // its not our address!
    {
      return;
    }
    // check CRC
    if(CRC16_IN()==0)
    {
      mb_buf_out_count = 0;
      uint16_t st,nu;
      uint8_t func = mb_buf_in[1];
      uint8_t i;
			uint8_t addr_t;
      switch(func)
      {
        case 3:
          // read holding registers. by bytes addr func starth startl totalh totall
          //st=mb_buf_in[2];
          //nu=mb_buf_in[4]*256+mb_buf_in[5];
					if(mb_buf_in[2] == 0x10){
						OxygenSensor.Temperature = (uint8_t)mb_buf_in[5]*256+(uint8_t)mb_buf_in[6];
						
					if(mb_buf_in[18]&0x1)	
						is_oxygen_updated = 1;
						OxygenSensor.DissolvedOxygen = (uint8_t)mb_buf_in[11]*256 + (uint8_t)mb_buf_in[12];
						OxygenSensor.DissolvedOxygenRate = (uint8_t)mb_buf_in[7]*256+(uint8_t)mb_buf_in[8];
					}
				
//          if( (st+nu) < 32) // dont ask more, that we has!
//            {
//							addr_t=st;
//							for(i=st;i<(st+nu);i++)
//							{
//								mb_reg[i]=mb_buf_in[addr_t]*256+mb_buf_in[addr_t+1];
//								addr_t++;
//								addr_t++;
//							}
//            }
//            else
//            {

//            }
          break;
        case 16: 
          // write holding registers. by bytes addr func starth startl totalh totall num_bytes regh regl ...
//          st=mb_buf_in[2]*256+mb_buf_in[3];
//          nu=mb_buf_in[4]*256+mb_buf_in[5];
//          if( (st+nu) > ModBusRegisters) // dont ask more, that we has!
//            {
//              mb_buf_out[mb_buf_out_count++]=mb_addr;
//              mb_buf_out[mb_buf_out_count++]=func+0x80;
//              mb_buf_out[mb_buf_out_count++]=2;
//            }
//            else
//              { // ATTN : skip num_bytes
//              for(i=0;i<nu;i++)
//                {
//                  mb_reg[st+i]=mb_buf_in[7+i*2]*256+mb_buf_in[8+i*2];
//                }
//              mb_buf_out[mb_buf_out_count++]=mb_addr;
//              mb_buf_out[mb_buf_out_count++]=func;
//              mb_buf_out[mb_buf_out_count++]=mb_buf_in[2]; // how many registers ask, so many wrote
//              mb_buf_out[mb_buf_out_count++]=mb_buf_in[3];
//              mb_buf_out[mb_buf_out_count++]=mb_buf_in[4];
//              mb_buf_out[mb_buf_out_count++]=mb_buf_in[5];
//            }
          break;
        default:  
          // Exception as we does not provide this function
//          mb_buf_out[mb_buf_out_count++]=mb_addr;
//          mb_buf_out[mb_buf_out_count++]=func+0x80;
//          mb_buf_out[mb_buf_out_count++]=1;
          break;
      }
      
//      CRC16_OUT();
//      
//     // If you want directly to USB-CDC 
//     //CDC_Transmit_FS(&mb_buf_out[0], mb_buf_out_count);
//     for(int i=0;i<mb_buf_out_count;i++)
//        {
//          osMessagePut(ModBusOutHandle,mb_buf_out[i],0);
//        }
    }
    // Ok, we parsed buffer, clean up
    mb_buf_in_count=0;
    //mb_buf_out_count=0;
}

// set value of register
void ModBus_SetRegister(uint8_t reg,uint16_t value)
{
  if(reg<ModBusRegisters)
  {
    mb_reg[reg]=value;
  }
}
// grab value of register
uint16_t ModBus_GetRegister(uint8_t reg)
{
  if(reg<ModBusRegisters)
  {
    return mb_reg[reg];
  }
  return 0;
}


// Calculate CRC for outcoming buffer
// and place it to end.
void CRC16_OUT(void)
{
  uint16_t crc = 0xFFFF;
  uint16_t pos = 0;
  uint8_t i =0;
  uint8_t lo =0;
  uint8_t hi =0;
  
  for (pos = 0; pos < mb_buf_out_count; pos++)
  {
    crc ^= mb_buf_out[pos];

  for (i = 8; i != 0; i--)
    {
    if ((crc & 0x0001) != 0)
      {
      crc >>= 1;
      crc ^= 0xA001;
      }
    else
      crc >>= 1;
    }
  }
  lo = crc & 0xFF;
  hi = ( crc >> 8 ) & 0xFF;
  
  mb_buf_out[mb_buf_out_count++] = lo;
  mb_buf_out[mb_buf_out_count++] = hi;
}

// Calculate CRC fro incoming buffer
// Return 0 - if CRC is correct, overwise return 0 
uint8_t CRC16_IN(void)
{
  uint16_t crc = 0xFFFF;
  uint16_t pos = 0;
  uint8_t i =0;
  uint8_t lo =0;
  uint8_t hi =0;
  
  for (pos = 0; pos < mb_buf_in_count-2; pos++)
  {
    crc ^= mb_buf_in[pos];

  for (i = 8; i != 0; i--)
    {
    if ((crc & 0x0001) != 0)
      {
      crc >>= 1;
      crc ^= 0xA001;
      }
    else
      crc >>= 1;
    }
  }
  lo = crc & 0xFF;
  hi = ( crc >> 8 ) & 0xFF;
  if( (mb_buf_in[mb_buf_in_count-2] == lo) && 
       (mb_buf_in[mb_buf_in_count-1] == hi) )
    {
      return 0;
    }
  return 1;
}
