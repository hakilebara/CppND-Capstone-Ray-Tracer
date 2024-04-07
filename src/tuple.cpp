#include "tuple.h"    

Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

bool Tuple::isPoint()
{
  return this->w == 1;
}

bool Tuple::isVector()
{
  return this->w == 0;
}

bool operator==(const Tuple& lhs, const Tuple& rhs)
{
  return equal(lhs.x, rhs.x)
    && equal(lhs.y, rhs.y)
    && equal(lhs.z, rhs.z)
    && equal(lhs.w, rhs.w);
}

Tuple operator+(const Tuple& lhs, const Tuple& rhs)
{
  return Tuple(
    lhs.x + rhs.x,
    lhs.y + rhs.y,
    lhs.z + rhs.z,
    lhs.w + rhs.w
  );
}

Point::Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {}

Vector::Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {}
