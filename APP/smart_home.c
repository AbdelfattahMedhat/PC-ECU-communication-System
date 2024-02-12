#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "servo.h"
#include "RGB.h"
#include "led.h"
#include "smart_home.h"
#include "USART.h"
#include "USART_service.h"
#include "LCD_interface.h"



static const  tasks_t task_arr[TASKS_NUM]={{"servo",servo_set_angle},{"led_on",LED_ON},{"led_off",LED_OFF},{"rgb",generate_rgb}};
/************************************************************************/
/*                        #COMPARE_STRINGS                              */
/************************************************************************/	
state_t string_compare(u8*str1,u8*str2)
{
	u8 i=0;
	state_t state=EQUAL;
	while(str2[i]||str1[i])
	{
		if(str2[i]!=str1[i])
		{
			state=NOT_EQUAL;
			break;
		}
		i++;
	}
	return state;
}	

search_t search_string(u8*str,u8*index)
{
	search_t state=NOT_FOUND;
	u8 i;
	for( i=0;i<TASKS_NUM;i++)
	{
		if (string_compare(str,task_arr[i].str)==EQUAL)
		{
			state = FOUND;
			*index=i;
			break;
		}
	}
	return state;
}

Error_t procces(void)
{
	Error_t state=OK;
	u8*name=0;
	u8 data=0;
	u8*uart_str=0;
	if(UART_into_func_and_data(uart_str,&name,&data)==OK)
	{
		
		u8 task_index=0;
		if (search_string(name,&task_index)==FOUND)
		{
			task_arr[task_index].pf(data);
		}
		else
		{
			state=NOK;
		}	
	}
	else
	{
		state=NOK;
	}
	return state;
}

Error_t UART_into_func_and_data(u8*str,u8**func,u8*data)
{
	Error_t state=OK;
	if (USART_recivestr_getter(&str)==OK)
	{	
		*func=str;
		*data=0;
		u8 i,flag=0;
		for (i=0;str[i]!=' ';i++)
		{
			if (!str[i])
			{
				flag=1;
				break;
			}
		}
		if (flag==0)
		{
			str[i]=0;
			i++;
			for (;str[i];i++)
			{
				*data=(*data*10)+(str[i]-'0');
			}
		}	
	}
	else
		{
			state = NOK;
		}
	return state;
}