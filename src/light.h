#ifndef LIGHT_H
#define LIGHT_H

#include "tuple.h"
#include "material.h"

struct PointLight
{
  PointLight(Point position, Color intensity) : position(position), intensity(intensity) {}

  Point position;
  Color intensity;
};

Color lighting(const Material&, const PointLight&, const Point&, const Vector&, const Vector&);

#endif
