#ifndef _INIT_H_
#define _INIT_H_

typedef void (*cal_back)(void);

struct init_desc {
	cal_back func;
};

#define call_back0(fun) \
	__attribute__((section("init0"))) struct init_desc cal_back##fun = {(cal_back)fun};

#define call_back1(fun) \
	__attribute__((section("init1"))) struct init_desc cal_back##fun = {(cal_back)fun};

#define call_back2(fun) \
	__attribute__((section("init2"))) struct init_desc cal_back##fun = {(cal_back)fun};

extern void do_callback(void);

#endif

