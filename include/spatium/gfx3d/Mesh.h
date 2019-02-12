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

#ifndef SPATIUMLIB_GFX3D_MESH_H
#define SPATIUMLIB_GFX3D_MESH_H

#include <vector>
#include <array>

namespace spatium {
namespace gfx3d {

/// \class Mesh
class Mesh
{
public:
  Mesh(const std::vector<std::array<double, 3>> &vertices, const std::vector<std::array<int, 2>> &edges)
  : m_vertices(vertices)
  , m_edges(edges)
  {
    //
  }
  
  // TODO: Rule of 5

private:
  std::vector<std::array<double, 3>> m_vertices;
  std::vector<std::array<int, 2>> m_edges;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_MESH_H