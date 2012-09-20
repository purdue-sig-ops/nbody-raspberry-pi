/*
* Simple program that tests for big or little endian
*/

#include <stdio.h>

int main(void)
{
	int x=0x01;
	char * ptr = (char *)&x;
	*ptr; //first byte
	if(*ptr == 1)
	 printf("Little endian");
	else
	 printf("Big endian");
	printf("\n");
}
