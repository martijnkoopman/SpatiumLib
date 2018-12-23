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

#ifndef SPATIUMLIB_GRAPHICS_LINE_H
#define SPATIUMLIB_GRAPHICS_LINE_H

#include "Point.h"

namespace Graphics2D {

/// \class Line
/// \brief 2D line in an image
class Line
{
public:
  /// Constructor
  ///
  /// \param[in] start Start point in pixel coordinates
  /// \param[in] end End point in pixel coordinates
  Line(const Point &start, const Point &end)
  : m_start(start)
  , m_end(end)
  {
  }

  /// Copy constructor.
  Line(const Line &other) = default;

  /// Destructor
  virtual ~Line() = default;

  /// Assignment operator
  Line& operator=(const Line &other) = default;

  /// Get start point.
  Point start() const
  {
    return m_start;
  }

  /// Set start point.
  void setStart(const Point &start)
  {
      m_start = start;
  }

  /// Get end point.
  Point end() const
  {
    return m_end;
  }

  /// Set end point.
  void setEnd(const Point &end)
  {
    m_end = end;
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Line &line)
  {
    os << "Line start = (" << line.m_start << ") end = (" << line.m_end << ")" << std::endl;
    return os;
  }

protected:
  /// Start point of line.
  Point m_start;

  /// End point of line.
  Point m_end;
};

} // namespace Graphics2D

#endif // SPATIUMLIB_GRAPHICS_LINE_H
