#include "componment/wait.h"
#include "componment/scheduler.h"
#include "componment/list.h"
#include "componment/thread.h"

extern int printf(const char *fmt, ...);

void wait_queue_init(struct wait_queue *q)
{
	//init queue
	list_init(&q->list);
}

void wait_event(struct wait_queue *queue, unsigned int condition)
{
	printf("###########################wait_event is called\n\r");
	if(condition) {
		return;
	}

	printf("###########################wait event\n\r");

	//modify current status
	current->status = TASK_BLOCKED;

	//add current task to wait queue
	list_add_tail(&queue->list, &current->qlist);

	//do a scheduler
	scheduler();
}

void wake_up(struct wait_queue *queue)
{
	struct list_head *pos;
	struct task_struct *p;

	printf("###########################wake up\n\r");
	//each object in queue
	list_for_each(pos, &queue->list) {
		pos = (&(queue->list))->next;

		p = container_of(pos, struct task_struct, qlist);

		//modify object status
		p->status = TASK_READY;

		//add to ready list
		scheduler_add_task(p);
	}

	list_init(&queue->list);

	//do a scheduler
	scheduler();
}

