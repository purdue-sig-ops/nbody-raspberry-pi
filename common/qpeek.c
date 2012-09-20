#include "list.h"

void * qpeek (list * lst)
{
	if (lst == NULL || lst->tail == NULL)
		return (void *)NULL;

	return lst->tail->data;
}
