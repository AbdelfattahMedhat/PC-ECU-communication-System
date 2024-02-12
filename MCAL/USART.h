

#ifndef USART_H_
#define USART_H_

#define MAX_DATA_NUM 15

/************************************************************************/
/*                  send and receive buffers                            */
/************************************************************************/


/************************************************************************/
/*                           TYPES                                      */
/************************************************************************/
typedef enum
{
	Empty,
	Recieve,
	Tranmit
}Uart_Interruprt_t;



typedef enum
{
	PARITY_DISABLE,
	PARITY_EVEN=2,
	PARITY_ODD
}parity_mode_t;

typedef enum
{
	ONE_BIT,
	TWO_BITS
}stop_bits_t;

typedef enum
{
	_5_BITS,
	_6_BITS,
	_7_BITS,
	_8_BITS,
	_9_BITS
}char_size_t;


/************************************************************************/
/*                           SHIFTS                                     */
/************************************************************************/
#define Interrupt_Shift 5
#define UPM 4
#define USBS 3
#define UCSZ 1
/************************************************************************/
/*                       #STATES                                        */
/************************************************************************/
#define ENABLE 1
#define DISABLE 0
/************************************************************************/
/*                       #MAIN_FUNC                                     */
/************************************************************************/
void USART_init(u32 baud_rate,char_size_t size,parity_mode_t parity_m,stop_bits_t stop_b);
void USART_transmit(u8 Data);
u8 USART_recive(void);
/************************************************************************/
/*                      receive int func                                */
/************************************************************************/
void Recieve_complete_function(void);
/************************************************************************/
/*                                   UCSRB                              */
/************************************************************************/
void USART_RX_complete_int_En(void);
void USART_RX_complete_int_Dis(void);
void USART_TX_complete_int_En(void);
void USART_TX_complete_int_Dis(void);
void USART_Data_reg_emp_int_En(void);
void USART_Data_reg_emp_int_Dis(void);
void Uart_Interrupt(Uart_Interruprt_t type, u8 state);
void USART_RX_En(void);
void USART_RX_Dis(void);
void USART_TX_En(void);
void USART_TX_Dis(void);
/************************************************************************/
/*                        UCSRC(frame formation)                        */
/************************************************************************/
void UASRT_parity_mode(parity_mode_t mode);
/*************************************************************************/

void USART_stop_bits(stop_bits_t bits);
/*************************************************************************/

void USART_char_size(char_size_t size);
/************************************************************************/
/*                           ISR func                                   */
/************************************************************************/
void ISR_USART_Recive_complete_set_callback(void(*func)(void));
void ISR_USART_Transmit_complete_set_callback(void(*func)(void));
void ISR_USART_Data_Reg_empty_set_callback(void(*func)(void));


#endif /* USART_H_ */