#ifndef MATRIX_H   
#define MATRIX_H

#include <initializer_list>
#include <vector>

struct Matrix
{
  Matrix(std::initializer_list<std::initializer_list<double>>);  // Initializer list constructor

  // Accessor functions
  std::vector<double>& operator[](size_t index);  // Non-const subscript operator for mutable access
  const std::vector<double>& operator[](size_t index) const;  // Const subscript operator for read-only access
private:
  std::vector<std::vector<double>> data;
};
#endif
