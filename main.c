#include "s3c24xx.h"
#include "lib/printf.h"
#include "nand.h"

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
		}
	}

	return 0;
}

