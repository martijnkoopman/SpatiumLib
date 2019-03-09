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

#ifndef SPATIUMLIB_GFX3D_DIRECTIONALLIGHT_H
#define SPATIUMLIB_GFX3D_DIRECTIONALLIGHT_H

#include "Light.h"
#include <spatium/geom3d/Vector3.h>

namespace spatium {
namespace gfx3d {

/// \class DirectionalLight
/// \brief Light source that emits light in one direction as parallel rays <> the position.
class DirectionalLight : public Light
{
public:

  /// Constrcutor
  ///
  /// \param[in] direction Direction of the light
  /// \param[in] strength Strength
  /// \param[in] color Color (RGB)
  DirectionalLight(double strength = 10,
                   std::array<unsigned char, 3> color = {255, 255, 255})
    : Light(strength, color)
    , m_direction({0,0,0})
  {
  }

  ///\todo Write to ostream

protected:
  geom3d::Vector3 m_direction;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_DIRECTIONALLIGHT_H
