#include <cmath>
#include "transform.h"

// To createa a translation matrix, take an identity matrix and change the values at t[0,3], t[1,3] and t[2,3] to be respectively the x, y and z translation values
Matrix translation(double x, double y, double z)
{
  return Matrix{
    { 1, 0, 0, x },
    { 0, 1, 0, y },
    { 0, 0, 1, z },
    { 0, 0, 0, 1 },
  };
}

// To construct a scaling matrix, take an identity matrix and change the values at t[0,0], t[1,1] and t[2,2] to be respectively the x, y and z scaling values
Matrix scaling(double x, double y, double z)
{
  return Matrix{
    { x, 0, 0, 0 },
    { 0, y, 0, 0 },
    { 0, 0, z, 0 },
    { 0, 0, 0, 1 },
  };
}

Matrix rotation_x(double r)
{
  return Matrix{
   { 1, 0,            0,           0 },
   { 0, std::cos(r), -std::sin(r), 0 },
   { 0, std::sin(r),  std::cos(r), 0 },
   { 0, 0,            0,           1 }
  };
}

Matrix rotation_y(double r)
{
  return Matrix{
   {  std::cos(r), 0, std::sin(r), 0 },
   {  0,           1, 0,           0 },
   { -std::sin(r), 0, std::cos(r), 0 },
   {  0,           0, 0,           1 }
  };
}

Matrix rotation_z(double r)
{
  return Matrix{
   { std::cos(r), -std::sin(r), 0, 0 },
   { std::sin(r),  std::cos(r), 0, 0 },
   { 0,            0,           1, 0 },
   { 0,            0,           0, 1 }
  };
}

Matrix shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
  return Matrix{
    {  1, xy, xz, 0 },
    { yx,  1, yz, 0 },
    { zx, zy,  1, 0 },
    {  0,  0, 0, 1 }
  };
}
