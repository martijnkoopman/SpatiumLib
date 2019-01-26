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

#include "Point.h"
#include "SpatiumLib/Imaging/Image.h"

namespace Graphics2D {

/// \class Drawing
class Drawing
{
public:

  template<typename T, int N>
  void drawCircle(const Point &center, int radius, bool fill, T value[N], Imaging::Image<T, N> &image)
  {
    //
  }

  template<typename T, int N>
  void drawLine(const Point &start, const Point &end, T value[N], Imaging::Image<T, N> &image)
  {
    //
  }

  template<typename T, int N>
  void drawRectangle(const Point &start, const Point &end, T value[N], Imaging::Image<T, N> &image)
  {

  }

protected:

private:
  Drawing() = delete;
  virtual ~Drawing() = delete;

};

} // namespace Graphics2D

#endif // SPATIUMLIB_GRAPHICS_DRAWING_H
