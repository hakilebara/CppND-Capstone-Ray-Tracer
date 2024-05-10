#include "sphere.h"
#include <random>

Sphere::Sphere()
{
  std::random_device rd;
  std::uniform_int_distribution<int> dist;
  id = dist(rd);
}

void set_transform(Sphere& sphere, const Matrix& transform)
{
  sphere.transform = transform; 
}

// The normal to a sphere at any point p is given by
// the vector from the center of the sphere to the point p
Vector normal_at(const Sphere& sphere, const Point& world_point)
{
  Point object_point = inverse(sphere.transform) * world_point;
  Vector object_normal = object_point - sphere.origin;
  Vector world_normal = transpose(inverse(sphere.transform)) * object_normal;
  world_normal.w = 0;
  return normalize(world_normal);
}
