#include "STDTYPES.h"
#include "MemMap.h"
#include "Utils.h"
#include "USART.h"
#include "LCD_interface.h"


/************************************************************************/
/*                     GLOBAL FLAGS                                     */
/************************************************************************/
// static u8 volatile Txc_flag=0;
// static u8 volatile Rxc_flag=0;
// static u8 volatile UDRE_flag=0;

/************************************************************************/
/*                       pointers to functions                          */
/************************************************************************/

static void (*USART_RX_FUNC)(void) =NULLPTR;
static void (*USART_TX_FUNC)(void) =NULLPTR;
static void (*USART_UDRE_FUNC)(void) =NULLPTR;

/************************************************************************/
/*                         functions                                    */
/************************************************************************/

void USART_init(u32 baud_rate,char_size_t size,parity_mode_t parity_m,stop_bits_t stop_b)
{
	/* Baud Rate */
	u8 baud =F_CPU/16ul/baud_rate-1;
	UBRRL=baud;
	//UBRRH=baud>>8; needed if baud size bigger than 1 byte
	/* frame form */
 	USART_char_size(size);
 	UASRT_parity_mode(parity_m);
 	USART_stop_bits(stop_b);
	 
	
}

/**********************communicate withOUT buffer*************************************/
/*
void USART_transmit(u8 Data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=Data;
}

u8 USART_recive(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}
*/


/************************************************************************/
/*                    interrupts control                                */
/************************************************************************/

void USART_RX_complete_int_En(void)
{
	SET_BIT(UCSRB,RXCIE);
}
void USART_RX_complete_int_Dis(void)
{
	CLR_BIT(UCSRB,RXCIE);
}
void USART_TX_complete_int_En(void)
{
	SET_BIT(UCSRB,TXCIE);
}
void USART_TX_complete_int_Dis(void)
{
	CLR_BIT(UCSRB,TXCIE);
}
void USART_Data_reg_emp_int_En(void)
{
	SET_BIT(UCSRB,UDRIE);
}
void USART_Data_reg_emp_int_Dis(void)
{
	CLR_BIT(UCSRB,UDRIE);
}
/*********************************************/


void Uart_Interrupt(Uart_Interruprt_t type, u8 state)
{
	UCSRB &= ~(1<<(type+Interrupt_Shift));
	UCSRB |= (state<<(type+Interrupt_Shift));
}



/************************************************************************/
/*                      RX and TX control                               */
/************************************************************************/
void USART_RX_En(void)
{
	SET_BIT(UCSRB,RXEN);
}
void USART_RX_Dis(void)
{
	CLR_BIT(UCSRB,RXEN);
}
void USART_TX_En(void)
{
	SET_BIT(UCSRB,TXEN);
}
void USART_TX_Dis(void)
{
	CLR_BIT(UCSRB,TXEN);
}
/************************************************************************/
/*                         frame formation                              */
/************************************************************************/
void UASRT_parity_mode(parity_mode_t mode)
{
	UCSRC&=~(3<<UPM);
	UCSRC|=mode<<UPM;
}

void USART_stop_bits(stop_bits_t bits)
{
	UCSRC&=~(1<<USBS);
	UCSRC|=bits<<USBS;
}

void USART_char_size(char_size_t size)
{
	if(size<_9_BITS)
	{
		UCSRC|=size<<UCSZ;	
	}
	else
	{
		UCSRC|=_8_BITS<<UCSZ;
		SET_BIT(UCSRB,UCSZ2);
	}

}
/************************************************************************/
/*                    call back functions                               */
/************************************************************************/
void ISR_USART_Recive_complete_set_callback(void(*func)(void))
{	
	USART_RX_FUNC =func;	
}
void ISR_USART_Transmit_complete_set_callback(void(*func)(void))
{
	USART_TX_FUNC =func;	
}

void ISR_USART_Data_Reg_empty_set_callback(void(*func)(void))
{
	USART_UDRE_FUNC=func;
}
/************************************************************************/
/*                        ISR functions                                 */
/************************************************************************/	
/*
ISR(UART_RX_vect)
{
	
	if(USART_RX_FUNC!=NULLPTR)
		USART_RX_FUNC();
}

ISR(UART_TX_vect)
{
	if(USART_TX_FUNC!=NULLPTR)
		USART_TX_FUNC();
}

ISR(UART_UDRE_vect)
{
	if(USART_UDRE_FUNC!=NULLPTR)
		USART_UDRE_FUNC();
}

*/