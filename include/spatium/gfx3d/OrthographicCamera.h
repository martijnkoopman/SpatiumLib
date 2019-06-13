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
  /// \param[in] near
  /// \param[in] far
  /// \param[in] size Orthographic size of image plane
  ///                 on Y axis, height of view.
  OrthographicCamera(double near, double far,
                     double size=10)
    : Camera(near, far)
    , m_size(size)
  {

  }

  ~OrthographicCamera() override = default;

  /// Get size of the viewing plane along the Y axis.
  ///
  /// \return Viewing plane size
  double size() const
  {
    return m_size;
  }

  /// Convert world point coordinates to view point coordinates.
  /// View coordinates (canonical coordinates) are in range [-1, 1]
  ///
  /// \param[in] point World point
  /// \return View point coordinates
//  geom3d::Point3 worldToViewPoint(const geom3d::Point3 &point) const override
//  {
//    // Convert point to camera space
//    geom3d::Point3 camPoint = m_transform.worldPointToObjectPoint(point);

//    // Compute orthographic projection matrix
//    geom3d::Matrix4x4 orthoMatrix = projectionMatrix();

//    // Project point from orthographic view volume to canonical view volume
//    return geom3d::Point3(orthoMatrix * camPoint);
//  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const OrthographicCamera &camera)
  {
    os << "Orthographic camera (size=" << camera.size() << ")";
    return os;
  }

protected:
  double m_size;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_ORTHOGRAPHICCAMERA_H
