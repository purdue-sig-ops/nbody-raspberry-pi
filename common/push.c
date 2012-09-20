#include "list.h"

void push (list * lst, void * data)
{
	if (lst == NULL)
		return;

	l_node * node = (l_node *)malloc(sizeof(l_node));
	if (node == NULL)
		return;

	node->data = data;
	node->next = lst->head;
	node->prev = NULL;

	if (lst->head != NULL)
		lst->head->prev = node;
	else
		lst->tail = node;

	lst->head = node;
}
