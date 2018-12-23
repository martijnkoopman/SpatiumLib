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

#include "IImageFilter.h"
#include <functional>

#ifndef SPATIUMLIB_GLOBALTHRESHOLDFILTER_H
#define SPATIUMLIB_GLOBALTHRESHOLDFILTER_H

namespace Imaging {

class GlobalThresholdFilter : public IImageFilter
{
public:
  GlobalThresholdFilter(unsigned char thesholdValue = 127, bool invert = false)
    : m_thresholdValue(thesholdValue)
    , m_invert(invert)
  {}

  // Copy constructor
  GlobalThresholdFilter(const GlobalThresholdFilter &rhs) = default;

  // Assignment operator
  GlobalThresholdFilter& operator=(const GlobalThresholdFilter &rhs) = default;

  // Destuctor
  virtual ~GlobalThresholdFilter() override = default;

  /// Get threshold value.
  ///
  /// \return Threshold value
  unsigned char thresholdValue() const
  {
    return m_thresholdValue;
  }

  /// Set threshold value.
  ///
  /// \param[in] value Threshold value
  void setThresholdValue(unsigned char value)
  {
    m_thresholdValue = value;
  }

  /// Get invert thresholding
  ///
  /// \return Invert thresholding
  bool invert() const
  {
    return m_invert;
  }

  /// Set invert thresholding
  ///
  /// \param[in] invert Invert thresholding
  void setInvert(bool invert)
  {
    m_invert = invert;
  }

  // Protected functions

  std::vector<Image::Format> supportedInputFormats() const override
  {
    return std::vector<Image::Format>{
      Image::Format_Grayscale8, Image::Format_RGB24,
      Image::Format_RGB32, Image::Format_RGBA32 };
  }

  Image::Format outputFormat() const override
  {
    return Image::Format_Grayscale8;
  }

  bool apply(const Image &input, Image &output) const override
  {
    return false;
  }

  bool apply(Image &image) const override
  {
    std::function<unsigned char(Image&, size_t)> getValue;
    std::function<void(Image&, size_t, unsigned char)> setValue;
    switch(image.format())
    {
      case Image::Format_Grayscale8:
        getValue = [&](Image &image, size_t i) -> unsigned char { return image.imageData()[i]; };
        setValue = [&](Image &image, size_t i, unsigned char value) { image.imageData()[i] = value; };
      break;
      case Image::Format_RGB24:
        getValue = [&](Image &image, size_t i) -> unsigned char { return image.imageData()[i * 3]; };
        setValue = [&](Image &image, size_t i, unsigned char value) {
          image.imageData()[i * 3] = value;
          image.imageData()[i * 3 + 1] = value;
          image.imageData()[i * 3 + 2] = value;
        };
      break;
    case Image::Format_RGB32:
    case Image::Format_RGBA32:
      getValue = [&](Image &image, size_t i) -> unsigned char { return image.imageData()[i * 4]; };
      setValue = [&](Image &image, size_t i, unsigned char value) {
        image.imageData()[i * 4] = value;
        image.imageData()[i * 4 + 1] = value;
        image.imageData()[i * 4 + 2] = value;
      };
    break;
      default:
        return false;
    }

    unsigned char newValue;
    for (size_t i = 0; i < image.width() * image.height(); i++)
    {
      newValue = (getValue(image, i) > m_thresholdValue ? 255 : 0);
      setValue(image, i, newValue);
    }

    return true;
  }

private:
  unsigned char m_thresholdValue;
  bool m_invert;
};

} // namespace Imaging

#endif // SPATIUMLIB_GLOBALTHRESHOLDFILTER_H

