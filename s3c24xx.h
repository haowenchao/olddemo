#ifndef _S3C24XX_H_
#define _S3C24XX_H_

void sdram_init(void);
void uart_init(void);
void uart_putc(unsigned char);
unsigned char uart_getc(void);
void clock_init(void);
void show_status(void);

#endif

