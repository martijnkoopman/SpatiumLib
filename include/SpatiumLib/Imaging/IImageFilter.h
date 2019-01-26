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

#include "SpatiumLib/Imaging/Image.h"

#ifndef SPATIUMLIB_IIMAGEFILTER_H
#define SPATIUMLIB_IIMAGEFILTER_H

#include <vector>
#include <algorithm> // std::find

namespace Imaging {

/// \class IImageFilter
/// \brief Interface class for all image filters.
class IImageFilter
{
public:
  // Destructor
  virtual ~IImageFilter() = default;

  // Apply filter
  template<typename T, int N>
  bool apply(const Image<T, N> &input, Image<T, 1> &output)
  {
    // Check image size equal
    if (input.width() != output.width() || input.height() != output.height())
    {
      return false;
    }

    return apply(input, output);
  }

  // Apply filter in place
  template<typename T, int N>
  bool apply(Image<T, N> &inoutput)
  {
    return apply(inoutput);
  }
};

} // namespace Imaging

#endif // SPATIUMLIB_IIMAGEFILTER_H
