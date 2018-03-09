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

#ifndef OBLATESPHEROID_H
#define OBLATESPHEROID_H

#include "Spheroid.h"

namespace SML {

/// \brief Oblate spheroid geometry
///
/// An oblate spheroid is a flattened spheroid. The equatorial axis length is
/// greater than the polar axis length. Such a spheroid is perfect for
/// approximating the shape of the earh.
class OblateSpheroid : public Spheroid
{
public:
  /// Constructor.
  /// Required: axisXY > axisZ
  ///
  /// \param[in] origin Origin
  /// \param[in] axisXY X and Y axis length
  /// \param[in] axisZ Z axis length
  OblateSpheroid(const Point3 &origin, double axisXY, double axisZ)
    : Spheroid(origin, axisXY, axisZ)
  {
  }

  /// Constructor
  /// Required: axisXY > axisZ
  ///
  /// \param[in] axisXY X and Y axis length
  /// \param[in] axisZ Z axis length
  OblateSpheroid(double axisXY, double axisZ)
    : Spheroid(axisXY, axisZ)
  {
  }

  /// Create oblate spheroid by a given inverse flattening (1/f).
  ///
  /// \param[in] origin Origin of spheroid
  /// \param[in] axisXY X and Y axis length (equatorial)
  /// \param[in] inverseFlattening 1/f
  /// \return Oblate spheroid
  static OblateSpheroid byFlattening(const Point3 &origin, double axisXY,
                                     double inverseFlattening)
  {
    return OblateSpheroid(origin, axisXY,
                          axisXY - ((1 / inverseFlattening) * axisXY));
  }

  /// Calculate the flattening.
  ///
  /// \return Flattening
  double flattening() const
  {
    return 1 - m_axisZ / m_axisX;
  }

  /// Calculate the eccentricity.
  ///
  /// \return Eccentricity
  double eccentricity() const
  {
    return 1 - (m_axisZ*m_axisZ) / (m_axisX*m_axisX);
  }

  /// Calculate Cartesian coordinates from oblate spheroidal coordinates.
  ///
  /// \param[in] longitude Longitude in radians
  /// \param[in] latitude Latitude in radians
  /// \param[in] height Height
  /// \return Point with cartesian x,y and z coordinates
  Point3 spheroidalToCartesianCoordinates(double longitude, double latitude,
                                          double height) const
  {
    // http://www.navipedia.net/index.php/
    // Ellipsoidal_and_Cartesian_Coordinates_Conversion
    double f = 1 - m_axisZ / m_axisX;
    double e2 = 2 * f - f*f;
    double N = m_axisX / sqrt(1 - e2 * pow(sin(latitude), 2) );
    double x = (N + height) * cos(latitude) * cos(longitude);
    double y = (N + height) * cos(latitude) * sin(longitude);
    double z = ((1 - e2) * N + height) * sin(latitude);
    return Point3(x, y, z);
  }

  /// Calculate oblate spheroidal coordinates from Cartesian coordinates.
  /// Cartesian vector (-1, 0, 0) points towards origin of spheroidal
  /// coordinate system.
  ///
  /// \param[in] x X coordinate
  /// \param[in] y Y coordinate
  /// \param[in] z Z coordinate
  /// \param[in] precision Precision to aquire in latitude and height.
  ///            Omitted if precision == 0
  /// \return Point with spheroidal coordinates: latitude, longitude and
  ///         elevation. Latitude and longtiude are in radians.
  Point3 cartesianToSpheroidalCoordinates(double x, double y, double z,
                                          double precision = 0) const
  {
    // http://www.navipedia.net/index.php/
    // Ellipsoidal_and_Cartesian_Coordinates_Conversion

    // Longitude
    double longitude = atan2(y,x);

    // Latitude
    double f = 1 - m_axisZ / m_axisX;
    double e2 = 2 * f - f*f;
    double p = sqrt(x*x + y*y);
    double latitude = atan(z / ((1 - e2) * p));

    // Height
    double N = m_axisX / sqrt(1 - e2 * pow(sin(latitude), 2));
    double height = (p / cos(latitude)) - N;

    // Note: latitude and height could be improved iterativly, but doesn't
    // seem necessarily

    return Point3(longitude, latitude, height);
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const OblateSpheroid &spheroid)
  {
    os << "OblateSpheroid\n";
    os << "Origin = " << spheroid.origin() << "\n";
    os << "X & Y axis length = " << spheroid.axisXY() << "\n";
    os << "Z axis length = " << spheroid.axisZ() << "\n";
    return os;
  }
};

} // namespace SML

#endif // OBLATESPHEROID_H
