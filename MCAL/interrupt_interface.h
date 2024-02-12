


#ifndef INTERRUPT_INTERFACE_H_
#define INTERRUPT_INTERFACE_H_

typedef enum
{
	LOW_LEVEL,
	ANY_LOGIC,
	FALLING_EDGE,
	RISING_EDGE
	}int_sense_t;

typedef enum
{
	INT_0,
	INT_1,
	INT_2,
	INT_NUM
	}INT_type;
typedef enum
{
	CLEAR,
	SET
}status_t;
void interrupt_enable_control(INT_type inturrpt,status_t status);
void interrupt_clear_flag(INT_type inturrpt);
void ext_interrupt_sense_resp(INT_type interrupt,int_sense_t sense);
void external_interrupt_init(void);
void interrupt_ISR(INT_type interrupt,void (*pf)(void));




#endif /* INTERRUPT_INTERFACE_H_ */