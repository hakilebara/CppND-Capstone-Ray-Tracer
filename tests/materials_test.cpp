#include <gtest/gtest.h>
#include <cmath>
#include "tuple.h"
#include "material.h"
#include "light.h"

// The default material
TEST(Materials, DefaultMaterial)
{
  Material m{};
  EXPECT_EQ(m.color, Color(1, 1, 1)) ;
  EXPECT_EQ(m.ambient, 0.1);
  EXPECT_EQ(m.diffuse, 0.9);
  EXPECT_EQ(m.specular, 0.9);
  EXPECT_EQ(m.shininess, 200.0);
}

// Lighting with the eye between the light and the surface
TEST(Materials, LightingWithEyeBetweenLightAndSurface)
{
  Material m{};
  Point position{0, 0, 0};
  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  PointLight light{Point{0, 0, -10}, Color{1, 1, 1}};
  Color result = lighting(m, light, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

// Lighting with the eye between light and surface, eye offset 45 degrees
TEST(Materials, LightingWithEyeBetweenLightAndSurfaceEyeOffset45deg)
{
  Material m{};
  Point position{0, 0, 0};
  Vector eyev{ 0, std::sqrt(2)/2, -std::sqrt(2)/2 };
  Vector normalv{0, 0, -1};
  PointLight light{Point{0, 0, -10}, Color{1, 1, 1}};
  Color result = lighting(m, light, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

// Lighting with eye opposite surface, light offset 45 degrees
TEST(Materials, LightingWithEyeOppositeSurfaceLightOffset45deg)
{
  Material m{};
  Point position{0, 0, 0};
  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  PointLight light{Point{0, 10, -10}, Color{1, 1, 1}};
  Color result = lighting(m, light, position, eyev, normalv);
  EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

// Lighting with eye in the path of the reflection vector
TEST(Materials, LightingWithEyeInPathOfReflectionVector)
{
  Material m{};
  Point position{0, 0, 0};
  Vector eyev{0, -std::sqrt(2)/2, -std::sqrt(2)/2};
  Vector normalv{0, 0, -1};
  PointLight light{Point{0, 10, -10}, Color{1, 1, 1}};
  Color result = lighting(m, light, position, eyev, normalv);
  EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

// Lighting with the light behind the surface
TEST(Materials, LightingWithLightBehindSurface)
{
  Material m{};
  Point position{0, 0, 0};
  Vector eyev{0, 0, -1};
  Vector normalv{0, 0, -1};
  PointLight light{Point{0, 0, 10}, Color{1, 1, 1}};
  Color result = lighting(m, light, position, eyev, normalv);
  EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}
