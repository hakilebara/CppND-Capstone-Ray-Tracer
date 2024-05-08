#include <gtest/gtest.h>
#include <vector>
#include "ray.h"

// An intersection encapsulates t and object
TEST(Intersections, IntersectionEncapsulation)
{
  Sphere s{};
  Intersection i{3.5, s};
  EXPECT_EQ(i.t, 3.5);
  EXPECT_EQ(i.object, s);
}

// Aggregating intersections
TEST(Intersections, AggregatingIntersections)
{
  Sphere s{};
  Intersection i1{1, s};
  Intersection i2{2, s};
  Intersections xs{std::vector<Intersection>{i1, i2}};
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].t, 1);
  EXPECT_EQ(xs[1].t, 2);
}

// The hit, when all intersections have positive t
TEST(Intersections, AllPositiveTHits)
{
  Sphere s{};
  Intersection i1{1, s};
  Intersection i2{2, s};
  Intersections xs{std::vector<Intersection>{i1, i2}};
  std::optional<Intersection> i = hit(xs);
  EXPECT_EQ(i, i1);
}

// The hit, when some intersections have negative t
TEST(Intersections, SomeNegativeTHits)
{
  Sphere s{};
  Intersection i1{-1, s};
  Intersection i2{1, s};
  Intersections xs{std::vector<Intersection>{i2, i1}};
  std::optional<Intersection> i = hit(xs);
  EXPECT_EQ(i, i2);
}

// The hit, when all intersections have negative t
TEST(Intersections, AllNegativeTHits)
{
  Sphere s{};
  Intersection i1{-2, s};
  Intersection i2{-1, s};
  Intersections xs{std::vector<Intersection>{i2, i1}};
  std::optional<Intersection> i = hit(xs);
  EXPECT_EQ(i, std::nullopt);
}

// The hit is always the lowest nonnegative intersection
TEST(Intersections, AlwaysLowestNonNegT)
{
  Sphere s{};
  Intersection i1{5, s};
  Intersection i2{7, s};
  Intersection i3{-3, s};
  Intersection i4{2, s};
  Intersections xs{std::vector<Intersection>{i1, i2, i3, i4}};
  std::optional<Intersection> i = hit(xs);
  EXPECT_EQ(i, i4);
}
