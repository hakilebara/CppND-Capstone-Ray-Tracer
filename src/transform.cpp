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

Matrix view_transform(const Point& from, const Point& to, const Vector& up)
{
  Vector forward = normalize(to - from);
  Vector upn = normalize(up);
  Vector left = cross(forward, upn);

  // Compute the true_up vector by taking the cross product of 'left' and
  // 'forward', this allows the originial 'up' vector to be only approximately
  // up, which makes framing scenes a lot easier, since there is not need to
  // personally break out a calculator to figure out the precise upward direction
  Vector true_up = cross(left, forward);

  // with the 'left', 'true_up', and 'forward' vectors, construct a matrix that
  // represents the orientation transformation
  Matrix orientation = Matrix{
    {  left.x,     left.y,     left.z,    0 },
    {  true_up.x,  true_up.y,  true_up.z, 0 },
    { -forward.x, -forward.y, -forward.z, 0 },
    {  0,          0,          0,         1 },
  };

  // append a translation to that transformation to move the scene into place
  // before orienting it.
  return orientation * translation(-from.x, -from.y, -from.z);
}
