#include <gtest/gtest.h>
#include "ray.h"
#include "tuple.h"
#include "transform.h"
#include "matrix.h"

// Creating and querying a ray
TEST(Rays, CreatingARay)
{
  Point origin{1, 2, 3};
  Vector direction{4, 5, 6};
  Ray r{origin, direction};
  EXPECT_EQ(r.origin, origin);
  EXPECT_EQ(r.direction, direction);
}

// Computing a point from a distance
TEST(Rays, ComputingDistanceFromPoint)
{
  Ray r{Point(2,3,4), Vector(1,0,0)};
  EXPECT_EQ(position(r, 0), Point(2, 3, 4));
  EXPECT_EQ(position(r, 1), Point(3, 3, 4));
  EXPECT_EQ(position(r, -1), Point(1, 3, 4));
  EXPECT_EQ(position(r, 2.5), Point(4.5, 3, 4));
}

// Translating a ray
TEST(Rays, TranslatingRay)
{
  Ray r{Point{1, 2, 3}, Vector{0, 1, 0}};
  Matrix m = translation(3, 4, 5);
  Ray r2 = transform(r, m);
  EXPECT_EQ(r2.origin, Point(4, 6, 8));
  EXPECT_EQ(r2.direction, Vector(0, 1, 0));
}

// Scaling a ray
TEST(Rays, ScalingRay)
{
  Ray r{Point{1, 2, 3}, Vector{0, 1, 0}};
  Matrix m = scaling(2, 3, 4);
  Ray r2 = transform(r, m);
  EXPECT_EQ(r2.origin, Point(2, 6, 12));
  EXPECT_EQ(r2.direction, Vector(0, 3, 0));
}
