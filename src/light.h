#ifndef LIGHT_H
#define LIGHT_H

#include "tuple.h"

struct PointLight
{
  PointLight(Point position, Color intensity) : position(position), intensity(intensity) {}

  Point position;
  Color intensity;
};

#endif
