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

#include <ostream>

namespace spatium {
namespace gfx3d {

/// \class Camera
/// \brief Camera scene object
///
/// Vantage point from where an image can be rendered.
class Camera : public SceneObject
{
public:

  /// Make camera look in the direction of target.
  ///
  /// \param[in] target Target position
  /// \param[in] up Up vector
  void lookAt(const geom3d::Point3 &target, const geom3d::Vector3 &up)
  {

  }

  /// Set camera position and make make camera look in direction of target.
  ///
  /// \param[in] position Camera position
  /// \param[in] target Target position
  /// \param[in] up Up vector
  void lookAt(const geom3d::Point3 &position, const geom3d::Point3 &target,
              const geom3d::Vector3 &up)
  {

  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Camera &camera)
  {
    os << "Camera";
    return os;
  }

protected:

private:
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_CAMERA_H
