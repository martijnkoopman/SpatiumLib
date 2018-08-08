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

#ifndef UTIL_H
#define UTIL_H

namespace Math {
namespace Geometry {

/// Convert decimal degrees to degrees, minutes and seconds.
///
/// \param[in] degreesDecimal Degrees as decimal
/// \param[out] degrees Degrees as whole number
/// \param[out] minutes Minutes as whole number
/// \param[out] seconds Seconds as decimal
inline void degrees2dms(double degreesDecimal, int &degrees, int &minutes, double &seconds)
{
  double residue = degreesDecimal;

  degrees = static_cast<int>(residue);
  residue -= degrees;

  minutes = static_cast<int>(residue / ((double)1 / 60));
  residue -= minutes * ((double)1 / 60);

  seconds = residue / ((double)1 / (60*60));
}

} // namespace Geometry
} // namespace Math

#endif // UTIL_H
