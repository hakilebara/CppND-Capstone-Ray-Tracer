#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>
#include "tuple.h"

struct Canvas
{
  Canvas(const int width, const int height);
  Color pixel_at(int x, int y);
  void write_pixel(int x, int y, Color c);
  std::string canvas_to_ppm();

  const int width, height;
private:
  std::string color_to_ppm_string(Color);
  std::vector<std::vector<Color> > grid;
};

#endif
