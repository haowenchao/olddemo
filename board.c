#include "s3c24xx.h"
#include "nand.h"

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
	swi_table_init();
	uart_init();
	sdram_init();
	nand_init();
	copy2ram();
}

