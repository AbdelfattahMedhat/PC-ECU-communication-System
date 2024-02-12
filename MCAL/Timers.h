#ifndef TIMER_HEADER_H
#define TIMER_HEADER_H
#include "STDTYPES.h"
#include "MemMap.h"
#include "Utils.h"
#endif

#ifndef TIMERS_H_
#define TIMERS_H_
/************************************************************************/
/*                     registers set                                    */
/************************************************************************/
#define TIMER0_SET(x) (TCNT0=(u8)x)
#define TIMER1_SET(x) (TCNT1=(u16)x)
#define OC0_SET(x) (OCR0=(u16)x)
#define OC1A_SET(x) (OCR1A=(u16)x)
#define OC1B_SET(x) (OCR1B=(u16)x)
#define ICR1_SET(x) (ICR1=(u16)x)
/***************************my addition****************/

#define TIMER0_READ TCNT0
#define TIMER1_READ TCNT1
#define ICR1_READ ICR1
typedef enum
{
	OVF_FPTR,
	OCA_FPTR,
	OCB_FPTR,
	ICU_FPTR,
	FPTR_NUM
	}timer_ISR_fptr;

/****************************************************/

typedef enum{
	TIMER0_STOP=0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNALl_FALLING,
	EXTERNAL_RISING,
	TIMER0_CLEAR_SCALER=0XF8
}Timer0Scaler_type;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0Mode_type;


typedef enum
{
	
	OC0_DISCONNECTED=0,
	OC0_TOGGLE=0x10,
	OC0_NON_INVERTING=0x20,
	OC0_INVERTING=0x30,
	OC0_MODES,
	/**********SHIFTS**************/
	OC0_CLEAR_BITS=0Xcf
}OC0Mode_type;

void TIMER0_Init(Timer0Mode_type mode,Timer0Scaler_type scaler);

void TIMER0_OC0Mode(OC0Mode_type mode);
void TIMER0_OV_InterruptEnable(void);
void TIMER0_OV_InterruptDisable(void);
void TIMER0_OC_InterruptEnable(void);
void TIMER0_OC_InterruptDisable(void);
void TIMER0_OV_SetCallBack(void(*local_fptr)(void));
void TIMER0_set_OCR0(u8 ticks);
void TIMER1_set_OCRA(u16 ticks);
void TIMER1_set_OCRB(u16 ticks);
/*********************************************************************************************************/

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_8BIT_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE=0X40,
	OCRA_NON_INVERTING=0X80,
	OCRA_INVERTING=0Xc0,
	OCRA_MODES=4,
	OCRA_CLEAR_BITS=0X3F

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE=0x10,
	OCRB_NON_INVERTING=0x20,
	OCRB_INVERTING=0x30,
	OCRB_MODES=4,
	OCRB_CLEAR_BITS=0XCF

}OC1B_Mode_type;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;




void Timer1_InputCaptureEdge(ICU_Edge_type edge);
void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler);
void Timer1_OCRA1Mode(OC1A_Mode_type oc1a_mode);
void Timer1_OCRB1Mode(OC1B_Mode_type oc1b_mode);


void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);

void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);

void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);

void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));

#endif /* TIMERS_H_ */