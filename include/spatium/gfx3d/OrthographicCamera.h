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

#ifndef SPATIUMLIB_GFX3D_ORTHOGRAPHICCAMERA_H
#define SPATIUMLIB_GFX3D_ORTHOGRAPHICCAMERA_H

#include "Camera.h"

#include <ostream>

namespace spatium {
namespace gfx3d {

/// \class OrthographicCamera
/// \brief Camera with orthographic projection
class OrthographicCamera : public Camera
{
public:

  /// Constructor
  ///
  /// \param[in] aspectRatio Aspect ratio (width/height)
  /// \param[in] size Orthographic size of image plane
  OrthographicCamera(double aspectRatio, double size=1)
    : m_aspectRatio(aspectRatio)
    , m_size(size)
  {

  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const OrthographicCamera &camera)
  {
    os << "Orthographic camera";
    return os;
  }

protected:
  double m_aspectRatio;
  double m_size;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_ORTHOGRAPHICCAMERA_H
