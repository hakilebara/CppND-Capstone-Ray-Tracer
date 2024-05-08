#include <cmath>
#include <algorithm>
#include "ray.h"
#include "maths.h"

Ray::Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}

Point position(Ray ray, double t)
{
  return ray.origin + ray.direction * t;
}

Intersections intersect(Sphere sphere, Ray ray)
{
  // The vector from the sphere's center, to the ray origin
  // the sphere is centeredd at the world origin
  Vector sphere_to_ray = ray.origin - Point{0, 0, 0};
  double a = dot(ray.direction, ray.direction);
  double b = 2 * dot(ray.direction, sphere_to_ray);
  double c = dot(sphere_to_ray, sphere_to_ray) - 1;

  double discriminant = std::pow(b, 2) - 4 * a * c;

  if (discriminant < 0) return std::vector<Intersection>{};

  double t1 = (-b - std::sqrt(discriminant)) / ( 2 * a );
  double t2 = (-b + std::sqrt(discriminant)) / ( 2 * a );

  std::vector<Intersection> xs{ {t1, sphere}, {t2, sphere} };
  return Intersections{xs};
}

Intersection::Intersection(double t, Sphere object) : t(t), object(object) {}

std::optional<Intersection> hit(const Intersections& xs)
{
  for (auto& i : xs.data) if(i.t >= 0) return i;
  return std::nullopt;
}

Ray transform(const Ray& ray, const Matrix& transform)
{
  return Ray{{transform * ray.origin}, {transform * ray.direction}};
}
