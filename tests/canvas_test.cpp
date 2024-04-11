#include <gtest/gtest.h>
#include "canvas.h"

// Creating a canvas
TEST(Canvas, Creation)
{
  Canvas c{10, 20};
  EXPECT_EQ(c.width, 10);
  EXPECT_EQ(c.height, 20);

  for(size_t i = 0; i < 10; ++i)
  {
    for(size_t j = 0; j < 20; ++j)
    {
      EXPECT_EQ(c.pixel_at(i, j), Color(0,0,0));
    }
  }
}

// Writing pixels to a canvas
TEST(Canvas, WritePixels)
{
  Canvas c{10, 20};
  Color red{1, 0, 0};
  c.write_pixel(2, 3, red);
  EXPECT_EQ(c.pixel_at(2,3), red);
}
