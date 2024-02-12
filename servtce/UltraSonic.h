#include "Ultra Sonic_cfg.h"


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
/************************************************************************/
/*                          TIMER                                       */
/************************************************************************/
#define START_TIME 0
#define SET_TIMER1(x)  (TCNT1=x)
#define T1_DELAY_50MS 15535       //to count 50 ms for overflow interrupt in normal mode                                                                                                                                                                                                                     
/************************************************************************/
/*                             BUFFER                                   */
/************************************************************************/
#define BUFFER1 0
#define BUFFER2 1
#define RESET_MODULE_COUNTER (module_counter=0)
#define TOGGLE_BUFFER_FLAG (flag_index^=1)

/************************************************************************/
/*                           DISTANCE                                   */
/************************************************************************/
#define TIME_CALCULATION ((falling_t-Rising_t)/58)
/************************************************************************/
/*                             ERRORS                                   */
/************************************************************************/
#define ERROR_RANGE 0
#define MAX_ERRORS 3
#define RESET_ERROR (out_range_count=0)
typedef enum
{
	IN_RANGE,
	OUT_RANGE
}ultra_sonic_error_t;
#define NOT_DONE 0
#define DONE 1
/************************************************************************/
/*                            DELAY                                     */
/************************************************************************/
#define TOGGLE_PIN_DELAY 10 //in micro seconds
#define ACCEPTABLE_LATENCY 30000 // in micro seconds
#define MEASURE_PERIOD 50 //in micro second
#define RESET_DELAY_COUNTER (delay_counter=0)
/************************************************************************/
/*                          FUNCTIONS                                   */
/************************************************************************/



void ultra_sonic_init(void);
void ultra_sonic_runnable(void);
u16 ultra_sonic_getter(MODULE_t module);
ultra_sonic_error_t ultra_sonic_trans_reciv(void);
void periodic_measure_set(void);


#endif /* ULTRASONIC_H_ */