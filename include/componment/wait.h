#ifndef _WAIT_H_
#define _WAIT_H_

#include "componment/list.h"
struct wait_queue {
	struct list_head list;
};

void wait_queue_init(struct wait_queue *q);
void wait_event(struct wait_queue *, unsigned int);
void wake_up(struct wait_queue *);

#define DECLARE_WAIT_QUEUE(queue) \
struct wait_queue queue;

#define DECLARE_WAIT_QUEUE_STATIC(queue) \
static struct wait_queue queue;

#endif

