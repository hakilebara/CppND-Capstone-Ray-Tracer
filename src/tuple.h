#ifndef TUPLE_H
#define TUPLE_H

#include "utils.h"

struct Tuple 
{
  Tuple(double x, double y, double z, double w);

  bool operator==(const Tuple& rhs)
  {
    return equal(this->x, rhs.x)
      && equal(this->y, rhs.y)
      && equal(this->z, rhs.z)
      && equal(this->w, rhs.w);
  }

  bool isPoint();
  bool isVector();

  double x, y, z, w;
};

struct Point : public Tuple
{
  Point(double x, double y, double z);
};

struct Vector : public Tuple
{
  Vector(double x, double y, double z);
};
#endif
