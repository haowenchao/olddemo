/*
 *file   : test/cmd_namd.c
 *author : haowenchao
 *mail   : haowenchao22@gmail.com
 *desc   : 
 */

#include "nand.h"
#include "printf.h"
#include "string.h"
#include "s3c24xx.h"
#include "componment/command.h"

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

DEFINE_COMMAND(nand, nand_opt)
{
	if(2 != argc) {
		printf("\n\r\n\rusage: nand read to read nand\n\r");
		printf("\n\r\n\rusage: nand write to write nand\n\r");

		return;
	}

	if(!strcmp("read", argv[1])) {
		read_nand();
	}
	else if(!strcmp("write", argv[1])) {
		write_nand();
	} else {
		printf("\n\r\n\runsupport option: %s\n\r", argv[1]);
	}
}

