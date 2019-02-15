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
    : m_position({0,0,0})
    , m_rotation({0,0,0})
    , m_scale({1,1,1})
  {}

  // TODO: Rule of 5

  /// Translate in world space
  ///
  /// \param[in] xyz Translation on X, Y and Z axis
  void translate(const geom3d::Vector3 &xyz)
  {
    m_position = m_position + xyz;
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

  /// Rotate (relative to object space)
  ///
  /// \param[in] euler Degrees around x, y and z axis
  void rotate(const geom3d::Vector3 &euler)
  {
    //m_transformation = m_transformation *
    //  geom3d::Matrix4x4::rotation(euler.x(), euler.y(), euler.z());
  }

  /// Set the rotation in world space
  ///
  /// \param[in] euler Rotation in euler angles
  void setRotation(const geom3d::Vector3 &euler)
  {
    m_rotation = euler;
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
  geom3d::Matrix4x4 transformationMatrix() const
  {
    return geom3d::Matrix4x4::translation(m_position.x(), m_position.y(), m_position.z()) *
    geom3d::Matrix4x4::rotation(m_rotation.x(), m_rotation.y(), m_rotation.z()) *
    geom3d::Matrix4x4::scaling(m_scale.x(), m_scale.y(), m_scale.z());
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
    return transformationMatrix() * point;
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
    return transformationMatrix().inverse() * point;
  }

protected:
  geom3d::Point3 m_position;
  geom3d::Vector3 m_rotation;
  geom3d::Vector3 m_scale;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_SCENEOBJECT_H
