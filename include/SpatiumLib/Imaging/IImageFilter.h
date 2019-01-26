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
  /*

  /// Run filter with input and output image.
  bool run(const Image &input, Image &output) const
  {
    // Check image size equal
    if (input.width() != output.width() || input.height() != output.height())
    {
      return false;
    }

    return apply(input, output);
  }

  bool runInPlace(Image &image) const
  {
    // Check input format supported
    std::vector<Image::Format> formats = supportedInputFormats();
    if (std::find(std::begin(formats),
                  std::end(formats),
                  image.format()) != std::end(formats))
    {
      return false;
    }

    // Check output format supported
    if (image.format() != outputFormat())
    {
      return false;
    }

    return apply(image);
  }

protected:
  virtual bool apply(const Image &input, Image &output) const = 0;
  virtual bool apply(Image &image) const = 0;

*/
};

} // namespace Imaging

#endif // SPATIUMLIB_IIMAGEFILTER_H
