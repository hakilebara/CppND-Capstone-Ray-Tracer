#include "matrix.h"

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
