#include "tuple.h"    
#include "maths.h"

Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

bool Tuple::isPoint()
{
  return this->w == 1;
}

bool Tuple::isVector()
{
  return this->w == 0;
}

Tuple Tuple::operator-()
{
  return Tuple(
    - this->x,
    - this->y,
    - this->z,
    - this->w
  );
}

bool operator==(const Tuple& lhs, const Tuple& rhs)
{
  return equal(lhs.x, rhs.x)
    && equal(lhs.y, rhs.y)
    && equal(lhs.z, rhs.z)
    && equal(lhs.w, rhs.w);
}

Tuple operator+(const Tuple& lhs, const Tuple& rhs)
{
  return Tuple(
    lhs.x + rhs.x,
    lhs.y + rhs.y,
    lhs.z + rhs.z,
    lhs.w + rhs.w
  );
}

Tuple operator-(const Tuple& lhs, const Tuple& rhs)
{
  return Tuple(
    lhs.x - rhs.x,
    lhs.y - rhs.y,
    lhs.z - rhs.z,
    lhs.w - rhs.w
  );
}

Tuple operator*(const Tuple& lhs, const double rhs)
{
  return Tuple(
    lhs.x * rhs,
    lhs.y * rhs,
    lhs.z * rhs,
    lhs.w * rhs
  );
}

Tuple operator/(const Tuple& lhs, const double rhs)
{
  return Tuple(
    lhs.x / rhs,
    lhs.y / rhs,
    lhs.z / rhs,
    lhs.w / rhs
  );
}

Point::Point(double x, double y, double z) : Tuple(x, y, z, 1.0) {}

Vector::Vector(double x, double y, double z) : Tuple(x, y, z, 0.0) {}

Color::Color(double red, double green, double blue) : Tuple(red, green, blue, 0.0), red(red), green(green), blue(blue) {}

Color operator*(const Color& lhs, const Color& rhs)
{
  return Color(
    lhs.red * rhs.red,
    lhs.green * rhs.green,
    lhs.blue * rhs.blue
  );
}
