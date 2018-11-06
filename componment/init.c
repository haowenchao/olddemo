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

static void do_callback1(void)
{
	struct init_desc *fstart, *fend;
	extern unsigned int __init1_start, __init1_end;

	fstart = (struct init_desc *)&__init1_start;
	fend   = (struct init_desc *)&__init1_end;

	while(fstart < fend) {
		fstart->func();
		fstart++;
	};
}

static void do_callback2(void)
{
	struct init_desc *fstart, *fend;
	extern unsigned int __init2_start, __init2_end;

	fstart = (struct init_desc *)&__init2_start;
	fend   = (struct init_desc *)&__init2_end;

	while(fstart < fend) {
		fstart->func();
		fstart++;
	};
}

void do_callback(void)
{
	do_callback0();
	do_callback1();
	do_callback2();
}

