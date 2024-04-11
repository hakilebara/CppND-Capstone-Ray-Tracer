#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "tuple.h"

struct Canvas
{
  Canvas(const int width, const int height);
  Color pixel_at(int x, int y);
  void write_pixel(int x, int y, Color c);
  const unsigned int width, height;
private:
  std::vector<std::vector<Color> > grid;
};

#endif
