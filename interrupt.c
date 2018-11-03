#include "lib/printf.h"

#define INTERRUPT_SRC_PIECES 32
#define INTMSK (*(volatile unsigned int *)0x4a000008)
#define INTPND (*(volatile unsigned int *)0x4a000010)
#define SRCPND (*(volatile unsigned int *)0x4a000000)
#define OFFSET (*((volatile unsigned int *)0x4a000014))

struct interrupt_desc {
	unsigned int offset;
	void (*irq_handler)(void *data);
	void *para;
};

static struct interrupt_desc int_tables[INTERRUPT_SRC_PIECES];

static void def_handler(void *para)
{
	struct interrupt_desc *p = (struct interrupt_desc *)para;

	printf("\n\rinterrupt id = %d\n\r", p->offset);
}

void irq_init(void)
{
	unsigned int i = 0;

	for(i = 0; i < (sizeof(int_tables) / sizeof(int_tables[0])); i++) {
		int_tables[i].offset = i;
		int_tables[i].irq_handler = def_handler;
		int_tables[i].para = (void *)&int_tables[i];
	}
}

void do_irq(void)
{
	unsigned int offset;
	struct interrupt_desc *p;

	offset = OFFSET;

	if(offset > sizeof(int_tables) / sizeof(int_tables[0])) {
		printf("\n\runknow interrupt source, is = %d\n\r", offset);
		return;
	}

	p = &int_tables[offset];

	SRCPND |= 1 << offset;
	INTPND |= 1 << offset;

	p->irq_handler(p->para);
}

void do_fiq(void)
{

}

int request_irq(unsigned int irq_no, void (*handler)(void *), void *para)
{
	struct interrupt_desc *p;

	if(irq_no > sizeof(int_tables) / sizeof(int_tables[0])) {
		printf("\n\rirq_no out of range\n\r");
		return -1;
	}

	if((void *)0 == handler) {
		printf("\n\rinvalid handler\n\r");
		return -1;
	}

	p = &int_tables[irq_no];

	p->irq_handler = handler;
	p->para = para;

	INTMSK &= ~(1 << irq_no);

	return 0;
}

void free_irq(unsigned int irq_no)
{
	struct interrupt_desc *p;

	if(irq_no > sizeof(int_tables) / sizeof(int_tables[0])) {
		printf("\n\rirq_no out of range\n\r");
		return;
	}

	p = &int_tables[irq_no];

	p->irq_handler = def_handler;
	p->para = (void *)0;

	INTMSK &= ~(1 << irq_no);
}

