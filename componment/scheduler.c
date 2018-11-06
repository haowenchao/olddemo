#include "componment/list.h"
#include "componment/init.h"
#include "componment/thread.h"

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

}

/*
 * Start to schedule
 */
void scheduler_start(void)
{

}

void scheduler_add_ready(struct task_struct *t)
{
	list_add(&ready_list, &t->list);
}

