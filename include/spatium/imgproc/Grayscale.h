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

#ifndef SPATIUMLIB_IMGPROC_GRAYSCALE_H
#define SPATIUMLIB_IMGPROC_GRAYSCALE_H

#include "IImageFilter.h"

namespace spatium {
namespace imgproc {

/// \class Grayscale
/// \brief Color image to grayscale
///
/// Convert color image as RGB format to grayscale.
template<typename T = unsigned char>
class Grayscale : public IImageFilter
{
public:
  /// Constructor.
  ///
  /// Coefficients are used to convert 3 RGB values to 1 grayscale value.
  /// Each coefficient is a weight for a partical channel: red, green and blue.
  /// The sum of the coefficients should be 1.
  ///
  /// \param[in] redCoeff Red coefficient (default = 0.2125)
  /// \param[in] greenCoeff Green coefficient (default = 0.7154)
  /// \param[in] blueCoff Blue coefficient (default = 0.0721)
  Grayscale(double redCoeff = 0.2125,
            double greenCoeff = 0.7154,
            double blueCoff = 0.0721)
    : m_redCoeff(redCoeff)
    , m_greenCoeff(greenCoeff)
    , m_blueCoeff(blueCoff)
  {}

  /// Apply filter.
  ///
  /// \param[in] input RGB image with 3 channels
  /// \param[out] output Grayscale image with 1 channel
  /// \return True on success, false on image dimensions mismatch
  bool apply(const Image<T, 3> &input, Image<T, 1> &output)
  {
    // Check image sizes
    if (input.width() != output.width() ||
        input.height() != output.height())
    {
      return false;
    }

    for (size_t y = 0; y < input.height(); y++)
    {
      for (size_t x = 0; x < input.width(); x++)
      {
        std::array<T, 3> pixel = input.pixel(x, y);
        output.pixel(x, y) = { pixel[0] * m_redCoeff + pixel[1] * m_greenCoeff + pixel[2] * m_blueCoeff };
      }
    }

    return true;
  }

  /// Set RGB coefficients.
  ///
  /// These coefficients are used to convert 3 RGB values to 1 grayscale value.
  /// Each coefficient is a weight for a partical channel: red, green and blue.
  /// The sum of the coefficients should be 1.
  ///
  /// \param[in] redCoeff Red coefficient (default = 0.2125)
  /// \param[in] greenCoeff Green coefficient (default = 0.7154)
  /// \param[in] blueCoff Blue coefficient (default = 0.0721)
  void setCoefficients(double redCoeff, double greenCoeff, double blueCoeff)
  {
    m_redCoeff = redCoeff;
    m_greenCoeff = greenCoeff;
    m_blueCoeff = blueCoeff;
  }

  /// Get RGB coefficients.
  ///
  /// These coefficients are used to convert 3 RGB values to 1 grayscale value.
  /// Each coefficient is a weight for a partical channel: red, green and blue.
  /// The sum of the coefficients should be 1.
  ///
  /// \return RGB coefficients
  std::array<double, 3> coefficients() const
  {
    return { m_redCoeff, m_greenCoeff, m_blueCoeff };
  }

private:
  double m_redCoeff;    ///< Red channel coefficient
  double m_greenCoeff;  ///< Green channel coefficient
  double m_blueCoeff;   ///< Blue channel coefficient
};

} // namespace imgproc
} // namespace spatium

#endif // SPATIUMLIB_IMGPROC_GRAYSCALE_H

