#include "list.h"

void * peek (list * lst)
{
	if (lst == NULL || lst->head == NULL)
		return (void *)NULL;

	return lst->head->data;
}
