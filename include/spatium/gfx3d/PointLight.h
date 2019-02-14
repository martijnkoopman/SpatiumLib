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
  PointLight(double strength, std::array<unsigned char, 3> color = {255, 255, 255})
    : Light(strength, color)
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
