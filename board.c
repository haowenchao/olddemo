#include "s3c24xx.h"
#include "nand.h"
#include "swi.h"
#include "interrupt.h"

#define GPFCON (*(volatile unsigned int *)0x56000050)
#define GPFUP (*(volatile unsigned int *)0x56000058)
#define INTMSK (*(volatile unsigned int *)0x4a000008)
#define EINTPEND (*(volatile unsigned int *)0x560000a8)

static void init_keys(void)
{
	//gpf0
	GPFCON &= ~0x3;
	GPFCON |= 0x2;
	GPFUP |= 0x1;

	//set interrupt
	INTMSK &= ~0x1;
}

void copy2ram(void)
{
	extern int code_start;
	extern int __bss_start;
	unsigned char *desc = (unsigned char *)0x30000000;
	int len;

	len = (int)&__bss_start - (int)&code_start;

	nand_read(desc, 0, len);
}

void board_init(void)
{
	uart_init();
	swi_table_init();
	irq_init();
	init_keys();

	main();
}

