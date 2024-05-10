#include <gtest/gtest.h>
#include "tuple.h"
#include "light.h"

// A point light has a position and intensity
TEST(Lights, PointLightHasPositionAndIntensity)
{
  Color intensity{1, 1, 1};
  Point position{0, 0, 0};
  PointLight light{position, intensity};
  EXPECT_EQ(light.position, position);
  EXPECT_EQ(light.intensity, intensity);
}
