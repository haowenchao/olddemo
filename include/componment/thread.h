#ifndef _THREAD_H_
#define _THREAD_H_

#include "componment/list.h"

typedef void (*task_t)(int argc, char **argv);
enum task_status {
	TASK_READY   = 1,
	TASK_RUN     = 2,
	TASK_BLOCKED = 3,
};

struct task_struct{
	//thread id
	unsigned int pid;

	//task status
	enum task_status status;

	//stack
	void *stack;

	//stack size
	unsigned int ss;

	//entry point
	task_t entry;

	//list node
	struct list_head list;
};

struct task_struct* task_create(task_t entry, unsigned int ss);
int task_init(struct task_struct *t, task_t entry, void * stack, unsigned int ss);
void task_start(struct task_struct *);
void taks_suspend(struct task_struct *);
struct task_struct *get_current(void);

/* low level related */
void context_switch_to(void *to);
void context_switch(void *from, void *to);
void * stack_init(struct task_struct *);

#endif

