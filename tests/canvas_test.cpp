#include <gtest/gtest.h>
#include <string>
#include <sstream>
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

// Constructing the PPM header
TEST(Canvas, PPMHeader)
{
  Canvas c{5, 3};
  std::string ppm = c.canvas_to_ppm();
  std::istringstream iss(ppm);
  std::string line;
  std::string ppm_header;
  bool first_line = true;
  int counter = 0;
  while(std::getline(iss, line) && counter < 3)
  {
    if (!first_line) { ppm_header += "\n"; }
    ppm_header += line;
    counter++;
    first_line = false;
  }
  EXPECT_EQ(ppm_header, "P3\n5 3\n255");
}

// Constructing the PPM pixel data
TEST(Canvas, PPMPixelData)
{
  Canvas c{5, 3};
  Color c1{1.5,  0,   0};
  Color c2{0,    0.5, 0};
  Color c3{-0.5, 0,   1};
  c.write_pixel(0, 0, c1);
  c.write_pixel(2, 1, c2);
  c.write_pixel(4, 2, c3);

  std::string ppm = c.canvas_to_ppm();
  std::istringstream iss(ppm);
  std::string line;
  int counter{1};
  std::string ppm_lines_4_to_6;
  bool first_line = true;

  while(getline(iss, line))
  {
    if (counter >= 4 && counter <= 6)
    {
      if(!first_line) { ppm_lines_4_to_6 += "\n"; }
      ppm_lines_4_to_6 += line;
      first_line = false;
    }
    if (counter > 6)
    {
      break;
    }
    ++counter;
  }
  std::string expected_ppm = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255";
  EXPECT_EQ(ppm_lines_4_to_6, expected_ppm);
}

// Splitting long lines in PPM files
TEST(Canvas, SplittingLongLines)
{
  Canvas c{10, 2};
  for (size_t i = 0; i < 10; ++i)
  {
    for (size_t j = 0; j < 2; ++j)
    {
      c.write_pixel(i, j, Color(1, 0.8, 0.6));
    }
  }
  std::string ppm = c.canvas_to_ppm();
  std::istringstream iss(ppm);
  std::string line;
  std::string ppm_lines_4_to_7;
  int counter{1};
  bool first_line = true;

  while(getline(iss, line))
  {
    if (counter >= 4 && counter <= 7)
    {
      if(!first_line) { ppm_lines_4_to_7 += "\n"; }
      ppm_lines_4_to_7 += line;
      first_line = false;
    }
    if (counter > 7)
    {
      break;
    }
    ++counter;
  }

  std::string expected_ppm = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153";
  EXPECT_EQ(ppm_lines_4_to_7, expected_ppm);
}

// PPM files are terminated by a newline character
TEST(Canvas, NewlineTermination)
{
  Canvas c{5, 3};
  std::string ppm = c.canvas_to_ppm();
  EXPECT_EQ(ppm.back(), '\n');
}
