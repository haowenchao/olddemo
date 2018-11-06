#include "componment/thread.h"

static struct task_struct current;

/*
 * This function would create a task
 */
struct task_struct* task_create(task_t entry, unsigned int ss)
{
}

int task_init(struct task_struct *t, task_t entry, void * stack, unsigned int ss)
{
}

void task_start(struct task_struct *t)
{
}

void taks_suspend(struct task_struct *t)
{
}

struct task_struct *get_current(void)
{
}

