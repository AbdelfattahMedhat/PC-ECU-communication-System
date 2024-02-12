/*
 * smart_home.h
 *
 * Created: 6/8/2023 3:10:33 PM
 *  Author: abdo
 */ 


#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#define TASKS_NUM 4

typedef struct  
{
	u8*str;
	void (*pf)(u8);
}tasks_t;

typedef enum
{
	EQUAL,
	NOT_EQUAL
	}state_t;

typedef enum
{
	NOT_FOUND,
	FOUND
	}search_t;

state_t string_compare(u8*str1,u8*str2);
search_t search_string(u8*str,u8*index);
Error_t UART_into_func_and_data(u8*str,u8**func,u8*data);
Error_t procces(void);

#endif /* SMART_HOME_H_ */