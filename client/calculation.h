#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "../common/util.h"

#define TIME_STEP 1
#define G 0.0000000000667384

// Compute the distance between two positions
double distance(Vector *v1, Vector *v2);

// Compute the acceleration of the planet 
// a = (G*m / r^2) * r_hat
Vector* compute_acceleration(Vector* r1, Vector* r2, double mass);

// Compute the unit vector from v1 to v2
Vector* unit_vector(Vector *v1, Vector *v2, double magnitude);

// Compute the next velocity
// vel_f = vel_i + a*t
void update_vel(Vector *vel, Vector *acc);

// Compute the next position 
// pos_f = pos_i + v_i * t + .5*a*t^2
void update_pos(Vector *pos, Vector *vel_i, Vector* acc);

// Iterate through the list of planets and update position and velocity of curr.
void update_planet(Planet *curr, Planet *planets, size_t size);
