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

#ifndef SPATIUMLIB_GEOM2D_VECTOR2_H
#define SPATIUMLIB_GEOM2D_VECTOR2_H

#include "spatium/Vector.h"
#include <cmath> // sqrt(), acos()

namespace spatium {
namespace geom2d {

/// \brief Vector in 2D space
///
/// Column vector with 3 rows. The first two elements
/// define the X and Y coordinates. The third element is always 0.
class Vector2 : public Vector
{
public:
  /// Constructor
  Vector2()
    : Vector(3)
  {
  }

  /// Constructor
  ///
  /// \param[in] x X coordinate
  /// \param[in] y Y coordinate
  Vector2(double x, double y)
    : Vector(3)
  {
    m_data[0] = x;
    m_data[1] = y;
  }

  /// Constructor
  ///
  /// \param[in] xy Array with X and Y coordinates
  Vector2(double xy[])
    : Vector(3)
  {
    m_data[0] = xy[0];
    m_data[1] = xy[1];
  }

  /// Constructor
  ///
  /// \param[in] vector STD vector
  Vector2(std::vector<double> vector)
    : Vector(3)
  {
    if (vector.size() < 2)
    {
      return;
    }

    m_data[0] = vector[0];
    m_data[1] = vector[1];
  }

  /// Copy constructor
  Vector2(const Vector2 &other) // Needed?
    : Vector(other)
  {
  }

  /// Copy constructor
  ///
  /// \param[in] other Other matrix
  /// \throw std::out_of_range Matrix dimensions out of range
  Vector2(const Matrix &other)
    : Vector(3)
  {
    if (other.rows() != 3
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match vector dimensions");
    }

    m_data[0] = other(0,0);
    m_data[1] = other(1,0);
  }

  /// Assignment operator
  Vector2& operator=(Vector2 other)
  {
    Vector::operator=(other);
    return *this;
  }

  /// Desctructor
  ~Vector2() = default;

  void x(double val) { m_data[0] = val; }
  double x() const   { return m_data[0]; }
  void y(double val) { m_data[1] = val; }
  double y() const   { return m_data[1]; }

  /// Get coordinates as array.
  ///
  /// \return Coordinates
  double* array() { return m_data.data(); }

  /// Add matrix to vector.
  ///
  /// \param[in] other Matrix to add
  /// \throw std::out_of_range Matrix dimensions out of range
  /// \return Added vector
  Vector2 operator+(const Matrix &other) const
  {
    if (other.rows() != 3
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match vector dimensions");
    }

    Vector2 result;
    result.x(x() + other(0,0));
    result.y(y() + other(1,0));
    return result;
  }

  /// Subtract matrix from vector.
  ///
  /// \param[in] other Matrix to subtract
  /// \throw std::out_of_range Matrix dimensions out of range
  /// \return Subtracted vector
  Vector2 operator-(const Matrix &other) const
  {
    if (other.rows() != 3
        || other.cols() != 1)
    {
      throw std::out_of_range("Matrix dimensions do not match vector dimensions");
    }

    Vector2 result;
    result.x(x() - other(0,0));
    result.y(y() - other(1,0));
    return result;
  }

  /// Multiply vector by scalar.
  ///
  /// \param[in] scalar
  /// \return Multiplied vector
  Vector2 operator*(double scalar) const
  {
    Vector2 result;
    result.x(x() * scalar);
    result.y(y() * scalar);
    return result;
  }

  /// Divide by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Divided vector
  Vector2 operator/(double scalar) const
  {
    Vector2 result;
    result.x(x() / scalar);
    result.y(y() / scalar);
    return result;
  }

  /// Calculate length of vector (magnitude).
  ///
  /// \return Length
  double length() const
  {
    return sqrt( (x() * x()) + (y() * y()) );
  }

  /// Normalize the vector.
  /// A normalized vector has length = 1.
  void normalize()
  {
    double l = length();
    x(x() / l);
    y(y() / l);
  }

  /// Get normalized copy of vector.
  /// A normalized vector has length = 1.
  ///
  /// \return Normalized vector
  Vector2 normalized() const
  {
    double l = length();

    Vector2 result;
    result.x(x() / l);
    result.y(y() / l);
    return result;
  }

  /// Calculate dot product with vector.
  /// Dot product = 0: vectors are orthogonal (perpendicular).
  /// Dot product = |a||b| (1 if normalized): vectors are parallel.
  ///
  /// \param[in] other Other vector
  /// \return Dot product
  double dot(const Vector2 &other) const
  {
    return x() * other.x() + y() * other.y();
  }

  /// Calculate angle with vector.
  ///
  /// \param[in] other Other vector
  /// \return Angle in radians
  double angle(const Vector2 &other) const
  {
    return acos((this->dot(other)) / (this->length() * other.length()));
  }

  /// Project vector onto vector.
  ///
  /// \param[in] other Vector to project
  /// \return Projected vector
  Vector2 project(const Vector2 &other) const
  {
    return this->normalized() * (other.dot(*this) / this->length());
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector)
  {
    os << "Vector2 (";
    os << vector.x() << ", ";
    os << vector.y() << ", 0)";
    return os;
  }
};

} // namespace geom2d
} // namespace spatium

#endif // SPATIUMLIB_GEOM2D_VECTOR2_H
