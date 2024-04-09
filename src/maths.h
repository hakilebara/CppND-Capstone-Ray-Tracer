#ifndef MATHS_H
#define MATHS_H

#include "tuple.h"

bool equal(double, double);
double magnitude(const Vector&);
Vector normalize(const Vector&);
double dot(const Vector&, const Vector&);
Vector cross(const Vector&, const Vector&);

#endif
