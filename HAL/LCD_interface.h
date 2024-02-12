/*
 * LCD_interface.h
 *
 * Created: 4/1/2023 4:43:01 PM
 *  Author: abdo
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

typedef enum{
	FIRST,
	SECOND
	}LCD_line_type;
#define LINE_START 0
void LCD_init(void);
void LCD_writechar(u8 ch);
void LCD_writestring(char* str);
void LCD_writeNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_Clear(void);
void LCD_SetCGRAM(u8 address);
void LCD_WriteDataInCGRAM(u8*Data);
u8* LCD_ReadDataInCGRAM(void);
void LCD_writefloatNumber(double num);
#endif /* LCD_INTERFACE_H_ */