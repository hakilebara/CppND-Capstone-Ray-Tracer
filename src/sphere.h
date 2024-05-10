#ifndef SPHERE_H
#define SPHERE_H

#include "matrix.h"

struct Sphere 
{
  Sphere();
  bool operator==(const Sphere& lhs) const { return id == lhs.id; }

  int id;
  Matrix transform = Matrix::identity_matrix;

};

void set_transforms(Sphere&, const Matrix&);

#endif
