


#ifndef LED_H_
#define LED_H_


#define LED1 0
#define	LED2 1
#define	LED3 2
#define	LED4 3
#define	LED5 4
#define	LED6 5
#define	LED7 6
#define	LED8 7

#define BASE_PIN PINC0

#define LED_NUM 8

void LED_ON(u8 led_num);

void LED_OFF(u8 led_num);

#endif /* LED_H_ */