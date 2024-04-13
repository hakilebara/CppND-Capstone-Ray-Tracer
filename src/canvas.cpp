#include <format>
#include <algorithm>
#include <cmath>
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

std::string Canvas::canvas_to_ppm()
{
  std::string ppm_header = std::format("P3\n{} {}\n255", this->width, this->height);
  std::string ppm;
  bool first_line = true;
  for (int j = 0; j < this->height; ++j)
  {
    if (!first_line) { ppm += "\n"; }
    bool first_color = true;
    int char_count{0};
    for (int i = 0; i < this->width; ++i)
    {
      std::string current_color = color_to_ppm_string(grid[i][j]);
      // No line in a PPM file should be more that 70 characters long
      if (char_count + current_color.size() < 70)
      {
        if (!first_color) { ppm += " "; }
        ppm += current_color;
        char_count += current_color.size();
      }
      else
      {
        ppm += "\n" + current_color;
        char_count = 0;
      }
      first_color = false;
    }
    first_line = false;
  }
  return std::format("{}\n{}\n", ppm_header, ppm);
}

std::string Canvas::color_to_ppm_string(Color c)
{
  // Convert a Color object to a string
  // Each pixel's element (Red, Green or Blue) should be strictly between 0 and 255.
  // The PPM format specifies that pixel values must be integers
  // and each int value should be separated by a space
  return std::format("{} {} {}",
      std::clamp(static_cast<int>(std::round(c.red * 255)),   0, 255),
      std::clamp(static_cast<int>(std::round(c.green * 255)), 0, 255),
      std::clamp(static_cast<int>(std::round(c.blue * 255)),  0, 255)
  );
}
