#ifndef _CLIENT_TABLE_H
#define _CLIENT_TABLE_H

#include "../common/clientinfo.h"
#define DEFAULT_SIZE 16

extern ClientInfo * ctab[];

void initialize (void);
int add_client (int, int);
void remove_client(int);
ClientInfo * get_client (int);

#endif
