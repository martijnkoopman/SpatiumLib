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

namespace spatium {
namespace gfx3d {

/// \class SceneObject
class SceneObject
{
public:
  // TODO: Rule of 5

  /// Get the transformation matrix
  ///
  /// \return Transformation matrix
  geom3d::Matrix4x4 transform() const
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
