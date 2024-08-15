#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include "world.h"
#include "tuple.h"
#include "transform.h"
#include "ray.h"

// Creating a world
TEST(World, CreatingWorld)
{
  World w{};
  EXPECT_EQ(w.objects.size(), 0);
  EXPECT_EQ(w.light, std::nullopt);
}

// The default world
TEST(World, DefaultWorld)
{
  PointLight light{Point{-10, 10, -10}, Color{1, 1, 1}};
  Sphere s1{};
  s1.material = Material{};
  s1.material.color = Color{0.8, 1.0, 0.6};
  s1.material.diffuse = 0.7;
  s1.material.specular = 0.2;

  Sphere s2{};
  s2.transform = scaling(0.5, 0.5, 0.5);

  World w = default_world();
  EXPECT_EQ(w.light.value(), light);
  EXPECT_EQ(w.objects.size(), 2);
}

// Intersect a world with a ray
TEST(World, IntersectWorldWithRay)
{
  World w = default_world();
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Intersections xs = intersect_world(w, r);
  EXPECT_EQ(xs.count(), 4);
  EXPECT_EQ(xs[0].t, 4);
  EXPECT_EQ(xs[1].t, 4.5);
  EXPECT_EQ(xs[2].t, 5.5);
  EXPECT_EQ(xs[3].t, 6);
}

// Shading an intersection
TEST(World, ShadingIntersection)
{
  World w = default_world();
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere shape = w.objects[0];
  Intersection i{4, shape};

  Computations comps = prepare_computations(i, r);
  Color c = shade_hit(w, comps);
  EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

// Shading an intersection from the inside
TEST(World, ShadingIntersectionFromTheInside)
{
  World w = default_world();
  w.light = PointLight{Point{0, 0.25, 0}, Color{1, 1, 1}};
  Ray r{Point{0,0,0}, Vector{0,0,1}};
  Sphere shape = w.objects[1];
  Intersection i{0.5, shape};
  Computations comps = prepare_computations(i, r);
  Color c = shade_hit(w, comps);
  EXPECT_EQ(c, Color(0.90498, 0.90498, 0.90498));
}


// The color when a ray misses
TEST(World, ColorWhenRayMiss)
{
  World w = default_world();
  Ray r{Point{0, 0, -5}, Vector{0, 1, 0}};
  Color c = color_at(w, r);
  EXPECT_EQ(c, Color(0, 0, 0));
}

// The color when a ray hits
TEST(World, ColorWhenRayHit)
{
  World w = default_world();
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Color c = color_at(w, r);
  EXPECT_EQ(c, Color(0.38066, 0.47583, 0.2855));
}

// The color with an intersection behind the ray
TEST(World, ColorWithIntersectionBehindRay)
{
  World w = default_world();
  Sphere outer = w.objects[0]; // the first object in w
  outer.material.ambient = 1;
  Sphere inner = w.objects[1]; // the second object in w
  inner.material.ambient = 1;
  inner.material.color = Color{0.1, 0.1, 0.1};

  Ray r{Point{0, 0, 0.75}, Vector{0, 0, -1}};
  Color c = color_at(w, r);
  EXPECT_EQ(c, inner.material.color);
}
