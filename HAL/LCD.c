#include "STDTYPES.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_interface.h"
#include "LCD_Cfg.h"

static void Write_ins(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void write_data(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


void LCD_init(void)
{
	_delay_ms(40);
	Write_ins(0x02);
	Write_ins(0x28);
	Write_ins(0x0c);//cursor modes en:0x0e blink:0x0f
	Write_ins(0x01);
	_delay_ms(1);
	Write_ins(0x06);
}

void LCD_writechar(u8 ch)
{
	write_data(ch);
}
void LCD_writestring(char* str)
{
	for(int i=0;str[i];i++)
	{
		write_data(str[i]);
	}
}
void LCD_writeNumber(s32 num)
{
	if(num==0)
	{
		LCD_writechar('0');
	}
	if(num<0)
	{
		num*=(-1);
		LCD_writechar('-');
	}
	u32 temp=0;
	u8 count=0;
	while(num)
	{
		temp=(temp*10)+(num%10);
		if(num%10==0 && temp==0)
		{
			count++;
		}
		num/=10;	
	}
	while(temp)
	{
		LCD_writechar(temp%10+'0');
		temp/=10;
	}
	while(count)
	{
		LCD_writechar('0');
		count--;
	}
}
void LCD_WriteBinary(u8 num)
{
	for(s8 i=7;i>=0;i--)
	{
		LCD_writechar(READ_BIT(num,i)+'0');
	}
}
void LCD_WriteHex(u8 num)
{
	u8 hex[2];
	for(int i=1;i>=0;i--)
	{
		hex[i]=num%16;
		num/=16;
	}
	for(int i=0;i<2;i++)
	{
		if(hex[i]>9)
		{
			LCD_writechar(hex[i]-10+'A');
		}
		else
		{
			LCD_writechar(hex[i]+'0');
		}
	}
}
void LCD_writefloatNumber(double num)
{
	u32 dec=0;
	LCD_writeNumber((u32)num);
	LCD_writechar('.');
	dec=num;
	num=(num-(double)dec)*1000;
	LCD_writeNumber(num);
}
void LCD_SetCursor(LCD_line_type line,u8 cell)
{
	if(line==FIRST)
	{
		Write_ins(0x80|cell);
	}
	else if(line==SECOND)
	{
		Write_ins(0xc0|cell);
	}
}
void LCD_Clear(void)
{
	Write_ins(1);
	_delay_ms(1);
}

void LCD_SetCGRAM(u8 address)
{
	Write_ins(0x40|address);
}
void LCD_WriteDataInCGRAM(u8*Data)
{
	for(int i=0;i<8;i++)
	{
		write_data(Data[i]);
	}
}
