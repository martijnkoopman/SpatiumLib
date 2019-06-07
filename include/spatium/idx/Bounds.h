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

#ifndef SPATIUMLIB_IDX_BOUNDS_H
#define SPATIUMLIB_IDX_BOUNDS_H

#include <array> // std::array
#include <vector> // std::vector

namespace spatium {
namespace idx {

/// \class Bounds
/// \brief Boundaries in D-dimensional space.
template<typename T, size_t D>
class Bounds
{
public:
  /// Default constructor
  Bounds()
    : m_center()
  {
  }

  /// Constructor
  Bounds(const std::array<T,D> &center)
    : m_center(center)
  {
  }

  std::array<T,D> center() const
  {
    return m_center;
  }

protected:
  std::array<T,D> m_center;
};

/// \class BoundingBox
/// \brief Axis-aligned bounding box (AABB) in D-dimensional space.
template<typename T, size_t D>
class BoundingBox : public Bounds<T,D>
{
public:
  /// Default onstructor
  BoundingBox()
    : Bounds<T,D>()
    , m_radii()
  {
  }

  /// Constructor
  BoundingBox(const std::array<T,D> &center, const std::array<T,D> &radii)
    : Bounds<T,D>(center)
    , m_radii(radii)
  {
  }

  /// Build from points
  ///
  /// \param[in] points Points in D-dimensional space.
  static BoundingBox<T,D> fromPoints(const std::vector<std::array<T,D>> &points)
  {
    if (points.size() == 0)
    {
      return BoundingBox();
    }

    // Set initial bounds
    std::array<T, D> minVal, maxVal;
    for (size_t i = 0; i < D; i++)
    {
      minVal[i] = maxVal[i] = points[0][i];
    }

    // Iterate points and update bounds
    for (size_t i = 1; i < points.size(); i++)
    {
      std::array<T, D> point = points[i];

      // Iterate dimensions
      for (size_t i = 0; i < D; i++)
      {
        if (point[i] < minVal[i]) {
          minVal[i] = point[i];
        } else if(point[i] > maxVal[i]) {
          maxVal[i] = point[i];
        }
      }
    }

    return BoundingBox<T,D>::fromMinMax(minVal, maxVal);
  }

  static BoundingBox<T,D> fromMinMax(const std::array<T,D> &min, const std::array<T,D> &max)
  {
    // Compute center and radii
    std::array<T,D> centerVal, radiiVal;
    for (size_t i = 0; i < D; i++)
    {
      centerVal[i] = max[i] * 0.5 + min[i] * 0.5;
      radiiVal[i] = max[i] * 0.5 - min[i] * 0.5;
    }

    return BoundingBox(centerVal,radiiVal);
  }

  bool isInside(const std::array<T,D> &point) const
  {
    for(size_t i = 0; i < D; i++)
    {
      if (point[i] < this->m_center[i] - m_radii[i])
      {
        return false;
      }
      else if(point[i] > this->m_center[i] + m_radii[i])
      {
        return false;
      }
    }

    return true;
  }

  std::array<T,D> min() const
  {
    std::array<T,D> res;
    for (size_t i = 0; i < D; i++)
    {
      res[i] = this->m_center[i] - m_radii[i];
    }
    return res;
  }

  std::array<T,D> max() const
  {
    std::array<T,D> res;
    for (size_t i = 0; i < D; i++)
    {
      res[i] = this->m_center[i] + m_radii[i];
    }
    return res;
  }

  T diameter(size_t dimension) const
  {
    return m_radii[dimension] * 2;
  }

protected:
  std::array<T,D> m_radii;
};

/// \class OrientedBoundingBox
/// \brief Oriented bounding box in D-dimensional space.
template<typename T, size_t D>
class OrientedBoundingBox : BoundingBox<T,D>
{
public:

protected:
  std::array<T,D> m_orientation;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_BOUNDS_H
