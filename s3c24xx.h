#ifndef _S3C24XX_H_
#define _S3C24XX_H_

void sdram_init(void);
void uart_init(void);
void uart_putc(unsigned char);
unsigned char uart_getc(void);
void clock_init(void);
void sprint(unsigned int, unsigned int, unsigned int, unsigned int);

#define show_status() \
asm("mov r0, pc\nmov r1, lr\nmov r2, sp\nmrs r3, cpsr\nbl sprint");

#endif

