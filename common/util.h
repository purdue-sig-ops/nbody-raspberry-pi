#include "vector.h"

#ifndef _UTIL_H
#define _UTIL_H

typedef struct {
	int id;
	int planet_id;
} Job;

typedef struct {
	int id;
	double mass;
	Vector *pos;
	Vector *velocity;
} Planet;

#endif
