#include "sphere.h"
#include <random>

Sphere::Sphere()
{
  std::random_device rd;
  std::uniform_int_distribution<int> dist;
  id = dist(rd);
}
