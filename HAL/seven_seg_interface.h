#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#define SEVEN_SEGM_PORT PORTC

#define DIGIT_1_PIN PIND0
#define DIGIT_2_PIN PIND1

void seven_seg_init(void);
void seven_seg_Write_number(u8 num);








#endif