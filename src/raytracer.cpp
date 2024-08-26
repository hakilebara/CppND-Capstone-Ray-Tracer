#include <iostream>
#include "canvas.h"
#include "tuple.h"
#include "ray.h"
#include "maths.h"
#include "material.h"
#include "light.h"
#include "world.h"
#include "transform.h"
#include "camera.h"


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

void renderScence()
{
  World world{};

  // The floor is an extremely flattened sphere with a matte texture
  Sphere floor{};
  floor.transform = scaling(10, 0.01, 10);
  floor.material.color = Color{1, 0.9, 0.9};
  floor.material.specular = 0;

  // The wall on the left has the same scale and color as teh floor, but is
  // also rotated and translated into place
  // Note: the transformations are multiplied in the reverse order
  Sphere left_wall{};
  left_wall.transform = translation(0, 0, 5) * rotation_y(-pi/4) *
    rotation_x(pi/2) * scaling(10, 0.01, 10);
  left_wall.material = floor.material;

  // The wall on the right is identical to the left wall, but is rotated the
  // opposite direction in y
  Sphere right_wall{};
  right_wall.transform  = translation(0, 0, 5) * rotation_y(pi/4) *
    rotation_x(pi/2) * scaling(10, 0.01, 10);
  right_wall.material = floor.material;

  // The large sphere in the middle is a unit sphere, translated upward
  // slightly and colored green.
  Sphere middle{};
  middle.transform = translation(-0.5, 1, 0.5);
  middle.material.color = Color{0.1, 1, 0.5};
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;

  // The smaller green sphere on the right is scaled in half
  Sphere right{};
  right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
  right.material.color = Color{0.5, 1, 0.1};
  right.material.diffuse = 0.7;
  right.material.specular = 0.3;

  // The smallest sphere is scaled by a third, before being translated
  Sphere left{};
  left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
  left.material.color = Color{1, 0.8, 0.1};
  left.material.diffuse = 0.7;
  left.material.specular = 0.3;

  world.objects.push_back(floor);
  world.objects.push_back(left_wall);
  world.objects.push_back(right_wall);
  world.objects.push_back(middle);
  world.objects.push_back(right);
  world.objects.push_back(left);

  // The light source is white, shining from above and to the left
  world.light = PointLight{Point{-10, 10, -10}, Color{1, 1, 1}};

  // Camera camera{100, 50, pi/3};
  Camera camera{1000, 500, pi/3};
  camera.transform = view_transform(Point{0, 1.5, -5}, Point{0, 1, 0}, Vector{0, 1, 0});

  Canvas canvas = render(camera, world);

  std::cout << canvas.canvas_to_ppm();
}

int main()
{
  renderScence();
}
