#include "componment/list.h"

int list_init(struct list_head *list)
{
	if (NULL == list)
		return -1;
	list->prev = list;
	list->next = list;

	return 0;
}

int list_add_tail(struct list_head *head, struct list_head *new)
{
	if (NULL == head || NULL == new)
		return -1;

	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;

	return 0;
}

int list_add(struct list_head *head, struct list_head *new)
{
	if (NULL == head || NULL == new)
		return -1;

	head->next->prev = new;
	new->next = head->next;
	new->prev = head;
	head->next = new;

	return 0;
}

int list_del(struct list_head *node)
{
	if (NULL == node)
		return -1;

	node->next->prev = node->prev;
	node->prev->next = node->next;

	return 0;
}

int is_empty(struct list_head *p)
{
	if(p->next == p && p->prev == p) {
		return 1;
	} else {
		return 0;
	}
}

