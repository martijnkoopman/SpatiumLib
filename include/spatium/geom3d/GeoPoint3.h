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

#ifndef SPATIUMLIB_GEOM3D_GEOPOINT3_H
#define SPATIUMLIB_GEOM3D_GEOPOINT3_H

#include "Point3.h"

namespace spatium {
namespace geom3d {

/// \class GeoPoint3
/// \brief Point in 3D geographical space as homogeneous coordinates
///
/// The implementation of GeoPoint3 is identical to Point3. Only the names of
/// the fields are different: longitude, latitude and elevation.
class GeoPoint3 : public Point3
{
public:
  /// Constructor
  GeoPoint3()
    : Point3()
  {
  }

  /// Constructor
  ///
  /// \param[in] longitude Longitude coordinate
  /// \param[in] latitude Latitude coordinate
  /// \param[in] elevation Elevation coordinate
  GeoPoint3(double longitude, double latitude, double elevation)
    : Point3(longitude, latitude, elevation)
  {
  }

  /// Constructor
  ///
  /// \param[in] lonLatElev Array with longitude, latitude and latitude
  ///                       coordinates
  GeoPoint3(double lonLatElev[])
    : Point3(lonLatElev)
  {
  }

  /// Copy constructor
  ///
  /// \param[in] other Other GeoPoint3
  GeoPoint3(const GeoPoint3 &other)
    : Point3(other)
  {
  }

  /// Copy constructor
  ///
  /// \param[in] other Other matrix
  /// \throw std::out_of_range Matrix dimensions out of range
  GeoPoint3(const Matrix &other)
    : Point3(other)
  {
  }

//  /// Assignment operator
//  GeoPoint3& operator=(GeoPoint3 other){
//    Matrix::operator=(other);
//    return *this;
//  }

  /// Assignment operator
  GeoPoint3& operator=(const GeoPoint3 &other) = default;

  /// Destructor
  ~GeoPoint3() = default;

  void longitude(double val) { m_data[0] = val; }
  double longitude() const { return m_data[0]; }
  void latitude(double val) { m_data[1] = val; }
  double latitude() const { return m_data[1]; }
  void elevation(double val) { m_data[2] = val; }
  double elevation() const { return m_data[2]; }

  /// Subtract matrix from geo point.
  ///
  /// \param[in] other Matrix to subtract
  /// \throw std::out_of_range Matrix dimensions out of range
  /// \return Subtracted point
  GeoPoint3 operator-(const Matrix &other) const
  {
      return Point3::operator -(other);
  }

  /// Add matrix to geo point.
  ///
  /// \param[in] other Matrix to add
  /// \throw std::out_of_range Matrix dimensions out of range
  /// \return Added point
  GeoPoint3 operator+(const Matrix &other) const
  {
    return Point3::operator +(other);
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const GeoPoint3 &geoPoint)
  {
    os << "GeoPoint3 (";
    os << geoPoint.longitude() << ", ";
    os << geoPoint.latitude() << ", ";
    os << geoPoint.elevation() << ", 1)";
    return os;
  }

private:
  using Point3::x;
  using Point3::y;
  using Point3::z;
};

} // namespace geom3d
} // namespace spatium

#endif // SPATIUMLIB_GEOM3D_GEOPOINT3_H
