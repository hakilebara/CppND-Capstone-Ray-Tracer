#ifndef SPHERE_H
#define SPHERE_H

#include "matrix.h"
#include "tuple.h"
#include "material.h"

struct Sphere 
{
  Sphere();
  bool operator==(const Sphere& lhs) const { return id == lhs.id; }

  int id;
  Matrix transform = Matrix::identity_matrix;
  Point origin{0, 0, 0};
  Material material{};
};

void set_transform(Sphere&, const Matrix&);
Vector normal_at(const Sphere&, const Point&);

#endif
