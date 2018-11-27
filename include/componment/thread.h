#ifndef _THREAD_H_
#define _THREAD_H_

#include "componment/list.h"
#include "componment/thread.h"
#include "componment/init.h"

int printf(const char *fmt, ...);

typedef void (*task_t)(void *para);
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

	//prioriy
	unsigned int priority;

	//slice
	unsigned int slice;
	unsigned int set_slice;

	//stack
	void *stack;

	//stack size
	unsigned int ss;

	//list node
	struct list_head list;
	struct list_head klist;
	struct list_head qlist;
};

extern struct task_struct *current;

struct task_struct* task_create(task_t entry, unsigned int ss);
int task_init(struct task_struct *, task_t, void *, unsigned int, unsigned int);
void task_start(struct task_struct *);
void task_suspend(struct task_struct *);
struct task_struct *get_current(void);

/* low level related */
void context_switch_to(void *to);
void context_switch(void *from, void *to);
void * stack_init(void *, unsigned int, task_t);

#define DECLARE_TASK(func, ss, tick)	\
	static void init_##func(void); \
	static unsigned char stack_##func[ss]; \
	static struct task_struct task_##func; \
	void func(void *p); \
	static void init_##func(void) \
	{ \
		printf("init task %s\n\r", #func); \
		task_init(&task_##func, func, stack_##func, ss, tick); \
		task_start(&task_##func); \
	} \
	call_back2(init_##func); \
	void func(void *p)

#endif

