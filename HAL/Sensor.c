#include "STDTYPES.h"
#include "ADC_Interface.h"
#include "Sensor_interface.h" 


u16 Temperature_SensorLM35_Output(void)
{
	u16 volt=ADC_readVolt(TEMP_SENSOR_CH);
	volt=volt+5-(volt%5);
		
  return volt;
}

u16 Pressure_SensorMPX4115_Output(void)
{
	u16 volt=ADC_READ(PRESS_SENSOR_CH);
	volt=((u32)((u32)1000*(volt)-((u32)1000*56))/940)+150;
	return volt;
}

u16 Smoke_sensor_Output(void)
{
	u16 volt=ADC_readVolt(SMOKE_SENSOR_CH)/5;
	
		volt=volt-(volt%5);

	return volt;
}