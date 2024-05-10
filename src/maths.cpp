#include <cmath>
#include "maths.h"
#include "matrix.h"

const double EPSILON = 0.00001;

bool equal(double a, double b)
{
  if (std::abs( a - b ) < EPSILON) { return true; }
  else { return false; }
}

double magnitude(const Vector& v)
{
  return std::sqrt(
    std::pow(v.x, 2)
    + std::pow(v.y, 2)
    + std::pow(v.z, 2)
    + std::pow(v.w, 2)
  );
}

Vector normalize(const Vector& v)
{
  return Vector(
      v.x / magnitude(v),
      v.y / magnitude(v),
      v.z / magnitude(v)
  );
}

double dot(const Vector& a, const Vector&b)
{
  return a.x * b.x +
         a.y * b.y +
         a.z * b.z +
         a.w * b.w;
}

Vector cross(const Vector& a, const Vector& b)
{
  return Vector(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
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
