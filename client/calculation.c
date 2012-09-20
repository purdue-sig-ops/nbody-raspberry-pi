#include "calculation.h"

/* Compute the distance between two positions
 */
double distance(Vector *v1, Vector *v2)
{
	double distance = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2) + pow(v1->z - v2->z, 2));
	return distance;
}


/* This function calculates the unit vector from v1 to v2
 */
Vector* unit_vector(Vector *v1, Vector *v2, double magnitude)
{
	Vector* unit = (Vector*)malloc(sizeof(Vector));

	unit->x = ((v2->x - v1->x) / magnitude);
	unit->y = ((v2->y - v1->y) / magnitude);
	unit->z = ((v2->z - v1->z) / magnitude);

        return unit;
}


/* Compute the acceleration of the planet
 * a = (G*m / r^2) * r_hat
 */
Vector* compute_acceleration(Vector* r1, Vector* r2, double mass)
{
	double r = distance(r1, r2);   // Distance between the two planets

	Vector* unit = unit_vector(r1, r2, r);   // unit vector

	double acc_mag = (G * mass) / pow(r,2);   // magnitude of acceleration

	unit->x = acc_mag * unit->x;
	unit->y = acc_mag * unit->y;
	unit->z = acc_mag * unit->z;

	return unit;
}


/* Compute the next velocity. Frees acceleration. Call after update_pos
 * vel_f = vel_i + a*t
 */
void update_vel(Vector *vel, Vector *acc)
{
	vel->x = vel->x + (acc->x * TIME_STEP);
	vel->y = vel->y + (acc->y * TIME_STEP);
	vel->z = vel->z + (acc->z * TIME_STEP);
}


/* Compute the next position
 * pos_f = pos_i + v_i * t + .5*a*t^2
 */
void update_pos(Vector *pos, Vector *vel_i, Vector* acc)
{
	pos->x = pos->x + (vel_i->x * TIME_STEP) + (.5 * acc->x * pow(TIME_STEP, 2));
	pos->y = pos->y + (vel_i->y * TIME_STEP) + (.5 * acc->y * pow(TIME_STEP, 2));
	pos->z = pos->z + (vel_i->z * TIME_STEP) + (.5 * acc->z * pow(TIME_STEP, 2));
}

void update_planet(Planet *curr, Planet *planets, size_t size) {
	Vector acc; 
	Vector* tmp;
	int i;
	for(i=0; i<size; i++) {
		if(planets[i].id==curr->id) continue;
		tmp=compute_acceleration(curr->pos, planets[i].pos, planets[i].mass);

		acc.x+=tmp->x;
		acc.y+=tmp->y;
		acc.z+=tmp->z;

		free(tmp);
	}
	update_pos(curr->pos, curr->velocity, &acc);
	update_vel(curr->velocity, &acc);
}
