#include "s3c24xx.h"
#include "lib/printf.h"
#include "nand.h"
#include "rtc.h"
#include "interrupt.h"

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

void time(void)
{
	struct time_desc time;

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

static void tick_handler(void *para)
{
	time();
}

int main(void)
{
	char t;
	int id = 0;

	printf("\n\rsystem starting\n\r");

	while(1) {
		printf("\n\r*********** haowenchao boot menu ************\n\r");
		printf("[w] to write test data to nand flash\n\r");
		printf("[r] to read the data writen in nand flash\n\r");
		printf("[s] to read the status register of processer\n\r");
		printf("[p] to print current time\n\r");
		printf("[m] to set current time\n\r");
		printf("[c] to enter clock mode\n\r");
		printf("[e] to exit clock mode\n\r");
		printf("[i] to enter the swi mode\n\r");
		printf("enter your selection\n\r");

		scanf("%c", &t);

		switch(t)
		{
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
			time();
		break;

		case 'm':
			set();
		break;

		case 'c':
			rtc_enable_tick(127);
			request_irq(8, tick_handler, (void *)0);
		break;


		case 'e':
			rtc_disable_tick();
		break;
		}
	}

	return 0;
}

