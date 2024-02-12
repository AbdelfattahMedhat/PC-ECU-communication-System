#define F_CPU 8000000U
#include <util/delay.h>
#include "STDTYPES.h"
#include "Timers.h"
#include "DIO_Interface.h"
#include "UltraSonic.h"
#include "LCD_interface.h"

/************************************************************************/
/*                              Buffers                                 */
/************************************************************************/
static volatile u16 buffer1[MODULES_NUM]={0};
static volatile u16 buffer2[MODULES_NUM]={0};
static volatile u16 *buffer_flag[]={buffer1,buffer2};
/************************************************************************/
/*                             global variables                         */
/************************************************************************/
u16 Rising_t,falling_t;
u8 module_counter,flag_index,access_buffer,out_range_count,delay_counter,sleep_flag,getter_flag;
/************************************************************************/
/*                       ISR functions                                  */
/************************************************************************/
static void ultra_sonic_isr(void)
{
	
	if(Rising_t==START_TIME)
	{
		
		Rising_t=ICR1_READ;
		Timer1_InputCaptureEdge(FALLING);
	}
	else
	{
		
		falling_t=ICR1_READ;
		
	}
}

static void ultra_sonic_sleep_period(void)
{
	SET_TIMER1(T1_DELAY_50MS);
	delay_counter++;
	
}
/************************************************************************/
/*                            Functions                                 */
/************************************************************************/
void ultra_sonic_init(void)
{
	Timer1_ICU_InterruptEnable();
	Timer1_ICU_SetCallBack(ultra_sonic_isr);
	Timer1_OVF_SetCallBack(ultra_sonic_sleep_period);
	
}
void ultra_sonic_runnable(void)
{


	
	if(sleep_flag==HIGH)
	{
		
		if(delay_counter>MEASURES_DELAY_COUNT)
		{
			sleep_flag=LOW;
			RESET_DELAY_COUNTER;
			Timer1_OVF_InterruptDisable();
		}
	}
	else
	{
		if(ultra_sonic_trans_reciv());// it return optional error for different logic out or in range
		periodic_measure_set();	
	}	
}
u16 ultra_sonic_getter(MODULE_t module)
{
	
		if(getter_flag==DONE)
		return buffer_flag[access_buffer][module];
		return NOT_DONE;
}

ultra_sonic_error_t ultra_sonic_trans_reciv(void)
{
	SET_TIMER1(START_TIME);
	Timer1_InputCaptureEdge(RISING);
	DIO_WritePin(module_pins[module_counter],HIGH);
	_delay_us(TOGGLE_PIN_DELAY);
	DIO_WritePin(module_pins[module_counter],LOW);
	if(falling_t>START_TIME || out_range_count>=MAX_ERRORS)
	{
			if(out_range_count>=MAX_ERRORS)
			{
				
				buffer_flag[flag_index][module_counter]=ERROR_RANGE;
			}
			else
			{
				buffer_flag[flag_index][module_counter]=TIME_CALCULATION;
				Rising_t=0;
				falling_t=0;
			}
			RESET_ERROR; // put 0 in out_range_counter
			module_counter++;
			_delay_us(MEASURE_PERIOD);	
	}
	else if(TIMER1_READ>ACCEPTABLE_LATENCY)
	{
		
		out_range_count++;
		return OUT_RANGE;
	}
	return IN_RANGE;
}


void periodic_measure_set(void)
{
	
	if(module_counter==MODULES_NUM)
	{
		RESET_MODULE_COUNTER;
		TOGGLE_BUFFER_FLAG;
		getter_flag=DONE;
		if(flag_index) // if index0 (false) its mean buffer1 is ready if index1 (true)
		{
			access_buffer=BUFFER1;
		}
		else
		{
			access_buffer=BUFFER2;
		}
		sleep_flag=HIGH;
		Timer1_OVF_InterruptEnable();
		SET_TIMER1(T1_DELAY_50MS);
	}
	
}