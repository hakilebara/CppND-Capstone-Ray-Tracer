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
