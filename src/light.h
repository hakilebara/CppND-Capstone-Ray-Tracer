#ifndef LIGHT_H
#define LIGHT_H

#include "tuple.h"
#include "material.h"
#include "light.h"

struct PointLight
{
  PointLight(Point position, Color intensity) : position(position), intensity(intensity) {}

  Point position;
  Color intensity;

  bool operator==(const PointLight& rhs) const
  {
    return position == rhs.position
      && intensity == rhs.intensity;
  }
};

Color lighting(const Material&, const PointLight&, const Point&, const Vector&, const Vector&);

#endif
