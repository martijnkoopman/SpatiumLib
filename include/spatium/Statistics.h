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

#ifndef SPATIUM_STATISTICS_H
#define SPATIUM_STATISTICS_H

#include "Vector.h"

namespace spatium {
namespace statistics {

/// Calculate mean value
///
/// \param[in] values Values vector
/// \return Mean value
inline double mean(const Vector &values)
{
  double result = 0;

  unsigned count = values.rows();
  const double divider = 1 / count;
  for (unsigned i = 0; i < count; i++)
  {
    result += values(i) * divider;
  }

  return result;
}

/// \todo variance, standard deviation, covariance matrix

} // namespace statistics
} // namespace spatium

#endif // SPATIUM_STATISTICS_H
