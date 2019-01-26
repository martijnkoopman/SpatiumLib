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
class GlobalThresholdFilter : public IImageFilter
{
public:
  GlobalThresholdFilter(T thesholdValue = 0, T newValue = 255)
    : m_thresholdValue(thesholdValue)
    , m_newValue(newValue)
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

  template<int N>
  bool apply(const Image<T, N> &input, Image<T, 1> &output)
  {
    for (int y = 0; y < input.height(); y++)
    {
      for (int x = 0; x < input.width(); x++)
      {
        //std::array<T, N> pixel = input.getPixel();
        //T value = pixelValue(pixel);
        //if (value > m_thresholdValue)
        //{
        //  output.setPixel(x, y, { m_newValue });
        //}
      }
    }
  }

//  bool apply(Image<T, 1> &inoutput)
//  {
//    for (int y = 0; y < inoutput.height(); y++)
//    {
//      for (int x = 0; x < inoutput.width(); x++)
//      {
//        T value = pixelValue(inoutput.getPixel());
//        if (value > m_thresholdValue)
//        {
//          inoutput.setPixel(x, y, m_newValue);
//        }
//      }
//    }
//  }

protected:

  T pixelValue(const std::array<T, 1> &pixel)
  {
    return pixel[0];
  }

  T pixelValue(const std::array<T, 3> &pixel)
  {
    return pixel[0] * 0.2125 + pixel[1] * 0.7154 + pixel[2] * 0.0721;
  }

  T pixelValue(const std::array<T, 4> &pixel)
  {
    return pixel[0] * 0.2125 + pixel[1] * 0.7154 + pixel[2] * 0.0721;
    // pixel[3] is unused (alpha value probaly)
  }

private:
  T m_thresholdValue;
  T m_newValue;
};

} // namespace Imaging

#endif // SPATIUMLIB_GLOBALTHRESHOLDFILTER_H

