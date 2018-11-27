#include "componment/list.h"
#include "componment/init.h"
#include "componment/thread.h"

#define MAX_PRIORITY 24

extern int printf(const char *fmt, ...);

struct task_queue{
	struct list_head list;
};

static unsigned int queue_priority = 0;
struct task_queue queues[MAX_PRIORITY];

static void schedule_init(void)
{
	int i = 0;

	for(i = 0; i < MAX_PRIORITY; i++) {
		list_init(&(queues[i].list));
	}
}
call_back1(schedule_init);

/*
 * get the first task in task queue with priority of p
 */
static struct task_struct *get_queue_task(unsigned int p)
{
	struct list_head *pos;

	if(p > 24)
		return NULL;

	pos = &queues[p].list;

	if(is_empty(pos)) {
		return NULL;
	}

	pos = pos->next;

	return (struct task_struct *)container_of(pos, \
		struct task_struct, list);
}

/*
 * get next task after task t in the same priority queue
 */
static struct task_struct *get_next_task(struct task_struct *t)
{
	struct list_head *pos;
	struct list_head *head;

	if(NULL == t)
		return NULL;

	pos = &t->list;
	head = &(queues[t->priority].list);

	if(pos->next == head) {
		pos = head->next;
	} else {
		pos = pos->next;
	}

	return (struct task_struct *)container_of(pos, \
		struct task_struct, list);
}

/*
 * if the task t is the only task in corresponding queue
 */
int is_only_task(struct task_struct *t)
{
	struct list_head *pos;
	struct list_head *head;

	if(NULL == t)
		return -1;

	pos  = &t->list;
	head = &(queues[t->priority].list);

	if(pos->next == head && pos->prev == head)
		return 1;

	return 0;
}

/*
 * Do a scheduler
 */
void scheduler(void)
{
	struct task_struct *from, *to;

	from = current;

	if(current->priority != queue_priority) {
		to = get_queue_task(queue_priority);
	} else {
		to = get_next_task(current);
	}

	if(from->status != TASK_READY) {
		list_del(&from->list);
	}

	to->slice = to->set_slice;

	current = to;

	context_switch(&(from->stack), &(to->stack));
}

/*
 * Start to schedule
 */
void scheduler_start(void)
{
	struct task_struct *to;

	to = get_queue_task(queue_priority);

	to->slice = to->set_slice;

	current = to;

	context_switch_to(to->stack);
}

void scheduler_add_task(struct task_struct *t)
{
	struct list_head *pos;

	pos = &queues[t->priority].list;

	list_add_tail(pos, &t->list);

	if(t->priority < queue_priority) {
		queue_priority = t->priority;

		scheduler();
	}
}

void tick(void)
{
	if(current->priority != queue_priority || \
	   current->status != TASK_READY || \
	   (!current->slice && !is_only_task(current))) {
		scheduler();
	} else {
		current->slice =  \
		(current->slice == 0) ? current->set_slice : current->slice - 1;
	}
}

