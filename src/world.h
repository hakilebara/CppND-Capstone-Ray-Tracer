#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <optional>
#include "light.h"
#include "sphere.h"
#include "ray.h"

struct World
{
  std::optional<PointLight> light;
  std::vector<Sphere> objects;
};

World default_world();

Intersections intersect_world(World, Ray);
#endif
