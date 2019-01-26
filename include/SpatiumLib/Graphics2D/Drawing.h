/*
 * Program: Spatium Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMLIB_GRAPHICS_DRAWING_H
#define SPATIUMLIB_GRAPHICS_DRAWING_H

#include "SpatiumLib/Imaging/Image.h"

namespace Graphics2D {

/// \class Drawing
class Drawing
{
public:

  //https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
  template<typename T, int N>
  static void drawCircle(Imaging::Image<T, N> &image, std::array<int, 2> center, int radius, std::array<T, N> val)
  {
    int x0 = center[0];
    int y0 = center[1];

    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y)
    {
      image.setPixel(x0 + x, y0 + y, val);
      image.setPixel(x0 + y, y0 + x, val);
      image.setPixel(x0 - y, y0 + x, val);
      image.setPixel(x0 - x, y0 + y, val);
      image.setPixel(x0 - x, y0 - y, val);
      image.setPixel(x0 - y, y0 - x, val);
      image.setPixel(x0 + y, y0 - x, val);
      image.setPixel(x0 + x, y0 - y, val);

      if (err <= 0)
      {
        y++;
        err += dy;
        dy += 2;
      }

      if (err > 0)
      {
        x--;
        dx += 2;
        err += dx - (radius << 1);
      }
    }
  }

  // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
  template<typename T, int N>
  static void drawLine(Imaging::Image<T, N> &image, const std::array<int, 2> &start, const std::array<int, 2> &end, const std::array<T, N> &val)
  {
    int x0 = start[0];
    int y0 = start[1];
    int x1 = end[0];
    int y1 = end[1];

    if(abs(y1 - y0) < abs(x1 - x0))
    {
      if(x0 > x1)
      {
        drawLineLow<T, N>(image, x1, y1, x0, y0, val);
      }
      else
      {
        drawLineLow<T, N>(image, x0, y0, x1, y1, val);
      }
    } else
    {
      if (y0 > y1)
      {
        drawLineHigh<T, N>(image, x1, y1, x0, y0, val);
      }
      else
      {
        drawLineHigh<T, N>(image, x0, y0, x1, y1, val);
      }
    }
  }

  template<typename T, int N>
  static void drawRectangle(Imaging::Image<T, N> &image, const std::array<int, 2> &topLeft, const std::array<int, 2> &bottomRight, const std::array<T, N> &val, bool fill = false)
  {
    if (fill)
    {
      for (int y = topLeft[1]; y <= bottomRight[1]; y++)
      {
        for (int x = topLeft[0]; x <= bottomRight[0]; x++)
        {
          image.setPixel(x, y, val);
        }
      }
    }
    else
    {
      // Horizontal edges (top & bottom)
      for (int x = topLeft[0]; x <= bottomRight[0]; x++)
      {
        image.setPixel(x, topLeft[1], val); // top edge
        image.setPixel(x, bottomRight[1], val); // bottom edge
      }

      // Vertical edges (left & right)
      for (int y = topLeft[1]; y <= bottomRight[1]; y++)
      {
        image.setPixel(topLeft[0], y, val); // left edge
        image.setPixel(bottomRight[0], y, val); // right edge
      }
    }
  }

protected:

  template<typename T, int N>
  static void drawLineLow(Imaging::Image<T, N> &image, int &x0, int &y0, int &x1, int &y1, const std::array<T, N> &val)
  {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
      yi = -1;
      dy = -dy;
    }
    int D = 2*dy - dx;
    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
      image.setPixel(x, y, val);
      if (D > 0)
      {
        y = y + yi;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }

  template<typename T, int N>
  static void drawLineHigh(Imaging::Image<T, N> &image, int x0, int y0, int x1, int y1, const std::array<T, N> &val)
  {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
      xi = -1;
      dx = -dx;
    }
    int D = 2*dx - dy;
    int x = x0;

    for (int y = y0; y <= y1; y++)
    {
      image.setPixel(x, y, val);
      if (D > 0)
      {
        x = x + xi;
        D = D - 2*dy;
      }
      D = D + 2*dx;
    }
  }

private:
  Drawing() = delete;
  virtual ~Drawing() = delete;

};

} // namespace Graphics2D

#endif // SPATIUMLIB_GRAPHICS_DRAWING_H
