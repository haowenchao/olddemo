#include "componment/wait.h"
#include "componment/thread.h"
#include "componment/scheduler.h"

extern int printf(const char *fmt, ...);

unsigned int from_stack;
unsigned int to_stack;
unsigned int context_switch_flag = 0;
unsigned int context_irq = 0;

struct task_struct *current;
static struct list_head threads;

static void thread_comp_init(void)
{
	list_init(&threads);
}
call_back1(thread_comp_init);

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

	list_add_tail(&threads, &(t->klist));
	return 0;
}

void list_all(void)
{
	struct list_head *p;
	struct task_struct *t;

	printf("pid\tstaus\n\r");
	list_for_each(p, &threads) {
		t = container_of(p, struct task_struct, klist);
		printf("%d\t%d\n\r", t->pid, t->status);
	}
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

void context_switch(void *from, void *to)
{
	from_stack = (unsigned int)from;
	to_stack = (unsigned int)to;
	context_switch_flag = 1;

	if(!context_irq) {
		context_irq = 0;
		asm("swi 1");
	}
}

void * stack_init(void *stack, unsigned int ss, task_t task)
{
	unsigned int *sp;
	unsigned char *p = (unsigned char *)stack + ss - 4;

	sp = (unsigned int*)p;

	*--sp = (unsigned int )task;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0x13;

	return sp;
}

struct wait_queue task_queue;

DECLARE_TASK(t1, 512)
{
	while(1) {
		printf("task id = %d\n\r", current->pid);
	}
}

DECLARE_TASK(t2, 512)
{
	while(1) {
		printf("task id = %d\n\r", current->pid);
		scheduler();
	}
}

DECLARE_TASK(t3, 512)
{
	while(1) {
		printf("task id = %d\n\r", current->pid);
	}
}

