#include "list.h"

void * dequeue (list * lst)
{
	l_node * tail;
	void * data;

	if (lst == NULL || lst->tail == NULL)
		return (void *)NULL;

	tail = lst->tail;
	data = head->data;
	lst->tail = tail->prev;

	if (lst->tail == NULL)
		lst->head = NULL;
	else
		lst->tail->next = NULL;

	free(tail);
	return data;
}
