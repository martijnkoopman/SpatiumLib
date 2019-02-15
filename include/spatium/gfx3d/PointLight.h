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

#ifndef SPATIUMLIB_GFX3D_POINTLIGHT_H
#define SPATIUMLIB_GFX3D_POINTLIGHT_H

#include "Light.h"
#include <spatium/geom3d/Point3.h>

namespace spatium {
namespace gfx3d {

/// \class PointLight
/// \brief Light source that emits light in all directions from a fixed point in space.
class PointLight : public Light
{
public:

  /// Constrcutor
  ///
  /// \param[in] strength Strength
  /// \param[in] color Color (RGB)
  PointLight(double strength = 10, std::array<unsigned char, 3> color = {255, 255, 255})
    : Light(strength, color)
    , m_position({0,0,0})
  {
  }

  ///\todo: Rule of 5

  ///\todo Write to ostream

protected:
  geom3d::Point3 m_position;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_POINTLIGHT_H
