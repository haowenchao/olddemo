#include "componment/list.h"
#include "componment/scheduler.h"
#include "componment/init.h"
#include "componment/timer.h"

static struct list_head timers;

/*
 * init the timer module, some static variables
 */
void sys_timer_init(void)
{
	list_init(&timers);
}
call_back1(sys_timer_init);

/*
 * add system jeffy
 */
void sys_tick(void)
{
	struct list_head *pos;
	struct timer_struct *t;

	list_for_each(pos, &timers) {
		t = container_of(pos, struct timer_struct, \
				 list);
		if(t->expires) {
			t->expires--;
		} else {
			list_del(&t->list);
			t->function(t);
		}
	}
	tick();
}

/*
 * init a timer
 * func is the function called when time out
 */
int timer_init(struct timer_struct *t, \
                void (*func)(struct timer_struct *), \
                unsigned int expires)
{
	if(expires < 1 || NULL == func || NULL == t)
		return -1;

	t->function = func;
	t->expires  = expires;

	return 0;
}

/*
 * modify the timer expire
 */
int timer_mod(struct timer_struct *t, unsigned int new)
{
	if(new < 1 || NULL == t)
		return -1;

	t->expires = new;

	return 0;
}

/*
 * start a timer
 */
int timer_add(struct timer_struct *t)
{
	if(NULL == t || NULL == t->function) {
		return -1;
	}

	list_add_tail(&timers, &t->list);

	return 0;
}

/*
 * stop a timer
 */
int timer_del(struct timer_struct *t)
{
	if(NULL == t)
		return -1;

	list_del(&t->list);

	return 0;
}

