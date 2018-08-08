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

#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "Geometry.h"
#include "Point3.h"
#include "Matrix4x4.h"
#include "Sphere.h"

namespace Math {
namespace Geometry {

/// \brief Ellipsoid geometry
///
/// An ellipsoid is defined by a point (origin) and three radii; one for each
/// axis.
///
/// Parametric description = x^2 / a^2 + y^2 / b^2 + z^2 / c^2 = 1
///
/// The ellipsoid is implemented by a sphere with an ellipsoidal
/// transformation applied to it.
class Ellipsoid : public Geometry
{
public:
  /// Constructor
  Ellipsoid(const Point3 &origin, double axisX, double axisY, double axisZ)
    : m_origin(origin)
    , m_axisX(axisX)
    , m_axisY(axisY)
    , m_axisZ(axisZ)
  {
    updateTransformation();
  }

  /// Constructor
  Ellipsoid(double axisX, double axisY, double axisZ)
    : m_origin(0,0,0)
    , m_axisX(axisX)
    , m_axisY(axisY)
    , m_axisZ(axisZ)
  {
    updateTransformation();
  }

  /// Copy constructor
  Ellipsoid(const Ellipsoid &other) = default;

  /// Assignment operator
  Ellipsoid& operator=(const Ellipsoid &other) = default;

  /// Destructor
  virtual ~Ellipsoid() = default;

  /// Set origin of ellipsoid.
  ///
  /// \param[in] origin Origin
  void origin(const Point3 &origin)
  {
    m_origin = origin;
    updateTransformation();
  }

  /// Get origin of ellipsoid.
  ///
  /// \return Origin
  Point3 origin() const
  {
    return m_origin;
  }

  /// Set the X axis length.
  ///
  /// \param[in] axisX X axis length
  void axisX(double axisX)
  {
    m_axisX = axisX;
    updateTransformation();
  }

  /// Get the X axis length.
  ///
  /// \return X axis length
  double axisX() const
  {
    return m_axisX;
  }

  /// Set the Y axis length.
  ///
  /// \param[in] axisY Y axis length
  void axisY(double axisY)
  {
    m_axisY = axisY;
    updateTransformation();
  }

  /// Get the Y axis length.
  ///
  /// \return Y axis length
  double axisY() const
  {
    return m_axisY;
  }

  /// Set the Z axis length.
  ///
  /// \param[in] axisZ Z axis length
  void axisZ(double axisZ)
  {
    m_axisZ = axisZ;
    updateTransformation();
  }

  /// Get the Z axis length.
  ///
  /// \return Z axis length
  double axisZ() const
  {
    return m_axisZ;
  }

  /// Compute Euclidean distance to point.
  ///
  /// \param[in] point Point
  /// \return Distance to point
  double distanceTo(const Point3 &point) const override
  {
    // Project point on ellipsoid
    Point3 pointProjected = projectPoint(point);

    // Compute distance to projected point
    return pointProjected.distanceTo(point);
  }

  /// Project point onto ellipsoid.
  ///
  /// \param[in] point Point
  /// \return Projected point
  Point3 projectPoint(const Point3 &point) const override
  {
    // Transform point to sphere space
    Point3 transPoint = m_ellipsoidalTransformationInverse * point;

    // Project point on unit sphere
    Sphere sphere(Point3(0,0,0), 1);
    Point3 transProjection = sphere.projectPoint(transPoint);

    // Transform projected point to ellipsoid space
    return m_ellipsoidalTransformation * transProjection;
  }

  /// Intersect line with ellipsoid.
  ///
  /// \param[in] origin Origin of line
  /// \param[in] direction Direction of line
  /// \param[out] intersection Intersection point
  /// \return True if there is an intersection, otherwise false
  bool intersectLine(const Point3 &origin,
                     const Vector3 &direction,
                     Point3 &intersection) const override
  {
    // Transform line origin and direction to unit sphere space
    Point3 transOrigin = m_ellipsoidalTransformationInverse * origin;
    Vector3 transDirection = m_ellipsoidalTransformationInverse * direction;

    // Intersect line with unit sphere
    Sphere sphere(Point3(0,0,0), 1);
    Point3 transIntersection;
    if (sphere.intersectLine(transOrigin, transDirection, transIntersection))
    {
      // Transform intersection to ellipsoid space
      intersection = m_ellipsoidalTransformation * transIntersection;
      return true;
    }
    else
    {
      return false;
    }
  }

