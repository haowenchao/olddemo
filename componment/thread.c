#include "componment/thread.h"
#include "componment/scheduler.h"

extern int printf(const char *fmt, ...);

struct task_struct *current;

static unsigned int getpid(void)
{
	static unsigned int a = 0;

	return a++;
}

/*
 * This function would create a task
 */
struct task_struct* task_create(task_t entry, unsigned int ss)
{
	return (void *)0;
}

int task_init(struct task_struct *t, task_t entry, void * stack, unsigned int ss)
{
	t->pid    = getpid();
	t->status = TASK_READY;
	t->stack  = stack_init(stack, ss, entry);
	t->entry  = entry;

	return 0;
}

void task_start(struct task_struct *t)
{
	if((void *)0 == t)
		return;

	//add to list
	scheduler_add_ready(t);
}

void task_suspend(struct task_struct *t)
{
	//change status
	t->status = TASK_BLOCKED;

	//del from list
	list_del(&t->list);
}

struct task_struct *get_current(void)
{
	return current;
}

void context_switch_to(void *to)
{
}

void context_switch(void *from, void *to)
{
}

void * stack_init(void *stack, unsigned int ss, task_t task)
{
}

DECLARE_TASK(t1, 512)
{
	printf("this is t1\n\r");
}

DECLARE_TASK(t2, 512)
{
	printf("this is t2\n\r");
}

DECLARE_TASK(t3, 512)
{
	printf("this is t3\n\r");
}

