#include <gtest/gtest.h>
#include "matrix.h"

// Constructing and inspecting a 4x4 matrix
TEST(Matrices, Create4x4)
{
  Matrix M{
    {1,    2,    3,    4   },
    {5.5,  6.5,  7.5,  8.5 },
    {9,    10,   11,   12  },
    {13.5, 14.5, 15.5, 16.5}};

  EXPECT_EQ(M[0][0], 1);
  EXPECT_EQ(M[0][3], 4);
  EXPECT_EQ(M[1][0], 5.5);
  EXPECT_EQ(M[1][2], 7.5);
  EXPECT_EQ(M[2][2], 11);
  EXPECT_EQ(M[3][0], 13.5);
  EXPECT_EQ(M[3][2], 15.5);
}

// A 2x2 matrix ought to be representable
TEST(Matrices, Create2x2)
{
  Matrix M{
    {-3,   5},
    { 1,  -2}
  };
  EXPECT_EQ(M[0][0],-3);
  EXPECT_EQ(M[0][1], 5);
  EXPECT_EQ(M[1][0], 1);
  EXPECT_EQ(M[1][1],-2);
}

// A 3x3 matrix ought to be representable
TEST(Matrices, Create3x3)
{
  Matrix M{
    {-3, 5,  0},
    {1, -2, -7},
    {0, 1,   1}
  };

  EXPECT_EQ(M[0][0], -3);
  EXPECT_EQ(M[1][1], -2);
  EXPECT_EQ(M[2][2], 1);
}
