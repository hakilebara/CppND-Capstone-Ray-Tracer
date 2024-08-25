#include <gtest/gtest.h>
#include "camera.h"
#include "maths.h"
#include "matrix.h"
#include "ray.h"
#include "transform.h"
#include "canvas.h"

// Constructing a camera
TEST(Camera, ConstructingACamera)
{
  double hsize = 160;
  double vsize = 120;
  double field_of_view = pi/2;
  Camera c{hsize, vsize, field_of_view};

  EXPECT_EQ(c.hsize, 160);
  EXPECT_EQ(c.vsize, 120);
  EXPECT_EQ(c.field_of_view, pi/2);
  EXPECT_EQ(c.transform, Matrix::identity_matrix);
}

// The pixel size for a horizontal canvas
TEST(Camera, ThePixelSizeForAHorizontalCanvas)
{
  Camera c{200, 125, pi/2};
  ASSERT_TRUE(equal(c.pixel_size(), 0.01));
}

// The pixel size for a vertical canvas
TEST(Camera, ThePixelSizeForAVertialCanvas)
{
  Camera c{125, 200, pi/2};
  ASSERT_TRUE(equal(c.pixel_size(), 0.01));
}

// Constructing a ray throught the center of the canvas
TEST(Camera, ConstructingARayThroughTheCenterOfTheCanvas)
{
  Camera c{201, 101, pi/2};
  Ray r = ray_for_pixel(c, 100, 50) ;

  EXPECT_EQ(r.origin, Point(0, 0, 0));
  EXPECT_EQ(r.direction, Vector(0, 0, -1));
}

// Constructing a ray through the corner of the canvas
TEST(Camera, ConstructingARayThroughACornerOfTheCanvas)
{
  Camera c{201, 101, pi/2};
  Ray r = ray_for_pixel(c, 0, 0);

  EXPECT_EQ(r.origin, Point(0, 0, 0));
  EXPECT_EQ(r.direction, Vector(0.66519, 0.33259, -0.66851));
}

// Constructing a ray when the camera is transformed
TEST(Camera, ConstructingARayWhenTheCameraIsTransformed)
{
  Camera c{201, 101, pi/2};
  c.transform = rotation_y(pi/4) * translation(0, -2, 5);
  Ray r = ray_for_pixel(c, 100, 50);

  EXPECT_EQ(r.origin, Point(0, 2, -5));
  EXPECT_EQ(r.direction, Vector(std::sqrt(2)/2, 0, -std::sqrt(2)/2));
}

// Rendering a world with a camera
TEST(Camera, RenderingAWorldWithACamera)
{
  World w = default_world();
  Camera c{11, 11, pi/2};
  Point from{0, 0, -5};
  Point to{0, 0, 0};
  Vector up{0, 1, 0};
  c.transform = view_transform(from, to, up);

  Canvas image = render(c, w);
  EXPECT_EQ(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855));
}
