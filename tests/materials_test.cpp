#include <gtest/gtest.h>
#include "tuple.h"
#include "material.h"

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
