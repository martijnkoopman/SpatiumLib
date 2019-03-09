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

#ifndef SPATIUMLIB_GEOM3D_POINT3_H
#define SPATIUMLIB_GEOM3D_POINT3_H

#include "spatium/Matrix.h"
#include "Vector3.h"

namespace spatium {
namespace geom3d {

/// \class Point3
/// \brief Point in 3D Cartesian space as homogeneous coordinates
///
/// A point is a Matrix with 1 column and 4 rows. The first three elements
/// define the X, Y and Z coordinates. The fourth element is always 1.
class Point3 : public Vector
{
public:
  /// Constructor
  Point3()
    : Vector(4)
  {
    m_data[3] = 1;
  }

  /// Constructor
  ///
  /// \param[in] x X coordinate
  /// \param[in] y Y coordinate
  /// \param[in] z Z coordinate
  Point3(double x, double y, double z)
    : Vector(4)
  {
    m_data[0] = x;
    m_data[1] = y;
    m_data[2] = z;
    m_data[3] = 1;
  }

  /// Constructor
  ///
  /// \param[in] xyz Array with X, Y and Z coordinates
  Point3(double xyz[])
    : Vector(4)
  {
    m_data[0] = xyz[0];
    m_data[1] = xyz[1];
    m_data[2] = xyz[2];
    m_data[3] = 1;
  }

  /// Copy constructor
  ///
  /// \param[in] other Other Point3
  Point3(const Point3 &other)
    : Vector(other)
  {
  }

  /// Copy constructor
  ///
  /// \param[in] other Other matrix
  /// \throw std::out_of_range Matrix dimensions out of range
  Point3(const Matrix &other)
    : Vector(4)
  {
    if (other.rows() != 4
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match point dimensions");
    }

    m_data[0] = other(0,0);
    m_data[1] = other(1,0);
    m_data[2] = other(2,0);
    m_data[3] = 1;
  }

  /// Assignment operator
  Point3& operator=(const Point3 &other) = default;

//  Point3& operator=(Point3 other){
//    Matrix::operator=(other);
//    return *this;
//  }

  /// Destructor
  ~Point3() = default;

  void x(double val) { m_data[0] = val; }
  double x() const { return m_data[0]; }
  void y(double val) { m_data[1] = val; }
  double y() const { return m_data[1]; }
  void z(double val) { m_data[2] = val; }
  double z() const { return m_data[2]; }

  /// Get coordinates as array.
  ///
  /// \return Coordinates
  double* array() { return m_data.data(); }

  /// Subtract matrix from point.
  ///
  /// \param[in] other Matrix to subtract
  /// \throw std::out_of_range Matrix dimensions out of range
  /// \return Subtracted point
  Point3 operator-(const Matrix &other) const
  {
    if (other.rows() != 4
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match point dimensions");
    }

    Point3 result;
    result.x(x() - other(0,0));
    result.y(y() - other(1,0));
    result.z(z() - other(2,0));
    return result;
  }

  /// Add matrix to point.
  ///
  /// \param[in] other Matrix to add
  /// \throw std::out_of_range Matrix dimensions out of range
  /// \return Added point
  Point3 operator+(const Matrix &other) const
  {
    if (other.rows() != 4
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match point dimensions");
    }

    Point3 result;
    result.x(x() + other(0,0));
    result.y(y() + other(1,0));
    result.z(z() + other(2,0));
    return result;
  }

  /// Calculate Euclidean distance to point.
  ///
  /// \param[in] point Other point
  /// \return Distance to point
  double distanceTo(const Point3 &point) const
  {
    return Vector3(*this - point).length();
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Point3 &point)
  {
    os << "Point3 (";
    os << point.x() << ", ";
    os << point.y() << ", ";
    os << point.z() << ", 1)";
    return os;
  }
};

} // namespace geom3d
} // namespace spatium

#endif // SPATIUMLIB_GEOM3D_POINT3_H
