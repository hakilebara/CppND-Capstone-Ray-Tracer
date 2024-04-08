#include <gtest/gtest.h>
#include "tuple.h"
#include "maths.h"

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

// Subtracting two points
TEST(Tuples, SubstractingTwoPoints)
{
  Point p1{3, 2, 1};
  Point p2{5, 6, 7};
  ASSERT_EQ(p1 - p2, Vector(-2, -4, -6));
}

// Substracting a vector from a point
TEST(Tuples, SubtractingVectorFromPoint)
{
  Point p{3, 2, 1};
  Vector v{5, 6, 7};
  ASSERT_EQ(p - v, Point(-2, -4, -6));
}

// Substracting two vectors
TEST(Tuples, SubstractingTwoVectors)
{
  Vector v1{3, 2, 1};
  Vector v2{5, 6, 7};
  ASSERT_EQ(v1 - v2, Vector(-2, -4, -6));
}

// Substracting a vector from the zero vector
TEST(Tuples, SubtractingVectorFromZeroVector)
{
  Vector zero{0, 0, 0};
  Vector v{1, -2, 3};
  ASSERT_EQ(zero - v, Vector(-1, 2, -3));
}

// Negating a tuple
TEST(Tuples, NegatingATuple)
{
  Tuple a{1, -2, 3, -4};
  ASSERT_EQ(-a, Tuple(-1, 2, -3, 4));
}

// Multiplying a tuple by a scalar
TEST(Tuples, MultiplyTupleByScalar)
{
  Tuple a{1, -2, 3, -4};
  ASSERT_EQ(a * 3.5, Tuple(3.5, -7, 10.5, -14));
}

// Multiplying a tuple by a fraction
TEST(Tuples, MultiplyTupleByFraction)
{
  Tuple a{1, -2, 3, -4};
  ASSERT_EQ(a * 0.5, Tuple(0.5, -1, 1.5, -2));
}

// Dividing a tuple by a scalar
TEST(Tuples, DividingTupleByScalar)
{
  Tuple a{1, -2, 3, -4};
  ASSERT_EQ(a / 2, Tuple(0.5, -1, 1.5, -2));
}

// Computing the magnitude of vector(1, 0, 0)
TEST(Tuples, ComputingVectorMagnitude01)
{
  Vector v{1, 0, 0};
  ASSERT_EQ(magnitude(v), 1);
}

// Computing the magnitude of vector(0, 1, 0)
TEST(Tuples, ComputingVectorMagnitude02)
{
  Vector v{0, 1, 0};
  ASSERT_EQ(magnitude(v), 1);
}

// Computing the magnitude of vector(0, 0, 1)
TEST(Tuples, ComputingVectorMagnitude03)
{
  Vector v{0, 0, 1};
  ASSERT_EQ(magnitude(v), 1);
}

// Computing the magnitude of vector(1, 2, 3)
TEST(Tuples, ComputingVectorMagnitude04)
{
  Vector v{1, 2, 3};
  ASSERT_EQ(magnitude(v), std::sqrt(14));
}

// Computing the magnitude of vector(-1, -2, -3)
TEST(Tuples, ComputingVectorMagnitude05)
{
  Vector v{-1, -2, -3};
  ASSERT_EQ(magnitude(v), std::sqrt(14));
}
