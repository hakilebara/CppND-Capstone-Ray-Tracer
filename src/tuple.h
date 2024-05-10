#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>

struct Tuple 
{
  Tuple(double x, double y, double z, double w);

  Tuple operator-();

  bool isPoint();
  bool isVector();

  double x, y, z, w;
};

struct Point : public Tuple
{
  Point(double x, double y, double z);
};

struct Vector : public Tuple
{
  Vector(double x, double y, double z);
};

struct Color : public Tuple
{
  Color(double r, double g, double b);
  double red, green, blue;
};

double magnitude(const Vector&);
Vector normalize(const Vector&);
double dot(const Vector&, const Vector&);
Vector cross(const Vector&, const Vector&);
Vector reflect(const Vector&, const Vector&);

bool operator==(const Tuple& lhs, const Tuple& rhs);
Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator*(const Tuple& lhs, const double rhs);
Tuple operator/(const Tuple& lhs, const double rhs);
Color operator*(const Color& lhs, const Color& rhs);
Point operator+(const Point& lhs, const Vector& rhs);
Vector operator*(const Vector& lhs, const double rhs);
Vector operator-(const Point& lhs, const Point& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
#endif
