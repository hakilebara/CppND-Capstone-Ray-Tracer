#include <gtest/gtest.h>
#include <vector>
#include "ray.h"

// A ray intersects a sphere at two points
TEST(Spheres, RaySphereIntersect)
{
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere s{};
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].t, 4.0);
  EXPECT_EQ(xs[1].t, 6.0);
}

// A ray intersects a sphere at a tangent
TEST(Spheres, RaySphereIntersectTangent)
{
  Ray r{Point{0, 1, -5}, Vector{0, 0, 1}};
  Sphere s{};
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].t, 5.0);
  EXPECT_EQ(xs[1].t, 5.0);
}

//  A ray misses a sphere
TEST(Spheres, RaySphereMiss)
{
  Ray r{Point{0, 2, -5}, Vector{0, 0, 1}};
  Sphere s{};
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 0);
}

// A ray originates inside a sphere
TEST(Spheres, RaySphereIntersectInside)
{
  Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
  Sphere s{};
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].t, -1.0);
  EXPECT_EQ(xs[1].t, 1.0);
}

// A ray is behind a sphere
TEST(Spheres, RaySphereBehind)
{
  Ray r{Point{0, 0, 5}, Vector{0, 0, 1}};
  Sphere s{};
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].t, -6.0);
  EXPECT_EQ(xs[1].t, -4.0);
}

// Intersect sets the object on the intersection
TEST(Spheres, RaySphereIntersectObject)
{
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere s{};
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].object, s);
  EXPECT_EQ(xs[1].object, s);
}
