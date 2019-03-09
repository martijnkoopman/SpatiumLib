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

#ifndef SPATIUMLIB_GFX3D_RENDEROBJECT_H
#define SPATIUMLIB_GFX3D_RENDEROBJECT_H

#include "SceneObject.h"

#include <array>

namespace spatium {
namespace gfx3d {

/// \class RenderObject
/// \brief Scene object that can be rendered.
///
/// A RenderObject has a certain size (bounds).
class RenderObject : public SceneObject
{
public:
  RenderObject()
    : SceneObject()
    , m_bounds({0})
  {}

  /// Get the boundaries of the object; axis aligned.
  /// Xmin, Xmax, Ymin, Ymax, Zmin, Zmax
  ///
  /// \return Boundaries
  std::array<double, 6> bounds() const
  {
    return m_bounds;
  }

protected:
  virtual void updateBounds() = 0;

  std::array<double, 6> m_bounds;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_RENDEROBJECT_H
