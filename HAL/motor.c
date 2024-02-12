#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "motor_interface.h"



void motor_init(void)
{
	u8 i,j;
	for(i=M1;i<MOTORS_NUMBER;i++)
	{for(j=IN1;j<MOTOR_PINS;j++)
		{
			DIO_WritePin(MotorPinArray[i][j],MotorStatusArray[i][j]);
		}
		
	}
}
void motor_run_cw(motor_number_type Motor)
{
	DIO_WritePin(MotorPinArray[Motor][EN],HIGH);
	DIO_WritePin(MotorPinArray[Motor][IN1],HIGH);
	DIO_WritePin(MotorPinArray[Motor][IN2],LOW);
}
void motor_run_ccw(motor_number_type Motor)
{
	DIO_WritePin(MotorPinArray[Motor][EN],HIGH);
	DIO_WritePin(MotorPinArray[Motor][IN1],LOW);
	DIO_WritePin(MotorPinArray[Motor][IN2],HIGH);
}
void motor_stop(motor_number_type Motor)
{
	DIO_WritePin(MotorPinArray[Motor][EN],LOW);
	DIO_WritePin(MotorPinArray[Motor][IN1],LOW);
	DIO_WritePin(MotorPinArray[Motor][IN2],LOW);
}
