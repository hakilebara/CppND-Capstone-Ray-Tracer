#include "matrix.h"
#include "maths.h"

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list)
{
  for (auto row : list)
  {
    data.push_back(row);
  }
}

std::vector<double>& Matrix::operator[](size_t index)
{
  return data[index];
}

const std::vector<double>& Matrix::operator[](size_t index) const
{
  return data[index];
}

bool Matrix::operator==(const Matrix& rhs) const
{
  for (size_t i = 0; i < this->data.size(); ++i)
  {
    for (size_t j = 0; j < this->data[i].size(); ++j)
    {
      if (!equal(this->data[i][j], rhs[i][j])) { return false; }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& rhs) const
{
  for (size_t i = 0; i < this->data.size(); ++i)
  {
    for (size_t j = 0; j < this->data[i].size(); ++j)
    {
      if (!equal(this->data[i][j], rhs[i][j])) { return true; }
    }
  }
  return false;
}

// The raytracer will only need 4x4 matrix multiplications
Matrix Matrix::operator*(const Matrix& rhs) const
{
  Matrix M{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };

  for (size_t i = 0; i < 4; ++i)
  {
    for (size_t j = 0; j < 4; ++j)
    {
      M[i][j] = this->data[i][0] * rhs[0][j] +
                this->data[i][1] * rhs[1][j] +
                this->data[i][2] * rhs[2][j] +
                this->data[i][3] * rhs[3][j];
    }
  }
  return M;
}

// Multiplying a matrix by a tuple produces another tuple
Tuple operator*(const Matrix& lhs, const Tuple& rhs)
{
  Tuple t{0, 0, 0, 0};
  t.x =     lhs.data[0][0] * rhs.x +
            lhs.data[0][1] * rhs.y +
            lhs.data[0][2] * rhs.z +
            lhs.data[0][3] * rhs.w;

  t.y =     lhs.data[1][0] * rhs.x +
            lhs.data[1][1] * rhs.y +
            lhs.data[1][2] * rhs.z +
            lhs.data[1][3] * rhs.w;

  t.z =     lhs.data[2][0] * rhs.x +
            lhs.data[2][1] * rhs.y +
            lhs.data[2][2] * rhs.z +
            lhs.data[2][3] * rhs.w;

  t.w =     lhs.data[3][0] * rhs.x +
            lhs.data[3][1] * rhs.y +
            lhs.data[3][2] * rhs.z +
            lhs.data[3][3] * rhs.w;

  return t;
}

Point operator*(const Matrix& lhs, const Point& rhs)
{
  Point p{0, 0, 0};
  p.x =     lhs.data[0][0] * rhs.x +
            lhs.data[0][1] * rhs.y +
            lhs.data[0][2] * rhs.z +
            lhs.data[0][3];

  p.y =     lhs.data[1][0] * rhs.x +
            lhs.data[1][1] * rhs.y +
            lhs.data[1][2] * rhs.z +
            lhs.data[1][3];

  p.z =     lhs.data[2][0] * rhs.x +
            lhs.data[2][1] * rhs.y +
            lhs.data[2][2] * rhs.z +
            lhs.data[2][3];

  return p;
}

Vector operator*(const Matrix& lhs, const Vector& rhs)
{
  Vector v{0, 0, 0};
  v.x =     lhs.data[0][0] * rhs.x +
            lhs.data[0][1] * rhs.y +
            lhs.data[0][2] * rhs.z +
            lhs.data[0][3] * 0;

  v.y =     lhs.data[1][0] * rhs.x +
            lhs.data[1][1] * rhs.y +
            lhs.data[1][2] * rhs.z +
            lhs.data[1][3] * 0;

  v.z =     lhs.data[2][0] * rhs.x +
            lhs.data[2][1] * rhs.y +
            lhs.data[2][2] * rhs.z +
            lhs.data[2][3] * 0;

  v.w =     lhs.data[3][0] * rhs.x +
            lhs.data[3][1] * rhs.y +
            lhs.data[3][2] * rhs.z +
            lhs.data[3][3] * 0;

  return v;
}

const Matrix Matrix::identity_matrix {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};

Matrix transpose(const Matrix& matrix)
{
  Matrix M{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };

  for (size_t i = 0; i < 4; i++) {
    M[0][i] = matrix[i][0];
    M[1][i] = matrix[i][1];
    M[2][i] = matrix[i][2];
    M[3][i] = matrix[i][3];
  }
  return M;
}

double determinant(const Matrix& matrix)
{
  double det = 0;
  if (matrix.data.size() == 2)
  {
    // To find the determinanat of a 2x2 matrix
    // determinant( [a, b],
    //              [c, d] ) = a*d - b*c
    det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  }
  else
  {
    // To find the determinant of larger matrices,
    // take any one of the rows or columns, then
    // for each of the elements multiply the element
    // by its cofactor and add the products together
    for (size_t i = 0; i < matrix.data.size(); ++i)
    {
      det += matrix[0][i] * cofactor(matrix, 0, i);
    }
  }

  return det;
}

Matrix submatrix(const Matrix& mat, int row, int column)
{
  Matrix temp = mat;
  temp.data.erase(temp.data.begin() + row);
  for (auto& row : temp.data)
  {
    row.erase(row.begin() + column);
  }
  return temp;
}

double minor(const Matrix& matrix, int row, int column)
{
  return determinant(submatrix(matrix, row, column));
}

// if row + column is an odd number, negate the minor
double cofactor(const Matrix& matrix, int row, int column)
{
  int sign = (row + column) % 2 ? -1 : 1;
  return minor(matrix, row, column) * sign;
}

bool is_invertible(const Matrix& matrix)
{
  // A matrix is invertible if its determinant is not zero
  return determinant(matrix) == 0 ? false : true;
}

Matrix inverse(const Matrix& matrix)
{
  if (!is_invertible(matrix))
  {
    throw std::invalid_argument("matrix is not invertible");
  }

  Matrix inv_matrix = matrix;
  for (size_t row = 0; row < matrix.data.size(); ++row)
  {
    for (size_t col = 0; col < matrix[row].size(); ++col)
    {
      double c = cofactor(matrix, row, col);

      // note that "col, row" here, instead of of "row, col",
      // accomplishes the transpose operation
      inv_matrix[col][row] = c / determinant(matrix);
    }
  }

  return inv_matrix;
}
