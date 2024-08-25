#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "world.h"

struct Camera
{
  Camera(const double hsize, const double vsize, const double field_of_view) : hsize(hsize), vsize(vsize), field_of_view(field_of_view){}

  Matrix transform = Matrix::identity_matrix;
  double pixel_size();

  const double hsize, vsize;
  const double field_of_view;
  double half_width, half_height;
};

Ray ray_for_pixel(Camera& camera, double px, double py);

Canvas render(Camera& camera, World& world);

#endif
