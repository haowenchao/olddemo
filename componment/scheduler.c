#include "componment/list.h"
#include "componment/init.h"
#include "componment/thread.h"

extern int printf(const char *fmt, ...);

static unsigned char init_stack[512];
static struct task_struct st_head;

void head_func(int a, char **p)
{
	printf("This is head_func\n\r");
}

static void schedule_init(void)
{
	list_init(&(st_head.list));
	task_init(&st_head, head_func, init_stack, 512);
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

	to->entry(1, (void *)0);

	context_switch(&(from->stack), &(to->stack));

	printf("in shceduler, %p\n\r", to);
}

/*
 * Start to schedule
 */
void scheduler_start(void)
{
	struct task_struct *to;

	to = (struct task_struct *)container_of(&(st_head.list).next, \
		struct task_struct, list);

	current = to;

	to->entry(1, (void *)0);

	context_switch_to(to->stack);
}

void scheduler_add_ready(struct task_struct *t)
{
	list_add(&(st_head.list), &t->list);
}

struct list_head tlist;

void add(void)
{
	list_add(&(st_head.list), &tlist);
}

void list(void)
{
	struct list_head *pos;

	list_for_each(pos, &(st_head.list)) {
		printf("%p\t", pos);
	}
}

