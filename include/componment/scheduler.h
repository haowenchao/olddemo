#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "componment/thread.h"

void scheduler(void);
void scheduler_start(void);
void scheduler_add_task(struct task_struct *t);
void tick(void);

#endif

