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

Point::Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {}

Vector::Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {}
