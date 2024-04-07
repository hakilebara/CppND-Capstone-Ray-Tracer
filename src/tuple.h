#ifndef TUPLE_H
#define TUPLE_H

const double EPSILON = 0.00001;

struct Tuple 
{
  Tuple(double x, double y, double z, double w);

  bool isPoint();
  bool isVector();

  double x, y, z, w;
};
#endif
