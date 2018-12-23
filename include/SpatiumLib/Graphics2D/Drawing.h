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

  void drawCircle(const Point &center, int radius, bool fill, unsigned value, Imaging::Image &image)
  {
    //
  }

  void drawLine(const Point &start, const Point &end, unsigned value, Imaging::Image &image)
  {
    //
  }

  void drawRectangle(const Point &start, const Point &end, unsigned value, Imaging::Image &image)
  {

  }

protected:

private:
  Drawing() = delete;
  virtual ~Drawing() = delete;

};

} // namespace Graphics2D

#endif // SPATIUMLIB_GRAPHICS_DRAWING_H
