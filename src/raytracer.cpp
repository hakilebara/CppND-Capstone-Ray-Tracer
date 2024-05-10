#include <iostream>
#include "canvas.h"
#include "tuple.h"
#include "ray.h"
#include "maths.h"
#include "material.h"
#include "light.h"


void render2D()
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

void render3D()
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

  Sphere sphere{};
  // assign a material to the sphere
  sphere.material = Material{};
  sphere.material.color = Color{1, 0.2, 1};

  // white light behind, above and to the left of the eye
  Point light_position{-10, 10, -10};
  Color light_color{1, 1, 1};
  PointLight light{light_position, light_color};

  for (size_t y = 0; y < canvas_pixels; ++y)
  {
    double world_y = half - pixel_size * y;

    for (size_t x = 0; x < canvas_pixels; ++x)
    {
      double world_x = -half + pixel_size * x;

      Point world_position{world_x, world_y, wall_z};

      Ray r{ray_origin, normalize(world_position - ray_origin)};
      Intersections xs = intersect(sphere, r);

      if (hit(xs))
      {
        Point point = position(r, hit(xs)->t);
        Vector normal = normal_at(hit(xs)->object, point);
        Vector eye = -r.direction;
        Color pixel_color = lighting(hit(xs)->object.material, light, point, eye, normal);
        c.write_pixel(x, y, pixel_color);
      }
    }
  }

  std::cout << c.canvas_to_ppm();
}

int main()
{
  render3D();
}
