#include <iostream>
#include "canvas.h"
#include "tuple.h"
#include "ray.h"
#include "maths.h"


void render()
{
  // start the ray at z = -5
  Point ray_origin = Point{0, 0, -5};

  // put the wall at z
  const double wall_z = 10;

  const double wall_size = 7;

  const int canvas_pixels = 100;

  double pixel_size = wall_size / canvas_pixels;

  double half = wall_size / 2;

  Canvas c{canvas_pixels, canvas_pixels};

  Color pixel_color{1, 0, 0};

  Sphere shape{};

  for (size_t y = 0; y < canvas_pixels; ++y)
  {
    double world_y = half - pixel_size * y;

    for (size_t x = 0; x < canvas_pixels; ++x)
    {
      double world_x = -half + pixel_size * x;

      Point position{world_x, world_y, wall_z};

      Ray r{ray_origin, normalize(position - ray_origin)};
      Intersections xs = intersect(shape, r);

      if (hit(xs))
      {
        c.write_pixel(x, y, pixel_color);
      }
    }
  }

  std::cout << c.canvas_to_ppm();
}

int main()
{
  render();
}
