#ifndef TUPLE_H
#define TUPLE_H

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
  double red() const { return this->x; }
  double green() const { return this->y; }
  double blue() const { return this->z; }
};

bool operator==(const Tuple& lhs, const Tuple& rhs);
Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator*(const Tuple& lhs, const double rhs);
Tuple operator/(const Tuple& lhs, const double rhs);
Color operator*(const Color& lhs, const Color& rhs);
#endif
