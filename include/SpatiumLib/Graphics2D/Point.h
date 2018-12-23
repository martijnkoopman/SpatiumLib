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

#ifndef SPATIUMLIB_GRAPHICS_POINT_H
#define SPATIUMLIB_GRAPHICS_POINT_H

#include <initializer_list>
#include <iostream>

namespace Graphics2D {

/// \class Point
class Point
{
public:

  /// Constructor
  ///
  /// \param[in] start Start point in pixel coordinates
  /// \param[in] end End point in pixel coordinates
  Point(int x, int y)
  : m_x(x)
  , m_y(y)
  {
  }

  /// Constructor
  ///
  /// \param[in] array Initializer list
  Point(std::initializer_list<int> array)
  : m_x(0)
  , m_y(0)
  {
    if (array.size() > 1)
    {
      auto it = array.begin();
      m_x = *it;
      m_y = *(++it);
    }
  }

  /// Destructor
  virtual ~Point() = default;

  /// Get X coordinate.
  int x() const
  {
    return m_x;
  }

  /// Set X coordinate.
  void setX(int x)
  {
    m_x = x;
  }

  /// Get Y coordinate.
  int y() const
  {
    return m_y;
  }

  /// Set Y coordinate.
  void setY(int y)
  {
    m_y = y;
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Point &point)
  {
    os << "Point " << point.m_x << ", " << point.m_y << std::endl;
    return os;
  }

protected:
  /// X coordinate.
  int m_x;

  /// Y coordinate.
  int m_y;
};

} // namespace Graphics2D

#endif // SPATIUMLIB_GRAPHICS_POINT_H
