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

#ifndef SPATIUMLIB_IMGPROC_SOBEL_H
#define SPATIUMLIB_IMGPROC_SOBEL_H

#include "IImageFilter.h"

#include <cmath> // std::sqrt

namespace spatium {
namespace imgproc {

/// \class Sobel
class Sobel : public IImageFilter
{
public:
  Sobel() = default;
  virtual ~Sobel() = default;

  // Apply filter
  template<typename T>
  bool apply(const Image<T, 1> &input, Image<T, 1> &output)
  {
    if (input.width() != output.width() ||
        input.height() != output.height())
    {
      return false;
    }

    // Iterate pixels
    for (size_t y = 1; y < input.height()-1; y++)
    {
      for (size_t x = 1; x < input.width()-1; x++)
      {
        double Gx = input.pixel(x-1, y-1)[0] * -1 +
                    input.pixel(x-1,   y)[0] * -2 +
                    input.pixel(x-1, y+1)[0] * -1 +
                    input.pixel(x+1, y-1)[0] * 1 +
                     input.pixel(x+1,   y)[0] * 2 +
               input.pixel(x+1, y+1)[0] * 1;

        double Gy = input.pixel(x-1, y-1)[0] * -1 +
               input.pixel(  x, y-1)[0] * -2 +
               input.pixel(x+1, y-1)[0] * -1 +
               input.pixel(x-1, y+1)[0] * 1 +
               input.pixel(  x, y+1)[0] * 2 +
               input.pixel(x+1, y+1)[0] * 1;

        T G = std::sqrt(Gx * Gx + Gy * Gy);
        output.pixel(x, y) = { G };
      }
    }

    return true;
  }
};

} // namespace imgproc
} // namespace spatium

#endif // SPATIUMLIB_IMGPROC_SOBEL_H

