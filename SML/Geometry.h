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

#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace SML {

class Point3;
class Vector3;

/// \brief Abstract Geometry class
///
/// Every concrete implementation of this class has to implement the following
/// functions:
/// - distanceTo
/// - projectPoint
/// - intersectLine
class Geometry
{
public:
  Geometry() = default;
  virtual ~Geometry() = default;

  /// Calculate Euclidean distance to point.
  ///
  /// \param[in] point Point
  /// \return Distance to point
  virtual double distanceTo(const Point3 &point) const = 0;

  /// Project point onto geometry.
  ///
  /// \param[in] point
  /// \return Projected point
  virtual Point3 projectPoint(const Point3 &point) const = 0;

  /// Intersect line with geometry.
  ///
  /// \param[in] origin Origin of line
  /// \param[in] direction Direction of line
  /// \param[out] intersection Intersection point
  /// \return True if there is an intersection, otherwise false
  virtual bool intersectLine(const Point3 &origin,
                             const Vector3 &direction,
                             Point3 &intersection) const = 0;
};

} // namespace SML

#endif // GEOMETRY_H
