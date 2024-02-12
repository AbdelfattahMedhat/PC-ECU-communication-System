#include "Timers.h"

static const u8 color_arr[15][3]={};
/*************************Pointer to functions to be assigned to ISR*********************************/
static void (*TIMER1[FPTR_NUM]) (void)={NULLPTR};

// static OC1A_Mode_type ocra_modes[OCRA_MODES];
// 
// static OC1B_Mode_type ocrb_modes[OCRB_MODES];
/*
static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
static void (*Timer1_OCB_Fptr) (void)=NULLPTR;
static void (*Timer1_ICU_Fptr) (void)=NULLPTR;
*/
/******************************************************************************************/
/*timer 0 functions*/
void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);
		break;
		case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
		case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	}
	TCCR0&=TIMER0_CLEAR_SCALER;//0b11111000 TO REMOVE ANY CONFIG BEFORE
	TCCR0|=scaler;
}

void TIMER0_OC0Mode(OC0Mode_type mode) //Compare Output Mode
{
	if(mode<OC0_MODES)
	{
		TCCR0&=OC0_CLEAR_BITS;//0B00110000
		TCCR0|=mode;
	}
	/*
	switch (mode)
	{
		case OC0_DISCONNECTED:
		CLR_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_TOGGLE:
		SET_BIT(TCCR0,COM00);
		CLR_BIT(TCCR0,COM01);
		break;
		case OC0_NON_INVERTING:
		CLR_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
		case OC0_INVERTING:
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		break;
	}
	*/
}
void TIMER0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE0);
}
void TIMER0_OV_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE0);
}
void TIMER0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE0);
}
void TIMER0_OC_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

/*************************************************************************/
/*timer 1 functions*/
void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler)
{
	
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_8BIT_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;

}
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode)
{
	TCCR1A&=OCRA_CLEAR_BITS; // clear ocra bits
	TCCR1A|=oc1a_mode;
	/*
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A,COM1A0);
		CLR_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
	*/
}
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode)
{
	TCCR1A&=OCRB_CLEAR_BITS; // clear ocrb bit
	TCCR1A|=oc1b_mode;
	/*switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLR_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A,COM1B0);
		CLR_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}*/
}
void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	/************can be modified later******************/
	if(edge==RISING)
	SET_BIT(TCCR1B,ICES1);
	
	else if(edge==FALLING)
	CLR_BIT(TCCR1B,ICES1);
}


/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLR_BIT(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1[OVF_FPTR]=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1[OCA_FPTR]=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1[OCB_FPTR]=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	TIMER1[ICU_FPTR]=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(TIMER1[OVF_FPTR]!=NULLPTR)
	{
		TIMER1[OVF_FPTR]();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(TIMER1[OCA_FPTR]!=NULLPTR)
	{
		TIMER1[OCA_FPTR]();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(TIMER1[OCB_FPTR]!=NULLPTR)
	{
		TIMER1[OCB_FPTR]();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(TIMER1[ICU_FPTR]!=NULLPTR)
	{
		TIMER1[ICU_FPTR]();
	}
}
/*********************************set 0 1A 1B compare register***************************/
void TIMER0_set_OCR0(u8 ticks)
{
	OCR0=255-ticks;
}
void TIMER1_set_OCRA(u16 ticks)
{
	OCR1A=255-ticks; // if fast pmw 8bit
}
void TIMER1_set_OCRB(u16 ticks)
{
	OCR1B=255-ticks;  // if fast pmw 8bit
}
					/************************************************************************/
					/*                               Timer2                                 */
					/************************************************************************/

#define TIMER2_SET(x) (TCNT2=x)

#define OC2_SET(x) (OCR2=x)

typedef enum
{
	TIMER2_NORMAL=0,
	TIMER2_PHASE_CORRECT=0x40,
	TIMER2_CTC=0x8,
	TIMER2_FAST_PWM=0X48,
	TIMER2_MODES_NUM
	}Timer2Mode_type;
	
typedef enum
{
	TIMER2_NO_PRESCALER=1,
	TIMER2_8_PRESCALER,
	TIMER2_32_PRESCALER,
	TIMER2_64_PRESCALER,
	TIMER2_128_PRESCALER,
	TIMER2_256_PRESCALER,
	TIMER2_1024_PRESCALER,
	TIMER2_PRESCALER_MODES_NUM
}Timer2_prescaler_type;

typedef enum
{
	OC2_DISCONNECTED=0,
	OC2_TOGGLE=0x10,
	OC2_NON_INVERTING=0x20,
	OC2_INVERTING=0x30,
	OC2_MODES,
	/**********SHIFTS**************/
	OC2_CLEAR_BITS=0Xcf
}OC2Mode_type;
				
void TIMER2_init(Timer2Mode_type mode,Timer2_prescaler_type prescaler)
{
	// SET PRESCALER 
	TCCR2&=~7;
	TCCR2|=prescaler;
	// MASKING FOR TCCR2 TO CONFIGURE WGM20 & WGM21
	TCCR2&=~(1<<WGM20|1<<WGM21);
	TCCR2|=mode;
	
}

void TIMER2_OC2_mode(OC2Mode_type mode)
{
	// MASKING FOR TCCR2 TO CONFIGURE COM21 & COM20
	TCCR2&=OC2_CLEAR_BITS;
	TCCR2|=mode;
}

typedef enum
{
	TIMER2_OVER_FLOW=0X40,
	TIMER2_OUTPUT_COMPARE_MATCH=0X80,
	TIMER2_CLEAR_BITS=0Xcf
}TIMER2_interrupt_status_type;

typedef enum
{
	TIMER2_INTERRUPT_EN,
	TIMER2_INTERRUPT_DIS
}TIMER2_interrupt_type;
void TIMER2_interrupt_control(TIMER2_interrupt_type inturrupt ,TIMER2_interrupt_status_type state )
{
	
}