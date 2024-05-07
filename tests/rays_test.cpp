#include <gtest/gtest.h>
#include "ray.h"
#include "tuple.h"

// Creating and querying a ray
TEST(Rays, CreatingARay)
{
  Point origin{1, 2, 3};
  Vector direction{4, 5, 6};
  Ray r{origin, direction};
  EXPECT_EQ(r.origin, origin);
  EXPECT_EQ(r.direction, direction);
}
