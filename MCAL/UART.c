#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "UART.h"
/***********************************************************************************************/

static void (*ptr_Empty)   (void) = NULLPTR;
static void (*UART_RX_Fptr)(void) = NULLPTR;
static void (*UART_TX_Fptr)(void) = NULLPTR;

/***********************************************************************************************/
void UART_Init(void)
{
	// Set The Baud Rate
	u16 ubrr = (F_CPU / ((u32)16 * (u32)config.baudRate) ) - 1;
	UBRRH	 = (u8)(ubrr >> 8);
	UBRRL    = (u8)(ubrr);
	
	// Initialize UART using struct configuration values 			
	UCSRC = (1 << URSEL) | config.dataSize | config.parityMode | config.stopBits;

	// Normal Speed
	CLR_BIT(UCSRA,U2X);
	
	// Enable UART 
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);	
}


void UART_Send(u8 data)
{
	//check the flag -- busy wait
	while(!READ_BIT(UCSRA,UDRE));
	
	UART_BUFFER=data;	
}

u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));

	return UART_BUFFER;
}

u8 UART_ReceivePerodic(u8* pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UART_BUFFER;
		return 1;		
	}
		return 0;
}


void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}
/**************************************** Interrupt Control *****************************************/
void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}
/**************************************** CallBack *****************************************/

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

/**************************************** ISRs *****************************************/
ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}

