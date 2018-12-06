#include "s3c24xx.h"
#include "printf.h"
#include "test/cmd_nand.h"

int main(void)
{
	char t;

	printf("\n\rsystem starting\n\r");

	while(1) {
		printf("\n\r*********** haowenchao boot menu ************\n\r");
		printf("[w] to write test data to nand flash\n\r");
		printf("[r] to read the data writen in nand flash\n\r");
		printf("enter your selection\n\r");

		terminal_scanf("%c", &t);

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
		}
	}

	return 0;
}

