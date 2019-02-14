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

#ifndef SPATIUMLIB_GFX3D_LIGHT_H
#define SPATIUMLIB_GFX3D_LIGHT_H

#include "SceneObject.h"

#include <array>

namespace spatium {
namespace gfx3d {

/// \class Light
/// \brief Light scene object
///
/// A Light emits light in all directions.
class Light : public SceneObject
{
public:

  /// Constrcutor
  ///
  /// \param[in] strength Strength
  /// \param[in] color Color (RGB)
  Light(double strength = 10, std::array<unsigned char, 3> color = {255, 255, 255})
    : m_strength(strength)
    , m_color(color)
  {
  }

  ///\todo: Rule of 5

  ///\todo Write to ostream

protected:
  double m_strength;
  std::array<unsigned char, 3> m_color;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_LIGHT_H
