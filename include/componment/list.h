#ifndef _LIST_H_
#define _LIST_H_

/* ADT */
struct list_head {
	struct list_head *next, *prev;
};

#ifndef NULL
#define NULL ((void *)0)
#endif

/* Operations */
int list_init(struct list_head *);
int list_add(struct list_head *, struct list_head *);
int list_del(struct list_head *);

#define offsetof(type, member) \
	((unsigned long) &((type *)0)->member)

#define container_of(ptr, type, member) \
	(type *)((char *)ptr - offsetof(type, member))

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#endif

