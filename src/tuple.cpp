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
Color operator+(const Color& lhs, const Color& rhs)
{
  return Color(
    lhs.x + rhs.x,
    lhs.y + rhs.y,
    lhs.z + rhs.z
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

Color operator*(const Color& lhs, const double rhs)
{
  return Color(
    lhs.x * rhs,
    lhs.y * rhs,
    lhs.z * rhs
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

Vector Vector::operator-() const
{
  return Vector(
    - this->x,
    - this->y,
    - this->z
  );
}

Color::Color() : Tuple(0, 0, 0, 0.0), red(0), green(0), blue(0) {};
Color::Color(double red, double green, double blue) : Tuple(red, green, blue, 0.0), red(red), green(green), blue(blue) {}

double magnitude(const Vector& v)
{
  return std::sqrt(
    std::pow(v.x, 2)
    + std::pow(v.y, 2)
    + std::pow(v.z, 2)
    + std::pow(v.w, 2)
  );
}

Vector normalize(const Vector& v)
{
  return Vector(
      v.x / magnitude(v),
      v.y / magnitude(v),
      v.z / magnitude(v)
  );
}

double dot(const Vector& a, const Vector&b)
{
  return a.x * b.x +
         a.y * b.y +
         a.z * b.z +
         a.w * b.w;
}

Vector cross(const Vector& a, const Vector& b)
{
  return Vector(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vector reflect(const Vector& in, const Vector& normal)
{
  return in - normal * 2 * dot(in, normal);
}

Color operator*(const Color& lhs, const Color& rhs)
{
  return Color(
    lhs.red * rhs.red,
    lhs.green * rhs.green,
    lhs.blue * rhs.blue
  );
}

Point operator+(const Point& lhs, const Vector& rhs)
{
  return Point(
    lhs.x + rhs.x,
    lhs.y + rhs.y,
    lhs.z + rhs.z
  );
}

Vector operator*(const Vector& lhs, const double rhs)
{
  return Vector(
    lhs.x * rhs,
    lhs.y * rhs,
    lhs.z * rhs
  );
}

// the subtraction of two points gives a vector
// that represent hot to "get to" point A to point B
Vector operator-(const Point& lhs, const Point& rhs)
{
  return Vector(
    lhs.x - rhs.x,
    lhs.y - rhs.y,
    lhs.z - rhs.z
  );
}

// The subtraction of two vectors results in a new vector
// that represents the difference between their magnitudes
// and directions
Vector operator-(const Vector& lhs, const Vector& rhs)
{
  return Vector(
    lhs.x - rhs.x,
    lhs.y - rhs.y,
    lhs.z - rhs.z
  );
}
