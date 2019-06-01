#include "s3c24xx.h"
#include "printf.h"
#include "componment/command.h"
#include "test/cmd_nand.h"

int main(void)
{
	char buff[256];

	printf("\n\rsystem starting\n\r");
	printf("\n\r*********** haowenchao boot menu ************\n\r");

	while(1) {
		get_command(buff);
		if(-1 == do_command(buff)) {
			printf("\n\runsupported command\n\r");
		}
	}

	return 0;
}

