/*
 * Program: Spatial Math Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPHEROID_H
#define SPHEROID_H

#include "ellipsoid.h"

namespace SML {

/// \brief Spheroid geometry
///
/// A spheroid is an ellipsoid with two equal semi-diamters.
///
/// A spheroid is defined by a point (origin) and two radii:
/// - Equatorial radius (axisXY)
/// - Polar radius (axisZ)
///
/// Parametric description = (x^2 + y^2) / a^2 + z^2 / c^2 = 1
class Spheroid : public Ellipsoid
{
public:
  /// Constructor
  ///
  /// \param[in] origin Origin
  /// \param[in] axisXY X and Y axis length
  /// \param[in] axisZ Z axis length
  Spheroid(const Point3 &origin, double axisXY, double axisZ)
    : Ellipsoid(origin, axisXY, axisXY, axisZ)
  {
  }

  /// Constructor
  ///
  /// \param[in] axisXY X and Y axis length
  /// \param[in] axisZ Z axis length
  Spheroid(double axisXY, double axisZ)
    : Ellipsoid(axisXY, axisXY, axisZ)
  {
  }

  /// Copy constructor
  Spheroid(const Spheroid &other) = default;

  /// Assignment operator
  Spheroid& operator=(const Spheroid &other) = default;

  /// Destructor
  virtual ~Spheroid() = default;

  /// Set X and Y axis length.
  ///
  /// \param[in] axisXY X and Y axis length.
  void axisXY(double axisXY)
  {
    m_axisX = axisXY;
    m_axisY = axisXY;
    updateTransformation();
  }

  /// Get X and Y axis length.
  ///
  /// \return X and Y axis length
  double axisXY() const
  {
    return m_axisX;
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Spheroid &spheroid)
  {
    os << "Spheroid\n";
    os << "Origin = " << spheroid.origin() << "\n";
    os << "X & Y axis length = " << spheroid.axisXY() << "\n";
    os << "Z axis length = " << spheroid.axisZ() << "\n";
    return os;
  }

private:
  // X and Y axis lengths can not be set independently for a spheroid
  // m_axisX == m_axisY
  using Ellipsoid::axisX;
  using Ellipsoid::axisY;
};

} // namespace SML

#endif // SPHEROID_H
