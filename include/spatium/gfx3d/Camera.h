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

#ifndef SPATIUMLIB_GFX3D_CAMERA_H
#define SPATIUMLIB_GFX3D_CAMERA_H

#include "SceneObject.h"

namespace spatium {
namespace gfx3d {

/// \class Camera
/// \brief Camera scene object
///
/// Vantage point from where an image can be rendered.
class Camera : public SceneObject
{
public:

protected:
  void updateBounds() override
  {
    m_bounds = {0};
  }

private:
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_CAMERA_H