  /// Compute surface normal at given point.
  ///
  /// \param[in] point Point with X, Y & Z coordinates
  /// \return Surface normal
  Vector3 surfaceNormal(const Point3 &point) const
  {
    // Ellipsoid = x^2 / a^2 + y^2 / b^2 + z^2 / c^2 = 1
    // Normal = Derivative
    //        = (2x / a^2, 2y / b^2,  2z / c^2)
    //        = (x / a^2, y / b^2,  z / c^2)
    Vector3 normal(point.x() / (m_axisX*m_axisX),
                   point.y() / (m_axisY*m_axisY),
                   point.z() / (m_axisZ*m_axisZ));
    normal.normalize();
    return normal;
  }

  /// Compute point on horizon in a given direction.
  ///
  /// \param[in] point Point above surface (Cartesian)
  /// \param[in] direction Direction towards horizon as polar coordinate in
  ///                      radians. 0 = east, 1/2 pi = north, etc.
  /// \param[in] poleLimit Whether or not to limit the latitude at the
  ///            poles. It wil not exceed (shrink again) beyond the horizon
  ///            of the pole.
  Point3 pointOnHorizon(const Point3 &point, double direction, bool poleLimit = false)
  {
    // Convert direction to X and Y
    double directionX = cos(direction); // Direction longitudinal
    double directionY = sin(direction); // Direction latitudinal

    // Transform point to unit sphere space
    Point3 transPoint = m_ellipsoidalTransformationInverse * point;

    // Unit sphere
    Sphere sphere(1);

    // Project point on unit sphere
    Point3 pointOnSphere = sphere.projectPoint(transPoint);

    // Compute distance to horizon on unit sphere
    double horizonDistance =
        sphere.distanceToHorizon(
          pointOnSphere.distanceTo(transPoint));

    // Note: Convert distance to angular distance:
    //       angular = distance / radius.
    //       radius = 1
    //       angular = distance
    double angularDistance = horizonDistance;

    // Convert to spherical coordinates
    Point3 sphericalCoordinates =
        sphere.cartesianToSphericalCoordinates(pointOnSphere.x(),
                                               pointOnSphere.y(),
                                               pointOnSphere.z());

    // Limit Y (latitude) near the poles if requested
    double pointOnHorizonSphericalY =
        sphericalCoordinates.y() + directionY * angularDistance;
    if (poleLimit)
    {
      if (pointOnHorizonSphericalY > Math::PI/2)
      {
        pointOnHorizonSphericalY = Math::PI/2;
      }
      else if (pointOnHorizonSphericalY < -Math::PI/2)
      {
        pointOnHorizonSphericalY = -Math::PI/2;
      }
    }

    // Add angle towards direction
    Point3 pointOnHorizonSpherical(
          sphericalCoordinates.x() + directionX * angularDistance,
          pointOnHorizonSphericalY,
          sphericalCoordinates.z());

    // Convert spherical to cartesian coordinates
    Point3 pointOnHorizon =
        sphere.sphericalToCartesianCoordinates(pointOnHorizonSpherical.x(),
                                               pointOnHorizonSpherical.y(),
                                               pointOnHorizonSpherical.z());

    // Transform point on horizon to ellipsoid space
    return m_ellipsoidalTransformation * pointOnHorizon;
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Ellipsoid &ellipsoid)
  {
    os << "Ellipsoid\n";
    os << "Origin = " << ellipsoid.origin() << "\n";
    os << "X axis length = " << ellipsoid.axisX() << "\n";
    os << "Y axis length = " << ellipsoid.axisY() << "\n";
    os << "Z axis length = " << ellipsoid.axisZ() << "\n";
    return os;
  }

protected:

  /// Update the transformation parameters that transform a sphere into this
  /// ellipsoid. These parameters are internally used to represent the
  /// ellipsoid as a transformed sphere.
  void updateTransformation()
  {
    m_ellipsoidalTransformation =
        Matrix4x4::translation(m_origin.x(), m_origin.y(), m_origin.z()) *
        Matrix4x4::scaling(m_axisX, m_axisY, m_axisZ);

    m_ellipsoidalTransformationInverse = m_ellipsoidalTransformation.inverse();
  }

  Matrix4x4 m_ellipsoidalTransformation;
  Matrix4x4 m_ellipsoidalTransformationInverse;

  Point3 m_origin;
  double m_axisX;
  double m_axisY;
  double m_axisZ;
};

} // namespace Geometry
} // namespace Math

#endif // ELLIPSOID_H
