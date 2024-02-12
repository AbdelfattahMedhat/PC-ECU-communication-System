#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "USART.h"
#include "USART_service.h"
#include "Timers.h"
#include "LCD_interface.h"

/************************************************************************/
/*                        frame struct                                  */
/************************************************************************/	
Frame frame={DEFAULT_USART_PIN,DEFAULT_USART_CHAR_SIZE,DEFAULT_USART_PARITY,DEFAULT_USART_STOP_BITS}; 
/************************************************************************/
/*                      functions                                       */
/************************************************************************/
void implement_USART_frame(DIO_Pin_type pin,char_size_t c_size,parity_mode_t parity_mode,stop_bits_t s_bit)
{
	frame.pin=pin;
	frame.char_size=c_size+CHAR_SIZE_BASE;
	frame.parity_m=parity_mode;
	frame.stop_b=s_bit;
}

void transmit_USART_frame(u8 character)
{
	u8 ones_counter=0;
/********************************start bit******************************************/
	DIO_WritePin(frame.pin,LOW);
	_delay_us(98); // DELAY FOR 104 TOTAL TIME
/********************************data bits***************************************/
	for(u8 i=0;i<frame.char_size;i++)
	{
		DIO_WritePin(frame.pin,READ_BIT(character,i)); 
		ones_counter+=READ_BIT(character,i); // counter for parity check
		_delay_us(95);  // DELAY FOR 104 TOTAL TIME
	}
/*******************************parity bit*******************************************/
	switch(frame.parity_m)                                 // parity bit
	{
		case PARITY_DISABLE : break;
		case PARITY_EVEN : if(ones_counter%2==0)
								{
									DIO_WritePin(frame.pin,LOW);
								}
						   else
								{
									DIO_WritePin(frame.pin,HIGH);
								}
								_delay_us(97);
								break;
		case PARITY_ODD : if(ones_counter%2==0)
								{
									DIO_WritePin(frame.pin,HIGH);
								}
						   else
								{
									DIO_WritePin(frame.pin,LOW);
								}
								_delay_us(97);
								break;
	}
	/*********************************stop bits***************************************/
	DIO_WritePin(frame.pin,HIGH); 
	_delay_us(98);
	if(frame.stop_b==TWO_BITS)
	{
		DIO_WritePin(frame.pin,HIGH);
		_delay_us(98);		// additional stop bit
	}
}
/*********************session work*****************************/
void USART_SendString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		USART_transmit(str[i]);
	}
		
}


void USART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=USART_recive();
	for(;str[i]!=13;)
	{
		i++;
		str[i]=USART_recive();
	}
	str[i]=0;
	
}

void USART_SendNumber(u32 num)
{
	USART_transmit((u8)num);
	USART_transmit((u8)(num>>8));
	USART_transmit((u8)(num>>16));
	USART_transmit((u8)(num>>24));
	/*u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);*/
	
}

u32 USART_RecieveNumber(void)
{
	u32 num;
	
	u8 b0=USART_recive();
	u8 b1=USART_recive();
	u8 b2=USART_recive();
	u8 b3=USART_recive();
	
	num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	
// 	u8*p=&num;
// 	p[0]=USART_recive();
// 	p[1]=USART_recive();
// 	p[2]=USART_recive();
// 	p[3]=USART_recive();
	
	return num;
	
}



