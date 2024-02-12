/*
 * Timers_cfg.h
 *
 * Created: 5/24/2023 6:47:36 AM
 *  Author: abdo
 */ 


#ifndef ULTRA_S_CFG_H_
#define ULTRA_S_CFG_H_

// #define MODULE1_PIN PINC1
// #define MODULE1_PIN PINC2
// #define MODULE1_PIN PINC3
// #define MODULE1_PIN PINC4
/************************************************************************/
/*                         modules number                               */
/************************************************************************/
typedef enum
{
	MODULE1,
	
	MODULES_NUM
}MODULE_t;

static const u8 module_pins[MODULES_NUM]={
							PINC0
					

};
 /************************************************************************/
 /*                   periodic measures                                  */
 /************************************************************************/


#define TOGGLE_PERIOD 10 //in micro second
#define MEASURES_DELAY_COUNT 20  //resolution 50ms FOR ONE COUNT




#endif /* TIMERS_CFG_H_ */