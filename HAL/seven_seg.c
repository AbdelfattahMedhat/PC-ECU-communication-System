#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "seven_seg_interface.h"
#include "seven_seg_private.h"





void seven_seg_init(void)
{
}
void seven_seg_Write_number(u8 num)
{   
 	DIO_WritePin(PIND0,LOW);
 	DIO_WritePort(PC,seven_seg_char[num%10]);
	 //DIO_WritePin(PIND0,HIGH);
 	
	 DIO_WritePort(PC,0);
	DIO_WritePin(PIND1,LOW);
	DIO_WritePort(PC,seven_seg_char[num/10]);
	//DIO_WritePin(PIND1,HIGH);
}
void seven_seg_Write_number_hex(u8 num)
{
	
}