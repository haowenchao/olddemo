#ifndef _INIT_H_
#define _INIT_H_

typedef void (*cal_back)(void);

struct init_desc {
	cal_back func;
};

#define call_back(fun) \
	__attribute__((section("init0"))) struct init_desc cal_back##fun = {(cal_back)fun};

extern void do_callback(void);

#endif

