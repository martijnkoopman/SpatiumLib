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

#ifndef SPATIUMLIB_GFX3D_SCENEOBJECT_H
#define SPATIUMLIB_GFX3D_SCENEOBJECT_H

#include "Transform.h"

#include <array>

namespace spatium {
namespace gfx3d {

/// \class SceneObject
/// \brief Object in a 3D scene
///
/// A SceneObject is transformable in world space.
class SceneObject
{
public:
  SceneObject()
    : m_transform()
  {}

  /// Get the transformation
  ///
  /// \return transformation
  Transform &transform()
  {
    return m_transform;
  }

protected:
  Transform m_transform;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_SCENEOBJECT_H
