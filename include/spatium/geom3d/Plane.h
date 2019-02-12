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

#ifndef SPATIUMLIB_GEOM3D_PLANE_H
#define SPATIUMLIB_GEOM3D_PLANE_H

#include "Geometry.h"
#include "Point3.h"
#include "Vector3.h"

namespace spatium {
namespace geom3d {

/// \brief Plane geometry
///
/// A plane is defined by a point (origin) and a vector perpendicular to the
/// plane (normal).
class Plane : public Geometry
{
public:
  /// Constructor
  ///
  /// \param[in] origin Origin
  /// \param[in] normal Normal
  Plane(const Point3 &origin, const Vector3 &normal)
    : m_origin(origin)
    , m_normal(normal.normalized())
  {
  }

  /// Constructor
  ///
  /// \param[in] normal Normal
  Plane(const Vector3 &normal)
    : m_origin(0,0,0)
    , m_normal(normal.normalized())
  {
  }

  /// Copy constructor
  Plane(const Plane &other) = default;

  /// Assignment operator
  Plane& operator=(const Plane &other) = default;

  /// Destructor
  virtual ~Plane() = default;

  /// Set origin of plane.
  ///
  /// \param[in] origin Origin
  void origin(const Point3 &origin)
  {
    m_origin = origin;
  }

  /// Get origin of plane.
  ///
  /// \return Origin
  Point3 origin() const
  {
    return m_origin;
  }

  /// Set normal of plane.
  ///
  /// \param[in] normal Normal
  void normal(const Vector3 &normal)
  {
    m_normal = normal.normalized();
  }

  /// Get normal of plane.
  ///
  /// \return Normal
  Vector3 normal() const
  {
    return m_normal;
  }

  /// Calculate Euclidean distance to point.
  ///
  /// \param[in] point Point
  /// \return Distance to point
  double distanceTo(const Point3 &point) const override
  {
    return fabs(Vector3(point - m_origin).dot(m_normal));
  }

  /// Project point onto plane.
  ///
  /// \param[in] point Point
  /// \return Projected point
  Point3 projectPoint(const Point3 &point) const override
  {
    return point - (m_normal * Vector3(point - m_origin).dot(m_normal));
  }

  /// Intersect line with plane.
  /// There is no intersection if the line is parallel to the plane.
  ///
  /// \param[in] origin Origin of line
  /// \param[in] direction Direction of line
  /// \param[out] intersection Intersection point
  /// \return True if there is an intersection, otherwise false
  bool intersectLine(const Point3 &origin,
                     const Vector3 &direction,
                     Point3 &intersection) const override
  {
    double dot = direction.dot(m_normal);
    if (dot == 0)
    {
      // Line and plane are parallel
      return false;
    }

    double d = Vector3(m_origin - origin).dot(m_normal) / dot;
    intersection = origin + (direction * d);
    return true;
  }

  /// Project vector onto plane.
  ///
  /// \param[in] vector Vector
  /// \return Projected vector
  Vector3 projectVector(const Vector3 &vector) const
  {
    return vector - (m_normal * vector.dot(m_normal));
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Plane &plane)
  {
    os << "Plane\n";
    os << "Origin = " << plane.origin() << "\n";
    os << "Normal = " << plane.normal() << "\n";
    return os;
  }

protected:
  Point3 m_origin;
  Vector3 m_normal; // Always normalized
};

} // namespace geom3d
} // namespace spatium

#endif // SPATIUMLIB_GEOM3D_PLANE_H
