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

#ifndef SPATIUMLIB_GFX2D_DRAWING_H
#define SPATIUMLIB_GFX2D_DRAWING_H

#include "spatium/Image.h"
#include "BezierCurve.h"

namespace spatium {
namespace gfx2d {

/// \class Drawing
/// \brief 2D drawing functions
///
/// Drawing is a non-instantiable class with various 2D drawing functions.
class Drawing
{
public:

  /// Draw a Bezier curve
  ///
  /// \param[in,out] image Image to draw in
  /// \param[in] curve Bezier curve
  /// \param[in] value Value to apply for each pixel on the curve
  template<typename T, int N>
  static void drawCurve(Image<T, N> &image, const BezierCurve &curve, std::array<T, N> val)
  {
    for (double t = 0; t <= 1; t += 0.01)
    {
      std::array<double, 2> p = curve.evaluate(t);
      image.pixel(p[0], p[1]) = val;
    }
  }

  /// Draw a circle
  ///
  /// \param[in,out] image Image to draw in
  /// \param[in] center Center point of the circle
  /// \param[in] radius Radius of the circle
  /// \param[in] val Value to apply for each pixel on the circle
  template<typename T, int N>
  static void drawCircle(Image<T, N> &image, std::array<int, 2> center,
                         int radius, std::array<T, N> val)
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
      image.pixel(x0 + x, y0 + y) = val;
      image.pixel(x0 + y, y0 + x) = val;
      image.pixel(x0 - y, y0 + x) = val;
      image.pixel(x0 - x, y0 + y) = val;
      image.pixel(x0 - x, y0 - y) = val;
      image.pixel(x0 - y, y0 - x) = val;
      image.pixel(x0 + y, y0 - x) = val;
      image.pixel(x0 + x, y0 - y) = val;

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

  /// Draw a line
  ///
  /// \param[in,out] image Image to draw in
  /// \param[in] start Start point of the line
  /// \param[in] end End point of the line
  /// \param[in] val Value to apply for each pixel on the line
  template<typename T, int N>
  static void drawLine(Image<T, N> &image,
                       const std::array<int, 2> &start,
                       const std::array<int, 2> &end,
                       const std::array<T, N> &val)
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

  /// Draw a rectangle
  ///
  /// \param[in,out] image Image to draw in
  /// \param[in] topLeft Top left corner of the rectangle
  /// \param[in] bottomRight Bottom right corner of the rectangle
  /// \param[in] val Value to apply for each pixel on the rectangle
  /// \param[in] fill Indicator to fill the rectangle (default = false)
  template<typename T, int N>
  static void drawRectangle(Image<T, N> &image,
                            const std::array<int, 2> &topLeft,
                            const std::array<int, 2> &bottomRight,
                            const std::array<T, N> &val,
                            bool fill = false)
  {
    if (fill)
    {
      for (int y = topLeft[1]; y <= bottomRight[1]; y++)
      {
        for (int x = topLeft[0]; x <= bottomRight[0]; x++)
        {
          image.pixel(x, y) = val;
        }
      }
    }
    else
    {
      // Horizontal edges (top & bottom)
      for (int x = topLeft[0]; x <= bottomRight[0]; x++)
      {
        image.pixel(x, topLeft[1]) = val; // top edge
        image.pixel(x, bottomRight[1]) = val; // bottom edge
      }

      // Vertical edges (left & right)
      for (int y = topLeft[1]; y <= bottomRight[1]; y++)
      {
        image.pixel(topLeft[0], y) = val; // left edge
        image.pixel(bottomRight[0], y) = val; // right edge
      }
    }
  }

protected:

  template<typename T, int N>
  static void drawLineLow(Image<T, N> &image,
                          int &x0, int &y0,
                          int &x1, int &y1,
                          const std::array<T, N> &val)
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
      image.pixel(x, y) = val;
      if (D > 0)
      {
        y = y + yi;
        D = D - 2*dx;
      }
      D = D + 2*dy;
    }
  }

  template<typename T, int N>
  static void drawLineHigh(Image<T, N> &image,
                           int x0, int y0,
                           int x1, int y1,
                           const std::array<T, N> &val)
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
      image.pixel(x, y) = val;
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
  ~Drawing() = delete;
};

} // namespace gfx2d
} // namespace spatium

#endif // SPATIUMLIB_GFX2D_DRAWING_H
