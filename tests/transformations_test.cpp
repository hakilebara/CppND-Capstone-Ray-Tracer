#include <gtest/gtest.h>
#include "transform.h"
#include "matrix.h"
#include "tuple.h"
#include "maths.h"

// Multiplying by a transalation matrix
TEST(Transformations, MultiplyByTranslationMatrix)
{
  Matrix transform = translation(5, -3, 2);
  Point p{-3, 4, 5};
  EXPECT_EQ(transform * p, Point(2, 1, 7));
}

// Multiplying by the inverse of a translation matrix
TEST(Transformations, MultiplyByTranslationMatrixInverse)
{
  Matrix transform = translation(5, -3, 2);
  Matrix inv = inverse(transform);
  Point p{-3, 4, 5};
  EXPECT_EQ(inv * p, Point(-8, 7, 3));
}

// Translation does not affect vectors
TEST(Transformations, TranslatingVectors)
{
  Matrix transform = translation(5, -3, 2);
  Vector v{-3, 4, 5};
  EXPECT_EQ(transform * v, v);
}

// A scaling matrix applied to a point
TEST(Transformations, ScalingPoint)
{
  Matrix transform = scaling(2, 3, 4);
  Point p{-4, 6, 8};
  EXPECT_EQ(transform * p, Point(-8, 18, 32));
}

// A scaling matrix applied to a vector
TEST(Transformations, ScalingVector)
{
  Matrix transform = scaling(2, 3, 4);
  Vector v{-4, 6, 8};
  EXPECT_EQ(transform * v, Vector(-8, 18, 32));
}

// Multiplying by the inverse of a scaling matrix
TEST(Transformations, MultiplyingByInverseOfScalingMatrix)
{
  Matrix transform = scaling(2, 3, 4);
  Matrix inv = inverse(transform);
  Vector v{-4, 6, 8};
  EXPECT_EQ(inv * v, Vector(-2, 2, 2));
}

// Reflection is scaling by a negative value
TEST(Transformations, Reflexion)
{
  Matrix transform = scaling(-1, 1, 1);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(-2, 3, 4));
}

// Rotating a point around the x axis
TEST(Transformations, XAxisRotation)
{
  Point p{0, 1, 0};
  Matrix half_quarter = rotation_x(pi/4);
  Matrix inv = inverse(half_quarter);
  EXPECT_EQ(inv * p, Point(-0, std::sqrt(2)/2, -std::sqrt(2)/2));
}

// Rotating a point around the y axis
TEST(Transformations, YAxisRotation)
{
  Point p{0, 0, 1};
  Matrix half_quarter = rotation_y(pi/4);
  Matrix full_quarter = rotation_y(pi/2);
  EXPECT_EQ(half_quarter * p, Point(std::sqrt(2)/2, 0, std::sqrt(2)/2));
  EXPECT_EQ(full_quarter * p, Point(1, 0, 0));
}

// Rotating a point around the z axis
TEST(Transformations, ZAxisRotation)
{
  Point p{0, 1, 0};
  Matrix half_quarter = rotation_z(pi/4);
  Matrix full_quarter = rotation_z(pi/2);
  EXPECT_EQ(half_quarter * p, Point(-std::sqrt(2)/2, std::sqrt(2)/2, 0));
  EXPECT_EQ(full_quarter * p, Point(-1, 0, 0));
}

// A shearing transformation moves x in proportion to y
TEST(Transformations, ShearingXtoY)
{
  Matrix transform = shearing(1, 0, 0, 0, 0, 0);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(5, 3, 4));
}

// A shearing transformation moves x in proportion to z
TEST(Transformations, ShearingXtoZ)
{
  Matrix transform = shearing(0, 1, 0, 0, 0, 0);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(6, 3, 4));
}

// A shearing transformation moves y in proportion to x
TEST(Transformations, ShearingYtoX)
{
  Matrix transform = shearing(0, 0, 1, 0, 0, 0);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(2, 5, 4));
}

// A shearing transformation moves y in proportion to z
TEST(Transformations, ShearingYtoZ)
{
  Matrix transform = shearing(0, 0, 0, 1, 0, 0);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(2, 7, 4));
}

// A shearing transformation moves z in proportion to x
TEST(Transformations, ShearingZtoX)
{
  Matrix transform = shearing(0, 0, 0, 0, 1, 0);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(2, 3, 6));
}

// A shearing transformation moves z in proportion to y
TEST(Transformation, ShearingZtoY)
{
  Matrix transform = shearing(0, 0, 0, 0, 0, 1);
  Point p{2, 3, 4};
  EXPECT_EQ(transform * p, Point(2, 3, 7));
}

// Individual transformations are applied in sequence
TEST(Transformations, TransformationSequence)
{
  Point p{1, 0, 1};
  Matrix A = rotation_x(pi/2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);

  Point p2 = A * p;
  EXPECT_EQ(p2, Point(1, -1, 0));

  Point p3 = B * p2;
  EXPECT_EQ(p3, Point(5, -5, 0));

  Point p4 = C * p3;
  EXPECT_EQ(p4, Point(15, 0, 7));
}

// Chained transformations must be applied in reverse order
TEST(Transformations, ReverseTransformationSequence)
{
  Point p{1, 0, 1};
  Matrix A = rotation_x(pi/2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);
  Matrix T = C * B * A;
  EXPECT_EQ(T * p, Point(15, 0, 7));
}
