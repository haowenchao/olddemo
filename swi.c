#include "lib/printf.h"

#define SWI_ID_PIECES 100 

void def_handler(void *para);

struct swi_desc {
	unsigned int id;
	void (*handler)(void *);
	void *para;
};

static struct swi_desc swi_table[SWI_ID_PIECES];

void swi_table_init(void)
{
	int i = 0;

	for(i = 0; i < SWI_ID_PIECES; i++) {
		swi_table[i].id = i;
		swi_table[i].handler = def_handler;
		swi_table[i].para = &swi_table[i];
	}
}

void do_swi(unsigned int id)
{
	struct swi_desc swi_id;
	
	if(id > sizeof(swi_table)/sizeof(swi_table[0])) {
		printf("\n\rswi id out of range, the id = %d\n\r", id);
		return;
	}

	swi_id = swi_table[id];

	swi_id.handler(swi_id.para);
}

void def_handler(void *para)
{
	struct swi_desc *p = (struct swi_desc *)para;

	printf("\n\rswi enter, swi id = %d\n\r", p->id);
}

