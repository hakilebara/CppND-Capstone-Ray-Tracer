#include <gtest/gtest.h>
#include "tuple.h"

// A tuple with w=1.0 is a point
TEST(Tuples, IsPoint)
{
  Tuple a{4.3, -4.2, 3.1, 1.0};
  EXPECT_EQ(a.x, 4.3);
  EXPECT_EQ(a.y, -4.2);
  EXPECT_EQ(a.z, 3.1);
  EXPECT_EQ(a.w, 1.0);
  ASSERT_TRUE(a.isPoint());
  ASSERT_FALSE(a.isVector());
}

// A tuple with w=0 is a vector
TEST(Tuples, IsVector)
{
  Tuple a{4.3, -4.2, 3.1, 0.0};
  EXPECT_EQ(a.x, 4.3);
  EXPECT_EQ(a.y, -4.2);
  EXPECT_EQ(a.z, 3.1);
  EXPECT_EQ(a.w, 0.0);
  ASSERT_FALSE(a.isPoint());
  ASSERT_TRUE(a.isVector());
}
