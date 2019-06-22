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

#ifndef SPATIUMLIB_IMGPROC_BLUR_H
#define SPATIUMLIB_IMGPROC_BLUR_H

#include "IImageFilter.h"

namespace spatium {
namespace imgproc {

/// \class Blur
class Blur
{
public:
  Blur() = default;
  virtual ~Blur() = default;

  // Apply filter
  template<typename T, int N>
  bool apply(const Image<T, N> &input, Image<T, N> &output)
  {
    if (input.width() != output.width() ||
        input.height() != output.height())
    {
      return false;
    }

    // Iterate pixels
    for (int y = 0; y < input.height(); y++)
    {
      for (int x = 0; x < input.width(); x++)
      {
        double divider = 1.0/9.0;
        double sum[N] = {};

        // Iterate window
        for (int i = -1; i < 2; i++)
        {
          for (int j = -1; j < 2; j++)
          {
            // Clamp x and y
            int dx = x+j;
            int dy = y+i;
            if (dx < 0) { dx = 0; } else if(dx == input.width()) { dx = input.width()-1; };
            if (dy < 0) { dy = 0; } else if(dy == input.height()) { dy = input.height()-1; };

            auto pixel = input.pixel(dx, dy);
            for (int c = 0; c < N; c++)
            {
              sum[c] += divider * pixel[c];
            }
          }
        }

        // Cast to T
        std::array<T,N> value;
        for (int c = 0; c < N; c++)
        {
          value[c] = sum[c]; /// \todo cast
        }

        output.pixel(x, y) = value;
      }
    }

    return true;
  }
};

} // namespace imgproc
} // namespace spatium

#endif // SPATIUMLIB_IMGPROC_BLUR_H

