#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "Utils.h"
#include "led.h"


void LED_ON(u8 led_num)
{
	if(led_num<LED_NUM)
	DIO_WritePin(led_num+BASE_PIN,HIGH);
}

void LED_OFF(u8 led_num)
{
	if(led_num<LED_NUM)
	DIO_WritePin(led_num+BASE_PIN,LOW);
}