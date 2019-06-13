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

#ifndef SPATIUMLIB_GFX3D_TRANSFORM_H
#define SPATIUMLIB_GFX3D_TRANSFORM_H

#include <spatium/geom3d/Point3.h>
#include <spatium/geom3d/Vector3.h>
#include <spatium/geom3d/Matrix4x4.h>
#include <spatium/Math.h> // PI

#include <array>

namespace spatium {
namespace gfx3d {

/// \class Transform
/// \brief Tranformation in 3D space.
///
/// Default transformation (identity).
///
/// 1 0 0 x
/// 0 1 0 y
/// 0 0 1 z
/// 0 0 0 1
///
/// 1st column = right vector
/// 2nd column = up vector
/// 3rd column = back vector
/// 4rd column = translation (position)
class Transform
{
public:
  Transform()
    : m_matrix()
  {}

  /// Get the vector pointing to the right (positive X axis)
  ///
  /// \return Right vector
  geom3d::Vector3 right() const
  {
    return geom3d::Vector3(m_matrix(0,0),
                           m_matrix(1,0),
                           m_matrix(2,0));
  }

  /// Get the vector pointing up (positive y axis)
  ///
  /// \return Up vector
  geom3d::Vector3 up() const
  {
    return geom3d::Vector3(m_matrix(0,1),
                           m_matrix(1,1),
                           m_matrix(2,1));
  }

  /// Get the vector pointing back (positive z axis)
  ///
  /// \return Back vector
  geom3d::Vector3 back() const
  {
    return geom3d::Vector3(m_matrix(0,2),
                           m_matrix(1,2),
                           m_matrix(2,2));
  }

  /// Get the position in world space (translation)
  ///
  /// \return Position
  geom3d::Point3 position() const
  {
    return geom3d::Point3(m_matrix(0,3),
                          m_matrix(1,3),
                          m_matrix(2,3));
  }

  /// Set the position in world space (translation)
  ///
  /// \param[in] position Position
  void setPosition(const geom3d::Point3 &xyz)
  {
    m_matrix(0,3) = xyz.x();
    m_matrix(1,3) = xyz.y();
    m_matrix(2,3) = xyz.z();
  }

  /// Translate in world space
  ///
  /// \param[in] xyz Translation on X, Y and Z axis
  void translate(const geom3d::Vector3 &xyz)
  {
    m_matrix(0,3) = m_matrix(0,3) + xyz.x();
    m_matrix(1,3) = m_matrix(1,3) + xyz.y();
    m_matrix(2,3) = m_matrix(2,3) + xyz.z();
  }

  /// Get the scale
  ///
  /// \return Scale on x, y and z axis
  geom3d::Vector3 scale() const
  {
    const geom3d::Matrix4x4 &M = m_matrix;
    double x = geom3d::Vector3(M(0,0), M(1,0), M(2,0)).length(); // 1st column
    double y = geom3d::Vector3(M(0,1), M(1,1), M(2,1)).length(); // 2nd column
    double z = geom3d::Vector3(M(0,2), M(1,2), M(2,2)).length(); // 3rd column
    return geom3d::Vector3(x,y,z);
  }

  /// Rotate (relative to self/object space)
  ///
  /// \param[in] euler Degrees around x, y and z axis
  void rotate(const geom3d::Vector3 &euler)
  {
    ///\todo This doesn't work... Use TRS?
    m_matrix = m_matrix * geom3d::Matrix4x4::rotation(euler.x(), euler.y(), euler.z());
  }

  /// Set the rotation in world space
  ///
  /// \param[in] euler Rotation in euler angles
  void setRotation(const geom3d::Vector3 &euler)
  {
    // Extract scale and translation from current matrix
    geom3d::Vector3 s = scale();
    geom3d::Point3 t = position();

    // Create translation, rotation and scale matrix
    geom3d::Matrix4x4 T = geom3d::Matrix4x4::translation(t.x(), t.y(), t.z());
    geom3d::Matrix4x4 R = geom3d::Matrix4x4::rotation(euler.x(), euler.y(), euler.z());
    geom3d::Matrix4x4 S = geom3d::Matrix4x4::scaling(s.x(), s.y(), s.z());

    // Constrcut matrix (scale first, then rotate, then translate)
    m_matrix = T * R * S;
  }

  /// Get the rotation in world space
  ///
  /// \return Rotation in euler angles
  geom3d::Vector3 rotation() const
  {
    ///\todo Check if should each column should be scaled first?

    // Extract euler angles from matrix
    double x, y, z;
    const geom3d::Matrix4x4 &M = m_matrix;
    if (M(2,0) != 1 && M(2,0) != -1) ///\todo Unsafe compare
    {
      y = -asin(M(2,0));
      x = atan2(M(2,1) / cos(y), M(2,2) / cos(y));
      z = atan2(M(1,0) / cos(y), M(0,0) / cos(y));

      // There is a second solution:
      //theta = spatium::PI - theta;
      //psi = atan2( M(2,1) / cos(theta), M(2,2) / cos(theta));
      //phi = atan2( M(1,0) / cos(theta), M(0,0) / cos(theta));
    }
    else
    {
      // There is an infinit amount of solutions
      // Z can have an arbitrary value
      z = 0;
      if (M(2,0) == -1) ///\todo Unsafe compare
      {
        y = spatium::PI / 2;
        x = z + atan2(M(0,1), M(0,2));
      }
      else
      {
        y = -spatium::PI / 2;
        x = -z + atan2(-M(0,1), -M(0,2));
      }
    }

    return geom3d::Vector3(x,y,z);
  }

  /// Set the transformation matrix
  ///
  /// \param[in] matrix Transformation matrix
  void setMatrix(const geom3d::Matrix4x4 &matrix)
  {
    m_matrix = matrix;
  }

  /// Get the transformation matrix
  ///
  /// \return Transformation matrix
  geom3d::Matrix4x4 matrix() const
  {
    return m_matrix;
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
    return matrix() * point;
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
    return matrix().inverse() * point;
  }

protected:
  /// Transformation matrix
  geom3d::Matrix4x4 m_matrix;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_TRANSFORM_H
