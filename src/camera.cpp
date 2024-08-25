#include "camera.h"
#include <cmath>
#include "tuple.h"

double Camera::pixel_size()
{
  double half_view = std::tan(this->field_of_view/2);
  double aspect = this->hsize / this->vsize;
  if (aspect >= 1)
  {
    this->half_width = half_view;
    this->half_height = half_view / aspect;
  }
  else
  {
    this->half_width = half_view * aspect;
    this->half_height = half_view;
  }

  return (this->half_width * 2) / this->hsize;
}

Ray ray_for_pixel(Camera& camera, double px, double py)
{
  // the offset from the edge of the canvas to the pixel's center
  double xoffset = (px + 0.5) * camera.pixel_size();
  double yoffset = (py + 0.5) * camera.pixel_size();

  // the untransformed coordinates of the pixel in world space.
  // (the camera looks towards -z, so +x is to the *left*.)
  double world_x = camera.half_width - xoffset;
  double world_y = camera.half_height - yoffset;

  // using the camera matrix, transform the canvas point and the origin,
  // (the canvas is at z=-1)
  Point pixel = inverse(camera.transform) * Point{world_x, world_y, -1};
  Point origin = inverse(camera.transform) * Point{0, 0, 0};
  Vector direction = normalize(pixel - origin);

   return Ray{origin, direction};
}

Canvas render(Camera& camera, World& world)
{
  Canvas image{(int)camera.hsize, (int)camera.vsize};

  for (int y = 0; y <= camera.vsize - 1; ++y)
  {
    for (int x = 0; x <= camera.hsize - 1; ++x)
    {
      Ray ray = ray_for_pixel(camera, x, y);
      Color color = color_at(world, ray);

      image.write_pixel(x, y, color);
    }
  }
  return image;
}
