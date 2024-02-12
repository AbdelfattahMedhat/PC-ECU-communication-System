
#ifndef SENSOR_INTERFACE_H_
#define SENSOR_INTERFACE_H_

#define TEMP_SENSOR_CH ADC0
#define PRESS_SENSOR_CH ADC7
#define SMOKE_SENSOR_CH ADC7
u16 Temperature_SensorLM35_Output(void);
u16 Pressure_SensorMPX4115_Output(void);
u16 Smoke_sensor_Output(void);




#endif /* SENSOR_INTERFACE_H_ */