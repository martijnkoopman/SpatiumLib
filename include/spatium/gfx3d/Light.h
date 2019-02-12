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

#include <array>

namespace spatium {
namespace gfx3d {

/// \class Light
class Light
{
public:

  /// Constrcutor
  ///
  /// \param[in] strength Strength
  /// \param[in] color Color (RGB)
  Light(double strength, std::array<unsigned char, 3> color = {255, 255, 255})
  : m_strength(strength)
  , m_color(color)
  {
  }


  // TODO: Rule of 5

private:
  double strength;
  std::array<unsigned char, 3> m_color;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_LIGHT_H