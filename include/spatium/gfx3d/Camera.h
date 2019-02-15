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

#include <spatium/geom3d/Point3.h>
#include <spatium/geom3d/Vector3.h>

#include <ostream>

namespace spatium {
namespace gfx3d {

/// \class Camera
/// \brief Camera scene object
///
/// Vantage point from where an image can be rendered.
class Camera
{
public:

  Camera()
    : m_position({0,0,0})
    , m_viewDirection({0,1,0})
    , m_viewUp({0,0,1})
  {
  }

  /// Make camera look in the direction of target.
  ///
  /// \param[in] target Target position
  /// \param[in] up Up vector
  void lookAt(const geom3d::Point3 &target, const geom3d::Vector3 &up)
  {
    setViewDirection(target - m_position);
    setViewUp(up);
  }

  /// Set camera position and make camera look in direction of target.
  ///
  /// \param[in] position Camera position
  /// \param[in] target Target position
  /// \param[in] up Up vector
  void lookAt(const geom3d::Point3 &position, const geom3d::Point3 &target,
              const geom3d::Vector3 &up)
  {
    setPosition(position);
    setViewDirection(target - m_position);
    setViewUp(up);
  }

  /// Set the position in world space (translation)
  ///
  /// \param[in] position Position
  void setPosition(const geom3d::Point3 &xyz)
  {
    m_position = xyz;
  }

  /// Get the position in world space (translation)
  ///
  /// \return Position
  geom3d::Point3 position() const
  {
    return m_position;
  }

  /// Set the view direction (view plane normal)
  /// This is the opposite of the direction of projection.
  ///
  /// \param[in] direction View direction
  void setViewDirection(const geom3d::Vector3 &direction)
  {
    m_viewDirection = direction.normalized();
  }

  /// Get the view direction (view plane normal)
  /// This is the opposite of the direction of projection.
  ///
  /// \return View direction
  geom3d::Point3 viewDirection() const
  {
    return m_viewDirection;
  }

  /// Set view up vector
  /// View up is directly orthogonalized with view direction. You should set
  /// view direction first.
  ///
  /// \param[in] direction View direction
  void setViewUp(const geom3d::Vector3 &viewUp)
  {
    m_viewUp = viewUp.normalized();
    orthogonalizeViewUp();
  }

  /// Get view up vector
  ///
  /// \return View up
  geom3d::Point3 viewUp() const
  {
    return m_viewUp;
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Camera &camera)
  {
    os << "Camera";
    return os;
  }

protected:

  /// Orthogonalize view up vector.
  /// Make view up perpendicular to view direction.
  void orthogonalizeViewUp()
  {
    geom3d::Vector3 viewRight = m_viewDirection.cross(m_viewUp);
    viewRight.normalize(); // Needed ??
    m_viewUp = viewRight.cross(m_viewDirection);
    m_viewUp.normalize(); // Needed ??
  }

  geom3d::Point3 m_position;
  geom3d::Vector3 m_viewDirection;
  geom3d::Vector3 m_viewUp;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_CAMERA_H
