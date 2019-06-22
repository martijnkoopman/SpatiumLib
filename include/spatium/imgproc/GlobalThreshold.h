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

#ifndef SPATIUMLIB_IMGPROC_GLOBALTHRESHOLD_H
#define SPATIUMLIB_IMGPROC_GLOBALTHRESHOLD_H

#include "IImageFilter.h"

namespace spatium {
namespace imgproc {

/// \class GlobalThresholdFilter
/// \brief Global threshold image filter
///
/// GlobalThreshold is a class for binarizing an image by a given threshold
/// value.
template<typename T>
class GlobalThreshold : public IImageFilter
{
public:
  GlobalThreshold(T thesholdValue = 0)
    : m_thresholdValue(thesholdValue)
  {}

  // Copy constructor
  GlobalThreshold(const GlobalThreshold &rhs) = default;

  // Assignment operator
  GlobalThreshold& operator=(const GlobalThreshold &rhs) = default;

  // Destuctor
  virtual ~GlobalThreshold() = default;

  /// Get threshold value.
  ///
  /// \return Threshold value
  T thresholdValue() const
  {
    return m_thresholdValue;
  }

  /// Set threshold value.
  ///
  /// \param[in] value Threshold value
  void setThresholdValue(T value)
  {
    m_thresholdValue = value;
  }

  // Apply filter
  template<int N>
  bool apply(const Image<T, N> &input, Image<T, 1> &output)
  {
    if (input.width() != output.width() ||
        input.height() != output.height())
    {
      return false;
    }

    T newValue = std::numeric_limits<T>::max();

    for (size_t y = 0; y < input.height(); y++)
    {
      for (size_t x = 0; x < input.width(); x++)
      {
        std::array<T, N> pixel = input.pixel(x, y);
        T value = PixelValue<T, 1>::value(pixel)[0];
        if (value > m_thresholdValue)
        {
          output.pixel(x, y) = { newValue };
        }
        else {
          output.pixel(x, y) = { 0 };
        }
      }
    }

    return true;
  }

  // Apply in place
  bool apply(Image<T, 1> &inoutput)
  {
    T newValue = std::numeric_limits<T>::max();

    for (int y = 0; y < inoutput.height(); y++)
    {
      for (int x = 0; x < inoutput.width(); x++)
      {
        std::array<T, 1> pixel = inoutput.pixel(x, y);
        T value = pixel[0];
        if (value > m_thresholdValue)
        {
          inoutput.pixel(x, y) = { newValue };
        }
        else {
          inoutput.pixel(x, y) = { 0 };
        }
      }
    }

    return true;
  }

private:
  T m_thresholdValue;
};

} // namespace imgproc
} // namespace spatium

#endif // SPATIUMLIB_IMGPROC_GLOBALTHRESHOLD_H

