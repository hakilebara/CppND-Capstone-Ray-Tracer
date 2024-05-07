#ifndef RAY_H
#define RAY_H

#include "tuple.h"

struct Ray
{
  Ray(Point origin, Vector direction);
  Point origin;
  Vector direction;
};

#endif
