


#ifndef USART_SERVICE_H_
#define USART_SERVICE_H_

#define CHAR_SIZE_BASE 5

#define DEFAULT_USART_PIN PINC2
#define DEFAULT_USART_CHAR_SIZE (_8_BITS+CHAR_SIZE_BASE)
#define DEFAULT_USART_PARITY PARITY_DISABLE
#define DEFAULT_USART_STOP_BITS ONE_BIT


typedef struct 
{
	DIO_Pin_type pin;
	char_size_t char_size;
	parity_mode_t parity_m;
	stop_bits_t stop_b;
}Frame;

void implement_USART_frame(DIO_Pin_type pin,char_size_t c_size,parity_mode_t parity_mode,stop_bits_t s_bit);	

void transmit_USART_frame(u8 character);
/***************************************************/
#define LITTLE   1
#define BIG     0
void USART_SendString(u8*str);
void USART_ReceiveString(u8*str);

void USART_SendNumber(u32 num);
u32 USART_RecieveNumber(void);
u8 endian_check(void);

void USART_SendStringCheckSum(u8*str);

u8 USART_ReceiveStringCheckSum(u8*str);

/************************************************************************/
/*                          USART_CHAR                                  */
/************************************************************************/
void USART_send_buffer(u8 Data);

u8 USART_recive_buffer(void);
/************************************************************************/
/*                      USART_STRING                                    */
/************************************************************************/
void USART_sendstr_buffer(u8* Data);

void USART_sendstr_Runnable(void);



void USART_receivestring_init(void);

Error_t USART_recivestr_getter(u8**Datastr);

/************************************************************************/
/*                        ISR_functions                                 */
/************************************************************************/
void Recieve_complete_function(void);

void send_complete_function(void);

#endif /* USART_SERVICE_H_ */