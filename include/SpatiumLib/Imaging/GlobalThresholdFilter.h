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

template<typename T>
class GlobalThresholdFilter
{
public:
  GlobalThresholdFilter(T thesholdValue = 0)
    : m_thresholdValue(thesholdValue)
  {}

  // Copy constructor
  GlobalThresholdFilter(const GlobalThresholdFilter &rhs) = default;

  // Assignment operator
  GlobalThresholdFilter& operator=(const GlobalThresholdFilter &rhs) = default;

  // Destuctor
  virtual ~GlobalThresholdFilter() = default;

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
    T newValue = std::numeric_limits<T>::max();

    for (int y = 0; y < input.height(); y++)
    {
      for (int x = 0; x < input.width(); x++)
      {
        std::array<T, N> pixel = input.getPixel(x, y);
        T value = Imaging::PixelValue<T, 1>::value(pixel)[0];
        if (value > m_thresholdValue)
        {
          output.setPixel(x, y, { newValue });
        }
        else {
          output.setPixel(x, y, { 0 });
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
        std::array<T, 1> pixel = inoutput.getPixel(x, y);
        T value = pixel[0];
        if (value > m_thresholdValue)
        {
          inoutput.setPixel(x, y, { newValue });
        }
        else {
          inoutput.setPixel(x, y, { 0 });
        }
      }
    }

    return true;
  }


private:
  T m_thresholdValue;
};

} // namespace Imaging

#endif // SPATIUMLIB_GLOBALTHRESHOLDFILTER_H

