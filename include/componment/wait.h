#ifndef _WAIT_H_
#define _WAIT_H_

struct wait_queue {

};

void wait_event(struct wait_queue *, unsigned int);
void wake_up(struct wait_queue *);

#endif

