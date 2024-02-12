#include "STDTYPES.h"
#include "DIO_Interface.h"
#include "motor_interface.h"

#define M1_IN1 PINC0
#define M1_IN2 PINC1
#define M1_EN PINC2

#define M2_IN1 PINC3
#define M2_IN2 PINC4
#define M2_EN PINC5

#define M3_IN1 PINC6
#define M3_IN2 PINC7
#define M3_EN PIND0

#define M4_IN1 PIND1
#define M4_IN2 PIND2
#define M4_EN PIND3

const DIO_Pin_type MotorPinArray[MOTORS_NUMBER][MOTOR_PINS]=
{//motor pins       { IN1 , IN2  ,  EN  }
				    {M1_IN1,M1_IN2,M1_EN},
					{M2_IN1,M2_IN2,M2_EN},
					{M3_IN1,M3_IN2,M3_EN},
					{M4_IN1,M4_IN2,M4_EN}
};

const DIO_PinVoltage_type MotorStatusArray[MOTORS_NUMBER][MOTOR_PINS]=
{
	//motor_init status{ IN1 , IN2  ,  EN  }
	                     {HIGH,LOW,LOW},
                         {HIGH,LOW,LOW},
					     {HIGH,LOW,LOW},
					     {HIGH,LOW,LOW}
};