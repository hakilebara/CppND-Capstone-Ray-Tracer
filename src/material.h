#ifndef MATERIAL_H
#define MATERIAL_H

#include "maths.h"
#include "tuple.h"

struct Material
{
  Material() {};

  Color color{1, 1, 1};
  double ambient = 0.1;
  double diffuse = 0.9;
  double specular = 0.9;
  double shininess = 200.0;

  bool operator==(const Material& rhs) const
  {
    return this->color == rhs.color
      && equal(this->ambient, rhs.ambient)
      && equal(this->diffuse, rhs.diffuse)
      && equal(this->specular, rhs.specular)
      && equal(this->shininess, rhs.shininess);
  }
};

#endif
