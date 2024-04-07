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

// point() creates tuples with w=1
TEST(Tuples, CreatePoint)
{
  Point p{4, -4, 3};
  ASSERT_TRUE(p == Tuple(4, -4, 3, 1));
}

// vector() creates tuples with w=0
TEST(Tuples, CreateVector)
{
  Vector v{4, -4, 3};
  ASSERT_TRUE(v == Tuple(4, -4, 3, 0));
}

// Adding two tuples
TEST(Tuples, TupleAddition)
{
  Tuple a1{3, -2, 5, 1};
  Tuple a2{-2, 3, 1, 0};
  ASSERT_EQ(a1 + a2, Tuple(1,1,6,1));
}
