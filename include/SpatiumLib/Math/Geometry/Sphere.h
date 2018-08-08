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

#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"
#include "Point3.h"
#include "Util.h"
#include "SpatiumLib/Math/Math.h"

namespace Math {
namespace Geometry {

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

  /// Compute Euclidean distance to point.
  ///
  /// \param[in] point Point
  /// \return distance to point
  double distanceTo(const Point3 &point) const override
  {
    return m_origin.distanceTo(point) - m_radius;
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
    if (Math::solveQuadratic(a, b, c, x1, x2))
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

  /// Compute distance to horizon as straight line from a point above surface
  /// to the horizon.
  ///
  /// \param[in] height Height above surface
  /// \return Straight distance to horizon
  //double distanceToHorizonStraight(double height) const
  //{
  //  return sqrt(height * (2 * m_radius + height));
  //}

  /// Compute distance to horizon as curved line over the surface of the
  /// sphere (arc length).
  ///
  /// \param[in] height Height above surface
  /// \return Curved distance to horizon
  double distanceToHorizon(double height) const
  {
    return m_radius * acos(m_radius / (m_radius + height));
  }

  /// Compute point on horizon in a given direction.
  ///
  /// \param[in] point Point above surface
  /// \param[in] direction Direction towards horizon as polar coordinate in
  ///                      radians. 0 = east, 1/2 pi = north, etc.
  Point3 pointOnHorizon(const Point3 &point, double direction)
  {
    // Convert direction to X and Y
    double directionX = cos(direction); // Direction longitudinal
    double directionY = sin(direction); // Direction latitudinal

    // Project point on sphere
    Point3 pointOnSphere = projectPoint(point);

    // Compute distance to horizon
    double horizonDistance =
        distanceToHorizon(pointOnSphere.distanceTo(point));

    // Convert distance to angular distance
    double angularDistance = horizonDistance / m_radius;

    // Convert point to spherical coordinates
    Point3 sphericalCoordinates =
        cartesianToSphericalCoordinates(pointOnSphere.x(),
                                        pointOnSphere.y(),
                                        pointOnSphere.z());

    // Add angle towards direction
    Point3 pointOnHorizonSpherical(
          sphericalCoordinates.x() + directionX * angularDistance,
          sphericalCoordinates.y() + directionY * angularDistance,
          sphericalCoordinates.z());

    // Convert spherical to cartesian coordinates
    return sphericalToCartesianCoordinates(pointOnHorizonSpherical.x(),
                                           pointOnHorizonSpherical.y(),
                                           pointOnHorizonSpherical.z());
  }

  /// Compute Cartesian coordinates from spherical coordinates.
  ///
  /// \param[in] longitude Longitude in radians
  /// \param[in] latitude Latitude in radians
  /// \param[in] height Height above surface
  /// \return Point with cartesian x,y and z coordinates
  Point3 sphericalToCartesianCoordinates(double longitude,
                                         double latitude,
                                         double height)
  {
    double radial = m_radius + height;
    double x = radial * cos(latitude) * cos(longitude);
    double y = radial * cos(latitude) * sin(longitude);
    double z = radial * sin(latitude);
    return Point3(x, y, z);

    // TODO: Maybe it is:
    // x= sin(phi) * cos(theta);
    // y = sin(phi) * sin(theta);
    // z = cos(phi);
  }

  /// Compute spherical coordinates from Cartesian coordinates.
  /// Cartesian vector (-1, 0, 0) points towards origin of spherical
  /// coordinate system.
  ///
  /// \param[in] x X coordinate
  /// \param[in] y Y coordinate
  /// \param[in] z Z coordinate
  /// \return Point with spherical coordinates: latitude, longitude and
  ///         height above surface. Latitude and longtiude are in radians.
  Point3 cartesianToSphericalCoordinates(double x, double y, double z)
  {
    double radial = sqrt(x*x + y*y + z*z);
    double latitude = asin(z/radial);
    double longitude = atan2(y, x);
    double height = radial - m_radius;
    return Point3(longitude, latitude, height);
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

} // namespace Geometry
} // namespace Math

#endif // SPHERE_H
