/*
 *file   : test/cmd_namd.c
 *author : haowenchao
 *mail   : haowenchao22@gmail.com
 *desc   : 
 */

#include "nand.h"
#include "s3c24xx.h"

void write_nand(void)
{
	int i = 0;
	unsigned char buff1[4096];

	for(i = 0; i < 4096; i++) {
		buff1[i] = (i % 26) + 'a';
	}

	nand_write(buff1, 1024*18, 4096);
}

void read_nand(void)
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

