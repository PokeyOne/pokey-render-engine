#include "distance.h"

/*
 Simply square the double and return the value
 */
double square(double v) {
	return v * v;
}

/*
 Calculate the distance from point 1 (defined as x1 y1 z1) to point 2 (define in the same fashion)
 */
double calculateDistance_c(double x1, double y1, double z1, double x2, double y2, double z2) {
    double deltas[3] = {absd(x1-x2), absd(y1-y2), absd(z1-z2)};
    
    return sqrt(square(deltas[0]) + square(deltas[1]) + square(deltas[2]));
}

/*
 Calculate the distance from point a to point b
 */
double calculateDistance_p(Vec3D a, Vec3D b) {
    return calculateDistance_c(a.x, a.y, a.z, b.x, b.y, b.z);
}
