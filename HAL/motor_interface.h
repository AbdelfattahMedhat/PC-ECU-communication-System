


#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


typedef enum{
	M1,
	M2,
	M3,
	M4,
	MOTORS_NUMBER
}motor_number_type;
typedef enum{
	IN1,
	IN2,
	EN,
	MOTOR_PINS
}motor_pins_type;
extern const DIO_Pin_type MotorPinArray[MOTORS_NUMBER][MOTOR_PINS]; 
extern const DIO_PinVoltage_type MotorStatusArray[MOTORS_NUMBER][MOTOR_PINS];
void motor_init(void);
void motor_run_cw(motor_number_type Motor);
void motor_run_ccw(motor_number_type Motor);
void motor_stop(motor_number_type Motor);



#endif /* CAR_INTERFACE_H_ */