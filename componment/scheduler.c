#include "componment/list.h"
#include "componment/init.h"
#include "componment/thread.h"

extern int printf(const char *fmt, ...);

static unsigned char init_stack[512];
static struct list_head ready_list;

static void schedule_init(void)
{
	list_init(&ready_list);
}
call_back1(schedule_init);

/*
 * Do a scheduler
 */
void scheduler(void *para)
{
	struct list_head *pos;
	struct task_struct *from, *to;

	from = get_current();
	pos = &(from->list);
	pos = pos->next;
	to = (struct task_struct *)container_of(pos, \
		struct task_struct, list);

	current = to;

	list_del(&(to->list));
	list_add_tail(&ready_list, &(from->list));

	context_switch(&(from->stack), &(to->stack));
}

/*
 * Start to schedule
 */
void scheduler_start(void)
{
	struct task_struct *to;

	to = (struct task_struct *)container_of(ready_list.next, \
		struct task_struct, list);

	current = to;

	list_del(&(to->list));
	context_switch_to(to->stack);
}

void scheduler_add_ready(struct task_struct *t)
{
	list_add_tail(&ready_list, &t->list);
}

