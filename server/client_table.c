#include "client_table.h"

ClientInfo * client_table;
int table_size;
int table_max;

void initialize ()
{
	client_table = (ClientInfo **) malloc (DEFAULT_SIZE * sizeof(ClientInfo *));
	table_max = DEFAULT_SIZE;
	table_size = 0; //for the sake of being explicit
}

int add_client (int ip, int frame)
{
	if (table_size >= table_max)
	{
		client_table = (ClientInfo *) realloc (client_table,
				table_max * 2 * sizeof(ClientInfo *));
	}

	ClientInfo * client = (ClientInfo *) malloc (sizeof(ClientInfo));
	client->id = table_size;
	client->ip = ip;
	client->frame = frame;
	client_table[table_size++] = client;

	return client->id;
}

void remove_client (int id)
{
	if (id >= table_size) return;

	free(client_table[id]);
	table_size--;

	if (table_size < table_max / 4)
	{
		client_table = (ClientInfo *) realloc (client_table,
				(table_max / 2) * sizeof(ClientInfo *));
	}
}

ClientInfo * get_client (int id)
{
	if (id >= table_size) return (ClientInfo *)0;

	return client_table[id];
}
