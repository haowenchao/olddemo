#ifndef _TIMER_H_
#define _TIMER_H_

void timer0_manual_update(void);
void timer0_start(void);
void timer0_stop(void);
void timer0_set_cnt(unsigned short val);
void delay_ms(unsigned int time);

#endif

