#include "list.h"

void * pop (list * lst)
{
	void * data;
	l_node * head;

	if (lst == NULL || lst->head == NULL)
		return (void *)NULL;

	head = lst->head;
	data = head->data;
	lst->head = head->next;

	if (lst->head == NULL)
		lst->tail = NULL;
	else
		lst->head->prev = NULL;

	free(head);
	return data;
}
