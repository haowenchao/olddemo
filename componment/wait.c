#include "componment/wait.h"

void wait_queue_init(struct wait_queue *q)
{
	//init queue
}

void wait_event(struct wait_queue *queue, unsigned int condition)
{
	if(condition) {
		return;
	}

	//modify current status

	//del current task from ready list


	//add current task to wait queue

	//do a scheduler
}

void wake_up(struct wait_queue *queue)
{
	//each object in queue

	//modify object status

	//del from queue

	//add to ready list

	//do a scheduler
}

