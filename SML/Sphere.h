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

#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"
#include "Point3.h"
#include "Util.h"

namespace SML {

class Vector3;

/// \brief Sphere geometry
///
/// A sphere is defined by a point (origin) and a radius.
///
/// Parametric description = x^2 + y^2 + z^2 = r^2
class Sphere : public Geometry
{
public:
  /// Constructor
  Sphere(const Point3 &origin, double radius)
    : m_origin(origin)
    , m_radius(radius)
  {
  }

  /// Constructor
  Sphere(double radius)
    : m_origin(0,0,0)
    , m_radius(radius)
  {
  }

  /// Copy constructor
  Sphere(const Sphere &other) = default;

  /// Assignment operator
  Sphere& operator=(const Sphere &other) = default;

  /// Destructor
  virtual ~Sphere() = default;

  /// Set origin of sphere.
  ///
  /// \param[in] origin Origin
  void origin(const Point3 &origin)
  {
    m_origin = origin;
  }

  /// Get origin of sphere.
  ///
  /// \return origin
  Point3 origin() const
  {
    return m_origin;
  }

  /// Set radius of sphere.
  ///
  /// \param[in] radius Radius
  void radius(double radius)
  {
    m_radius = radius;
  }

  /// Get radius of sphere.
  ///
  /// \return radius
  double radius() const
  {
    return m_radius;
  }

  /// Calculate Euclidean distance to point.
  ///
  /// \param[in] point Point
  /// \return distance to point
  double distanceTo(const Point3 &point) const override
  {
    return m_origin.distance(point) - m_radius;
  }

  /// Project point onto sphere.
  ///
  /// \param[in] point Point
  /// \return Projected point
  Point3 projectPoint(const Point3 &point) const override
  {
    Vector3 offset = point - m_origin;
    return m_origin + (offset * (m_radius/offset.length()));
  }

  /// Intersect line with sphere.
  ///
  /// \param[in] origin Origin of line
  /// \param[in] direction Direction of line
  /// \param[out] intersection Intersection point
  /// \return True if there is an intersection, otherwise false
  bool intersectLine(const Point3 &origin,
                     const Vector3 &direction,
                     Point3 &intersection) const override
  {
    Vector3 offset = origin - m_origin;

    double a = direction.dot(direction);
    double b = direction.dot(offset) * 2;
    double c = offset.dot(offset) - (m_radius * m_radius);

    double x1 = 0, x2 = 0;
    if (SML::solveQuadratic(a, b, c, x1, x2))
    {
      // Use x1 to find intersection
      intersection = origin + (direction * x1);
      return true;
    }
    else
    {
      return false;
    }
  }

  /// Compute surface normal at given point.
  ///
  /// \param[in] point Point
  /// \return Surface normal
  Vector3 surfaceNormal(const Point3 &point) const
  {
    // Sphere = x^2 + y^2 + z^2 = r^2
    // Normal = (2x, 2y,  2z)
    //        = (x, y,  z)
    Vector3 normal(point.x(), point.y(), point.z());
    normal.normalize();
    return normal;
  }

  /// Compute distance to horizon.
  ///
  /// \param[in] height Height above surface
  /// \return Distance to horizon
  double distanceToHorizon(double height) const
  {
    return sqrt(height * (2 * m_radius + height));
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Sphere &sphere)
  {
    os << "Sphere\n";
    os << "Origin = " << sphere.origin() << "\n";
    os << "Radius = " << sphere.radius() << "\n";
    return os;
  }

protected:
  Point3 m_origin;
  double m_radius;
};

} // namespace SML

#endif // SPHERE_H
