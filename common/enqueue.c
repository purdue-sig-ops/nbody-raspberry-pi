#include "list.h"

void enqueue (list * lst, void * data)
{
	if (lst == NULL)
		return;

	l_node * node = (l_node *)malloc(sizeof(l_node));
	if (node == NULL)
		return;

	node->data = data;
	node->prev = lst->tail;
	node->next = NULL;

	if (lst->tail != NULL)
		lst->tail->next = node;
	else
		lst->head = node;

	lst->tail = node;
}
