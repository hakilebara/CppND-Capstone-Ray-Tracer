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
  Intersection(double t, Sphere object);
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
  friend std::optional<Intersection> hit(const Intersections&);
  Intersection operator[](size_t index) { return data[index]; }
  Intersection operator[](size_t index) const { return data[index]; }

  unsigned int count() const { return data.size(); }

  private:
  std::vector<Intersection> data;
};

Intersections intersect(Sphere, Ray);

std::optional<Intersection> hit(const Intersections&);

Ray transform(const Ray&, const Matrix&);

#endif
