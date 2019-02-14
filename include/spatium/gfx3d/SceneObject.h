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

#include <spatium/geom3d/Point3.h>
#include <spatium/geom3d/Vector3.h>
#include <spatium/geom3d/Matrix4x4.h>
#include <spatium/geom3d/Point3.h>

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
  {}

  // TODO: Rule of 5

  /// Set the position in world space
  ///
  /// \param[in] position Position
  void setPosition(const geom3d::Point3 &point)
  {
    m_transformation(0,3) = point.x();
    m_transformation(1,3) = point.y();
    m_transformation(2,3) = point.z();
  }

  /// Get the position in world space
  ///
  /// \return Position
  geom3d::Point3 position() const
  {
    return geom3d::Point3(m_transformation(0,3),
                          m_transformation(1,3),
                          m_transformation(2,3));
  }

  /// Rotate (relative to object space)
  ///
  /// \param[in] euler Degrees around x, y and z axis
  void rotate(const geom3d::Vector3 &euler)
  {

  }

  /// Set the rotation in world space
  ///
  /// \param[in] euler Rotation in euler angles
  void setRotation(const geom3d::Vector3 &euler)
  {
    //
  }

  /// Get the rotation in world space
  ///
  /// \return Rotation in euler angles
  geom3d::Vector3 rotation() const
  {
    return geom3d::Vector3(0,0,0);
  }

  /// Get the transformation matrix
  ///
  /// \return Transformation matrix
  geom3d::Matrix4x4 transformation() const
  {
    return m_transformation;
  }

  /// Convert 3D Cartesian point coordinates from world space to object space.
  /// World coordinates are defined with resect to the world's global
  /// cordinate system. (Origin = [0,0,0])
  /// Object coordinates are defined with respect to the object's local
  /// coordinate system.
  ///
  /// \param[in] point Point cordinates in world space
  /// \return Point coordinates in object space
  geom3d::Point3 worldPointToObjectPoint(const geom3d::Point3 &point) const
  {
    return m_transformation * point;
  }

  /// Convert 3D Cartesian point coordinates from object space to world space.
  /// Object coordinates are defined with respect to the object's local
  /// coordinate system.
  /// World coordinates are defined with resect to the world's global
  /// cordinate system. (Origin = [0,0,0])
  ///
  /// \param[in] point Point cordinates in object space
  /// \return Point coordinates in world space
  geom3d::Point3 objectPointToWorldPoint(const geom3d::Point3 &point) const
  {
    return m_transformation.inverse() * point;
  }

protected:
  geom3d::Matrix4x4 m_transformation;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_SCENEOBJECT_H
