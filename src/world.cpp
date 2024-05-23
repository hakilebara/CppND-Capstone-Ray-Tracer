#include <iterator>
#include "world.h"
#include "transform.h"

World default_world()
{
  PointLight light{Point{-10, 10, -10}, Color{1, 1, 1}};
  Sphere s1{};
  s1.material = Material{};
  s1.material.color = Color{0.8, 1.0, 0.6};
  s1.material.diffuse = 0.7;
  s1.material.specular = 0.2;

  Sphere s2{};
  s2.transform = scaling(0.5, 0.5, 0.5);

  World w{};
  w.light = light;
  w.objects.push_back(s1);
  w.objects.push_back(s2);

  return w;
}

Intersections intersect_world(World w, Ray r)
{
  std::vector<Intersection> world_xs;
  for(auto object : w.objects)
  {
    Intersections xs = intersect(object, r);
    world_xs.insert(std::end(world_xs), std::begin(xs.data), std::end(xs.data));
  }
  std::sort(world_xs.begin(), world_xs.end(),
  [](const Intersection& a, const Intersection& b) {
      return a.t < b.t;
  });
  return Intersections{world_xs};
}
