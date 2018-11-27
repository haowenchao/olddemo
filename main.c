#include "s3c24xx.h"
#include "lib/printf.h"
#include "nand.h"
#include "rtc.h"
#include "timer.h"
#include "interrupt.h"
#include "componment/scheduler.h"

static void write_nand(void)
{
	int i = 0;
	unsigned char buff1[4096];

	for(i = 0; i < 4096; i++) {
		buff1[i] = (i % 26) + 'a';
	}

	nand_write(buff1, 1024*18, 4096);
}

static void read_nand(void)
{
	int i = 0;
	unsigned char buff2[4096];

	for(i = 0; i < 4096; i++) {
		buff2[i] = 0;
	}

	nand_read(buff2, 1024*18, 4096);

	for(i = 0; i < 4096; i++) {
		uart_putc(buff2[i]);
	}
}

struct time_desc time;
void timer(void)
{
	rtc_get(&time);
	printf("\n\r%d:%d:%d\t", time.year, time.month, time.date);
	printf("%d:%d:%d\n\r", time.hour, time.min, time.sec);
}

void set(void)
{
	struct time_desc time;

	time.hour = 16;
	time.min = 25;
	time.sec = 30;

	time.day = 3;
	time.date = 2;
	time.month = 1;
	time.year = 20;

	rtc_set(&time);
}

void alarm(void)
{
	struct time_desc time_alm;

	time_alm.hour = 16;
	time_alm.min = 26;
	time_alm.sec = 30;

	time_alm.day = 3;
	time_alm.date = 2;
	time_alm.month = 1;
	time_alm.year = 20;

	rtc_set_alarm_time(&time_alm);
}

static void rtc_handler(void *para)
{
	printf("\n\rthis is rtc handler\n\r");
}

static void tick_handler(void *para)
{
	timer();
}

static void test(void *p)
{
	printf("timer test\n\r");
}

extern void list_all(void);
int main(void)
{
	char t;
	int id = 0;

	printf("\n\rtick is set to 125ms\n\r");

	while(1) {
		printf("\n\r*********** haowenchao boot menu ************\n\r");
		printf("[w] to write test data to nand flash\n\r");
		printf("[r] to read the data writen in nand flash\n\r");
		printf("[s] to read the status register of processer\n\r");
		printf("[p] to print current time\n\r");
		printf("[m] to set current time\n\r");
		printf("[c] to enter clock mode\n\r");
		printf("[e] to exit clock mode\n\r");
		printf("[a] to test rtc alarm\n\r");
		printf("[i] to enter the swi mode\n\r");
		printf("[z] to list all tasks\n\r");
		printf("enter your selection\n\r");

		scanf("%c", &t);

		switch(t)
		{
		case 'a':
			rtc_enable_alarm(minen);
			request_irq(INT_RTC, rtc_handler, (void *)0);
			alarm();
		break;

		case 'w':
			write_nand();
			printf("\n\rfinish write nand flash\n\r");
		break;
		
		case 'r':
			read_nand();
			printf("\n\rfinish read nand flash\n\r");
		break;

		case 's':
			show_status();
			printf("\n\rfinish show status\n\r");
		break;

		case 'i':
			printf("\n\rinput swi id\n\r");
			scanf("%d", &id);

			switch(id)
			{
			case 0:
				asm("swi 0");
			break;

			case 1:
				asm("swi 1");
			break;

			case 2:
				asm("swi 2");
			break;

			default:
				asm("swi 123");
			break;
			}
			printf("\n\rreturn from swi exception\n\r");
		break;

		case 'p':
			timer();
		break;

		case 'm':
			set();
		break;

		case 'c':
			rtc_enable_tick(127);
			request_irq(8, tick_handler, (void *)0);
		break;

#define INTPND (*(volatile unsigned int *)0x4a000010)
#define SRCPND (*(volatile unsigned int *)0x4a000000)
#define INTMSK (*(volatile unsigned int *)0x4a000008)
#define RTCCON   (*((volatile unsigned char *)0x57000040))
#define TICNT    (*((volatile unsigned char *)0x57000044))
#define RTCALM   (*((volatile unsigned char *)0x57000050))
#define ALMSEC   (*((volatile unsigned char *)0x57000054))
#define ALMMIN   (*((volatile unsigned char *)0x57000058))
#define ALMHOUR  (*((volatile unsigned char *)0x5700005C))
#define ALMDATE  (*((volatile unsigned char *)0x57000060))
#define ALMMON   (*((volatile unsigned char *)0x57000064))
#define ALMYEAR  (*((volatile unsigned char *)0x57000068))
		case 'l':
			printf("RTCCON   = 0x%x\n\r", RTCCON );
			printf("TICNT    = 0x%x\n\r", TICNT  );
			printf("RTCALM   = 0x%x\n\r", RTCALM );
			printf("ALMSEC   = 0x%x\n\r", ALMSEC );
			printf("ALMMIN   = 0x%x\n\r", ALMMIN );
			printf("ALMHOUR  = 0x%x\n\r", ALMHOUR);
			printf("ALMDATE  = 0x%x\n\r", ALMDATE);
			printf("ALMMON   = 0x%x\n\r", ALMMON );
			printf("ALMYEAR  = 0x%x\n\r", ALMYEAR);
			printf("INTMSK   = 0x%x\n\r", INTMSK);
			printf("SRCPND   = 0x%x\n\r", SRCPND);
			printf("INTPND   = 0x%x\n\r", INTPND);
		break;

		case 'e':
			rtc_disable_tick();
		break;

		case 'u':
			//set tick
			rtc_enable_tick(15);
			request_irq(8, (void *)tick, (void *)0);

			//start schedule
			scheduler_start();
		break;

		case 'z':
			list_all();
		break;

		case 'y':
			request_irq(10, test, (void *)0);
			timer0_set_cnt(0xffff);
			timer0_manual_update();
			timer0_start();
		break;

		case 'h':
			printf("delay start\n\r");
			delay_ms(2000);
			printf("delay stop\n\r");
		break;

		case 'v':
			timer0_stop();
		break;
		}
	}

	return 0;
}

