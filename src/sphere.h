#ifndef SPHERE_H
#define SPHERE_H

#include "matrix.h"
#include "tuple.h"

struct Sphere 
{
  Sphere();
  bool operator==(const Sphere& lhs) const { return id == lhs.id; }

  int id;
  Matrix transform = Matrix::identity_matrix;
  Point origin{0, 0, 0};
};

void set_transform(Sphere&, const Matrix&);

#endif
