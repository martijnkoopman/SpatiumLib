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

#ifndef SPATIUMLIB_IDX_GEOMETRY_H
#define SPATIUMLIB_IDX_GEOMETRY_H

#include "Bounds.h"

namespace spatium {
namespace idx {

///\class Geometry
///\brief Geometry in D-dimensional space.
///
/// A geometry always has some kind of bounding volume. A single point is not
/// considered geometry.
template<typename T, size_t D>
class Geometry
{
  Bounds<T,D> bounds() const
  {
    return m_bounds;
  }

protected:
  Bounds<T, D> m_bounds;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_GEOMETRY_H
