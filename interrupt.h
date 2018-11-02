#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#define INT_ADC 31
#define INT_RTC 30
#define INT_SPI1 29
#define INT_UART0 28
#define INT_IIC 27
#define INT_USBH 26
#define INT_USBD 25
#define INT_NFCON 24
#define INT_UART1 23
#define INT_SPI0 22 
#define INT_SDI 21
#define INT_DMA3 20
#define INT_DMA2 19
#define INT_DMA1 18
#define INT_DMA0 17
#define INT_LCD 16
#define INT_UART2 15
#define INT_TIMER4 14
#define INT_TIMER3 13
#define INT_TIMER2 12
#define INT_TIMER1 11
#define INT_TIMER0 10
#define INT_WDT_AC97 9
#define INT_TICK 8
#define nBATT_FLT 7
#define INT_CAM 6
#define EINT8_23 5
#define EINT4_7 4
#define EINT3 3
#define EINT2 2
#define EINT1 1
#define EINT0 0

#define MSKINT_ADC 1<<31
#define MSKINT_RTC 1<<30
#define MSKINT_SPI1 1<<29
#define MSKINT_UART0 1<<28
#define MSKINT_IIC 1<<27
#define MSKINT_USBH 1<<26
#define MSKINT_USBD 1<<25
#define MSKINT_NFCON 1<<24
#define MSKINT_UART1 1<<23
#define MSKINT_SPI0 1<<22 
#define MSKINT_SDI 1<<21
#define MSKINT_DMA3 1<<20
#define MSKINT_DMA2 1<<19
#define MSKINT_DMA1 1<<18
#define MSKINT_DMA0 1<<17
#define MSKINT_LCD 1<<16
#define MSKINT_UART2 1<<15
#define MSKINT_TIMER4 1<<14
#define MSKINT_TIMER3 1<<13
#define MSKINT_TIMER2 1<<12
#define MSKINT_TIMER1 1<<11
#define MSKINT_TIMER0 1<<10
#define MSKINT_WDT_AC97 1<<9
#define MSKINT_TICK 1<<8
#define MSKnBATT_FLT 1<<7
#define MSKINT_CAM 1<<6
#define MSKEINT8_23 1<<5
#define MSKEINT4_7 1<<4
#define MSKEINT3 1<<3
#define MSKEINT2 1<<2
#define MSKEINT1 1<<1
#define MSKEINT0 1<<0

void irq_init(void);

#endif

