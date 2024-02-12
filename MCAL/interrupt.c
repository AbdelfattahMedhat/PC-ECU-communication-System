#include "STDTYPES.h"
#include "MemMap.h"
#include "interrupt_interface.h"
#include "ext_int_cfg.h"
#include "LCD_interface.h"
#include "Utils.h"

static void (*INT_FUNC_ARR[INT_NUM])(void)={NULLPTR};
/*
static void (*INT0_FUNC)(void)=NULL_PTR;
static void (*INT1_FUNC)(void)=NULL_PTR;
static void (*INT2_FUNC)(void)=NULL_PTR;
*/
void interrupt_enable_control(INT_type inturrpt,status_t status)
{
	switch(inturrpt)
	{
		case INT_0: if(status)
					{
						SET_BIT(GICR,INT0);
					}
					else
					{
						CLR_BIT(GICR,INT0);
					}
					break;
		case INT_1: if(status)
					{
						SET_BIT(GICR,INT1);
					}
					else
					{
						CLR_BIT(GICR,INT1);
					}
					break;
		case INT_2: if(status)
					{
						SET_BIT(GICR,INT2);
					}
					else
					{
						CLR_BIT(GICR,INT2);
					}
					break;
		case INT_NUM: 
		           break;						
				}	
}
void interrupt_clear_flag(INT_type interrupt)
{
	switch(interrupt)
	{
		case INT_0:
		CLR_BIT(GIFR,INT0);
		break;
		case INT_1:
		CLR_BIT(GIFR,INT1);
		break;
		case INT_2:
		CLR_BIT(GIFR,INT2);
		break;
		case INT_NUM:
		break;
	}
	
}

void ext_interrupt_sense_resp(INT_type interrupt,int_sense_t sense)
{
	switch(interrupt)
	{
		case INT_0: // 4 sense states are available
		MCUCR=MCUCR|sense;
		break;
		case INT_1:// 4 sense states are available
		MCUCR=MCUCR|(sense<<2);
		break;
		case INT_2://Only--> 2 sense states are available
		if(sense==FALLING_EDGE)
		{
			CLR_BIT(MCUCSR,ISC2);
		}
		else if(sense==RISING_EDGE)
		{
			SET_BIT(MCUCSR,ISC2);
		}
		break;
		case INT_NUM:// do nothing
		break;
	}
}
void external_interrupt_init(void)
{
	sei();
	interrupt_enable_control(INT_0,DEFAULT_STATE);
	interrupt_enable_control(INT_1,DEFAULT_STATE);
	interrupt_enable_control(INT_2,DEFAULT_STATE);
	ext_interrupt_sense_resp(INT_0,DEFAULT_SENSE);
	ext_interrupt_sense_resp(INT_1,DEFAULT_SENSE);
	ext_interrupt_sense_resp(INT_2,DEFAULT_SENSE);
}
void interrupt_ISR(INT_type interrupt,void (*pf)(void))
{
	INT_FUNC_ARR[interrupt]=pf;
	/*
	switch(interrupt)
	{
		case INT_0:
		INT0_FUNC=pf;
		break;
		case INT_1:
		INT1_FUNC=pf;
		break;
		case INT_2:
		INT2_FUNC=pf;
		break;
	}*/
	
}
ISR(INT0_vect)
{
	if(INT_FUNC_ARR[INT_0]!=0)
	{
	INT_FUNC_ARR[INT_0]();	
	}
	
}

ISR(INT1_vect)
{
	if(INT_FUNC_ARR[INT_1]!=0)
	{
	INT_FUNC_ARR[INT_1]();	
	}
	
}

ISR(INT2_vect)
{
	if(INT_FUNC_ARR[INT_2]!=0)
	{
	INT_FUNC_ARR[INT_2]();	
	}
}