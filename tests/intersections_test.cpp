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

// Precomputing the state of an intersection
TEST(Intersections, PrecomputingIntersectionState)
{
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere shape{};
  Intersection i{4, shape};
  Computations comps = prepare_computations(i, r);
  EXPECT_EQ(comps.t, i.t);
  EXPECT_EQ(comps.object, i.object);
  EXPECT_EQ(comps.point, Point(0, 0, -1));
  EXPECT_EQ(comps.eyev, Vector(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector(0, 0, -1));
}

// The hit, when an intersection occurs on the outside
TEST(Intersections, HitIntersectionOnTheOutside)
{
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere shape{};
  Intersection i{4, shape};
  Computations comps = prepare_computations(i, r);
  EXPECT_FALSE(comps.inside);
}

// The hit, when an intersection occurs on the inside
TEST(Intersections, HitIntersectionOnTheInside)
{
  Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
  Sphere shape{};
  Intersection i{1, shape};
  Computations comps = prepare_computations(i, r);
  EXPECT_EQ(comps.point, Point(0, 0, 1));
  EXPECT_EQ(comps.eyev, Vector(0, 0, -1));
  EXPECT_TRUE(comps.inside);
  // normal would have been (0, 0, 1), but is inverted
  EXPECT_EQ(comps.normalv, Vector(0, 0, -1));
}
