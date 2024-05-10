#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "ray.h"
#include "matrix.h"
#include "transform.h"
#include "maths.h"


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

// A Sphere's default transformation
TEST(Spheres, SphereDefaultTransformation)
{
  Sphere s{};
  EXPECT_EQ(s.transform, Matrix::identity_matrix);
}

// Changing a sphere's transformation
TEST(Spheres, ChangingSphereTransformation)
{
  Sphere s{};
  Matrix t = translation(2, 3, 4);
  set_transform(s, t);
  EXPECT_EQ(s.transform, t);
}

// Intersecting a scaled sphere with a ray
TEST(Spheres, IntersectingScaledSphereWithRay)
{
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere s{};
  set_transform(s, scaling(2, 2, 2));
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 2);
  EXPECT_EQ(xs[0].t, 3);
  EXPECT_EQ(xs[1].t, 7);
}

// Intersecting a translated sphere with a ray
TEST(Spheres, IntersectingTranslatedSphereWithRay)
{
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  Sphere s{};
  set_transform(s, translation(5, 0, 0));
  Intersections xs = intersect(s, r);
  EXPECT_EQ(xs.count(), 0);
}

// The normal on a sphere at a point on the x axis
TEST(Spheres, NormalOnSphereAtPointX)
{
  Sphere s{};
  Vector n = normal_at(s, Point{1, 0, 0});
  EXPECT_EQ(n, Vector(1, 0, 0));
}

// The normal on a sphere at a point on the y axis
TEST(Spheres, NormalOnSphereAtPointY)
{
  Sphere s{};
  Vector n = normal_at(s, Point{0, 1, 0});
  EXPECT_EQ(n, Vector(0, 1, 0));
}

// The normal on a sphere at a point on the z axis
TEST(Spheres, NormalOnSphereAtPointZ)
{
  Sphere s{};
  Vector n = normal_at(s, Point{0, 0, 1});
  EXPECT_EQ(n, Vector(0, 0, 1));
}
// The normal on a sphere at a nonaxial point
TEST(Spheres, NormalOnSphereAtNonaxialPoint)
{
  Sphere s{};
  Vector n = normal_at(s, Point{ std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3 });
  EXPECT_EQ(n, Vector( std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3 ));
}

// Ther normal is a normalized vector
TEST(Spheres, NormalIsNormalizedVector)
{
  Sphere s{};
  Vector n = normal_at(s, Point{ std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3 });
  EXPECT_EQ(n, normalize(n));
}

// Computing the normal on a translated sphere
TEST(Spheres, NormalOnTranslatedSphere)
{
  Sphere s{};
  set_transform(s, translation(0, 1, 0));
  Vector n = normal_at(s, Point{0, 1.70711, -0.70711});
  EXPECT_EQ(n, Vector(0, 0.70711, -0.70711));
}

// Computing the normal on a transformed sphere
TEST(Spheres, NormalOnTransformedSphere)
{
  Sphere s{};
  Matrix m = scaling(1, 0.5, 1) * rotation_z(pi/5);
  set_transform(s, m);
  Vector n = normal_at(s, Point{0, std::sqrt(2)/2, -std::sqrt(2)/2});
  EXPECT_EQ(n, Vector(0, 0.97014, -0.24254));
}
