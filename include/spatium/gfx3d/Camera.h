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
#include <spatium/geom3d/Point3.h>
#include <spatium/geom3d/Vector3.h>

#include <ostream>

namespace spatium {
namespace gfx3d {

/// \class Camera
/// \brief Camera object in a 3D scene
///
/// Vantage point from where an image can be rendered.
/// In its default position centred at the origin and aligned along the
/// negative z-axis.
class Camera : public SceneObject
{
public:

  /// Constructor
  Camera(double near, double far)
    : SceneObject()
    , m_near(near)
    , m_far(far)
  {
  }

  virtual ~Camera() = default;

  /// Get the distance to the near clipping plane in world space.
  ///
  /// \return Near clipping plane distance.
  double near() const
  {
    return m_near;
  }

  /// Get the distance to the far clipping plane in world space.
  ///
  /// \return Far clipping plane distance.
  double far() const
  {
    return m_far;
  }

  /// Set view direction towards target position.
  /// The resulting transformation matrix maps the reference point to the
  /// negative z axis and the eye point to the origin.
  ///
  /// \param[in] target Target position
  /// \param[in] up Up vector
  ///                May not be parallel with view direction vector
  void lookAt(const geom3d::Point3 &target, const geom3d::Vector3 &up)
  {
    // Compute vector from target to eye
    geom3d::Vector3 back = geom3d::Vector3(m_transform.position() - target).normalized();

    // Normalize and orthogonalize view up vector
    geom3d::Vector3 right = up.normalized().cross(back);
    geom3d::Vector3 upOrtho = back.cross(right);

    // Set rotation of transformation matrix based on view direction and view
    // up vector.
    geom3d::Matrix4x4 M = m_transform.matrix();

    // First column is right vector
    M(0,0) = right(0);
    M(1,0) = right(1);
    M(2,0) = right(2);

    // Second column is up vector
    M(0,1) = upOrtho(0);
    M(1,1) = upOrtho(1);
    M(2,1) = upOrtho(2);

    // Third column is back vector
    M(0,2) = back(0);
    M(1,2) = back(1);
    M(2,2) = back(2);

    m_transform.setMatrix(M);
  }

  /// Set camera position and set view direction towards target position.
  /// The resulting transformation matrix maps the reference point to the
  /// negative z axis and the eye point to the origin.
  ///
  /// \param[in] eye Camera/eye position
  /// \param[in] target Target position
  /// \param[in] up Up vector
  ///                May not be parallel with vector from eye to target
  void lookAt(const geom3d::Point3 &eye, const geom3d::Point3 &target,
              const geom3d::Vector3 &up)
  {
    m_transform.setPosition (eye);
    lookAt(target, up);
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Camera &camera)
  {
    os << "Camera";
    return os;
  }

protected:
  double m_near;
  double m_far;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_CAMERA_H
