#include "canvas.h"

Canvas::Canvas(const int width, const int height) : width(width), height(height) {
  // Every pixel in the canvas is initialized to black
  grid = std::vector<std::vector<Color> >(width, std::vector<Color>(height, Color(0,0,0)));
}

Color Canvas::pixel_at(int x, int y)
{
  return this->grid[x][y];
}

void Canvas::write_pixel(int x, int y, Color color)
{
  this->grid[x][y] = color;
}
