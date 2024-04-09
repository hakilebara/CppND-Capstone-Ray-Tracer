#include <cmath>
#include "maths.h"

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
