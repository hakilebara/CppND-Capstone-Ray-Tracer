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

// Testing an invertible matrix for invertibility
TEST(Matrices, Intertibility)
{
  Matrix A{
    { 6,  4,  4,  4},
    { 5,  5,  7,  6},
    { 4, -9,  3, -7},
    { 9,  1,  7, -6}
  };
  EXPECT_EQ(determinant(A), -2120);
  EXPECT_EQ(is_invertible(A), true);
}

// Testing an noninvertible matrix for invertibility
TEST(Matrices, NonIntertibility)
{
  Matrix A{
    {-4,  2, -2, -3},
    { 9,  6,  2,  6},
    { 0, -5,  1, -5},
    { 0,  0,  0,  0}
  };
  EXPECT_EQ(determinant(A), 0);
  EXPECT_EQ(is_invertible(A), false);
}

// Calculating the inverse of a matrix
TEST(Matrices, Inverse01)
{
  Matrix A{
    {-5,  2,  6, -8},
    { 1, -5,  1,  8},
    { 7,  7, -6, -7},
    { 1, -3,  7,  4}
  };
  Matrix B = inverse(A);
  Matrix C{
    {  0.21805,  0.45113,  0.24060, -0.04511 },
    { -0.80827, -1.45677, -0.44361,  0.52068 },
    { -0.07895, -0.22368, -0.05263,  0.19737 },
    { -0.52256, -0.81391, -0.30075,  0.30639 }
  };
  EXPECT_EQ(determinant(A), 532);
  EXPECT_EQ(cofactor(A, 2, 3), -160);
  EXPECT_EQ(B[3][2], -160.0/532.0);
  EXPECT_EQ(B[2][3], 105.0/532.0);
  EXPECT_EQ(B, C);
}

// Calculating the inverse of another matrix
TEST(Matrices, Inverse02)
{
  Matrix A{
    {  8,  -5,  9,  2 },
    {  7,   5,  6,  1 },
    { -6,   0,  9,  6 },
    { -3,   0, -9, -4 },
  };

  Matrix B{
    { -0.15385, -0.15385, -0.28205, -0.53846 },
    { -0.07692, 0.12308, 0.02564, 0.03077 },
    { 0.35897, 0.35897, 0.43590, 0.92308 },
    { -0.69231, -0.69231, -0.76923, -1.92308 }
  };
  EXPECT_EQ(inverse(A), B);
}

// Calculating the inverse of a third matrix
TEST(Matrices, Inverse03)
{
  Matrix A{
    { 9, 3, 0, 9 },
    { -5, -2, -6, -3 },
    { -4, 9, 6, 4 },
    { -7, 6, 6, 2 }
  };

  Matrix B{
    { -0.04074, -0.07778, 0.14444, -0.22222 },
    { -0.07778, 0.03333, 0.36667, -0.33333 },
    { -0.02901, -0.14630, -0.10926, 0.12963 },
    { 0.17778, 0.06667, -0.26667, 0.33333 }
  };

  EXPECT_EQ(inverse(A), B);
}

// Multiplying a product by its inverse
TEST(Matrices, InverseMultiplication)
{
  Matrix A{
    {  3, -9,  7,  3 },
    {  3, -8,  2, -9 },
    { -4,  4,  4,  1 },
    { -6,  5, -1,  1 }
  };

  Matrix B{
    { 8, 2, 2, 2 },
    { 3, -1, 7, 0 },
    { 7, 0, 5, 4 },
    { 6, -2, 0, 5 }
  };

  Matrix C = A * B;

  EXPECT_EQ( C * inverse(B), A);
}
