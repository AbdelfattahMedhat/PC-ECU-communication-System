#include "STDTYPES.h"
#include "MemMap.h"
#include "KeyPAd_interface.h"
#include "LCD_interface.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "interrupt_interface.h"
#include "Timers.h"
#include "USART.h"
#include "Utils.h"
#include "UART.h"

#define STANDERD_DELAY 0


int main(void)
{
 	DIO_Init();
	LCD_init();
 	RGB_init();
 	
	UART_Init();
	
	u8 x='a';
	
	while (1)
	{
		UART_Send(x);
		_delay_ms(200);
		x++;
		
	}
}

