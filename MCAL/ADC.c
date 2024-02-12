#include "STDTYPES.h"
#include "MemMap.h"
#include "ADC_Interface.h"
#include "LCD_interface.h"
#include "Utils.h"

static u16 volt_ref =5000;

void ADC_init(voltref_type Vref ,ADC_prescaler_type scaler )
{
	//set Vref selection
	Vref=Vref<<6;
	ADMUX=ADMUX|Vref;
	//set ADC prescaler
	scaler=scaler&7;
	ADCSRA=ADCSRA|scaler;
	//ADCL and ADCH set
	CLR_BIT(ADCSRA,ADLAR);
	//Enable ADC
	SET_BIT(ADCSRA,ADEN);
	if(Vref==AREF)
	{
		volt_ref=VREF;
	}
	else if(Vref==VOLT2_56_)
	{
		volt_ref=2560;
	}
}


u16 ADC_READ(ADC_pin_type ADC_pin)
{
	u16 num;
	//select channel pin
	ADMUX=ADMUX&0xE0;
	ADMUX=ADMUX|ADC_pin;
	//start convertion
	SET_BIT(ADCSRA,ADSC);
	//wait until finish conversion
	while(READ_BIT(ADCSRA,ADSC));
	//read input
	num=(u16)ADC;
	return num;
}
u16 ADC_readVolt(ADC_pin_type ADC_pin)
{
	u16 num=0;
	if(ADC_pin == ADC7)
	{
		num=ADC_filteration_ADC7();
	}
	else if(ADC_pin == ADC0)
	{
		num=ADC_filteration_ADC0();
	}
	num=((u32)num*(u32)volt_ref)/1024;
	return num;
}

u16 ADC_filteration_ADC7(void)
{
	static u16 ADC7_filter[10]={0};
	static u8 index=0;
	u16 output=0;
	ADC7_filter[index]=ADC_READ(ADC7);
	index++;
	if(index==10)
	{
		index=0;
	}
	for(u8 i=0;i<10;i++)
	{
		output+=ADC7_filter[i];
	}
	return output/10;
}

u16 ADC_filteration_ADC0(void)
{
	static u16 ADC0_filter[10]={0};
	static u8 index=0;
	u16 output=0;
	ADC0_filter[index]=ADC_READ(ADC0);
	index++;
	if(index==10)
	{
		index=0;
	}
	for(u8 i=0;i<10;i++)
	{
		output+=ADC0_filter[i];
	}
	return output/10;
}