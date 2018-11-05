#include "componment/init.h"

static void do_callback0(void)
{
	struct init_desc *fstart, *fend;
	extern unsigned int __init0_start, __init0_end;

	fstart = (struct init_desc *)&__init0_start;
	fend   = (struct init_desc *)&__init0_end;

	while(fstart < fend) {
		fstart->func();
		fstart++;
	};
}

void do_callback(void)
{
	do_callback0();
}

