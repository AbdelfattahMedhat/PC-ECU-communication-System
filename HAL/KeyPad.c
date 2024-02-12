#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "LCD_interface.h"
#include "KeyPAd_interface.h"
#include "Utils.h"
extern const u8 KeypadCols[];
extern const u8 KeypadRows[];
extern const u8 keypadChar[][COLUMNS];

void keypad_init(void)
{
	for(u8 i=0;i<ROWS;i++)
	{
		DIO_WritePin(KeypadRows[i],HIGH);
	}
}
u8 keypad_getnumber(void)
{
	u8 i,j,character=NO_KEY;
	for(i=0;i<ROWS;i++)
	{
		DIO_WritePin(KeypadRows[i],LOW);
		for(j=0;j<COLUMNS;j++)
		{
			if(DIO_ReadPin(KeypadCols[j])==LOW)
			{
				  _delay_ms(DECOUNCING_MS);
			      if(DIO_ReadPin(KeypadCols[j])==LOW)
				  {
					  character=keypadChar[i][j];
				  }
			}
		}
		DIO_WritePin(KeypadRows[i],HIGH);
	}
	return character;
}
u8* KeyPad_scan_string(u8 size)
{
	static u8 str[DEFAULT_STR_LENGTH]={0};
		u8 temp=0;
		u8 i=0;
	while(temp!='=' && i<size)
	{
		temp=keypad_getnumber();
		if(temp>='0' && temp<='9')
		{
			LCD_writechar('*');
			str[i]=temp;
			i++;
		}
	}
	return str;
}