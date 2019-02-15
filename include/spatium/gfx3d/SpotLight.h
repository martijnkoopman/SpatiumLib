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

#ifndef SPATIUMLIB_GFX3D_SPOTLIGHT_H
#define SPATIUMLIB_GFX3D_SPOTLIGHT_H

#include "Light.h"
#include <spatium/geom3d/Point3.h>
#include <spatium/geom3d/Vector3.h>

namespace spatium {
namespace gfx3d {

/// \class SpotLight
/// \brief Light source that emits a beam of light in one particular direction
///        from a fixed point in space.
class SpotLight : public Light
{
public:

  /// Constrcutor
  ///
  /// \param[in] position Position of the light source
  /// \param[in] direction Direction of the light
  /// \param[in] radius Radius of the light beam
  /// \param[in] strength Strength of the light
  /// \param[in] color Color (RGB)
  SpotLight(double radius, double strength = 10,
  std::array<unsigned char, 3> color = {255, 255, 255})
    : Light(strength, color)
    , m_radius(radius)
    , m_position({0,0,0})
    , m_direction({0,0,0})
  {
  }

  ///\todo: Rule of 5

  ///\todo Write to ostream

protected:
  double m_radius;
  geom3d::Point3 m_position;
  geom3d::Vector3 m_direction;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_SPOTLIGHT_H
