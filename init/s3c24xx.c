#include "lib/printf.h"
#include "componment/init.h"

/* uart init related macros */
#define GPHCON		(*(volatile unsigned long *)0x56000070)
#define GPHUP		(*(volatile unsigned long *)0x56000078)
#define ULCON0		(*(volatile unsigned long *)0x50000000)
#define UCON0		(*(volatile unsigned long *)0x50000004)
#define UFCON0		(*(volatile unsigned long *)0x50000008)
#define UMCON0		(*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0	(*(volatile unsigned long *)0x50000010)
#define UTXH0		(*(volatile unsigned char *)0x50000020)
#define URXH0		(*(volatile unsigned char *)0x50000024)
#define UBRDIV0		(*(volatile unsigned long *)0x50000028)
#define GPH3_msk	(3 << (2*3))
#define GPH2_msk	(3 << (2*2))
#define GPH3_rx		(2 << (2*3))
#define GPH2_tx		(2 << (2*2))
#define TXD0READY	(1<<2)
#define RXD0READY	(1)

/*Memory Controllers*/
#define     BWSCON    (*(volatile unsigned long *)0x48000000)
#define     BANKCON0  (*(volatile unsigned long *)0x48000004)
#define     BANKCON1  (*(volatile unsigned long *)0x48000008)
#define     BANKCON2  (*(volatile unsigned long *)0x4800000C)
#define     BANKCON3  (*(volatile unsigned long *)0x48000010)
#define     BANKCON4  (*(volatile unsigned long *)0x48000014)
#define     BANKCON5  (*(volatile unsigned long *)0x48000018)
#define     BANKCON6  (*(volatile unsigned long *)0x4800001C)
#define     BANKCON7  (*(volatile unsigned long *)0x48000020)
#define     REFRESH   (*(volatile unsigned long *)0x48000024)
#define     BANKSIZE  (*(volatile unsigned long *)0x48000028)
#define     MRSRB6    (*(volatile unsigned long *)0x4800002C)
#define     MRSRB7    (*(volatile unsigned long *)0x48000030)

void sdram_init(void)
{

	BWSCON = 0x22000000;

	BANKCON6 = 0x18001;
	BANKCON7 = 0x18001;

	REFRESH  = 0x8404f5;

	BANKSIZE = 0xb1;

	MRSRB6   = 0x20;
	MRSRB7   = 0x20;
}

void uart_init(void)
{
	//set port mode
	GPHCON &= ~(GPH3_msk | GPH2_msk);
	GPHCON |= (GPH3_rx | GPH2_tx);
	GPHUP   = 0x0c;
	
	//set data format
	ULCON0 = 0x3;	
	
	//set work mode
	UCON0 = 0x5;
	UFCON0  = 0x00;     //no FIFO
	UMCON0  = 0x00;     //no flow control	
	
	//set baud rate
	UBRDIV0 = 26;
}
call_back0(uart_init);

void uart_putc(unsigned char val)
{
	while (!(UTRSTAT0 & TXD0READY));

	UTXH0 = val;	
}

unsigned char uart_getc(void)
{
	unsigned char val = 0;

	while (!(UTRSTAT0 & RXD0READY));

	val = URXH0;

	return val;
}

void putc(char val)
{
	uart_putc((unsigned char )val);
}

char getc(void)
{
	return uart_getc();
}

void sprint(unsigned int pc, unsigned int lr, unsigned int sp, \
	unsigned int cpsr)
{
	printf("\n\rpc value is %0x\n\r", pc);
	printf("lr value is %0x\n\r", lr);
	printf("sp value is %0x\n\r", sp);
	printf("cpsr value is %0x\n\r", cpsr);
}

