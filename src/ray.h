#ifndef RAY_H
#define RAY_H

#include <vector>
#include <optional>
#include "tuple.h"
#include "sphere.h"
#include "matrix.h"

struct Ray
{
  Ray(Point origin, Vector direction);
  Point origin;
  Vector direction;
};

Point position(Ray ray, double t);

struct Intersection
{
  Intersection(double t, Sphere object) : t(t), object(object) {}
  double t;
  Sphere object;
  bool operator==(const Intersection& rhs) const
  {
    return this->t == rhs.t && this->object == rhs.object;
  }
};

struct Intersections
{
  Intersections(std::vector<Intersection> xs) : data(xs) {
    std::sort(data.begin(), data.end(),
    [](const Intersection& a, const Intersection& b) {
        return a.t < b.t;
    });
  }
  Intersection operator[](size_t index) { return data[index]; }
  Intersection operator[](size_t index) const { return data[index]; }

  unsigned int count() const { return data.size(); }

  std::vector<Intersection> data;
};

struct Computations
{
  Computations(double t, Sphere object, Point point, Vector eyev, Vector normalv) :
    t(t),
    object(object),
    point(point),
    eyev(eyev),
    normalv(normalv) {}

  Computations();
  double t;
  Sphere object;
  Point point;
  Vector eyev;
  Vector normalv;
  bool inside;
};

Computations prepare_computations(const Intersection&, const Ray&);

Intersections intersect(const Sphere&, const Ray&);

std::optional<Intersection> hit(const Intersections&);

Ray transform(const Ray&, const Matrix&);

#endif
