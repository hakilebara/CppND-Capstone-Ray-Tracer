#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include "tuple.h"

struct Matrix
{
  Matrix(std::initializer_list<std::initializer_list<double>>);  // Initializer list constructor
  friend Tuple operator*(const Matrix& lhs, const Tuple& rhs);

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

Matrix transpose(const Matrix&);
double determinant(const Matrix&);

#endif
