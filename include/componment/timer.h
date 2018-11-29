#ifndef _SYS_TIMER_H_
#define _SYS_TIMER_H_

#include "componment/list.h"

struct timer_struct {
	unsigned int expires;
	void (*function)(struct timer_struct *);
	struct list_head list;
};

extern void sys_tick(void);
extern int timer_init(struct timer_struct *t, \
		       void (*func)(struct timer_struct *), \
		       unsigned int expires);
extern int timer_mod(struct timer_struct *, unsigned int );
extern int timer_add(struct timer_struct *);
extern int timer_del(struct timer_struct *);

#define DEFINE_TIMER(timer, func, expires) \
struct timer_struct timer; \
void func(struct timer_struct *t); \
static void init_##timer (void) \
{ \
	timer_init(&timer, func, expires); \
	timer_add(&timer); \
} \
call_back2(init_##timer); \
void func(struct timer_struct *t)

#endif

