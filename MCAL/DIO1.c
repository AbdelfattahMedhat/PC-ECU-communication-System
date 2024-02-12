

#include "StdTypes.h"
#include "Registers.h"
#include "Utils.h"


#include "DIO_Interface.h"



void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status)
{
	switch(status)
	{
		case OUTPUT:
		switch(pin/8)
		{
			case PA:
			SET_BIT( DDRA,pin%8);
			CLR_BIT(PORTA,pin%8);
			break;
			case PB:
			SET_BIT( DDRB,pin%8);
			CLR_BIT(PORTB,pin%8);
			break;
			case PC:
			SET_BIT( DDRC,pin%8);
			CLR_BIT(PORTC,pin%8);
			break;
			case PD:
			SET_BIT( DDRD,pin%8);
			CLR_BIT(PORTD,pin%8);
			break;		
		}
		break;
		case INFREE:
		switch(pin/8)
		{
			case PA:
			CLR_BIT(DDRA,pin%8);
			CLR_BIT(PORTA,pin%8);
			break;
			case PB:
			CLR_BIT(DDRB,pin%8);
			CLR_BIT(PORTB,pin%8);
			break;
			case PC:
			CLR_BIT(DDRC,pin%8);
			CLR_BIT(PORTC,pin%8);
			break;
			case PD:
			CLR_BIT(DDRD,pin%8);
			CLR_BIT(PORTD,pin%8);
			break;
		}
		break;
		
		case INPULL:
		switch(pin/8)
		{
			case PA:
			CLR_BIT(DDRA,pin%8);
			SET_BIT(PORTA,pin%8);
			break;
			case PB:
			CLR_BIT(DDRB,pin%8);
			SET_BIT(PORTB,pin%8);
			break;
			case PC:
			CLR_BIT(DDRC,pin%8);
			SET_BIT(PORTC,pin%8);
			break;
			case PD:
			CLR_BIT(DDRD,pin%8);
			SET_BIT(PORTD,pin%8);
			break;
		}
		break;
	}
}



void DIO_WritePin(DIO_Pin_type pin,DIO_PinVoltage_type volt)
{
	if (volt==HIGH)
	{
		switch(pin/8)
		{
			case PA:
			
			SET_BIT(PORTA,pin%8);
			break;
			case PB:
			
			SET_BIT(PORTB,pin%8);
			break;
			case PC:
			
			SET_BIT(PORTC,pin%8);
			break;
			case PD:
			
			SET_BIT(PORTD,pin%8);
			break;
		}
		
	}
	else if (volt==LOW)
	{
		switch(pin/8)
		{
			case PA:
			
			CLR_BIT(PORTA,pin%8);
			break;
			case PB:
			
			CLR_BIT(PORTB,pin%8);
			break;
			case PC:
			
			CLR_BIT(PORTC,pin%8);
			break;
			case PD:
			
			CLR_BIT(PORTD,pin%8);
			break;
		}
	}
	else
	{
		/* do nothing */
	}
	
}


DIO_PinVoltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_PinVoltage_type volt=LOW;
	
	switch(pin/8)
	{
		case PA:
		
		volt=READ_BIT(PINA,pin%8);
		break;
		case PB:
		
		volt=READ_BIT(PINB,pin%8);
		break;
		case PC:
		
		volt=READ_BIT(PINC,pin%8);
		break;
		case PD:
		
		volt=READ_BIT(PIND,pin%8);
		break;
	}
	
	return volt;
}
void DIO_TogglePin(DIO_Pin_type pin)
{
	switch(pin/8)
	{
		case PA:
		TOG_BIT(PORTA,pin%8);
		break;
		
		case PB:
		TOG_BIT(PORTB,pin%8);
		break;
		
		case PC:
		TOG_BIT(PORTC,pin%8);
		break;
		 
		case PD:
		TOG_BIT(PORTD,pin%8);
		break; 
	}
}
void DIO_WritePort(DIO_Port_type port,u8 value)
{
	switch(port)
	{
		case PA:
		DDRA=value;
		PORTA=value;
		break;
		
		case PB:
		DDRB=value;
		PORTB=value;
		break;
		
		case PC:
		DDRC=value;
		PORTC=value;
		break;
		
		case PD:
		DDRD=value;
		PORTD=value;
		break;
	}
}
u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 Read=0;
	switch(port)
	{
		case PA:
		Read=PINA;
		break;
		
		case PB:
		Read=PINB;
		break;
		
		case PC:
		Read=PINC;
		break;
		
		case PD:
		Read=PIND;
		break;
	}
	return Read;
}

// Error_t DIO_ReadPin(DIO_Port_type port,u8 pin_num,DIO_PinVoltage_type*Pvolt)
// {
// 	if (Pvolt==NULLPTR)
// 	{
// 		return NULL_PTR_ERROR;
// 	}
// 	else if ((port>PD)||(pin_num>7))
// 	{
// 	 return OUT_OF_RANGE;	
// 	}
// 	else
// 	{
// 		switch(port)
// 		{
// 			case PA:
// 			
// 			*Pvolt=READ_BIT(PINA,pin_num);
// 			break;
// 			case PB:
// 			
// 			*Pvolt=READ_BIT(PINB,pin_num);
// 			break;
// 			case PC:
// 			
// 			*Pvolt=READ_BIT(PINC,pin_num);
// 			break;
// 			case PD:
// 			
// 			*Pvolt=READ_BIT(PIND,pin_num);
// 			break;
// 		}
// 		return OK;
// 	}
// }



void DIO_Init(void)
{
// 	DIO_Pin_type i;
// 	for (i=PINA0;i<TOTAL_PINS;i++)
// 	{
// 		DIO_InitPin(i,OUTPUT);
// 	}
}