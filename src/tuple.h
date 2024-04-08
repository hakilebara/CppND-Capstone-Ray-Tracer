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

bool operator==(const Tuple& lhs, const Tuple& rhs);
Tuple operator+(const Tuple& lhs, const Tuple& rhs);
Tuple operator-(const Tuple& lhs, const Tuple& rhs);
Tuple operator*(const Tuple& lhs, const double rhs);
Tuple operator/(const Tuple& lhs, const double rhs);
#endif
