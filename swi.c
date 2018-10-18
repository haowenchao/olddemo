#include "lib/printf.h"

#define NAME_MAX_LENG 20

void def_handler(void *para);

struct swi_desc {
	unsigned int id;
	void (*handler)(void *);
	void *para;
};

static struct swi_desc swi_table[] = {
	{1, def_handler, (void *)&swi_table[0]},
	{2, def_handler, (void *)&swi_table[1]},
	{3, def_handler, (void *)&swi_table[2]},
};

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

