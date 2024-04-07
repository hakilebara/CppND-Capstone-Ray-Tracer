#ifndef UTILS_H
#define UTILS_H

#include <cmath>

const double EPSILON = 0.00001;

inline bool equal(double a, double b)
{
  if (std::abs( a - b ) < EPSILON) { return true; }
  else { return false; }
}
#endif
