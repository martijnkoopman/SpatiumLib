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

#ifndef SPATIUMLIB_GRAPHICS_BEZIERCURVE_H
#define SPATIUMLIB_GRAPHICS_BEZIERCURVE_H

#include <vector> // vector
#include <array> // array

namespace Graphics2D {

/// \class BezierCurve
class BezierCurve
{
public:
  BezierCurve(const std::vector<std::array<int, 2>> &controlPoints)
    : m_controlPoints(controlPoints)
  {
    /// \todo Implement
  }
private:
  std::vector<std::array<int, 2>> m_controlPoints;
};

} // namespace Graphics2D

#endif // SPATIUMLIB_GRAPHICS_BEZIERCURVE_H