u8 endian_check(void)
{
	u32 num=1;
	u8*p=&num;
	if(*p==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u32 endian_convert(u32 num)
{
	u8*p=&num;
	u8 temp;
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	temp=p[1];
	p[1]=p[2];
	p[2]=temp;
	
	num=(num>>24)|(num<<24)|((num>>8)&0x0000ff00)|((num<<8)&0x00ff0000);
	return num;
	
}

u16 endian_convert16(u16 num)
{
	num=num>>8|num<<8;
	return num;
	
}


void USART_SendStringCheckSum(u8*str)
{
	u8 i;
	u16 sum=0;
	u8 len;
	for (i=0;str[i];i++)
	{
		sum=sum+str[i];
	}
	len=i;
	USART_transmit(len);
	for (i=0;str[i];i++)
	{
		USART_transmit(str[i]);
	}
	USART_transmit((u8)sum);
	USART_transmit((u8)(sum>>8));
}

u8 USART_ReceiveStringCheckSum(u8*str)
{
	u8 len,i,b1,b0;
	u16 sumCalc=0,sumRec;
	len=USART_recive();
	for (i=0;i<len;i++)
	{
		str[i]=USART_recive();
		sumCalc+=str[i];
	}
	b0=USART_recive();
	b1=USART_recive();
	sumRec=(u16)b0|((u16)b1<<8);
	if (sumRec==sumCalc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}
/******************************************************/

/************************************************************************/
/*                        global index                                  */
/************************************************************************/
static u8 send_buffer_index=0;
static u8 receive_buffer_index=0;

static volatile u8 send_buffer_index_TXC=0;
static volatile u8 receive_buffer_index_RXC=0;
/**********************************************************************/
static u8 send_buffer[MAX_DATA_NUM]={0};
static u8 receive_buffer[MAX_DATA_NUM]={0};
/***********************************************************************/
static u8* sendstr_buffer[MAX_DATA_NUM]={0};
static u8 receivestr_buffer[MAX_DATA_NUM][10];
/***************************ISR Functions***********************************/	




/***********************SEND strings**********************************/
void USART_sendstr_buffer(u8* Data)
{
	 // set call back functions
	 ISR_USART_Transmit_complete_set_callback(send_complete_function);
	
	sendstr_buffer[send_buffer_index]=Data;
	send_buffer_index++;
	
	if (send_buffer_index==MAX_DATA_NUM)
	{
		send_buffer_index=0;
	}
}

void send_complete_function(void)
{
	if(send_buffer_index_TXC != send_buffer_index)
	{
		UDR=send_buffer[send_buffer_index_TXC];
		send_buffer_index_TXC++;
		if (send_buffer_index_TXC==MAX_DATA_NUM)
		{
			send_buffer_index_TXC=0;
		}
	}	
}


void USART_sendstr_Runnable(void)
{
	static u8 start_flag=0;
	static u8 i=0;
	if (send_buffer_index_TXC!=send_buffer_index)
	{
		if(start_flag==1)
		{
			if(READ_BIT(UCSRA,UDRE))
			{
				if(sendstr_buffer[send_buffer_index_TXC][i])
				{
					UDR=sendstr_buffer[send_buffer_index_TXC][i];
					i++;
				}
				else
				{
					send_buffer_index_TXC++;
					i=0;
				}
			}
			if (send_buffer_index_TXC==MAX_DATA_NUM)
			{
				send_buffer_index_TXC=0;
			}
		}
		else
		{
			UDR=sendstr_buffer[send_buffer_index_TXC][i];
			i++;
			start_flag=1;
		}
	}
	
}
/***********************************receive strings**************************************/


void USART_receivestring_init(void)
{
	ISR_USART_Recive_complete_set_callback(Recieve_complete_function);
}


/*
Error_t USART_recivestr_getter(u8 * Datastr)
{
	Error_t error=OK;
	if (receive_buffer_index!=receive_buffer_index_RXC)
	{
		
		if(Datastr!=NULLPTR)
		{
			Datastr= receivestr_buffer[receive_buffer_index];
			receive_buffer_index++;
			if(receive_buffer_index==MAX_DATA_NUM)
			{
				receive_buffer_index=0;
			}
		}
		else
		{
			error=NULL_PTR_;
		}
	}
	else
	{
		error=EMPTY;
	}
	
	
	return error;
}*/

Error_t USART_recivestr_getter(u8**Datastr)
{
    Error_t error=OK;
	if (receive_buffer_index!=receive_buffer_index_RXC)
	{
			*Datastr= receivestr_buffer[receive_buffer_index];
			receive_buffer_index++;
			if(receive_buffer_index==MAX_DATA_NUM)
			{
				receive_buffer_index=0;
			}
	}
	else
	{
		error=EMPTY;
	}
	return error;
}

void Recieve_complete_function(void)
{
	static u8 i=0;
	u8 temp=UDR;
	if (temp!=13)
	{
		LCD_writechar(temp);
		receivestr_buffer[receive_buffer_index_RXC][i]=temp;
		i++;
			
	}
	else
	{
		receive_buffer_index_RXC++;
		i=0;
	}
	
	if (receive_buffer_index_RXC==MAX_DATA_NUM)
	{
		receive_buffer_index_RXC=0;
	}
}

/*****************************************character**********************************/
void USART_send_buffer(u8 Data)
{
	static u8 start_flag=0;
	
	if (start_flag==0)
	{
		UDR=Data;
		start_flag=1;
	}
	else
	{
		send_buffer[send_buffer_index]=Data;
		send_buffer_index++;
		
		if(send_buffer_index==MAX_DATA_NUM)
		{
			send_buffer_index=0;
		}
	}
	
	
}

u8 USART_recive_buffer(void)
{
	u8 temp=receive_buffer[receive_buffer_index];
	receive_buffer_index++;
	if(receive_buffer_index==MAX_DATA_NUM)
	{
		receive_buffer_index=0;
	}
	return temp;
}