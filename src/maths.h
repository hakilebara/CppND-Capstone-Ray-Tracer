#ifndef MATHS_H
#define MATHS_H

#include <numbers>
#include "tuple.h"
#include "sphere.h"

inline constexpr double pi = std::numbers::pi;

bool equal(double, double);
double magnitude(const Vector&);
Vector normalize(const Vector&);
double dot(const Vector&, const Vector&);
Vector cross(const Vector&, const Vector&);
Vector normal_at(const Sphere&, const Point&);
#endif
