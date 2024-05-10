#include <cmath>
#include "maths.h"

const double EPSILON = 0.00001;

bool equal(double a, double b)
{
  if (std::abs( a - b ) < EPSILON) { return true; }
  else { return false; }
}
