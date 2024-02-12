/*
 * ADC_Interface.h
 *
 * Created: 4/10/2023 9:59:19 PM
 *  Author: abdo
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define VREF 5000    //external volt by micro

typedef enum
{
	AREF,
	AVCC,
	VOLT2_56_=2
	}voltref_type;
typedef enum
{
	ADC_PRE_2=1,
	ADC_PRE_4,
	ADC_PRE_8,
	ADC_PRE_16,
	ADC_PRE_32,
	ADC_PRE_64,
	ADC_PRE_128
	}ADC_prescaler_type;
typedef enum {
	MUX0,
	 MUX1,
	 MUX2,
	 MUX3,
	 MUX4,
	 ADLAR,
	 REFS0,
	 REFS1
	}ADMUX_register_type;

typedef enum {
	ADPS0,
	ADPS1,
	ADPS2,
	ADIE,
	ADIF,
	ADATE,
	ADSC,
	ADEN
}ADCSRA_register_type;
typedef enum
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
	}ADC_pin_type;
void ADC_init(voltref_type Vref ,ADC_prescaler_type scaler );
u16 ADC_READ(ADC_pin_type ADC_pin);
u16 ADC_readVolt(ADC_pin_type ADC_pin);
u16 ADC_filteration_ADC7(void);
u16 ADC_filteration_ADC0(void);

#endif /* ADC_INTERFACE_H_ */