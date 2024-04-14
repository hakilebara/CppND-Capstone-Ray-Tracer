#include <gtest/gtest.h>
#include "matrix.h"
#include "tuple.h"

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

// Matrix equality with identical matrices
TEST(Matrices, MatrixEquality)
{
  Matrix A{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2},
  };

  Matrix B{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2},
  };
  EXPECT_EQ(A, B);
}

// Matrix equality with different matrices
TEST(Matrices, MatrixNonEquality)
{
   Matrix A{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2},
  };

  Matrix B{
    {2, 3, 4, 5},
    {6, 7, 8, 9},
    {8, 7, 6, 5},
    {4, 3, 2, 1},
  };
  EXPECT_NE(A, B);
}

// Multiplying two matrices
TEST(Matrices, MultiplyingTwoMatrices)
{
  Matrix A{
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2},
  };

  Matrix B{
    {-2, 1, 2, 3 },
    { 3, 2, 1, -1},
    { 4, 3, 6, 5 },
    { 1, 2, 7, 8 },
  };

  Matrix result{
    {20, 22,  50,  48},
    {44, 54, 114, 108},
    {40, 58, 110, 102},
    {16, 26,  46,  42}
  };
  EXPECT_EQ(A*B, result);
}

// A matrix multiplied by a tuple
TEST(Matrices, MatrixMultipliedByTuple)
{
  Matrix A{
    {1, 2, 3, 4},
    {2, 4, 4, 2},
    {8, 6, 4, 1},
    {0, 0, 0, 1},
  };
  Tuple b{1, 2, 3, 1};
  EXPECT_EQ(A*b, Tuple(18, 24, 33, 1));
}

// Multiplying a matrix by the identity matrix
TEST(Matrices, IdentityMatrix)
{
  Matrix A{
    {0, 1,  2,  4},
    {1, 2,  4,  8},
    {2, 4,  8, 16},
    {4, 8, 16, 32},
  };

  EXPECT_EQ(A*Matrix::identity_matrix, A);
}

// Multiplying the identity matrix by a tuple
TEST(Matrices, IdentityMatrixTuple)
{
  Tuple a{1, 2, 3, 4};
  EXPECT_EQ(Matrix::identity_matrix*a, a);
}
