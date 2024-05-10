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
