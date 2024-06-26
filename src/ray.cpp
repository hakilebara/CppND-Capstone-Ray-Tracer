#include <cmath>
#include <algorithm>
#include "ray.h"

Ray::Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

Point position(Ray ray, double t)
{
  return ray.origin + ray.direction * t;
}

Intersections intersect(const Sphere& sphere, const Ray& ray)
{
  Ray ray2 = transform(ray, inverse(sphere.transform));
  // The vector from the sphere's center, to the ray origin
  // the sphere is centeredd at the world origin
  Vector sphere_to_ray = ray2.origin - Point{0, 0, 0};
  double a = dot(ray2.direction, ray2.direction);
  double b = 2 * dot(ray2.direction, sphere_to_ray);
  double c = dot(sphere_to_ray, sphere_to_ray) - 1;

  double discriminant = std::pow(b, 2) - 4 * a * c;

  if (discriminant < 0) return std::vector<Intersection>{};

  double t1 = (-b - std::sqrt(discriminant)) / ( 2 * a );
  double t2 = (-b + std::sqrt(discriminant)) / ( 2 * a );

  std::vector<Intersection> xs{ {t1, sphere}, {t2, sphere} };
  return Intersections{xs};
}

std::optional<Intersection> hit(const Intersections& xs)
{
  for (auto& i : xs.data) if(i.t >= 0) return i;
  return std::nullopt;
}

Ray transform(const Ray& ray, const Matrix& transform)
{
  return Ray{{transform * ray.origin}, {transform * ray.direction}};
}

Computations prepare_computations(const Intersection& intersection, const Ray& ray)
{
  // instantiate a data structure for storing some precomputed values
  Point point = position(ray, intersection.t);
  Computations comps{intersection.t, intersection.object, point, -ray.direction, normal_at(intersection.object, point)};

  // copy the intersection's properties, for convenience
  comps.t = intersection.t;
  comps.object = intersection.object;

  // precompute some useful values
  comps.point = position(ray, comps.t);
  comps.eyev = -ray.direction;
  comps.normalv = normal_at(comps.object, comps.point);

  if (dot(comps.normalv, comps.eyev) < 0)
  {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  }
  else
  {
    comps.inside = false;
  }

  return comps;
}
