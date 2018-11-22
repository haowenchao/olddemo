#include "lib/printf.h"
#include "componment/init.h"

#define TCFG0  (*((volatile unsigned int *)0x51000000))
#define TCFG1  (*((volatile unsigned int *)0x51000004))
#define TCON   (*((volatile unsigned int *)0x51000008))
#define TCNTB0 (*((volatile unsigned int *)0x5100000C))
#define TCMPB0 (*((volatile unsigned int *)0x51000010))
#define TCNTO0 (*((volatile unsigned int *)0x51000014))
#define TCNTB1 (*((volatile unsigned int *)0x51000018))
#define TCMPB1 (*((volatile unsigned int *)0x5100001C))
#define TCNTO1 (*((volatile unsigned int *)0x51000020))
#define TCNTB2 (*((volatile unsigned int *)0x51000024))
#define TCMPB2 (*((volatile unsigned int *)0x51000028))
#define TCNTO2 (*((volatile unsigned int *)0x5100002C))
#define TCNTB3 (*((volatile unsigned int *)0x51000030))
#define TCMPB3 (*((volatile unsigned int *)0x51000034))
#define TCNTO3 (*((volatile unsigned int *)0x51000038))
#define TCNTB4 (*((volatile unsigned int *)0x5100003C))
#define TCNTO4 (*((volatile unsigned int *)0x51000040))

/* TCFG0 related macros */
#define PRESCALER1_100 (99 << 0)

/* TCFG1 related macros */
#define TIMER0OFFSET   0
#define TIMER1OFFSET   4
#define TIMER2OFFSET   8
#define TIMER3OFFSET   12
#define TIMER4OFFSET   16
#define MUXDIVIDER2    0
#define MUXDIVIDER4    1
#define MUXDIVIDER8    2
#define MUXDIVIDER16   3

#define TIMER0_MASK            (0x1f)
#define TIMER0_START           (1 << 0)
#define TIMER0_MANUAL_UPDATE   (1 << 1)
#define TIMER0_OUTPUT_INVERTER (1 << 2)
#define TIMER0_AUTO_RELOAD     (1 << 3)
#define TIMER0_DEAD_ZONE       (1 << 4)

void timer0_init(void)
{
	TCFG0 &= ~0xff;
	TCFG0 |= PRESCALER1_100;
	TCFG1 |= MUXDIVIDER8;
	TCON  &= ~TIMER0_MASK;
	TCON  |= TIMER0_AUTO_RELOAD;
}
call_back1(timer0_init);

void timer0_manual_update(void)
{
	TCON |= TIMER0_MANUAL_UPDATE;
	TCON &= ~TIMER0_MANUAL_UPDATE;
}

void timer0_start(void)
{
	TCON |= 0x1;
}

void timer0_stop(void)
{
	TCON &= ~0x1;
}

void timer0_set_cnt(unsigned short val)
{
	TCNTB0 = val;
}

void ms(void)
{
	timer0_set_cnt(500);
	timer0_manual_update();
	timer0_start();

	while(TCNTO0) {
	}
}

void delay_ms(unsigned int time)
{
	while(time--){
		ms();
	}
}

