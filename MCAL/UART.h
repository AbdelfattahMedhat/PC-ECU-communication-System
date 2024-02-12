#ifndef UART_H_
#define UART_H_

#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
/*********************************************************************************/

#define UART_BUFFER   UDR
#define F_CPU         8000000

/************************************ Enums ************************************/
// Commonly used baud rates
typedef enum {
	BAUD_4800   = 4800,
	BAUD_9600   = 9600,
	BAUD_19200  = 19200,
	BAUD_38400  = 38400,
	BAUD_57600  = 57600,
	BAUD_115200 = 115200
} UART_BaudRate;

// UART frame data size
typedef enum {
	UART_DATA_5_BIT = 0b00000000,
	UART_DATA_6_BIT = 0b00000010,  
	UART_DATA_7_BIT = 0b00000100, 
	UART_DATA_8_BIT = 0b00000110  
} UART_DataSize;

// UART parity mode
typedef enum {
	UART_PARITY_DISABLED = 0b00000000,
	UART_PARITY_EVEN     = 0b00100000,
	UART_PARITY_ODD      = 0b00110000
} UART_ParityMode;

// UART stop bits
typedef enum {
	UART_STOP_1_BIT = 0b00000000,
	UART_STOP_2_BIT = 0b00001000
} UART_StopBits;

/************ UART configuration struct ************/
typedef struct {
	UART_BaudRate	baudRate;
	UART_DataSize   dataSize;
	UART_ParityMode parityMode;
	UART_StopBits   stopBits;
} UART_Config;

extern const UART_Config config;

/************************************ Declaration ************************************/

void UART_Init(void);


void UART_Send(u8 data);
u8   UART_Receive(void);
u8   UART_ReceivePerodic(u8*pdata);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

void UART_SendNoBlock(u8 data);
u8   UART_ReceiveNoBlock(void);

#endif /* UART_H_ */