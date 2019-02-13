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

#ifndef SPATIUMLIB_GFX3D_PERSPECTIVECAMERA_H
#define SPATIUMLIB_GFX3D_PERSPECTIVECAMERA_H

#include "Camera.h"

#include <ostream>

namespace spatium {
namespace gfx3d {

/// \class Camera
/// \brief Camera with perspective projection
class PerspectiveCamera : public Camera
{
public:


  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const PerspectiveCamera &camera)
  {
    os << "Perspective camera";
    return os;
  }

protected:

private:
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_PERSPECTIVECAMERA_H
