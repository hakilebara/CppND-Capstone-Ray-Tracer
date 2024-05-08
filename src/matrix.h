#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include "tuple.h"

struct Matrix
{
  Matrix(std::initializer_list<std::initializer_list<double>>);  // Initializer list constructor
  friend Tuple operator*(const Matrix& lhs, const Tuple& rhs);
  friend Point operator*(const Matrix& lhs, const Point& rhs);
  friend Vector operator*(const Matrix& lhs, const Vector& rhs);
  friend Matrix submatrix(const Matrix&, int, int);
  friend double determinant(const Matrix&);
  friend Matrix inverse(const Matrix&);

  // Non-const subscript operator for mutable access
  std::vector<double>& operator[](size_t index);
  // Const subscript operator for read-only access
  const std::vector<double>& operator[](size_t index) const;

  bool operator==(const Matrix& rhs) const;
  bool operator!=(const Matrix& rhs) const;
  Matrix operator*(const Matrix& rhs) const;
  static const Matrix identity_matrix;
private:
  std::vector<std::vector<double>> data;
};

Tuple operator*(const Matrix& lhs, const Tuple& rhs);
Point operator*(const Matrix& lhs, const Point& rhs);
Vector operator*(const Matrix& lhs, const Vector& rhs);

Matrix transpose(const Matrix&);
double determinant(const Matrix&);
Matrix submatrix(const Matrix&, int row, int column);
double minor(const Matrix&, int row, int column);
double cofactor(const Matrix&, int row, int column);
bool is_invertible(const Matrix&);
Matrix inverse(const Matrix&);

#endif
