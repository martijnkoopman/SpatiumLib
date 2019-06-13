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
    , m_color({255, 255, 255})
  {}

  /// Get the boundaries of the object; axis aligned.
  /// Xmin, Xmax, Ymin, Ymax, Zmin, Zmax
  ///
  /// \return Boundaries
  std::array<double, 6> bounds() const
  {
    return m_bounds;
  }

  /// Set the color.
  ///
  /// Color is defined as RGB values with range 0 - 255.
  ///
  /// \param[in] col Color
  void setColor(const std::array<unsigned char, 3> color)
  {
    m_color = color;
  }

  /// Get the color.
  ///
  /// Color is defined as RGB values with range 0 - 255
  ///
  /// \return Color
  std::array<unsigned char, 3> color() const
  {
    return m_color;
  }

protected:
  virtual void updateBounds() = 0;

  std::array<double, 6> m_bounds; ///\TODO: use BoundingBox<double, 3> from namespace idx
  std::array<unsigned char, 3> m_color;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_RENDEROBJECT_H
