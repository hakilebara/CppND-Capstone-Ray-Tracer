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
