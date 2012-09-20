#include "list.h"

void init_list (list * lst)
{
	if (lst == NULL)
		return;

	list->head = NULL;
	list->tail = NULL;
}
