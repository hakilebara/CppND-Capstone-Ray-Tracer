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

// Transposing a matrix
TEST(Matrices, TransposeMatrix)
{
  Matrix A{
    {0, 9, 3, 0},
    {9, 8, 0, 8},
    {1, 8, 5, 3},
    {0, 0, 5, 8}
  };
  Matrix transposed{
    {0, 9, 1, 0},
    {9, 8, 8, 0},
    {3, 0, 5, 5},
    {0, 8, 3, 8}
  };
  EXPECT_EQ(transpose(A), transposed);
}

// Transposing the identity matrix
TEST(Matrices, TransposeIdentityMatrix)
{
  EXPECT_EQ(transpose(Matrix::identity_matrix), Matrix::identity_matrix);
}

// Calculating the determinant of a 2x2 matrix
TEST(Matrices, Determinant2x2)
{
  Matrix A{
    { 1, 5 },
    {-3, 2 }
  };
  EXPECT_EQ(determinant(A), 17);
}

// A submatrix of a 3x3 matrix is a 2x2 matrix
TEST(Matrices, Submatrix3x3)
{
  Matrix A{
    {  1,  5,  0 },
    { -3,  2,  7 },
    {  0,  6, -3 }
  };

  Matrix B{
    { -3, 2 },
    {  0, 6 }
  };
  EXPECT_EQ(submatrix(A, 0, 2), B);
}

// A submatrix of a 4x4 matrix is a 3x3 matrix
TEST(Matrices, Submatrix4x4)
{
  Matrix A{
    { -6,  1,  1,  6},
    { -8,  5,  8,  6},
    { -1,  0,  8,  2},
    { -7,  1, -1,  1}
  };

  Matrix B{
    { -6,  1,  6},
    { -8,  8,  6},
    { -7, -1,  1}
  };

  EXPECT_EQ(submatrix(A, 2, 1), B);
}

// Calculating a minor of a 3x3 matrix
TEST(Matrices, Minor3x3)
{
  Matrix A{
    { 3,  5,  0 },
    { 2, -1, -7 },
    { 6, -1,  5 }
  };

  Matrix B = submatrix(A, 1, 0);
  EXPECT_EQ(determinant(B), 25);
  EXPECT_EQ(minor(A, 1, 0), 25);
}

// Calculating a cofactor of a 3x3 matrix
TEST(Matrices, Cofactor3x3)
{
  Matrix A{
    { 3,  5,  0 },
    { 2, -1, -7 },
    { 6, -1,  5 }
  };
  EXPECT_EQ(minor(A, 0, 0), -12);
  EXPECT_EQ(cofactor(A, 0, 0), -12);
  EXPECT_EQ(minor(A, 1, 0), 25);
  EXPECT_EQ(cofactor(A, 1, 0), -25);
}

// Calculating the determinant of a 3x3 matrix
TEST(Matrices, Determinant3x3)
{
  Matrix A{
    {  1,  2,  6 },
    { -5,  8, -4 },
    {  2,  6,  4 }
  };
  EXPECT_EQ(cofactor(A, 0, 0),  56);
  EXPECT_EQ(cofactor(A, 0, 1),  12);
  EXPECT_EQ(cofactor(A, 0, 2), -46);
  EXPECT_EQ(determinant(A), -196);

}

// Calculating the determinant of a 4x4 matrix
TEST(Matrices, Determinant4x4)
{
  Matrix A{
    { -2, -8,  3,  5},
    { -3,  1,  7,  3},
    {  1,  2, -9,  6},
    { -6,  7,  7, -9}
  };
  EXPECT_EQ(cofactor(A, 0, 0),  690);
  EXPECT_EQ(cofactor(A, 0, 1),  447);
  EXPECT_EQ(cofactor(A, 0, 2),  210);
  EXPECT_EQ(cofactor(A, 0, 3),   51);
  EXPECT_EQ(determinant(A), -4071);
}
